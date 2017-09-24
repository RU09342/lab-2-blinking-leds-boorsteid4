// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Button Blink                                                                                                                              |
//|      |_ MSP430FR5994                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/21/17                                                                                                                           |
//| Last Updated: 9/23/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr5994.h>

#define LED_1       BIT0    // LED_0 = 0x0001h
#define LED_2       BIT1    // LED_1 = 0x0002h
#define LED_OUT     P1OUT
#define LED_DIR     P1DIR
#define BUTTON1     BIT6    // BUTTON (S1) = 0x0040h
#define BUTTON2     BIT5    // BUTTON (S2) = 0x0020h
#define BUTTON1_UP  P5IN & BUTTON1
#define BUTTON2_UP  P5IN & BUTTON2

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED_DIR |= (LED_1 + LED_2); // Set P1.0 and P1.1 to output direction
    P5DIR &= ~(BUTTON1 + BUTTON2); // Clear P5.6 and P5.5 to input direction
    LED_OUT &= ~(LED_1 + LED_2); // Clear the LEDs (LED_1 and LED_2 OFF)
    P5REN |= (BUTTON1 + BUTTON2); // Enables a pull-resistor on the button pin
    P5OUT |= (BUTTON1 + BUTTON2); // Writes a "1" to the port pin, telling the resistor to pull up

    while(1)
    {
        if(BUTTON1_UP)
            LED_OUT &= ~LED_1; // LED_1 OFF
        else if(~BUTTON1_UP)
            LED_OUT |= LED_1; // LED_1 ON

        if(BUTTON2_UP)
            LED_OUT &= ~LED_2; // LED_2 OFF
        else if(~BUTTON2_UP)
            LED_OUT |= LED_2; // LED_2 ON
    }

}
