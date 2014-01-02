/* -----------------------------------------------------------------------------
 * File:			LS_HD44780.c
 * Module:			LCD HD44780 Controller Interface
 * Author:			Leandro Schwarz
 * Version:			1.0
 * Last edition:	10/09/2012
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "../header/LS_HD44780.h"

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

lcdControl_t lcdControl;
FILE lcdStream = FDEV_SETUP_STREAM(lcdWriteStd, NULL, _FDEV_SETUP_WRITE);

/* -----------------------------------------------------------------------------
 * Performs LCD module initialization.
 * -------------------------------------------------------------------------- */

void lcdInit(void)
{
    LCD_IO_CONFIGURE();
    LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | (0x03 << LCD_DATA_D4);
    _delay_us(1);
    set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(1);
    clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(45);
    _delay_ms(5);
    _delay_us(1);
    set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(1);
    clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(45);
    _delay_us(200);
    _delay_us(1);
    set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(1);
    clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(45);
    LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | (0x02 << LCD_DATA_D4);
    _delay_us(1);
    set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(1);
    clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
    _delay_us(45);
    lcdCommand(0x28);
    lcdCommand(0x08);
    LCD_CLEAR_SCREEN();
    LCD_DISPLAY_ON();
    LCD_CURSOR_MOVE_FIRST_LINE();
    return;
}

/* -----------------------------------------------------------------------------
 * Writes a character on the display using the standard output handler.
 * -------------------------------------------------------------------------- */

int16 lcdWriteStd(int8 character, FILE * stream)
{
    uint8 i = 2;

    if (character == '\n') {
        for (i = lcdControl.column; i < (LCD_COLUMNS); i++)
            lcdWrite(' ');
        LCD_CURSOR_MOVE_NEXT_LINE();
    } else {
        lcdControl.column++;
        LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | ((character >> 4) << LCD_DATA_D4);
        do {
            set_bit(LCD_CONTROL_PORT, LCD_CONTROL_RS);
            _delay_us(1);
            set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
            _delay_us(1);
            clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
            _delay_us(45);
            LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | ((character & 0x0F) << LCD_DATA_D4);
            i--;
        } while (i > 0);
    }
    return 0;
}

/* -----------------------------------------------------------------------------
 * Sends a command to the display module.
 * -------------------------------------------------------------------------- */

void lcdCommand(int8 command)
{
    uint8 i = 2;

    LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | ((command >> 4) << LCD_DATA_D4);
    do {
        clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_RS);
        _delay_us(1);
        set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
        _delay_us(1);
        clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
        _delay_us(45);
        if (command < 4)
            _delay_ms(2);
        LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | ((command & 0x0F) << LCD_DATA_D4);
        i--;
    } while (i > 0);
    return;
}

/* -----------------------------------------------------------------------------
 * Writes a character on the display.
 * -------------------------------------------------------------------------- */

void lcdWrite(int8 character)
{
    uint8 i = 2;

    if (character == '\n')
        LCD_CURSOR_MOVE_NEXT_LINE();
    else {
        LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | ((character >> 4) << LCD_DATA_D4);
        do {
            set_bit(LCD_CONTROL_PORT, LCD_CONTROL_RS);
            _delay_us(1);
            set_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
            _delay_us(1);
            clr_bit(LCD_CONTROL_PORT, LCD_CONTROL_E);
            _delay_us(45);
            LCD_DATA_PORT = (LCD_DATA_PORT & (~(0x0F << LCD_DATA_D4))) | ((character & 0x0F) << LCD_DATA_D4);
            i--;
        } while (i > 0);
    }
    return;
}
