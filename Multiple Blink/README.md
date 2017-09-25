# Multiple Blink

Multiple LEDs blink at different rates.

## Compatability

This program works with all boards in this repository.

### Disabling GPIO Default Mode

On all boards except the G2553, the GPIO power-on default high-impedance mode must be deactivated for the program to work. This is implemented by the following line of code:

<code>PM5CTL0 &= ~LOCKLPM5;</code>

## Implementation

This function will begin at program startup. Two or more LEDs will begin blinking at different rates.