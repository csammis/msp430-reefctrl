/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 */

#include <msp430.h>
#include "mode.h"
#include "lcd.h"
#include "action.h"
#include "time.h"

// Define SOURCE_FROM_SMCLK if the MCU doesn't have a 32768Hz crystal for ACLK

//#define SOURCE_FROM_SMCLK

#define Interrupt(x) void __attribute__((interrupt(x)))

#define BUTTON1 BIT3
#define BUTTON2 BIT4

#define STATE_MOONLIGHTS 0x0001
#define STATE_MAINLIGHTS 0x0002
#define STATE_FUGELIGHTS 0x0004

#define STATE_MAINPUMPS 0x0010
#define STATE_SKIMPUMPS 0x0020
#define STATE_POWRHEADS 0x0040

// init_clocks
//  One-stop shop for MCU clock configuration
void init_clocks()
{
    // Hold WDT at first
    WDTCTL = (WDTPW + WDTHOLD);

    // SMCLK: DC0 (1MHz) / 8 = 125KHz
    DCOCTL= 0;
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;
    BCSCTL2 |= DIVS_3; //SMCLK = DCO / 8 = 125KHz
}

int main()
{
    // Initialization: clocks first, then peripherals, then start the timers last.
    init_clocks();

    init_lcd();
    init_mode();
    init_time();

    // debugging the timer functions
    P1DIR |= BIT0 + BIT6;
    P1OUT |= BIT0 + BIT6;

#ifdef SOURCE_FROM_SMCLK
    // This will set the timerA interrupt to go every 1.953125Hz
    TACCR0 = 0xFFFF;
    TACTL = TASSEL_2 | MC_1;
    TACCTL0 = CCIE;
#else
    // TimerA functions as a RTC sourced from ACLK
    BCSCTL1 &= XTS;
    BCSCTL3 |= LFXT1S_0 | XCAP_3;

    TACCR0 = 0x7FFF;
    TACTL = TASSEL_1 | MC_1;
    TACCTL0 = CCIE;
#endif
    
    // WDT functions as a sensor poll at SMCLK / 8192 = 66ms
    WDTCTL = (WDTPW + WDTTMSEL + WDTCNTCL + WDTIS1 + WDTIS0);
    IFG1 &= ~WDTIFG;    // Clear the WDT interrupt flag
    IE1 |= WDTIE;       // Enable WDT interrupts

    __bis_SR_register(CPUOFF | GIE); // Switch to LPM0 and enable interrupts

    return 0;
}

// wdt_isr
//  Poll the sensors and update state accordingly
Interrupt(WDT_VECTOR) wdt_isr()
{
    P1OUT ^= BIT6;
}

// timerA_isr
//  Increment the clock one step when TimerA elapses
Interrupt(TIMERA0_VECTOR) timerA_isr()
{
    TACCTL0 &= ~CCIFG;
    time_tick();
}

//eof

