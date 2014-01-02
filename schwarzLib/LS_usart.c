/* -----------------------------------------------------------------------------
 * File:			LS_usart.c
 * Module:			USART Controller Interface
 * Author:			Leandro Schwarz
 * Version:			1.1
 * Last edition:	08/02/2013
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "../header/LS_usart.h"

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

usartControl_t usartControl;
FILE usartStream = FDEV_SETUP_STREAM(usartTransmitStd, usartReceiveStd, _FDEV_SETUP_RW);
uint8 usartReceiverBuffer[USART_RECEIVER_BUFFER_SIZE];
uint8 usartReceiverBufferNextRead;	// Pointer to the next read location
uint8 usartReceiverBufferNextWrite;	// Pointer to the next write location
uint8 usartReceiverBufferLength;	// Buffer length

/* -----------------------------------------------------------------------------
 * Configures the USART controller
 * -------------------------------------------------------------------------- */

void usartInit(void)
{
	// Clear errors
	UCSR0A &= 0xE3;
	usartControl.frameError = 0;
	usartControl.bufferOverflowError = 0;
	usartControl.parityError = 0;

	// USART configuration
	switch(usartControl.mode){
	case 0:
		clr_bit(UCSR0A,U2X0);			// Normal speed
		clr_bit(UCSR0C,UCPOL0);			// Write zero in asynchronous mode
		clr_bit(UCSR0C,UMSEL01);		// Asynchronous mode
		clr_bit(UCSR0C,UMSEL00);		// Asynchronous mode
		usartControl.ubrr = (F_CPU / 16 / USART_BAUD_RATE) - 1;
		break;
	case 1:
		set_bit(UCSR0A,U2X0);			// Double speed
		clr_bit(UCSR0C,UCPOL0);			// Write zero in asynchronous mode
		clr_bit(UCSR0C,UMSEL01);		// Asynchronous mode
		clr_bit(UCSR0C,UMSEL00);		// Asynchronous mode
		usartControl.ubrr = (F_CPU / 8 / USART_BAUD_RATE) - 1;
		break;
	case 2:
		clr_bit(UCSR0A,U2X0);			// Write zero in synchronous mode
		if(usartControl.polarity)
			set_bit(UCSR0C,UCPOL0);		// XCK rising edge
		else
			clr_bit(UCSR0C,UCPOL0);		// XCK falling edge
		clr_bit(UCSR0C,UMSEL01);		// Synchronous mode
		set_bit(UCSR0C,UMSEL00);		// Synchronous mode
		break;
	case 3:
		clr_bit(UCSR0A,U2X0);			// Write zero in synchronous mode
		if(usartControl.polarity)
			set_bit(UCSR0C,UCPOL0);		// XCK rising edge
		else
			clr_bit(UCSR0C,UCPOL0);		// XCK falling edge
		set_bit(UCSR0C,UMSEL01);		// Master SPI mode
		set_bit(UCSR0C,UMSEL00);		// Master SPI mode
		usartControl.ubrr = (F_CPU / 2 / USART_BAUD_RATE) - 1;
		break;
	}

	// Sets the baud rate
	UBRR0H = (uint8)(usartControl.ubrr >> 8);
	UBRR0L = (uint8)usartControl.ubrr;

	// Receiver buffer
	if(usartControl.receiverBufferEnable)
		USART_RECEPTION_COMPLETE_INTERRUPT_ENABLE();
	else
		USART_RECEPTION_COMPLETE_INTERRUPT_DISABLE();

	return;
}	

/* -----------------------------------------------------------------------------
 * Checks if an error occurred during transmission or reception
 * -------------------------------------------------------------------------- */

uint8 usartCheckError(void)
{
	usartControl.frameError = tst_bit(UCSR0A, FE0);
	usartControl.bufferOverflowError = tst_bit(UCSR0A, DOR0);
	usartControl.parityError = tst_bit(UCSR0A, UPE0);
	return (usartControl.parityError | usartControl.bufferOverflowError | usartControl.frameError);
}

/* -----------------------------------------------------------------------------
 * Transmits data in 5, 6, 7 or 8 bits modes using the USART controller
 * -------------------------------------------------------------------------- */

void usartTransmit(int8 data)
{
	while(!USART_IS_TRANSMITTER_BUFFER_EMPTY())
		;	// Waits until last transmission ends
	UDR0 = data;
	return;
}

/* -----------------------------------------------------------------------------
 * Transmits data in 9 bits mode using the USART controller
 * -------------------------------------------------------------------------- */

