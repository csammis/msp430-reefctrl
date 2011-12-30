/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * time.c
 *  Implementation of time.h
 *
 */

#include "time.h"
#include <msp430.h>

unsigned char currtime[4];
unsigned char can_time_tick;

#define SECONDS 0
#define MINUTES 1
#define HOURS   2
#define DAYS    3

void init_time()
{
    can_time_tick = 1;

    currtime[SECONDS] = 0;
    currtime[MINUTES] = 0;
    currtime[HOURS]   = 0;
    currtime[DAYS]    = 0;
}

void time_set(char seconds, char minutes, char hours, char day)
{
    can_time_tick = 0;

    currtime[SECONDS] = seconds;
    currtime[MINUTES] = minutes;
    currtime[HOURS]   = hours;
    currtime[DAYS]    = day;

    can_time_tick = 1;
}

void time_tick()
{
    if (!can_time_tick)
    {
        return;
    }

    // Clock fallover -
    //  Maximum values in the parts of currtime are 59 59 23 6
    if (currtime[SECONDS] == 59)
    {
        if (currtime[MINUTES] == 59)
        {
            if (currtime[HOURS] == 23)
            {
                if (currtime[DAYS] == 6)
                {
                    currtime[DAYS] = 0;
                }
                else
                {
                    currtime[DAYS]++;
                }

                currtime[HOURS] = 0;
            }
            else
            {
                currtime[HOURS]++;
            }

            currtime[MINUTES] = 0;
        }
        else
        {
            currtime[MINUTES]++;
        }
        
        currtime[SECONDS] = 0;
    }
    else
    {
        currtime[SECONDS]++;
    }
}

//eof

