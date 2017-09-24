// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Off-Board Blink                                                                                                                              |
//|      |_ MSP430G2553                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/23/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430g2553.h>


#define LED_0 BIT0
#define LED_1 BIT6
#define LED_OUT P1OUT
#define LED_DIR P1DIR
#define BUTTON BIT3

unsigned int blink = 0;

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
LED_DIR |= (LED_0 + LED_1); // Set P1.0 and P1.6 to output direction
LED_OUT &= ~(LED_0 + LED_1); // Set the LEDs off
P1REN |= BUTTON; //Enables a puller-Resistor on the button-pin
P1OUT |= BUTTON; //Writes a "1" to the port pin, telling the resistor to pull up
P1IES |= BUTTON; //Triggers when you PRESS the button :: Pick one...
//P1IES &= ~BUTTON; // Triggers when you RELEASE the button :: ...or pick the other
P1IE |= BUTTON; //Enables the selector-mask for generating interrupts on the relevant pin

__enable_interrupt(); // Interrupts get enabled *here* - they were disabled thus far..

for (;;)
{

if(blink > 0)
{
P1OUT ^= (LED_0 + LED_1); // Toggle P1.0 and P1.6 using exclusive-OR

__delay_cycles(100000); // SW Delay of 10000 cycles at 1Mhz

}
}

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
blink ^= 0x01;
P1IFG &= ~BUTTON; // P1.3 IFG cleared
LED_OUT &= ~(LED_0 + LED_1); // Clear the LEDs so they start in OFF state

}
