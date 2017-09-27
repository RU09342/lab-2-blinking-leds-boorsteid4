// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430FR5994                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/26/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr5994.h>

#define LED1        BIT0 // LED1 is defined as 0x0001h
#define LED2        BIT1 // LED2 is defined as 0x0002h
#define LED_SEL0    P1SEL0 // LED_SEL0 is defined as P1SEL0
#define LED_SEL1    P1SEL1 // LED_SEL1 is defined as P1SEL1
#define LED_OUT     P1OUT // LED_OUT is defined as P1OUT
#define LED_DIR     P1DIR // LED_DIR is defined as P1DIR

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED_SEL0 &= ~(LED1 + LED2); // Select I/O function for P1.0 and P1.1 by masking with LED1 + LED2 and clearing LED_SEL0
    LED_SEL1 &= ~(LED1 + LED2); //   ...and LED_SEL1
    LED_DIR |= (LED1 + LED2); // Set LED1 and LED2 to output direction
    LED_OUT &= ~(LED1 + LED2); // Clear P1.0 and P1.1 (turn LED1 and LED2 off) by masking with LED and clearing LED_OUT

    while(1) // This initiates an "infinite" loop for polling
    {
        if(count % 1000 == 0) // If count reaches a multiple of 1000... (blinks slower)
        {
            LED_OUT ^= LED1; // Toggle P1.0 by masking with LED1 and xor'ing with LED_OUT
        }
        if(count % 500 == 0) // If count reaches a multiple of 500... (blinks faster)
        {
            LED_OUT ^= LED2; // Toggle P1.1 by masking with LED1 and xor'ing with LED_OUT
        }

        count++; // Increment the counter
    }

}
