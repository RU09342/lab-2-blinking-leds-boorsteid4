// _________________________________________________________________________________________________________________________________________________
//|  Lab 2                                                                                                                                          |
//|  |_ Multiple Blink                                                                                                                              |
//|      |_ MSP430F5529
//|
//| NOW WITH 100% MORE LEDs!
//|
//| Author: Damon Boorstein                                                                                                                         |
//| Date Created: 9/20/17                                                                                                                           |
//| Last Updated: 9/25/17                                                                                                                           |
//|_________________________________________________________________________________________________________________________________________________|

#include <msp430.h>

#define LED1        BIT0    // LED1 = 0x0001h
#define LED2        BIT7    // LED2 = 0x0080h
#define LED3        BIT2    // LED2 = 0x0004h
#define LED4        BIT3    // LED3 = 0x0008h
#define LED1_OUT    P1OUT
#define LED2_OUT    P4OUT
#define LED1_DIR    P1DIR
#define LED2_DIR    P4DIR

unsigned int count = 0;
unsigned int state = 0;
unsigned int ns = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED1_DIR |= (LED1 + LED3 + LED4); // Set LED1 (red) to output direction on P1
    LED2_DIR |= LED2; // Set LED2 (green) to output direction on P4
    LED1_OUT &= ~(LED1 + LED3 + LED4); // Clear LED1 (OFF)
    LED2_OUT &= ~LED2; // Clear LED2 (OFF)

    while(1) // Infinite loop
    {
        // Finite State Machine
        switch(state)
        {
        case 0:
            LED2_OUT |= LED2;
            ns = 1;
            break;
        case 1:
            LED2_OUT &= ~LED2;
            LED1_OUT |= LED1;
            ns = 2;
            break;
        case 2:
            LED1_OUT &= ~LED1;
            LED1_OUT |= LED3;
            ns = 3;
            break;
        case 3:
            LED1_OUT &= ~LED3;
            LED1_OUT |= LED4;
            ns = 4;
            break;
        case 4:
            LED1_OUT &= ~LED4;
            LED1_OUT |= LED3;
            ns = 5;
            break;
        case 5:
            LED1_OUT &= ~LED3;
            LED1_OUT |= LED1;
            ns = 6;
            break;
        case 6:
            LED1_OUT &= ~LED1;
            LED2_OUT |= LED2;
            ns = 7;
            break;
        case 7:
            LED2_OUT &= ~LED2;
            ns = 0;
            break;
        default:
            LED1_OUT &= ~LED1;
            LED2_OUT &= ~LED2;
            LED1_OUT &= ~LED3;
            ns = 0;
            break;
        }

        // Program clock
        if(count % 750 == 0) // every 750 cycles...
            state = ns; // current state <= next state
        count++;
    }


}
