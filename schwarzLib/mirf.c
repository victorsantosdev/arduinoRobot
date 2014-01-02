/*
    Copyright (c) 2007 Stefan Engelke <mbox@stefanengelke.de>

    Permission is hereby granted, free of charge, to any person 
    obtaining a copy of this software and associated documentation 
    files (the "Software"), to deal in the Software without 
    restriction, including without limitation the rights to use, copy, 
    modify, merge, publish, distribute, sublicense, and/or sell copies 
    of the Software, and to permit persons to whom the Software is 
    furnished to do so, subject to the following conditions:
	
    The above copyright notice and this permission notice shall be 
    included in all copies or substantial portions of the Software.
	
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
	
    $Id$
	
    -----
	
    Modified by Alex from Inside Gadgets (http://www.insidegadgets.com)
    Last Modified: 22/08/2012
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "../header/LS_ATmega328.h"
#include "../header/LS_defines.h"
#include "../header/LS_HD44780.h"
#include "../header/nRF24L01.h"
#include "../header/mirf.h"
#include "../header/LS_usart.h"

// Defines for setting the MiRF registers for transmitting or receiving mode
#define TX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) )
#define RX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) ) )

//#define debug

// Flag which denotes transmitting or receiving mode
volatile uint8_t PMODE;

// Initializes pins ans interrupt to communicate with the MiRF module
// Should be called in the early initializing phase at startup.

void mirf_init(void)
{
    // Define CSN and CE as Output and set them to default
    set_bit(DDRB, CSN);
    set_bit(DDRB, CE);
    mirf_CE_lo;
    mirf_CSN_hi;
}

// Sets the important registers in the MiRF module and powers the module
// in receiving mode

void mirf_config(void)
{
    // Set RF channel
    mirf_config_register(RF_CH, mirf_CH);

    // Set length of incoming payload 
    mirf_config_register(RX_PW_P0, mirf_PAYLOAD);

    // Set RADDR and TADDR
    // Set RADDR and TADDR as the transmit address since we also enable auto acknowledgement
    mirf_write_register(RX_ADDR_P0, TADDR, ADDR_LEN);
    mirf_write_register(TX_ADDR, TADDR, ADDR_LEN);

    // Enable RX_ADDR_P0 address matching since we also enable auto acknowledgement
    mirf_config_register(EN_RXADDR, 1 << ERX_P0);

    PMODE = TXMODE; // Start in transmitting mode
    TX_POWERUP; // Power up in transmitting mode
}

// Flush RX and TX FIFO

void mirf_flush_rx_tx(void)
{
    mirf_CSN_lo; // Pull down chip select
    spi_transfer(FLUSH_RX); // Flush RX
    mirf_CSN_hi; // Pull up chip select

    mirf_CSN_lo; // Pull down chip select
    spi_transfer(FLUSH_TX); // Write cmd to flush tx fifo
    mirf_CSN_hi; // Pull up chip select
}

// Read the status register

uint8_t mirf_status(void)
{
    mirf_CSN_lo; // Pull down chip select
    spi_transfer(R_REGISTER | (REGISTER_MASK & STATUS));
    uint8_t status = spi_transfer(NOP); // Read status register
    mirf_CSN_hi; // Pull up chip select
    return status;
}

// Checks if data is available for reading

uint8_t mirf_data_ready(void)
{
    mirf_CSN_lo; // Pull down chip select
    spi_transfer(R_REGISTER | (REGISTER_MASK & STATUS));
    uint8_t status = spi_transfer(NOP); // Read status register
    mirf_CSN_hi; // Pull up chip select
    return status & (1 << RX_DR);
}

// Checks if MAX_RT has been reached

uint8_t mirf_max_rt_reached(void)
{
    mirf_CSN_lo; // Pull down chip select
    spi_transfer(R_REGISTER | (REGISTER_MASK & STATUS));
    uint8_t status = spi_transfer(NOP); // Read status register
    mirf_CSN_hi; // Pull up chip select
    return status & (1 << MAX_RT);
}

// Reads mirf_PAYLOAD bytes into data array

void mirf_get_data(uint8_t *data)
{
    mirf_CSN_lo; // Pull down chip select
    spi_transfer(R_RX_PAYLOAD); // Send cmd to read rx payload
    spi_read_data(data, mirf_PAYLOAD); // Read payload
    mirf_CSN_hi; // Pull up chip select
    mirf_config_register(STATUS, (1 << RX_DR)); // Reset status register
}

// Write one byte into the MiRF register

void mirf_config_register(uint8_t reg, uint8_t value)
{
    mirf_CSN_lo;
    spi_transfer(W_REGISTER | (REGISTER_MASK & reg));
    spi_transfer(value);
    mirf_CSN_hi;
}

// Reads an array of bytes from the MiRF registers.

void mirf_read_register(uint8_t reg, uint8_t *value, uint8_t len)
{
    mirf_CSN_lo;
    spi_transfer(R_REGISTER | (REGISTER_MASK & reg));
    spi_read_data(value, len);
    mirf_CSN_hi;
}

// Writes an array of bytes into the MiRF register

void mirf_write_register(uint8_t reg, uint8_t *value, uint8_t len)
{
    mirf_CSN_lo;
    spi_transfer(W_REGISTER | (REGISTER_MASK & reg));
    spi_write_data(value, len);
    mirf_CSN_hi;
}

// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.

void mirf_send(uint8_t *value, uint8_t len)
{
    PMODE = TXMODE; // Set to transmitter mode
    TX_POWERUP; // Power up

    mirf_CSN_lo; // Pull down chip select
    spi_transfer(FLUSH_TX); // Write cmd to flush tx fifo
    mirf_CSN_hi; // Pull up chip select

    mirf_CSN_lo; // Pull down chip select
    spi_transfer(W_TX_PAYLOAD); // Write cmd to write payload
    spi_write_data(value, len); // Write payload
    mirf_CSN_hi; // Pull up chip select

    mirf_CE_hi; // Start transmission
    _delay_us(15);
    mirf_CE_lo;
}


// Receive data

uint8_t mirf_receive_data(uint8_t * buffer, uint8_t len)
{
    RX_POWERUP; // Power up to receiver mode
    mirf_CE_hi; // Start listening

    uint8_t waitcount = 0;
    while (!(mirf_status() & (1 << RX_DR))) { // Wait until data is ready to be read
        _delay_us(500);
        waitcount++;
        if (waitcount >= 100) { // If we haven't heard back in 50ms, exit
            mirf_CE_lo; // Stop listening
            return 0;
        }
    }
    mirf_CE_lo; // Stop listening

    mirf_CSN_lo; // Pull down chip select
    spi_transfer(R_RX_PAYLOAD); // Send cmd to read rx payload
    spi_read_data(buffer, len); // Read payload

 #ifdef debug
    uint8_t i;
    printf("DENTRO DO MIRF\n");
    for (i = 0; i < len; i++) {
        printf("data[%d]: %d\n", i, buffer[i]); //just for debug 
    }
    _delay_ms(500);
#endif
    
    mirf_CSN_hi; // Pull up chip select
    mirf_config_register(STATUS, (1 << RX_DR)); // Reset status register

    return 0;
}