/*
 * nmeatest.c
 * Test methods for the reefctrl NMEA time parsing functionalities
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 */

#include <io.h>
#include <signal.h>
#include "nmea.h"

#define TESTRUN 8

#if TESTRUN == 1
    // Normal, get single digit hour
    #define GGA_TEST "$GPGGA,053740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64\r\n"
    #define GGA_EXPECTED_RETVAL 0
    #define GGA_EXPECTED_HOURS  5
#elif TESTRUN == 2
    // Normal, get double digit hour
    #define GGA_TEST "$GPGGA,123740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64\r\n"
    #define GGA_EXPECTED_RETVAL 0
    #define GGA_EXPECTED_HOURS  12
#elif TESTRUN == 3
    // Abnormal, wrong NMEA sentence
    #define GGA_TEST "$GPGLL,2503.6319,N,12136.0099,E,053740.000,A,A*52\r\n"
    #define GGA_EXPECTED_RETVAL ERR_NMEA_SENTENCE_BAD_HEADER
    #define GGA_EXPECTED_HOURS  0
#elif TESTRUN == 4
    // Abnormal, empty string (bad header)
    #define GGA_TEST ""
    #define GGA_EXPECTED_RETVAL ERR_NMEA_SENTENCE_BAD_HEADER
    #define GGA_EXPECTED_HOURS  0
#elif TESTRUN == 5
    // Abnormal, string too short (bad header)
    #define GGA_TEST "$GPGG"
    #define GGA_EXPECTED_RETVAL ERR_NMEA_SENTENCE_BAD_HEADER
    #define GGA_EXPECTED_HOURS  0
#elif TESTRUN == 6
    // Abnormal, string too short
    #define GGA_TEST "$GPGGA,"
    #define GGA_EXPECTED_RETVAL ERR_NMEA_SENTENCE_TOO_SHORT
    #define GGA_EXPECTED_HOURS  0
#elif TESTRUN == 7
    #define GGA_TEST "$GPGGA,1"
    #define GGA_EXPECTED_RETVAL ERR_NMEA_SENTENCE_TOO_SHORT
    #define GGA_EXPECTED_HOURS  0
#elif TESTRUN == 8
    // Normal, get double digit hour
    #define GGA_TEST "$GPGGA,233740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64\r\n"
    #define GGA_EXPECTED_RETVAL 0
    #define GGA_EXPECTED_HOURS  23
#endif

int main()
{
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    
    unsigned char nHours = 0;
    short nRetval = GetUtcHourFromGGA(GGA_TEST, &nHours);

    if (nRetval == GGA_EXPECTED_RETVAL)
    {
        if (nHours == GGA_EXPECTED_HOURS)
        {
            P1OUT |= BIT0;
        }
    }

    __bis_SR_register(CPUOFF | GIE); // Switch to LPM0 and enable interrupts
    return 0;
}
