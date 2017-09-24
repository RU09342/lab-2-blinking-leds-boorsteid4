# Simple Blink
For starters, you will need to blink one of the on-board LED's at a particular rate. It is up to you to determine what rate you want to blink it at, however it has to be symmetrical (50% Duty Cycle), meaning equal times on and off. You should attempt multiple different speeds before moving on to the next part of the lab.

## YOU NEED TO CREATE THE FOLLOWING FOLDERS
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## How to not damage your processor
Remember that your microprocessors are not hooked up to a nuclear power plant and they can only provide a finite amount of current and power to your attached devices. For each of your processors you should see what the maximum supply current is for the digital output pins and note it in your designs. Diodes are an interesting device where the V-I curve becomes almost a short circuit after only a couple volts. If you have a diode biased to operate at say 1 volt above its turn on voltage, you are going to be drawing quite a bit of amperage. 

Before you actually begin this lab, take the time to mess around with the simulation below and understand what the importance of the series resistance is in the design. What does the resistance prevent from happening? Does having this resistance impact the performance of the LED?

<a href="http://everycircuit.com/circuit/5180823226810368">LED Current - EveryCircuit</a><br>
<iframe width="560" height="360" src="http://everycircuit.com/embed/5180823226810368" frameborder="0"></iframe>

## README
Remember to replace this README with your README once you are ready to submit. I would recommend either making a copy of this file or taking a screen shot. There might be a copy of all of these README's in a folder on the top level depending on the exercise.

## Extra Work
Since this is so basic, there are a few things which might be interesting to implement.

### UART Control: Single Character
For starters, it would be interesting to tie in some of the UART code that was used before into this project. You might want to have the speed of the blinking controlled by a character sent over UART. For example, 's' could be a slow setting, 'm' could be medium speed, 'f' could be fast, and 'o' could be off.

### UART Control: Rate Number
Instead of depending on a character, what if we wanted to send a blinking period in milliseconds? So instead of 's', you could send something like '100' which corresponds to a 100 millisecond delay between the time the LED turns on again. Before you decide to tackle this, I would take a look at using a logic analyzer to see exactly what your computer is sending to your microprocessor. Also remember that the code previously provided will only service the UART Buffer one character at a time.