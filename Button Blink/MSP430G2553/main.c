// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Button Blink                                                                                                                              |
//|      |_ MSP430G2553                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/23/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430g2553.h>

#define LED_0       BIT0    // LED_0 = 0x0001h
#define LED_OUT     P1OUT
#define LED_DIR     P1DIR
#define BUTTON      BIT3    // BUTTON = 0x0008h
#define BUTTON_UP   P1IN & BUTTON

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer


    LED_DIR |= LED_0; // Set P1.0 to output direction
    P1DIR &= ~BUTTON; // Clear P1.3 to input direction
    LED_OUT &= ~LED_0; // Clear the LED (LED OFF)
    P1REN |= BUTTON; // Enables a pull-resistor on the button pin
    P1OUT |= BUTTON; // Writes a "1" to the port pin, telling the resistor to pull up

    while(1)
    {
        if(BUTTON_UP)
            LED_OUT &= ~LED_0; // LED OFF

        else
            LED_OUT |= LED_0; // LED ON
    }

}
