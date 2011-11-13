/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * lcd.h
 *  Methods and data for manipulating an external LCD display
 *
 */

#ifndef __LCD_H__
#define __LCD_H__

// init_lcd
//  Initializes the connected LCD
void init_lcd();

// lcd_clear
//  Clear the entire LCD character array
void lcd_clear();

// lcd_clear_row
//  Clear the specified character row 
void lcd_clear_row(short y);

// lcd_write_string
//  Write the contents of a string to the specified x,y offsets on the screen
void lcd_write_string(short x, short y, const char* pStr);

#endif // __LCD_H__

//eof

