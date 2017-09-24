// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Button Blink                                                                                                                              |
//|      |_ MSP430F5529                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/21/17                                                                                                                           |
//| Last Updated: 9/23/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430f5529.h>

#define LED_1       BIT0    // LED_0 = 0x0001h
#define LED_2       BIT7    // LED_1 = 0x0080h
#define LED1_OUT    P1OUT
#define LED1_DIR    P1DIR
#define LED2_OUT    P4OUT
#define LED2_DIR    P4DIR
#define BUTTON      BIT1    // Both BUTTONs (S1 and S2) = 0x0002h
#define BUTTON1_UP  P2IN & BUTTON
#define BUTTON2_UP  P1IN & BUTTON

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    // DO NOT PM5CTL0 &= ~LOCKLPM5 ON MSP430F5529

    LED1_DIR |= LED_1; // Set P1.0 to output direction
    LED2_DIR |= LED_2; // Set P4.7 to output direction
    P1DIR &= ~BUTTON; // Clear P1.1 to input direction
    P2DIR &= ~BUTTON; // Clear P2.1 to input direction
    LED1_OUT &= ~LED_1; // Clear the LED (LED_1 OFF)
    LED2_OUT &= ~LED_2; // Clear the LED (LED_2 OFF)
    P1REN |= BUTTON; // Enables a pull-resistor on the button pin
    P2REN |= BUTTON;
    P1OUT |= BUTTON; // Writes a "1" to the port pin, telling the resistor to pull up
    P2OUT |= BUTTON;

    while(1)
    {
        if(BUTTON1_UP)
            LED1_OUT &= ~LED_1; // LED_1 OFF
        else if(~BUTTON1_UP)
            LED1_OUT |= LED_1; // LED_1 ON

        if(BUTTON2_UP)
            LED2_OUT &= ~LED_2; // LED_2 OFF
        else if(~BUTTON2_UP)
            LED2_OUT |= LED_2; // LED_2 ON
    }

}
