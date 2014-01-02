/* -----------------------------------------------------------------------------
 * File:			LS_HD44780.h
 * Module:			LCD HD44780 Controller Interface
 * Author:			Leandro Schwarz
 * Version:			1.0
 * Last edition:	10/09/2012
 * -------------------------------------------------------------------------- */

#ifndef __LS_HD44780_H
#define __LS_HD44780_H 10

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "LS_defines.h"
#if __LS_DEFINES_H < 89
#error Wrong definition file (LS_defines.h).
#endif
#include <stdio.h>

// -----------------------------------------------------------------------------
// New data type definition ----------------------------------------------------

typedef struct lcdControl_t {
    uint8 line : 2; // 0 to 3
    uint8 column : 6; // 0 to 39
    uint8 displayOn : 1; // 0 off, 1 on
    uint8 cursorOn : 1; // 0 off, 1 on
    uint8 cursorBlink : 1; // 0 off, 1 on
    uint8 moveDirection : 1; // 0 left, 1 right
    uint8 insert : 1; // 0 off, 1 on
    uint8 dataBits : 1; // 0 4-bits, 1 8-bits
    uint8 fontSize : 1; // 0 5x8, 1 5x10
    uint8 unusedBits : 1;
} lcdControl_t;

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

extern lcdControl_t lcdControl;
extern FILE lcdStream;

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

#ifdef LCD_8X1
#define LCD_LINES	1
#define LCD_COLUMNS	8
#endif
#ifdef LCD_8X2
#define LCD_LINES	2
#define LCD_COLUMNS	8
#endif
#ifdef LCD_12X2
#define LCD_LINES	2
#define LCD_COLUMNS	12
#endif
#ifdef LCD_16X1
#define LCD_LINES	1
#define LCD_COLUMNS	16
#endif
#ifdef LCD_16X2
#define LCD_LINES	2
#define LCD_COLUMNS	16
#endif
#ifdef LCD_16X4
#define LCD_LINES	4
#define LCD_COLUMNS	16
#endif
#ifdef LCD_20X1
#define LCD_LINES	1
#define LCD_COLUMNS	20
#endif
#ifdef LCD_20X2
#define LCD_LINES	2
#define LCD_COLUMNS	20
#endif
#ifdef LCD_20X4
#define LCD_LINES	4
#define LCD_COLUMNS	20
#endif
#ifdef LCD_24X2
#define LCD_LINES	2
#define LCD_COLUMNS	24
#endif
#ifdef LCD_40X2
#define LCD_LINES	2
#define LCD_COLUMNS	40
#endif
#ifdef LCD_40X4
#define LCD_LINES	4
#define LCD_COLUMNS	40
#endif

// -----------------------------------------------------------------------------
// Macrofunction definitions ---------------------------------------------------

