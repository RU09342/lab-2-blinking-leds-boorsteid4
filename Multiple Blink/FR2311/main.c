// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430FR2311                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/20/17                                                                                                                           |
//| Last Updated: 9/26/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr2311.h>

#define LED         BIT0 // LED is defined as 0x0001h
#define LED1_SEL0   P1SEL0 // LED1_SEL0 is defined as P1SEL0
#define LED1_SEL1   P1SEL1 // LED1_SEL1 is defined as P1SEL1
#define LED2_SEL0   P2SEL0 // LED2_SEL0 is defined as P2SEL0
#define LED2_SEL1   P2SEL1 // LED2_SEL1 is defined as P2SEL1
#define LED1_OUT    P1OUT // LED1_OUT is defined as P1OUT
#define LED2_OUT    P2OUT // LED2_OUT is defined as P2OUT
#define LED1_DIR    P1DIR // LED1_DIR is defined as P1DIR
#define LED2_DIR    P2DIR // LED2_DIR is defined as P2DIR

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED1_SEL0 &= ~LED; // Select I/O function for P1.0 by masking with LED and clearing LED1_SEL0
    LED1_SEL1 &= ~LED; //   ...and LED1_SEL1
    LED2_SEL0 &= ~LED; // Select I/O function for P2.0 by masking with LED and clearing LED2_SEL0
    LED2_SEL1 &= ~LED; //   ...and LED2_SEL1
    LED1_DIR |= LED; // Change P1.0 to an output by masking with LED and setting LED1_DIR
    LED2_DIR |= LED; // Change P2.0 to an output by masking with LED and setting LED2_DIR
    LED1_OUT &= ~LED; // Clear P1.0 (turn LED1 off) by masking with LED and clearing LED1_OUT
    LED2_OUT &= ~LED; // Clear P2.0 (turn LED2 off) by masking with LED and clearing LED2_OUT

    while(1) // This initiates an "infinite" loop for polling
    {
        if(count % 1000 == 0) // If count reaches a multiple of 1000... (blinks slower)
            LED1_OUT ^= LED; // Toggle P1.0 by masking with LED and xor'ing with LED1_OUT
        if(count % 500 == 0) // If count reaches a multiple of 500... (blinks faster)
            LED2_OUT ^= LED; // Toggle P2.0 by masking with LED and xor'ing with LED2_OUT

        count++; // Increment the counter
    }

}
