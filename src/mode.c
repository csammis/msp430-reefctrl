/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * mode.c
 *  Implementation of mode.h
 *
 */

#include "defines.h"
#include "mode.h"
#include "lcd.h"

// The upper byte of g_Mode contains the current mode selection,
// the lower byte contains the number of timer elapses recorded
// since the mode button was pressed (to switch modes)
unsigned short g_Mode;

void init_mode()
{
    g_Mode = 0x0000;
}

void switch_mode()
{
    // Test the upper byte of g_Mode
    unsigned short nCurrentMode = get_current_mode();
    switch (nCurrentMode)
    {
        case MODE_HOME:
            nCurrentMode = MODE_FEED;
            break;
        case MODE_FEED:
            nCurrentMode = MODE_TIME;
            break;
        case MODE_TIME:
        default:
            nCurrentMode = MODE_HOME;
            break;
    }

    // Clear and set the upper byte of g_Mode to the new mode
    g_Mode &= 0x00FF;
    g_Mode |= nCurrentMode;

    update_display_for_mode();
}

void update_display_for_mode()
{
    unsigned short nCurrentMode = get_current_mode();
    
    lcd_clear_row(0);
    switch (nCurrentMode)
    {
        case MODE_FEED:
            lcd_write_string(0, 0, "Feeding");
            break;
        case MODE_TIME:
            lcd_write_string(0, 0, "Set time");
            break;
        case MODE_HOME:
            lcd_write_string(0, 0, "reefctrl");
            break;
    }
}

void test_mode_switch()
{
    unsigned short nTimerCycles = g_Mode & 0x00FF;
    if (nTimerCycles == TIMER_RATE_HZ)
    {
        switch_mode();
        nTimerCycles = 0;
    }
    else
    {
        nTimerCycles++;
    }

    // Clear and set the lower byte of g_Mode to the new timer cycle count
    reset_mode_switch();
    g_Mode |= nTimerCycles;
}

void reset_mode_switch()
{
    g_Mode &= 0xFF00;
}

unsigned short get_current_mode()
{
    return g_Mode & 0xFF00;
}



//eof