#define LCD_STDIO()			stdin = stdout = stderr = &lcdStream
#define LCD_CLEAR_SCREEN()		do{lcdControl.line = 0;lcdControl.column = 0;lcdCommand(0x01);}while(0)
#define LCD_CURSOR_HOME()		do{lcdControl.column = 0;lcdCommand(0x02);}while(0)
#define LCD_LEFT_RIGHT()		do{lcdControl.moveDirection = 0;lcdCommand(0x04 | (lcdControl.insert));}while(0)
#define LCD_RIGHT_LEFT()		do{lcdControl.moveDirection = 1;lcdCommand(0x06 | (lcdControl.insert));}while(0)
#define LCD_CURSOR_OVERWRITE()		do{lcdControl.insert = 0;lcdCommand(0x04 | (lcdControl.moveDirection << 1));}while(0)
#define LCD_CURSOR_INSERT()		do{lcdControl.insert = 1;lcdCommand(0x05 | (lcdControl.moveDirection << 1));}while(0)
#define LCD_DISPLAY_ON()		do{lcdControl.displayOn = 1;lcdCommand(0x0C | (lcdControl.cursorOn << 1) | lcdControl.cursorBlink);}while(0)
#define LCD_DISPLAY_OFF()		do{lcdControl.displayOn = 0;lcdCommand(0x08 | (lcdControl.cursorOn << 1) | lcdControl.cursorBlink);}while(0)
#define LCD_CURSOR_ON()			do{lcdControl.cursorOn = 1;lcdCommand(0x0A | (lcdControl.displayOn << 2) | lcdControl.cursorBlink);}while(0)
#define LCD_CURSOR_OFF()		do{lcdControl.cursorOn = 0;lcdCommand(0x08 | (lcdControl.displayOn << 2) | lcdControl.cursorBlink);}while(0)
#define LCD_CURSOR_BLINK_ON()		do{lcdControl.cursorBlink = 1;lcdCommand(0x09 | (lcdControl.displayOn << 2) | (lcdControl.cursorOn << 1));}while(0)
#define LCD_CURSOR_BLINK_OFF()		do{lcdControl.cursorBlink = 0;lcdCommand(0x08 | (lcdControl.displayOn << 2) | (lcdControl.cursorOn << 1));}while(0)
#define LCD_DISPLAY_SHIFT_LEFT()	lcdCommand(0x18)
#define LCD_DISPLAY_SHIFT_RIGHT()	lcdCommand(0x1C)
#define LCD_CURSOR_MOVE_LEFT()		lcdCommand(0x10)
#define LCD_CURSOR_MOVE_RIGHT()		lcdCommand(0x14)
#define LCD_DDRAM_SET(address)		lcdCommand(0x80 | address)
#define LCD_CURSOR_MOVE_FIRST_LINE()	do{lcdControl.line = 0;lcdControl.column = 1;lcdCommand(0x80);}while(0)
#if LCD_LINES == 1
#define LCD_CURSOR_MOVE_NEXT_LINE()	do{lcdCommand(0x80);lcdControl.column = 0;while(0)
#elif LCD_LINES == 2
#define LCD_CURSOR_MOVE_NEXT_LINE()	do{if(lcdControl.line == 0){lcdControl.line = 1;lcdCommand(0xC0);}else{lcdControl.line = 0;lcdCommand(0x80);}lcdControl.column = 0;}while(0)
#else
#define LCD_CURSOR_MOVE_NEXT_LINE()	do{switch(lcdControl.line){case 0:lcdControl.line = 1;lcdCommand(0xC0);break;case 1:lcdControl.line = 2;lcdCommand(0x94);break;case 2:lcdControl.line = 3;lcdCommand(0xD4);break;case 3:lcdControl.line = 0;lcdCommand(0x80);break;}lcdControl.column = 0;}while(0)
#endif
#ifdef LCD_4BITS_MODE
#if LCD_LINES == 1
#ifdef LCD_5x8_FONT
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x20)
#else
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x24)
#endif
#else
#ifdef LCD_5x8_FONT
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x28)
#else
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x2C)
#endif
#endif
#else
#if LCD_LINES == 1
#ifdef LCD_5x8_FONT
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x30)
#else
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x34)
#endif
#else
#ifdef LCD_5x8_FONT
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x38)
#else
#define LCD_CONFIGURE_MODULE()	lcdCommand(0x3C)
#endif
#endif
#endif


#ifdef LCD_4_BITS_MODE
#define LCD_IO_CONFIGURE()	do{LCD_DATA_PORT &= ~(0x0F << LCD_DATA_D4);LCD_DATA_DDR |= (0x0F << LCD_DATA_D4);LCD_CONTROL_PORT &= ~((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));LCD_CONTROL_DDR |= ((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));}while(0)
#endif
#ifdef LCD_8_BITS_MODE
#define LCD_IO_CONFIGURE()	do{LCD_DATA_PORT = 0x00;LCD_DATA_DDR = 0xFF;LCD_CONTROL_PORT &= ~((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));LCD_CONTROL_DDR |= ((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));}while(0)
#endif

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

void lcdInit(void);
int16 lcdWriteStd(int8 c, FILE * stream);
void lcdWrite(int8 character);
void lcdCommand(int8 command);


#endif
