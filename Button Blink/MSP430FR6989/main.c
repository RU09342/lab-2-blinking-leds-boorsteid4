// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Button Blink                                                                                                                              |
//|      |_ MSP430FR6869                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/23/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr6989.h>

#define LED_1       BIT0    // LED_0 = 0x0001h
#define LED_2       BIT7    // LED_1 = 0x0080h
#define LED1_OUT    P1OUT
#define LED1_DIR    P1DIR
#define LED2_OUT    P9OUT
#define LED2_DIR    P9DIR
#define BUTTON1     BIT1    // BUTTON (S1) = 0x0002h
#define BUTTON2     BIT2    // BUTTON (S2) = 0x0004h
#define BUTTON1_UP  P1IN & BUTTON1
#define BUTTON2_UP  P1IN & BUTTON2

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED1_DIR |= LED_1; // Set P1.0 to output direction
    LED2_DIR |= LED_2; // Set P9.7 to output direction
    P1DIR &= ~(BUTTON1 + BUTTON2); // Clear P1.1 and P1.2 to input direction
    LED1_OUT &= ~LED_1; // Clear the LED (LED_1 OFF)
    LED2_OUT &= ~LED_2; // Clear the LED (LED_2 OFF)
    P1REN |= (BUTTON1 + BUTTON2); // Enables a pull-resistor on the button pin
    P1OUT |= (BUTTON1 + BUTTON2); // Writes a "1" to the port pin, telling the resistor to pull up

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
