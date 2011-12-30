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

    // Draw a divider line on the screen
    unsigned char c;
    unsigned char d[] = { 0xFF };
    for (c = 0; c < 6; c++)
    {
        lcd_write_graphic(70, c, d, 1);
    }
    
    // TimerA functions as a RTC sourced from ACLK
    BCSCTL1 &= XTS;
    BCSCTL3 |= LFXT1S_0 | XCAP_3;

    TACCR0 = 0x3FFF;
    TACTL = TASSEL_1 | MC_1;
    TACCTL0 = CCIE;

    P1OUT ^= BIT3;

    __bis_SR_register(CPUOFF | GIE); // Switch to LPM0 and enable interrupts

    return 0;
}

unsigned char drip_x = 79;
unsigned char drip_y = 0;

// timerA_isr
//  Increment the clock one step when TimerA elapses
Interrupt(TIMERA0_VECTOR) timerA_isr()
{
    TACCTL0 &= ~CCIFG;

    switch (drip_y)
    {
    case 0:
        lcd_write_graphic(drip_x, drip_y, graphic_drip, GRAPHIC_DRIP_SIZE);
        break;
    case 1: case 2: case 3: case 4: case 5:
        lcd_clear_char_columns(drip_x, drip_y - 1, GRAPHIC_DRIP_SIZE);
        lcd_write_graphic(drip_x, drip_y, graphic_drip, GRAPHIC_DRIP_SIZE);
        break;
    case 6:
        lcd_clear_char_columns(drip_x, 5, GRAPHIC_DRIP_SIZE);
        lcd_write_graphic(drip_x, 5, graphic_splash, GRAPHIC_SPLASH_SIZE);
        break;
    case 7:
        lcd_clear_char_columns(drip_x, 5, GRAPHIC_SPLASH_SIZE);
        drip_y = -1;
        break;
    }

    drip_y++;
}
//eof

