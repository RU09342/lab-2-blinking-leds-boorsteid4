// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430F5529
//|
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/20/17                                                                                                                           |
//| Last Updated: 9/26/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

// ***NOTE: This program supports up to 4 LED outputs, but there are only 2 on-board LEDs that are accessible.***
//          This program extends to pins P1.2 and P1.3.

#include <msp430f5529.h>

#define LED1        BIT0    // LED1 = 0x0001h
#define LED2        BIT7    // LED2 = 0x0080h
#define LED3        BIT2    // LED3 = 0x0004h
#define LED4        BIT3    // LED4 = 0x0008h
#define LED1_SEL    P1SEL   // LED1_SEL = LED3_SEL = LED4_SEL = P1SEL
#define LED2_SEL    P4SEL   // LED2_SEL = P4SEL
#define LED1_OUT    P1OUT   // LED1_OUT = LED3_OUT = LED4_OUT = P1OUT
#define LED2_OUT    P4OUT   // LED2_OUT = P4OUT
#define LED1_DIR    P1DIR   // LED1_DIR = LED3_OUT = LED4_OUT = P1DIR
#define LED2_DIR    P4DIR   // LED2_DIR = P4DIR

unsigned int count = 0;
unsigned int state = 0;
unsigned int ns = 0; // next state

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED1_SEL &= ~(LED1 + LED3 + LED4); // Select I/O function for P1.0, P1.2, and P1.3
                                       // by masking with LED1 + LED3 + LED4 and clearing LED1_SEL
    LED2_SEL &= ~LED2; // Select I/O function for P4.7 by masking with LED2 and clearing LED2_SEL
    LED1_DIR |= (LED1 + LED3 + LED4); // Change P1.0, P1.2, and P1.3 to outputs
                                      // by masking with LED1 + LED3 + LED4 and setting LED1_DIR
    LED2_DIR |= LED2; // Change P4.7 to an output by masking with LED2 and setting LED2_DIR
    LED1_OUT &= ~(LED1 + LED3 + LED4); // Clear P1.0, P1.2, and P1.3 (turn the LEDs off)
                                       // by masking with LED1 + LED3 + LED4 and clearing LED1_OUT
    LED2_OUT &= ~LED2; // Clear P4.7 (turn LED2 off) by masking with LED2 and clearing LED2_OUT

    while(1) // This initiates an "infinite" loop for polling
    {
        // Finite State Machine
        //
        //      Produces a "ping-pong" effect in the LEDs, where one LED turns off and the LED next to it turns on until
        //      the end of the series and the process repeats in the opposite direction.

        switch(state)
        {
        case 0: // Initial state
            LED2_OUT |= LED2; // Set P4.7 (turn LED2 on) by masking with LED2 and setting LED2_OUT
            ns = 1; // The next state is 1
            break; // break out of this case loop
        case 1: // State 1
            LED2_OUT &= ~LED2; // Clear P4.7 (turn LED2 off) by masking with LED2 and clearing LED2_OUT
            LED1_OUT |= LED1; // Set P1.0 (turn LED1 on) by masking with LED1 and setting LED1_OUT
            ns = 2; // The next state is 2
            break; //break out of this case loop
        case 2:                                               // This process continues...
            LED1_OUT &= ~LED1;
            LED1_OUT |= LED3;
            ns = 3;
            break;
        case 3:
            LED1_OUT &= ~LED3;
            LED1_OUT |= LED4;
            ns = 4;
            break;
        case 4:
            LED1_OUT &= ~LED4;
            LED1_OUT |= LED3;
            ns = 5;
            break;
        case 5:
            LED1_OUT &= ~LED3;
            LED1_OUT |= LED1;
            ns = 6;
            break;
        case 6:
            LED1_OUT &= ~LED1;
            LED2_OUT |= LED2;
            ns = 7;
            break;
        case 7:
            LED2_OUT &= ~LED2;
            ns = 0; // The state machine returns to the initial state here
            break;
        default:                // By default, all LEDs will be turned off and ns will be set to 0
            LED1_OUT &= ~LED1;  // This happens in case an error occurs.
            LED2_OUT &= ~LED2;
            LED1_OUT &= ~LED3;
            ns = 0;
            break;
        }

        // Program clock
        if(count % 750 == 0) // If count reaches a multiple of 750...
        {
            state = ns; // current state <= next state
            count = 0; // Reset the counter
        }
        count++; // Increment the counter
    }


}
