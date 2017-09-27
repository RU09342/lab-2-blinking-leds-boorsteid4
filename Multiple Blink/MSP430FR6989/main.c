// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430FR6989                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/27/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr6989.h>

#define LED1        BIT0 // LED1 is defined as 0x0001h
#define LED2        BIT7 // LED2 is defined as 0x0080h
#define LED1_SEL0   P1SEL0 // LED1_SEL0 is defined as P1SEL0
#define LED1_SEL1   P1SEL1 // LED1_SEL1 is defined as P1SEL1
#define LED2_SEL0   P9SEL0 // LED9_SEL0 is defined as P1SEL0
#define LED2_SEL1   P9SEL1 // LED9_SEL1 is defined as P1SEL1
#define LED1_OUT    P1OUT // LED1_OUT is defined as P1OUT
#define LED1_DIR    P1DIR // LED1_DIR is defined as P1DIR
#define LED2_OUT    P9OUT // LED2_OUT is defined as P9OUT
#define LED2_DIR    P9DIR // LED2_DIR is defined as P9DIR


unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED1_SEL0 &= ~LED1; // Select I/O function for P1.0 by masking with LED1 and clearing LED1_SEL0
    LED1_SEL1 &= ~LED1; //   ...and LED1_SEL1
    LED2_SEL0 &= ~LED2; // Select I/O function for P9.7 by masking with LED2 and clearing LED2_SEL0
    LED2_SEL1 &= ~LED2; //   ...and LED2_SEL1
    LED1_DIR |= LED1; // Change P1.0 to an output by masking with LED1 and setting LED1_DIR
    LED2_DIR |= LED2; // Change P9.7 to an output by masking with LED2 and setting LED2_DIR
    LED1_OUT &= ~LED1; // Clear P1.0 (turn LED1 off) by masking with LED1 and clearing LED1_OUT
    LED2_OUT &= ~LED2; // Clear P9.7 (turn LED2 off) by masking with LED2 and clearing LED2_OUT


    while(1) // This initiates an "infinite" loop for polling
    {
        if(count % 1000 == 0) // If count reaches a multiple of 1000... (blinks slower)
        {
            LED1_OUT ^= LED1; // Toggle P1.0 by masking with LED1 and xor'ing with LED1_OUT
        }
        if(count % 500 == 0) // If count reaches a multiple of 500... (blinks faster)
        {
            LED2_OUT ^= LED2; // Toggle P9.7 by masking with LED12 and xor'ing with LED2_OUT
        }

        count++; // Increment the counter
    }
}
