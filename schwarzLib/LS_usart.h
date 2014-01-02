/* -----------------------------------------------------------------------------
 * File:			LS_usart.h
 * Module:			USART Controller Interface
 * Author:			Leandro Schwarz
 * Version:			1.1
 * Last edition:	08/02/2013
 * -------------------------------------------------------------------------- */

#ifndef __LS_USART_H
#define __LS_USART_H 11

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "LS_defines.h"
#if __LS_DEFINES_H < 90
#error Wrong definition file (LS_defines.h).
#endif
#include <stdio.h>
#include <avr/interrupt.h>

// -----------------------------------------------------------------------------
// New data type definition ----------------------------------------------------

typedef struct usartControl_t {
    uint8 mode : 2;
    uint8 polarity : 1;
    uint8 frameError : 1;
    uint8 bufferOverflowError : 1;
    uint8 parityError : 1;
    uint8 transmitterEnabled : 1;
    uint8 receiverEnabled : 1;
    uint8 transmitterInterruptEnabled : 1;
    uint8 receiverInterruptEnabled : 1;
    uint8 bufferEmptyInterruptEnabled : 1;
    uint8 dataBits : 3;
    uint8 parity : 2;
    uint16 ubrr : 12;
    uint8 stopBits : 1;
    uint8 receiverBufferEnable : 1;
    uint8 unusedBits : 2;
} usartControl_t;

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

extern FILE usartStream;
extern usartControl_t usartControl;
extern uint8 usartReceiverBuffer[USART_RECEIVER_BUFFER_SIZE];
extern uint8 usartReceiverBufferNextRead;
extern uint8 usartReceiverBufferNextWrite;
extern uint8 usartReceiverBufferLength;

// -----------------------------------------------------------------------------
// Code substitution definitions -----------------------------------------------

#define USART_RECEIVER_BUFFER_FUNCTION_HANDLER			ISR(USART_RX_vect){usartAddDataToReceiverBuffer(usartReceive());return;}

// -----------------------------------------------------------------------------
// Macrofunction definitions ---------------------------------------------------

