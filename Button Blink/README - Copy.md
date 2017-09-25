# Button Blink
Now that you have looked at blinking the LED from some built in delay, but what if we wanted to control the state of the LED by a button? You may think "Why would I need a Microcontroller to perform the job of a switch?". And that is where you come in. The bare minimum for this part of the lab is to essentially replicate a switch with your development board.

# YOU NEED TO CREATE THE FOLLOWING FOLDERS
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## README
Remember to replace this README with your README once you are ready to submit. I would recommend either making a copy of this file or taking a screen shot. There might be a copy of all of these README's in a folder on the top level depending on the exercise.

## Extra Work
What can we do to make this a little bit more worthy of needing a microcontroller.

### Button Based Speed Control
Much like the UART controlled speed, what if you could cycle between speeds based on a button press? The speed could progress through a cycle of "Off-Slow-Medium-Fast" looping back when you hit the end.

### Color Change
What if upon a button press, the LED which was blinking changed. Some of the development boards contain two LEDs, so you could swap between a Red and a Green LED.