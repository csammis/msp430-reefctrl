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

#define Interrupt(x) void __attribute__((interrupt(x)))

// init_clocks
//  One-stop shop for MCU clock configuration
void init_clocks()
{
    // Hold WDT at first
    WDTCTL = (WDTPW + WDTHOLD);

    DCOCTL= 0;
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;
}

int main()
{
    // Initialization: clocks first, then peripherals, then start the timers last.
    init_clocks();
    init_lcd();
    
    init_mode();
    init_time();

    lcd_clear();
    lcd_write_string(0, 0, "C");

    P1OUT ^= BIT3;

    __bis_SR_register(CPUOFF | GIE); // Switch to LPM0 and enable interrupts

    return 0;
}

// timerA_isr
//  Increment the clock one step when TimerA elapses
Interrupt(TIMERA0_VECTOR) timerA_isr()
{
    TACCTL0 &= ~CCIFG;
    time_tick();
}

//eof

