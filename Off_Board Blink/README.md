# Off Board Blink

Using essentially the same code as Multiple Blink, two off-board LEDs are blinked at a particular rate.

## Implementation

This code uses the same code as Multiple Blink, but the pins have been changed to P1.4 and P1.7 since they are open GPIO. The G2553 is the only board that can be used for this exercise because the MSP430G2553 IC is removable. Place the chip on a breadboard, and ground two LEDs. Connect a 1 kiloOhm resistor from each pin to the LEDs to complete the circuit. When connecting VCC, use a 3.3 V input, as this is the input voltage to the chip when it is on the board. A 10 Ohm resistor is used to jump RST and VCC, since RST operates on a negative edge, and jumping with VCC will disable reset. A bulk cap of .1 microF and a bypass cap of .01 microF are in parallel with the VCC line and used to stabilize the input voltage. Both caps are grounded.

<img src="offboard.png" alt="Off-Board LED Circuit" style="width:1894;height:143">