#define USART_STDIO()									stdin = stdout = stderr = &usartStream
#define USART_IS_RECEPTION_COMPLETE()					tst_bit(UCSR0A,RXC0)
#define USART_IS_TRANSMISSION_COMPLETE()				tst_bit(UCSR0A,TXC0)
#define USART_IS_TRANSMITTER_BUFFER_EMPTY()				tst_bit(UCSR0A,UDRE0)
#define USART_RECEPTION_COMPLETE_INTERRUPT_ENABLE()		do{set_bit(UCSR0B,RXCIE0);usartControl.receiverInterruptEnabled = 1;}while(0)
#define USART_RECEPTION_COMPLETE_INTERRUPT_DISABLE()	do{clr_bit(UCSR0B,RXCIE0);usartControl.receiverInterruptEnabled = 0;}while(0)
#define USART_TRANSMISSION_COMPLETE_INTERRUPT_ENABLE()	do{set_bit(UCSR0B,TXCIE0);usartControl.transmitterInterruptEnabled = 1;}while(0)
#define USART_TRANSMISSION_COMPLETE_INTERRUPT_DISABLE()	do{clr_bit(UCSR0B,TXCIE0);usartControl.transmitterInterruptEnabled = 0;}while(0)
#define USART_BUFFER_EMPTY_INTERRUPT_ENABLE()			do{set_bit(UCSR0B,UDRIE0);usartControl.bufferEmptyInterruptEnabled = 1;}while(0)
#define USART_BUFFER_EMPTY_INTERRUPT_DISABLE()			do{clr_bit(UCSR0B,UDRIE0);usartControl.bufferEmptyInterruptEnabled = 0;}while(0)
#define USART_RECEIVER_ENABLE()							do{set_bit(UCSR0B,RXEN0);usartControl.receiverEnabled = 1;}while(0)
#define USART_RECEIVER_DISABLE()						do{clr_bit(UCSR0B,RXEN0);usartControl.receiverEnabled = 0;}while(0)
#define USART_TRANSMITTER_ENABLE()						do{set_bit(UCSR0B,TXEN0);usartControl.transmitterEnabled = 1;}while(0)
#define USART_TRANSMITTER_DISABLE()						do{clr_bit(UCSR0B,TXEN0);usartControl.transmitterEnabled = 0;}while(0)
#define USART_USART_5_DATA_BITS()						do{clr_bit(UCSR0B,UCSZ02);clr_bit(UCSR0C,UCSZ01);clr_bit(UCSR0C,UCSZ00);usartControl.dataBits = 0;}while(0)
#define USART_USART_6_DATA_BITS()						do{clr_bit(UCSR0B,UCSZ02);clr_bit(UCSR0C,UCSZ01);set_bit(UCSR0C,UCSZ00);usartControl.dataBits = 1;}while(0)
#define USART_USART_7_DATA_BITS()						do{clr_bit(UCSR0B,UCSZ02);set_bit(UCSR0C,UCSZ01);clr_bit(UCSR0C,UCSZ00);usartControl.dataBits = 2;}while(0)
#define USART_USART_8_DATA_BITS()						do{clr_bit(UCSR0B,UCSZ02);set_bit(UCSR0C,UCSZ01);set_bit(UCSR0C,UCSZ00);usartControl.dataBits = 3;}while(0)
#define USART_USART_9_DATA_BITS()						do{set_bit(UCSR0B,UCSZ02);set_bit(UCSR0C,UCSZ01);set_bit(UCSR0C,UCSZ00);usartControl.dataBits = 4;}while(0)
#define USART_MODE_ASYNCHRONOUS_NORMAL()				usartControl.mode = 0
#define USART_MODE_ASYNCRHONOUS_DOUBLE_SPEED()			usartControl.mode = 1
#define USART_MODE_SYNCHRONOUS_NORMAL()					usartControl.mode = 2
#define USART_MODE_SYNCHRONOUS_SPI()					usartControl.mode = 3
#define USART_SINGLE_STOP_BIT()							do{clr_bit(UCSR0C,USBS0);usartControl.stopBits = 0;}while(0)
#define USART_DOUBLE_STOP_BIT()							do{set_bit(UCSR0C,USBS0);usartControl.stopBits = 1;}while(0)
#define USART_PARITY_DISABLED()							do{clr_bit(UCSR0C,UPM01);clr_bit(UCSR0C,UPM00);usartControl.parity = 0;}while(0)
#define USART_PARITY_EVEN()								do{set_bit(UCSR0C,UPM01);clr_bit(UCSR0C,UPM00);usartControl.parity = 1;}while(0)
#define USART_PARITY_ODD()								do{set_bit(UCSR0C,UPM01);set_bit(UCSR0C,UPM00);usartControl.parity = 2;}while(0)
#define USART_XCK_RISING_EDGE()							usartControl.polarity = 0
#define USART_XCK_FALLING_EDGE()						usartControl.polarity = 1
#define USART_RECEIVER_BUFFER_ENABLE()					usartControl.receiverBufferEnable = 1
#define USART_RECEIVER_BUFFER_DISABLE()					usartControl.receiverBufferEnable = 0

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

uint8 usartCheckError(void);
void usartClearReceptionBuffer(void);
void usartInit(void);
uint8 usartReceive(void);
uint16 usartReceive9bits(void);
int16 usartReceiveStd(FILE * stream);
void usartTransmit(int8 data);
void usartTransmit9bits(uint16 data);
int16 usartTransmitStd(int8 data, FILE * stream);
uint8 usartIsReceiverBufferEmpty(void);
uint8 usartGetDataFromReceiverBuffer(void);
void usartAddDataToReceiverBuffer(uint8 data);

#endif
