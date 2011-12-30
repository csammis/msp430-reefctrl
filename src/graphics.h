/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * graphics.h
 *  Definitions for various reef-related graphics to display on an LCD
 */

 #define GRAPHIC_DRIP_SIZE 5
 const unsigned char graphic_drip[] = { 0x78, 0xFE, 0xFF, 0xFE, 0x78 };

 #define GRAPHIC_SPLASH_SIZE 5
 const unsigned char graphic_splash[] = {0xA0, 0x40, 0x80, 0x40, 0xA0 };

 //eof

