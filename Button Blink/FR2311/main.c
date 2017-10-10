//***************************************************************************************
// LAB 2: LED Blinking
//
// MSP430FR2311 Button Blink
//
// Description: Toggle P1.0 and P2.0 by xor'ing them inside of a software loop.
// ACLK = n/a, MCLK = SMCLK = default DCO
//
//           MSP430FR2311
//           -----------
//        /|\|      XIN|-
//         | |         |
//         --|RST  XOUT|-
//           |     P1.0|-->LED1
// Button -->|P1.1 P2.0|-->LED2
//
// Damon Boorstein
// Rowan University
// Date Created: September 12, 2017
// Date Updated: October 10, 2017
//
// Built with Code Composer Studio v7.2.0
//***************************************************************************************
#include <msp430fr2311.h>


#define LED         BIT0
#define LED1_OUT    P1OUT
#define LED2_OUT    P2OUT
#define LED1_DIR    P1DIR
#define LED2_DIR    P2DIR
#define BUTTON      BIT1

unsigned int blink = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO default

    P1SEL0 &= ~(BUTTON + LED); // Select I/O for P1.0 and P1.1
    P1SEL1 &= ~(BUTTON + LED);
    P2SEL0 &= ~(BUTTON + LED); // Select I/O for P2.0 and P2.1
    P2SEL1 &= ~(BUTTON + LED);
    LED1_DIR |= LED; // Set P1.0
    LED2_DIR |= LED; // and P2.0 to output direction
    LED1_OUT &= ~LED; // Clear LED1
    LED2_OUT &= ~LED; // and LED2
    P1DIR &= ~BUTTON; // Set P1.1 to input direction
    P1REN |= BUTTON; // Enable a puller-resistor on the button-pin
    P1OUT |= BUTTON; // Tell the resistor to pull up

    for (;;) // Polling for blink
    {
        if(BUTTON & P1IN) // If the button is not pressed
        {
            blink &= 0;
            LED1_OUT &= ~LED;
            LED2_OUT &= ~LED;
        }

        else
            blink ^= 0x01;

        if(blink > 0)
        {
        LED1_OUT ^= LED; // Toggle P1.0
        LED2_OUT ^= LED; // and P2.0 using xor

        __delay_cycles(100000); // SW Delay of 10000 cycles at 1Mhz
        }

    }

}
