// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430FR6989                                                                                                                             |
//|                                                                                                                                                 |
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/12/17                                                                                                                           |
//| Last Updated: 9/20/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430fr6989.h>

#define LED1        BIT0    // LED1 = 0x0001h
#define LED2        BIT7    // LED2 = 0x0080h
#define LED1_OUT    P1OUT
#define LED1_DIR    P1DIR
#define LED2_OUT    P9OUT
#define LED2_DIR    P9DIR


unsigned int timerCount = 0;
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate
                          // previously configured port settings

    LED1_DIR |= LED1; // Set LED0 to output direction on P1
    LED2_DIR |= LED2; // Set LED1 to output direction on P9
    LED2_OUT &= ~LED2; // Clear the green LED (OFF)
    LED1_OUT |= LED1; // Set the red LED (ON)

    while(1)
    {
        if(count % 1000 == 0)
        {
            LED1_OUT ^= LED1; // Toggle LED1
            LED2_OUT ^= LED2; // Toggle LED2
        }
        count++;
    }
}
