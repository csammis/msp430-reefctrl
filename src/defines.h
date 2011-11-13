/*
 * defines.h
 * #defines for ease of access to data in the reefctrl project
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__

// This really needs to not be more than 0xFF the mode scheme falls apart
#define TIMER_RATE_HZ 4

// Bitmasks for the device state variable

#define STATE_IS_FEEDING    0x80;
#define STATE_SUMP_LOW      0x40;
#define STATE_RESV_LOW      0x20;
#define STATE_IS_CLEANING   0x10;
#define STATE_LIGHT_PHASE   0x0F;

#endif //__DEFINES_H__

//eof

