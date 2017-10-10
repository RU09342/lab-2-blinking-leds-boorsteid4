//***************************************************************************************
// LAB 2: LED Blinking
//
// MSP430FR6989 Button Blink
//
// Description: Toggle P1.0 and P9.7 by xor'ing them inside of a polling loop.
// ACLK = n/a, MCLK = SMCLK = default DCO
//
//           MSP430FR6989
//           -----------
//        /|\|      XIN|-
//         | |         |
//         --|RST  XOUT|-
//           |     P1.0|-->LED1
// Button -->|P1.1 P9.7|-->LED2
//
// Damon Boorstein
// Rowan University
// Date Created: September 12, 2017
// Date Updated: October 10, 2017
//
// Built with Code Composer Studio v7.2.0
//***************************************************************************************

#include <msp430fr6989.h>

#define LED1        BIT0    // LED_0 = 0x0001h
#define LED2        BIT7    // LED_1 = 0x0080h
#define LED1_OUT    P1OUT
#define LED1_DIR    P1DIR
#define LED2_OUT    P9OUT
#define LED2_DIR    P9DIR
#define BUTTON1     BIT1    // BUTTON (S1) = 0x0002h
#define BUTTON2     BIT2    // BUTTON (S2) = 0x0004h

unsigned int blink = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    P1SEL0 &= ~(BUTTON2 + BUTTON1 + LED1); // Select I/O for P1.0-2
    P1SEL1 &= ~(BUTTON2 + BUTTON1 + LED1);
    P9SEL0 &= ~LED2; // Select I/O for P9.7
    P9SEL1 &= ~LED2;
    LED1_DIR |= LED1; // Set P1.0 to output direction
    LED2_DIR |= LED2; // Set P9.7 to output direction
    P1DIR &= ~(BUTTON2 + BUTTON1); // Clear P1.1 to input direction
    LED1_OUT &= ~LED1; // Clear the LED (LED1 OFF)
    LED2_OUT &= ~LED2; // Clear the LED (LED2 OFF)
    P1REN |= (BUTTON2 + BUTTON1); // Enables a pull-resistor on the button pin
    P1OUT |= (BUTTON2 + BUTTON1); // Writes a "1" to the port pin, telling the resistor to pull up

    while(1)
    {
        if((BUTTON1 & P1IN) || (BUTTON2 & P1IN)) // If the button is not pressed
        {
            blink &= 0;
            LED1_OUT &= ~LED1;
            LED2_OUT &= ~LED2;
        }

        else if (~(BUTTON1 & P1IN) || ~(BUTTON2 & P1IN))
            blink ^= 0x01;

        if(blink > 0)
        {
        LED1_OUT ^= LED1; // Toggle P1.0
        LED2_OUT ^= LED2; // and P9.7 using xor

        __delay_cycles(100000); // SW Delay of 10000 cycles at 1Mhz
        }
    }

}