void usartTransmit9bits(uint16 data)
{
	uint8 aux;

	while(!USART_IS_TRANSMITTER_BUFFER_EMPTY())
		;	// Waits until last transmission ends
	aux = ((data & 0x100) >> 8);
	if(aux)
		set_bit(UCSR0B, TXB80);
	else
		clr_bit(UCSR0B, TXB80);
	UDR0 = (uint8)data;
	return;
}

/* -----------------------------------------------------------------------------
 * Transmits data in 5, 6, 7 or 8 bits modes using the USART controller and
 * standard output heandler
 * -------------------------------------------------------------------------- */

int16 usartTransmitStd(int8 data, FILE * stream)
{
	while(!USART_IS_TRANSMITTER_BUFFER_EMPTY())
		;	// Waits until last transmission ends
	UDR0 = data;
	return FALSE;
}

/* -----------------------------------------------------------------------------
 * Receives data in 5, 6, 7 or 8 bits modes using the USART controller
 * -------------------------------------------------------------------------- */

uint8 usartReceive(void)
{
	uint8 status;

	while(!USART_IS_RECEPTION_COMPLETE())
		;	// Waits until last reception ends
	status = UCSR0A;
	usartControl.frameError = tst_bit(status, FE0);
	usartControl.bufferOverflowError = tst_bit(status, DOR0);
	usartControl.parityError = tst_bit(status, UPE0);
	return UDR0;
}

/* -----------------------------------------------------------------------------
 * Receives data in 9 bits modes using the USART controller
 * -------------------------------------------------------------------------- */

uint16 usartReceive9bits(void)
{
	uint8 status;
	uint8 byteh;
	uint8 bytel;
	uint16 byte;

	while(!USART_IS_RECEPTION_COMPLETE());	// Waits until last reception ends
	status = UCSR0A;
	byteh = UCSR0B;
	bytel = UDR0;

	usartControl.frameError = tst_bit(status, FE0);
	usartControl.bufferOverflowError = tst_bit(status, DOR0);
	usartControl.parityError = tst_bit(status, UPE0);

	byte = (uint16)(byteh & 0x02) << 7;
	byte |= bytel;
	return  byte;
}

/* -----------------------------------------------------------------------------
 * Receives data in 5, 6, 7 or 8 bits modes using the USART controller and
 * standard input heandler
 * -------------------------------------------------------------------------- */

int16 usartReceiveStd(FILE * stream)
{
	while(!USART_IS_RECEPTION_COMPLETE())
		;	// Waits until last reception ends
	return (int16)UDR0;
}

/* -----------------------------------------------------------------------------
 * Clears the receptor data buffer
 * -------------------------------------------------------------------------- */

void usartClearReceptionBuffer(void)
{
	uint8 aux;
    (void) aux; //eliminar o warning referente a variavel nao utilizada
	while(USART_IS_RECEPTION_COMPLETE()) {
		aux = UDR0;
    }    
	return;
}

/* -----------------------------------------------------------------------------
 * Adds data to the reception buffer. The function has NO CONTROL of lost data.
 * -------------------------------------------------------------------------- */

void usartAddDataToReceiverBuffer(uint8 data)
{
	if(((usartReceiverBufferNextWrite + 1) % USART_RECEIVER_BUFFER_SIZE) != usartReceiverBufferNextRead){
		usartReceiverBuffer[usartReceiverBufferNextWrite] = data;
		usartReceiverBufferNextWrite = (usartReceiverBufferNextWrite + 1) % USART_RECEIVER_BUFFER_SIZE;
		usartReceiverBufferLength++;
	}
	return;
}

/* -----------------------------------------------------------------------------
 * Gets data from the reception buffer. If the buffer is empty, the last
 * retrieved data will be returned and the pointer will not be changed. The
 * usartIsReceiverBufferEmpty() function must be called to check if there is new
 * data in the buffer.
 * -------------------------------------------------------------------------- */

uint8 usartGetDataFromReceiverBuffer(void)
{
	uint8 data = usartReceiverBuffer[usartReceiverBufferNextRead];
	if(usartReceiverBufferLength > 0){
		usartReceiverBufferNextRead = (usartReceiverBufferNextRead + 1) % USART_RECEIVER_BUFFER_SIZE;
		usartReceiverBufferLength--;
	}
	return data;
}

/* -----------------------------------------------------------------------------
 * Verifies if there is new data in the receiver buffer. Must be called before
 * reading the buffer.
 * -------------------------------------------------------------------------- */

uint8 usartIsReceiverBufferEmpty(void)
{
	if(usartReceiverBufferLength == 0)
		return TRUE;
	return FALSE;
}
