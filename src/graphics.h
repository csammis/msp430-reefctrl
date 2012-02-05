/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * graphics.h
 *  Methods for drawing various reef-related graphics to the attached LCD
 */

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

// graphics_draw_line
//  Draw a vertical line on the LCD at the specified column
void graphics_draw_line(unsigned char x);

// graphics_start_drip_animation
//  Begin the drip animation at the specified column
void graphics_start_drip_animation(unsigned char x);

// graphics_step_drip_animation
//  Draw the next frame of the drip animation
void graphics_step_drip_animation();

// graphics_stop_drip_animation
//  Erase and reset the drip animation
void graphics_stop_drip_animation();

// graphics_write_string
//  Write a string to the specified coordinates on the LCD
void graphics_write_string(unsigned char x, unsigned char y, const char* pStr);

#endif //__GRAPHICS_H__

 //eof

