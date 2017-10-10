// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Button Blink                                                                                                                              |
//|      |_ MSP430F5529                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/21/17                                                                                                                           |
//| Last Updated: 10/10/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430f5529.h>

#define LED1        BIT0 // LED1 is defined as 0x0001h
#define LED2        BIT7 // LED2 is defined as 0x0080h
#define LED1_SEL    P1SEL // LED1_SEL is defined as P1SEL
#define LED2_SEL    P4SEL // LED1_SEL is defined as P4SEL
#define LED1_OUT    P1OUT // LED1_OUT is defined as P1OUT
#define LED1_DIR    P1DIR // LED1_DIR is defined as P1DIR
#define LED2_OUT    P4OUT // LED2_OUT is defined as P4OUT
#define LED2_DIR    P4DIR // LED2_OUT is defined as P4OUT
#define BUTTON      BIT1  // BUTTON is defined as 0x0002h
#define BUTTON1_UP  P2IN & BUTTON // BUTTON1_UP is defined as P2IN & BUTTON
#define BUTTON2_UP  P1IN & BUTTON // BUTTON2_UP is defined as P1IN & BUTTON

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED1_SEL &= ~LED1; // Select I/O function for P1.0 by masking with LED1 and clearing LED_SEL
    LED2_SEL &= ~LED2; // Select I/O function for P4.7 by masking with LED2 and clearing LED_SEL
    LED1_DIR |= LED1; // Change P1.0 to an output by masking with LED1 and setting LED1_DIR
    LED2_DIR |= LED2; // Change P4.7 to an output by masking with LED2 and setting LED2_DIR
    P1DIR &= ~BUTTON; // Change P2.1 to an input by masking with BUTTON and clearing P1DIR
    P4DIR &= ~BUTTON; // Change P1.1 to an input by masking with BUTTON and clearing P4DIR
    LED1_OUT &= ~LED1; // Clear P1.0 (turn LED1 off) by masking with LED1 and clearing LED1_OUT
    LED2_OUT &= ~LED2; // Clear P4.7 (turn LED2 off) by masking with LED2 and clearing LED2_OUT
    P1REN |= BUTTON; // Enable a pull-resistor on P1.1 by masking with BUTTON and setting P1REN
    P2REN |= BUTTON; // Enable a pull-resistor on P2.1 by masking with BUTTON and setting P2REN
    P1OUT |= BUTTON; // Tell the resistor to pull up by masking with BUTTON and setting P1OUT
    P2OUT |= BUTTON; // Tell the resistor to pull up by masking with BUTTON and setting P2OUT

    while(1) // This initiates an "infinite" loop for polling
    {
        if(BUTTON1_UP) // If BUTTON1 is up...
            LED1_OUT &= ~LED1; // turn LED1 OFF
        else if(~BUTTON1_UP) // Else, if BUTTON1 is down...
            LED1_OUT |= LED1; // turn LED1 ON

        if(BUTTON2_UP) // If BUTTON2 is up...
            LED2_OUT &= ~LED2; // turn LED2 OFF.
        else if(~BUTTON2_UP) // Else, if BUTTON2 is down...
            LED2_OUT |= LED2; // turn LED2 ON.
    }

}
