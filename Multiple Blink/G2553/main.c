// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430G2553                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/27/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430g2553.h>

#define LED1    BIT0 // LED1 is defined as 0x0001h
#define LED2    BIT6 // LED2 is defined as 0x0040h
#define LED_SEL P1SEL // LED_SEL is defined as P1SEL
#define LED_OUT P1OUT // LED_OUT is defined as P1OUT
#define LED_DIR P1DIR // LED_DIR is defined as P1DIR

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED_SEL &= ~(LED1 + LED2); // Select I/O function for P1.0, P1.6 by masking with LED1 + LED2 and clearing LED_SEL
    LED_DIR |= (LED1 + LED2); // Change P1.0 and P1.6 to an output by masking with LED1 + LED2 and setting LED_DIR
    LED_OUT &= ~(LED1 + LED2); // Clear P1.0 and P1.6 (Turn LED1 and LED2 off)
                               // by masking with LED1 + LED2 and clearing with LED_OUT

    while(1) // This initiates an "infinite" loop for polling
    {
        if(count % 1000 == 0) // If count reaches a multiple of 1000... (blinks slower)
            LED_OUT ^= LED1; // Toggle P1.0 by masking with LED1 and xor'ing with LED_OUT
        if(count % 500 == 0) // If count reaches a multiple of 500... (blinks faster)
            LED_OUT ^= LED2; // Toggle P1.6 by masking with LED2 and xor'ing with LED_OUT

        count++;
    }

}
