/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * lcd.c
 *  Implementation of lcd.h for a PCD8544 LCD controller
 *
 */

#include "lcd.h"
#include <msp430.h>

// The LCD should be connected to the MSP430 controller pins P1.x
#define LCD_SCE_PIN  BIT0
#define LCD_DC_PIN   BIT1
#define LCD_LED_PIN  BIT3
#define LCD_RST_PIN  BIT4
#define LCD_SCLK_PIN BIT5
#define LCD_DATA_PIN BIT6

#define LCD_WRITE_DATA 1
#define LCD_WRITE_COMMAND 0

// Convenience macros for P1 pin toggling
#define P1_LO(x) P1OUT &= ~x
#define P1_HI(x) P1OUT |=  x
#define LCD_PULSE_CLOCK P1_LO(LCD_SCLK_PIN); P1_HI(LCD_SCLK_PIN);


// PCD8544 constants courtesy of RobG at 43oh.com forums
#define PCD8544_POWERDOWN 0x04
#define PCD8544_ENTRYMODE 0x02
#define PCD8544_EXTENDEDINSTRUCTION 0x01

#define PCD8544_DISPLAYBLANK 0x0
#define PCD8544_DISPLAYNORMAL 0x4
#define PCD8544_DISPLAYALLON 0x1
#define PCD8544_DISPLAYINVERTED 0x5

// Normal instruction set
#define PCD8544_FUNCTIONSET 0x20
#define PCD8544_DISPLAYCONTROL 0x08
#define PCD8544_SETYADDR 0x40
#define PCD8544_SETXADDR 0x80
#define PCD8544_HPIXELS   84
#define PCD8544_VBANKS   6
#define PCD8544_MAXBYTES 504 // PCD8544_HPIXELS * PCD8544_VBANKS

// Extended instruction set
#define PCD8544_SETTEMP 0x04
#define PCD8544_SETBIAS 0x10
#define PCD8544_SETVOP 0x80

//transform
#define NONE 0x00
#define FLIP_H 0x01
#define FLIP_V 0x02
#define ROTATE 0x04 // 90 deg CW
#define ROTATE_90_CW ROTATE
#define ROTATE_90_CCW (FLIP_H | FLIP_V | ROTATE)
#define ROTATE_180 (FLIP_H | FLIP_V)

// lcd_write_data
//  Selects the LCD bus, writes data, waits for it to be written, and deselects the bus
void lcd_write_data(unsigned char mode, unsigned char data)
{
    if (mode == LCD_WRITE_DATA)
    {
        P1_HI(LCD_DC_PIN);
    }
    else
    {
        P1_LO(LCD_DC_PIN);
    }

    // Enable clock signals for programming
    P1_LO(LCD_SCE_PIN);
    
    unsigned char mask = 0x80;
    while (mask)
    {
        if (data & mask)
        {
            P1_HI(LCD_DATA_PIN);
        }
        else
        {
            P1_LO(LCD_DATA_PIN);
        }
        
        LCD_PULSE_CLOCK;
        mask >>= 1;
    }

    // Disable clock signals again
    P1_HI(LCD_SCE_PIN);
}

// lcd_set_address
//  Moves the current writing location to the specified coordinates
void lcd_set_address(unsigned char x, unsigned char y)
{
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_SETXADDR | x);
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_SETYADDR | y);
}

void init_lcd()
{
    P1DIR |= LCD_DC_PIN + LCD_SCE_PIN + LCD_SCLK_PIN + LCD_RST_PIN + LCD_LED_PIN + LCD_DATA_PIN;

    P1_LO(LCD_LED_PIN);

    P1_LO(LCD_SCE_PIN);

    // Send a reset to the LCD ('R)
    P1_HI(LCD_RST_PIN); P1_LO(LCD_RST_PIN); P1_HI(LCD_RST_PIN);

    LCD_PULSE_CLOCK;

    P1_HI(LCD_SCE_PIN);

    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_SETVOP | 0xBF);
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_SETTEMP | 0x02);
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_SETBIAS | 0x03);
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_FUNCTIONSET);
    lcd_write_data(LCD_WRITE_COMMAND, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);

    lcd_clear();
}

void lcd_clear()
{
    lcd_set_address(0, 0);
    int c = 0;
    while(c < PCD8544_MAXBYTES) {
        lcd_write_data(LCD_WRITE_DATA, 0);
        c++;
    }
    lcd_set_address(0, 0);
}

void lcd_clear_row(unsigned char y)
{
}

char drip_1[6] = {0x78, 0xFE, 0xFF, 0xFE, 0x78, 0x00};

void lcd_write_string(unsigned char x, unsigned char y, const char* pStr)
{
    lcd_set_address(x, y);
}

void lcd_write_graphic(unsigned char x, unsigned char y, const unsigned char graphic[], unsigned short size)
{
    lcd_set_address(x, y);

    unsigned short i;
    for (i = 0; i < size; i++)
    {
        lcd_write_data(LCD_WRITE_DATA, graphic[i]);
    }
}

void lcd_clear_char_columns(unsigned char x, unsigned char y, unsigned short number)
{
    lcd_set_address(x, y);
    unsigned short i;
    for (i = 0; i < number; i++)
    {
        lcd_write_data(LCD_WRITE_DATA, 0x00);
    }
}

//eof

