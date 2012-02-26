/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 */

#include <msp430.h>
#include "lcd.h"
#include "graphics.h"

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

    // Set up the screen
    graphics_draw_line(70);

    graphics_write_string(0, 0,  "Auto topoff");
    graphics_write_string(0, 1,  "~~~~~~~~~~~");
    graphics_write_string(0, 2,  "Status:");

    graphics_start_drip_animation(79);

    // TimerA functions as a RTC sourced from ACLK
    BCSCTL1 &= XTS;
    BCSCTL3 |= LFXT1S_0 | XCAP_3;

    TACCR0 = 0x3FFF; // every half-second
    TACTL = TASSEL_1 | MC_1;
    TACCTL0 = CCIE;

    //csnote the LCD will normally not have its backlight on
    P1OUT ^= BIT3;

    __bis_SR_register(CPUOFF | GIE); // Switch to LPM0 and enable interrupts

    return 0;
}

// timerA_isr
//  Increment the clock one step when TimerA elapses
Interrupt(TIMERA0_VECTOR) timerA_isr()
{
    TACCTL0 &= ~CCIFG;

    //csnote: the drip animation starts at col 79
    graphics_step_drip_animation();

    //csnote: status flashing is too odd looking at 0.5Hz, set TACCR0 to 0x7FFF for status messages
    //graphics_flash_status(STATUS_EMPTY);
}
//eof

