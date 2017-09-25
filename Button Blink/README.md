# Button Blink

A button is used to toggle an LED on and off. When the user presses the button, the LED will remain high until the button is released. On some boards, buttons are mapped to specific LEDs if there are multiple buttons.

## Compatability

This program works with all boards in this repository.

### Disabling GPIO Default Mode

On all boards except the G2553, the GPIO power-on default high-impedance mode must be deactivated for the program to work. This is implemented by the following line of code:

<code>PM5CTL0 &= ~LOCKLPM5;</code>

## Implementation

An LED will turn on when the corresponding pushbutton is activated. LED1 usually maps with S1 (Button 1) and LED2 usually maps with S2 (Button 2).