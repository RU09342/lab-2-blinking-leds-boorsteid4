# Simple Blink

## Program Description

A single LED is blinked at a specific frequency.

## Implementation

It may be desirable, as a preliminary step, to <code>#define</code> variables for certain macros. For example, I defined "LED1" as BIT0, which is a macro which represents the hex code 0x0001h.
 
The first necessary step in any implementation is to disable the watchdog timer using the following line of code: <code></code> Depending on the microprocessor, the next step may involve disabling the default GPIO high-impedance mode. To do this, use this line of code: <code></code>.

Before writing any functions, the digital I/O registers must be set up. There are different digital I/O parameters for different microprocessors. See the appropriate sections below for the microprocessor being used. Any Select registers must be set to 0 to enable the I/O function on the pin. The Direction register must be set to 1 to enable output on the pin. The Output register must be initially set to 0 on the pin. To change each of these register values, the programmer must first mask the value with the bit location on P1, in this case BIT0. This will ensure no other register values are unecessarily altered.

Finally, the code. This program polls for changes in the unsigned integer variable "count". The count variable will increment at the end of each loop. Each time count reaches 1000, the LED will toggle by xor'ing the last value in P1OUT at BIT0. The count variable will also be reset.

### MSP430F5529 & MSP430G2553

There is one Select register. It is not necessary to disable GPIO high-impedance mode. 

### MSP430FRx

There are two Select registers, PxSEL0 and PxSEL1. The GPIO high-impedance mode must be disabled.

 
