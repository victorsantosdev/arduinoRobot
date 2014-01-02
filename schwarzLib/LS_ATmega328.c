/* -----------------------------------------------------------------------------
 * File:			LS_ATmega328.c
 * Module:			ATmega328 basic interface
 * Author:			Leandro Schwarz
 * Version:			5.2
 * Last edition:	08/02/2013
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "LS_defines.h"
#include "LS_ATmega328.h"
//#include "LS_HD44780.h"
//#include "nRF24L01.h"
//#include "LS_usart.h"
//#include "fsm.h"

//file definitions

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

//defines da lib mirf do nRF24L01

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifndef boolean
typedef uint8_t boolean;
#endif

#ifndef byte
typedef uint8_t byte;
#endif

//#define debug

/* -----------------------------------------------------------------------------
 * Writes a byte in the specified address in the EEPROM
 * -------------------------------------------------------------------------- */

void eepromWrite(uint8 data, uint8 address)
{
    while (EECR & (1 << EEPE))
        ; // Wait for completion of previous write
    EEAR = address;
    EEDR = data;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    return;
}

/* -----------------------------------------------------------------------------
 * Reads a byte from the specified address in the EEPROM
 * -------------------------------------------------------------------------- */

uint8 eepromRead(uint16 address)
{
    while (EECR & (1 << EEPE))
        ; // Wait for completion of previous write
    EEAR = address;
    EECR |= (1 << EERE);
    return EEDR;
}

/* -----------------------------------------------------------------------------
 * Configures the SPI controller as master
 * -------------------------------------------------------------------------- */

//funcao alterada para se comportar como o acionamento da SPI da funcao exemplo do nRF24L01

void spiMasterInit(uint8 clockPrescaller)
{
    set_bit(SPI_DDR, SPI_MOSI);
    set_bit(SPI_DDR, SPI_SCK);
    clr_bit(SPI_DDR, SPI_MISO);
    set_bit(SPI_PORT, SPI_MISO);

    SPCR |= (1 << SPE) | (1 << MSTR) | (clockPrescaller & 0x03);

}

/* -----------------------------------------------------------------------------
 * Sends data to the SPI bus
 * -------------------------------------------------------------------------- */
//modificacao para o nRF24L01+

//era spiMasterTransmit

uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    // Wait for transmission complete
    return SPDR;
}

//Funcoes vindas do exemplo de funcionamento do nRF24L01

// Write data using SPI

void spi_write_data(uint8_t * dataout, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++) {
        spi_transfer(dataout[i]);
    }
}

// Read data using SPI

uint8_t spi_read_data(uint8_t * datain, uint8_t len)
{
    uint8_t i;

    /* todas as linhas comentadas sao usadas para debug*/

    //printf("DENTRO DO SPI\n");

    for (i = 0; i < len; i++) {
        datain[i] = spi_transfer(0x00);
        //datain[i] = i;                            
        //printf("data[%d]: %d\n", i, datain[i]);   
    }
    //_delay_ms(500);

    return 0;

}

/* -----------------------------------------------------------------------------
 * Configures the SPI controller as slave
 * -------------------------------------------------------------------------- */

void spiSlaveInit(void)
{
    clr_bit(SPI_DDR, SPI_MOSI);
    clr_bit(SPI_DDR, SPI_SCK);
    set_bit(SPI_DDR, SPI_MISO);
    SPCR = (1 << SPE);
    return;
}

/* -----------------------------------------------------------------------------
 * Receives data from the SPI bus
 * -------------------------------------------------------------------------- */

uint8 spiSlaveReceive(void)
{
    while (!(SPSR & (1 << SPIF)))
        ; // Wait for reception complete
    return SPDR;
}

adcConfiguration_t adcGetConfiguration(void)
{
    adcConfiguration_t config;

    config.reference = ADMUX >> 6;
    config.channel = ADMUX & 0x0F;
    config.leftAdjust = tst_bit(ADMUX, ADLAR);
    config.enable = tst_bit(ADCSRA, ADEN);
    config.autoTrigger = tst_bit(ADCSRA, ADATE);
    config.interruptEnable = tst_bit(ADCSRA, ADIE);
    config.prescaller = ADCSRA & 0x07;
    config.triggerSource = ADCSRB & 0x07;
    config.digitalDisabled = DIDR0 & 0x3F;
    config.analogComparator = tst_bit(ADCSRB, ACME);

    return config;
}

void adcLoadConfiguration(adcConfiguration_t config)
{
    ADMUX = (config.reference << 6) | (config.leftAdjust << 5) | config.channel;
    ADCSRA = (config.enable << 7) | (config.autoTrigger << 5) | (config.interruptEnable << 3) | config.prescaller;
    ADCSRB = (config.analogComparator << 6) | config.triggerSource;
    DIDR0 = config.digitalDisabled;
    return;
}

void adcStartConversion(void)
{
    set_bit(ADCSRA, ADSC);
    return;
}

void adcSelectChannel(uint8 channel)
{
    ADMUX = ((ADMUX & 0xF0) | channel);
    return;
}

void adcWaitConversionFinish(void)
{
    while (tst_bit(ADCSRA, ADSC))
        ; // Wait until conversion finishes
    return;
}

///* função de debug em lcd 16x2 */
//void lcd_debug(char * frase)
//{
//    LCD_CLEAR_SCREEN();
//    LCD_CURSOR_MOVE_FIRST_LINE();
//    printf(frase);
//    _delay_ms(25);
//
//}
