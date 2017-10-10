// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Button Blink                                                                                                                              |
//|      |_ MSP430FR2311                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 10/10/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

/*
 * EXTRA WORK:
 *
 *  MULTI-SPEED BUTTON BLINK:
 *
 *      Pressing the button changes the LED blink rate.
 */

#include <msp430fr2311.h>

#define LED1        BIT0 // LED is defined as 0x0001h
#define LED1_SEL0   P1SEL0 // LED_SEL0 is defined as P1SEL0
#define LED1_SEL1   P1SEL1 // LED_SEL1 is defined as P1SEL1
#define LED1_OUT    P1OUT // LED1_OUT is defined as P1OUT
#define LED1_DIR    P1DIR // LED1_DIR is defined as P1DIR
#define BUTTON          BIT1  // BUTTON is defined as 0x0002h
#define BUTTON_UP       P1IN & BUTTON // BUTTON1_UP is defined as P2IN & BUTTON

unsigned int count = 0; //
unsigned int x = 0;
unsigned int y = 0;
unsigned int i = 0;
float sample = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED1_SEL0 &= ~LED1; // Select I/O function for P1.0 by masking with LED1 and clearing LED_SEL0
    LED1_SEL1 &= ~LED1; //      ...and LED1_SEL1
    LED1_DIR |= LED1; // Change P1.0 to an output by masking with LED1 and setting LED1_DIR
    P1DIR &= ~BUTTON; // Change P1.1 to an input by masking with BUTTON and clearing P1DIR
    LED1_OUT &= ~LED1; // Clear P1.0 (turn LED1 off) by masking with LED1 and clearing LED1_OUT
    P1REN |= BUTTON; // Enable a pull-resistor on P1.1 by masking with BUTTON and setting P1REN
    P1OUT |= BUTTON; // Tell the resistor to pull up by masking with BUTTON and setting P1OUT

    while (1) // This initiates an "infinite" loop for polling
    {
        /* Debouncing control:
         *
         *  This button may bounce 1000 times before returning to a steady state. Bouncing can confuse the program
         *  into moving on at an incorrect time. The following code takes 1000 samples and increments a variable
         *  sample for each time the program finds the button in the down position.
         *
         */

        for (i = 1000; i>0; i--) // 1000 iterations
        {
            if (!(BUTTON_UP)) // If we receive a signal that the button is down...
                    sample++; // Increment sample
        }

        // With debouncing, sample is most likely greater than 1000 after one button press

        if (sample/500 > 0.5) // If 1000/500 > 0.5...
        {
            count++; // Increment count

            // This switch statement sets the delay (x) b/w blinks
            switch (count % 3)
            {
            case (0): // 1st button press
                x = 5000; // short delay (fast blink)
                break;
            case (1): // 2nd button press
                x = 10000; // medium delay (medium blink)
                break;
            case (2): // 3rd button press
                x = 50000; // long delay (slow blink)
                break;
            }
        }

        LED1_OUT ^= LED1; // Toggle the LED

            while (y < x) // While y (another counter) < the blink delay...
            {
                if (!(BUTTON_UP)) // If the button is pressed...
                    break; // Break out of the while loop
                y++; // Increment y
                     // Higher x (delay) means more time for y to be greater than x
            }

            // Reset y and sample at the end
            y = 0;
            sample = 0;
        }
    }
