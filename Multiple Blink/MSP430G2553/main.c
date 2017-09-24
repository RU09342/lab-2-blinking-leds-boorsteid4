// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430G2553                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/20/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430g2553.h>

#define LED_0   BIT0    // LED_0 = 0x0001h
#define LED_1   BIT6    // LED_1 = 0x0040h
#define LED_OUT P1OUT
#define LED_DIR P1DIR

unsigned int count = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1DIR |= (LED_0 + LED_1); // Set LED0 and LED1 to output direction
    P1OUT &= LED_1; // Clear the green LED (OFF)
    P1OUT |= LED_0; // Set the red LED (ON)

    while(1) // Infinite loop
    {
        if(count % 1000 == 0) // Cycle every 1000 clock cycles
        P1OUT ^= (LED_0 + LED_1); // Toggle the LEDs
        count++;
    }

}
