/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * peripherals.h
 *  Defines for the pin assignments of the reefctrl peripheral devices.
 *  This file can be referred to in order to determine uC wiring setup if necessary.
 */

// Convenience macros for toggling states on P1
#define P1_LO(x) P1OUT &= ~x
#define P1_HI(x) P1OUT |=  x

// Pinouts for the float switches in the tank and the resevoir
#define LVL_TANK_PIN BIT2
#define LVL_RESV_PIN BIT4

// Pinouts for controlling the PCD8544
#define LCD_SCE_PIN  BIT0
#define LCD_DC_PIN   BIT1
#define LCD_LED_PIN  BIT3
#define LCD_RST_PIN  BIT4
#define LCD_SCLK_PIN BIT5
#define LCD_DATA_PIN BIT6

// Pinout for the relay to drive the topoff pump
#define RELAY_PIN BIT7

inline void start_pump()
{
    P1_HI(RELAY_PIN);
}

inline void stop_pump()
{
    P1_LO(RELAY_PIN);
}

//eof

