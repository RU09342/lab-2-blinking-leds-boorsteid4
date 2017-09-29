# Button Blink

A button is used to toggle an LED on and off. When the user presses the button, the LED will remain high until the button is released. On some boards, buttons are mapped to specific LEDs if there are multiple buttons.

## Implementation

The setup of the Select, Direction, and Output registers corresponds with the previous two exercises. What is different here is the addition of the Input and Resistor-enable registers, PxIN and PxREN, respectively. These registers must be set up properly so the program can read input from a button, for instance. To do this, the Direction register must be cleared (set to 0) on the same pin as the button. Following this, the a pull-resistor must be set on the button. This is as common a practice in microprocessors as in normal electronics. Putting either a pull-up or pull-down resistor on an LED or a switch will ensure the resulting voltage dropped across the device becomes a known value. In fact, every I/O pin on the MSP430 family devices has a configurable pull-resistor.

A pull-up resistor is needed on the button pin so that when the button is pressed, the voltage across the output pin (the LED) is Vcc - 0.3 (3.3 - 0.3 = ~3 V). To accomplish this, first set (to 1) the corresponding bit in the Resistor-enable register. Next, set the same bit on the Output register. This will tell the compiler to configure the resistor to pull up. With this having been done, the pin is now set up as an input.

We're not done, yet. Now, the button pressed must be synchronized with an LED. This can be implemented in a polling loop with an <code>if</code> statement that checks for equality between the inverse of the button pin and the same bit in the Input register. This signifies that the button has been pressed. From there, any control statements can be added to control the LED blink rate.

### Debouncing

A second-order design problem with pushbuttons is bouncing. Pushbuttons are mechanical switches that use a flimsy metal contact to complete a circuit whenever pressed. This flimsy sheet has a habit of reverberating, causing unintended shorts. On an oscilloscope, this can be seen in the form of hundreds of square voltage spikes before returning to a steady state.

To work around this, we can account for these spikes by taking a longer sample of button presses. Whereas the implementation polls for one button press, we can poll for 1000 button "presses" and add them to a float variable <code>sample</code>. If this float is close to 1000, we can assume the user has just pressed the button. Then the rest code will run as intended. This was implemented on the MSP4302311.

### EXTRA WORK: Variable Frequency LED

A program which sets the blink rate of an LED with each button press was implemented on the MSP430FR2311. An integer variable <code>x</code> represents the delay between blinks, and <code>y</code> is the counter a which increments to x. A switch statement keeps track of how many times the button has been pressed and sets <code>x</code> to a value based on this number. The higher the value of the delay, the slower the LED will blink. So, pressing once enables fast blink; twice, medium blink; three times, slow blink. This process will repeat for additional button presses.