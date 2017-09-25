# Simple Blink

A single LED (on any board LED1) is blinked at a specific frequency.

## Compatability

This program works with all boards in this repository.

### Disabling GPIO Default Mode

On all boards except the G2553, the GPIO power-on default high-impedance mode must be deactivated for the program to work. This is implemented by the following line of code:

<code>PM5CTL0 &= ~LOCKLPM5;</code>

## Implementation

This function will begin at program startup. A specific LED will begin blinking without user input.