// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Simple Blink                                                                                                                                |
//|      |_ MSP430F5529                                                                                                                            |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/20/17                                                                                                                           |
//| Last Updated: 9/20/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430f5529.h>

#define LED1     BIT0 // LED1 is defined as a 0x0001h

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    P1DIR |= LED1; // Set P1.0 as an output
    P1OUT &= ~LED1; // LED1 is initialized as off

    while(1) // Infinite loop
    {
        if(count % 1000 == 0) // Cycle every 1000 clock cycles
            P1OUT ^= LED1; // Toggle LED1
        count++; // Increment the counter
    }

}
