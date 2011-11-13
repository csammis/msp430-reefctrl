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

#define BUTTON1 BIT3
#define BUTTON2 BIT4

#define STATE_MOONLIGHTS 0x0001
#define STATE_MAINLIGHTS 0x0002
#define STATE_FUGELIGHTS 0x0004

#define STATE_MAINPUMPS 0x0010
#define STATE_SKIMPUMPS 0x0020
#define STATE_POWRHEADS 0x0040


// State and methods to switch between reefctrl functions

void update_display_for_state()
{
    //TODO implement this

    // MODE_FEED && !is_feeding, display "Feed?"
    // MODE_FEED && is_feeding, display time remaining on feed

    // MODE_HOME display time and light state

    // MODE_TIME display time and "Set?"
}

void update_action()
{
    //TODO implement this
}

int main()
{
    init_lcd();
    init_mode();

    return 0;
}

void __attribute__((interrupt(PORT1_VECTOR))) port1_isr()
{
    if (P1IFG & BUTTON1)
    {
        switch_mode();
    }
}

void __attribute__((interrupt(TIMERA1_VECTOR))) timer_isr()
{
    if (P1IN & BUTTON2)
    {
        update_action();
    }
}

