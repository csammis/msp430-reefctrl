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

#define BUTTON1 BIT3
#define BUTTON2 BIT4

#define STATE_MOONLIGHTS 0x0001
#define STATE_MAINLIGHTS 0x0002
#define STATE_FUGELIGHTS 0x0004

#define STATE_MAINPUMPS 0x0010
#define STATE_SKIMPUMPS 0x0020
#define STATE_POWRHEADS 0x0040


//#define SOURCE_FROM_SMCLK

int main()
{
    WDTCTL = WDTPW + WDTHOLD; //this will eventually not be here

    init_lcd();
    init_mode();
    init_time();

    // debugging the time_tick function
    P1DIR |= BIT0 + BIT6;
    P1OUT |= BIT0 + BIT6;

    /* Timer setup */

#ifdef SOURCE_FROM_SMCLK

    // This will set the timerA interrupt to go every 1.953125Hz
    DCOCTL= 0;
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;

    BCSCTL2 |= DIVS_3; //SMCLK = DCO / 8 = 125KHz

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
    
    // WDT functions as a sensor poll

    // Set up interrupts
    //P1IE   = BUTTON1 | BUTTON2;
    //P1OUT |= BUTTON1 | BUTTON2;
    //P1REN  = BUTTON1 | BUTTON2;

    __bis_SR_register(CPUOFF | GIE); // Switch to LPM0 and enable interrupts

    return 0;
}

// debounce
//  debounces a button using a cycle delay
/*
void debounce(unsigned char ucPin)
{
    // Disable the interrupt and clear the pending flag
    P1IE  &= ~ucPin;
    P1IFG &= ~ucPin;

    __asm__
    (
        "mov #1000, r2  \n\t"
        "dec r2         \n\t"
        "jnz $-2        \n\t"
    );

    // Clear the pending interrupt flags and re-enable the interrupt
    P1IFG &= ~ucPin;
    P1IE  |=  ucPin;
}

//void __attribute__((interrupt(PORT1_VECTOR)))

Interrupt(PORT1_VECTOR) port1_isr()
{
    if (P1IFG & BUTTON1)
    {
        debounce(BUTTON1);
        switch_mode();
    }
    
    if (P1IFG & BUTTON2)
    {
        debounce(BUTTON2);
        update_action();
    }
}
*/

Interrupt(TIMERA0_VECTOR) timerA_isr()
{
    TACCTL0 &= ~CCIFG;

    time_tick();
}

