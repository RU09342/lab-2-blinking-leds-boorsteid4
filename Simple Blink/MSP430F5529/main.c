// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Simple Blink                                                                                                                                |
//|      |_ MSP430F5529                                                                                                                            |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/20/17                                                                                                                           |
//| Last Updated: 9/26/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430f5529.h>

#define LED1    BIT0 // LED1 is defined as a 0x0001h
#define LED_SEL P1SEL // LED_SEL is defined as P1SEL
#define LED_DIR P1DIR // LED_DIR is defined as P1DIR
#define LED_OUT P1OUT // LED_OUT is defined as P1OUT

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED_SEL &= ~LED1; // Select I/O function for P1.0 by masking with LED1 and clearing LED_SEL
    LED_DIR |= LED1; // Change P1.0 to an output by masking with LED1 and setting LED_DIR
    LED_OUT &= ~LED1; // Clear P1.0 (turn LED1 off) by masking with LED1 and clearing LED_OUT

    while(1) // This initiates an "infinite" loop for polling
    {
        if(count % 1000 == 0) // If count reaches a multiple of 1000...
        {
            LED_OUT ^= LED1; // Toggle P1.0 by masking with LED1 and xor'ing with LED_OUT
            count = 0; // Reset the counter
        }

        count++; // Increment the counter
    }

}
