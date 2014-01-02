#include "../header/nRF24L01.h"
#include "../header/LS_defines.h"
#include "../header/LS_ATmega328.h"
#include "util/delay.h"
#include "../header/LS_usart.h"

uint8_t getReg( uint8_t reg ){
    _delay_us(10);                  //make sure last command was a while ago...
    clr_bit(SPI_PORT, SPI_SS  );    //CSN low - nRF starts to listen for command
    _delay_us(10);
     spi_transfer(R_REGISTER + reg);    //R_Register = set the nRF to reading mode, "reg" = this registry will be read back
    _delay_us(10);
     reg = spi_transfer(NOP);   //Send NOP (dummy byte) once to receive back the first byte in the reg register
    _delay_us(10);
    set_bit(SPI_PORT, SPI_SS); //CSN high - nRF goes back to doing nothing
    
    return reg; //return the read registry
}

