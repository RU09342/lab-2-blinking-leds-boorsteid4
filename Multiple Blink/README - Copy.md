# Multiple Blink
Now that we have blinked at least 1 LED, what about blinking multiple LEDS at the same time? The minimum that you need to develop is blinking at least two LEDs at two different rates. Although I am not going to give you a speed, you should probably pick a rate which is visible to a standard human. I really hope that you take this further and perform some of the extra work for this part of the lab exercise.


# YOU NEED TO CREATE THE FOLLOWING FOLDERS
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## README
Remember to replace this README with your README once you are ready to submit. I would recommend either making a copy of this file or taking a screen shot. There might be a copy of all of these README's in a folder on the top level depending on the exercise.

## Extra Work
When you take a look at the development boards, you are limited to what is built into the platform.

### Even More LEDs
Since up to this point you should have hopefully noticed that you are simply just controlling each pin on your processor. So... what is keeping you from putting an LED on each pin? Can you actually control the speed of each of these LEDs?

### Patterned Lights
If you can control a ton of LEDs, what is keeping you from having a little fun? Why not try and make something like a moving face or other moving object in lights. *CAUTION* I would only do this if you have finished the rest of the lab.

### UART Pattern Control
If you have been using UART, could you set which LEDs are on or off based off some UART command? Would you want to send an Array over UART such as [1 0 1 0] or would you want to send a byte that corresponds to the status? Can you not only say which LEDs are on, but also tell them to blink at a particular rate if they were on (so LED1 Blink every 100ms)?