/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * peripherals.h
 *  Defines for the pin assignments of the reefctrl peripheral devices.
 *
 *  What is being used by what:
 *      P1.0: PCD8544, SCE pin
 *      P1.1: PCD8544, DC pin
 *      P1.2: Water level switch to GND
 *      P1.3: PCD8544, LED pin
 *      P1.4: PCD8544, RST pin (this needs to be replaced with an RC circuit)
 *      P1.5: USI, clock (to PCD8544 SCLK)
 *      P1.6: USI, output (to PCD8544 DATA)
 *      P1.7: Currently available
 */

// Convenience macros for toggling states on P1
#define P1_LO(x) P1OUT &= ~x
#define P1_HI(x) P1OUT |=  x

// Pinouts for the float switches in the tank and the resevoir
#define LVL_TANK_PIN BIT2

// Pinouts for controlling the PCD8544
#define LCD_SCE_PIN  BIT0
#define LCD_DC_PIN   BIT1
#define LCD_LED_PIN  BIT3
#define LCD_RST_PIN  BIT4
#define LCD_SCLK_PIN BIT5

//eof

