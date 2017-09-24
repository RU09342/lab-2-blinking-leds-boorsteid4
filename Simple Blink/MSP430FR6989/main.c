// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Simple Blink                                                                                                                                |
//|      |_ MSP430FR6989                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/20/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr6989.h>

#define LED1     BIT0 // LED1 is defined as a 0x0001h

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    P1DIR |= LED1; // Isolate P1 output to P1.0 (LED1)
    P1OUT &= ~LED1; // LED1 is initialized as off


    while(1)
    {
        if(count % 1000 == 0) // Cycle every 1000 clock cycles
            P1OUT ^= LED1; // Toggle LED1
        count++; // Increment the counter
    }

}
