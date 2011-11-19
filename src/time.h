/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * time.h
 *  Methods and data for maintaining time on the reefctrl
 *
 */

#ifndef __TIME_H__
#define __TIME_H__

// init_time
//  Initializes the clock data structures (to zeros)
void init_time();

// time_tick
//  Increments the clock by one second
void time_tick();

// time_set
//  Initialze the clock with a set of values, pretty much for debug purposes only
void time_set(char seconds, char minutes, char hours, char day);

#endif //__TIME_H__

//eof

