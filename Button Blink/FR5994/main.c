//***************************************************************************************
// LAB 2: LED Blinking
//
// MSP430FR5994 Button Blink
//
// Description: Toggle P1.0 and P1.1 by xor'ing them in a polling loop.
// ACLK = n/a, MCLK = SMCLK = default DCO
//
//           MSP430FR5994
//           -----------
//        /|\|      XIN|-
//         | |         |
//         --|RST  XOUT|-
// Button1-->|P5.6 P1.0|-->LED1
// Button -->|P5.5 P1.1|-->LED2
//
// Damon Boorstein
// Rowan University
// Date Created: September 21, 2017
// Date Updated: October 10, 2017
//
// Built with Code Composer Studio v7.2.0
//***************************************************************************************

#include <msp430fr5994.h>

#define LED1        BIT0    // LED_0 = 0x0001h
#define LED2        BIT1    // LED_1 = 0x0002h
#define LED_OUT     P1OUT
#define LED_DIR     P1DIR
#define BUTTON1     BIT6    // BUTTON (S1) = 0x0040h
#define BUTTON2     BIT5    // BUTTON (S2) = 0x0020h
#define BUTTON1_UP  BUTTON1 & P5IN
#define BUTTON2_UP  BUTTON2 & P5IN

unsigned int blink = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    P1SEL0 &= ~(LED2 + LED1); // Select I/O direction for P1
    P1SEL1 &= ~(LED2 + LED1);
    P5SEL0 &= ~(BUTTON2 + BUTTON1); // Select I/O direction for P5
    P5SEL1 &= ~(BUTTON2 + BUTTON1);
    LED_DIR |= (LED1 + LED2); // Set P1.0 and P1.1 to output direction
    P5DIR &= ~(BUTTON1 + BUTTON2); // Clear P5.6 and P5.5 to input direction
    LED_OUT &= ~(LED1 + LED2); // Clear the LEDs (LED_1 and LED_2 OFF)
    P5REN |= (BUTTON1 + BUTTON2); // Enables a pull-resistor on the button pin
    P5OUT |= (BUTTON1 + BUTTON2); // Writes a "1" to the port pin, telling the resistor to pull up

    while(1)
    {
        if((BUTTON2 + BUTTON1) & P5IN) // Press and hold both buttons to enable blinking
        {
            blink &= 0x00;
            LED_OUT &= ~(LED2 + LED1);
        }

        else
           blink ^= 0x01;

        if(blink > 0)
        {
            LED_OUT ^= (LED2 + LED1); // Toggle LED1 and LED1 using xor
            __delay_cycles(100000); // SW Delay of 10000 cycles at 1Mhz
        }

    }

}
