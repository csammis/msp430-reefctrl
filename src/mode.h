/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * mode.h
 *  Methods and data for changing the input mode of the reefctrl
 *
 */

#ifndef __MODE_H__
#define __MODE_H__

#define MODE_HOME 0x0000
#define MODE_FEED 0x0100
#define MODE_TIME 0x0200

// init_mode
//  Initializes the device mode
void init_mode();

// switch_mode
//  Switches the active input mode to the next in sequence
void switch_mode();

// test_mode_switch
//  Determine whether enough timer cycles have elapsed to switch modes
void test_mode_switch();

// reset_mode_switch
//  Stop counting timer cycles to a mode switch
void reset_mode_switch();

// update_display_for_mode
//  Updates the LCD display to show the current mode
void update_display_for_mode();

// get_current_mode
//  Gets the value representing the current input mode
unsigned short get_current_mode();

#endif //__MODE_H__

//eof

