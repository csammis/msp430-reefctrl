/*
 * nmea.h
 * Parsing functions for NMEA sentences
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 */

#define ERR_NMEA_SENTENCE_TOO_SHORT -1
#define ERR_NMEA_SENTENCE_BAD_HEADER -2
#define ERR_NMEA_BAD_ARGUMENTS -3

// GetUtcHourFromGGA
//  Parse out the UTC hour from a GGA sentence
//
//  An example packet:
//      $GPGGA,053740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64
short GetUtcHourFromGGA(const char* pStr, unsigned char* pnHours)
{
    if (!pnHours || !pStr)
    {
        return ERR_NMEA_BAD_ARGUMENTS;
    }

    char* pIter = (char*)pStr;
    unsigned int nIdx = 0;

    // Verify that this is a GGA sentence
    for (; nIdx < 6; ++nIdx, ++pIter)
    {
        char cExpected = 'G';
        switch (nIdx)
        {
            case 0: cExpected = '$'; break;
            case 2: cExpected = 'P'; break;
            case 5: cExpected = 'A'; break;
        }

        if ((*pIter) != cExpected || (*pIter) == '\0')
        {
            return ERR_NMEA_SENTENCE_BAD_HEADER;
        }
    }

    if (*pIter++ != ',')
    {
        return ERR_NMEA_SENTENCE_TOO_SHORT;
    }
    
    // Get the hours
    if (*pIter == '\0' || *(pIter + 1) == '\0')
    {
        return ERR_NMEA_SENTENCE_TOO_SHORT;
    }
    
    char nVal = ((*pIter++) - '0') * 10;
    nVal += (*pIter) - '0';
    *pnHours = nVal;

    return 0;
}
