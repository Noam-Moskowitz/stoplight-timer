# Development Log

This document is meant to track my progress throughout the Stoplight Timer project, including what I've tried, what worked (and what didn't), and anything interesting I've learned along the way.

## V1 — Initial Implementation

### First Attempt — Putting Everything Together

My first attempt was to take the [timer code](https://github.com/Noam-Moskowitz/stoplight-timer/blob/20cc8ad87fa04e70f6ca057122f65a9baeb8a97c/main/main.ino) I'd written and pair it with my original [circuit wiring](https://github.com/Noam-Moskowitz/stoplight-timer/blob/20cc8ad87fa04e70f6ca057122f65a9baeb8a97c/main/circut_state.svg) (commit `20cc8ad`).

And... it didn't work.

At first, I thought the issue was probably my code, which isn't perfect and honestly could still be part of the problem. But after looking into it a little more, I realized there was a bigger issue with how I'd wired the button.

So instead of trying to figure out everything that was wrong with the project at once, I figured I'd try something simpler. Before worrying about the timer, **can I even wire a button properly and reliably track when it's being pressed?**

### Second Attempt — Getting the Button Working

That's where [manual_switch.ino](https://github.com/Noam-Moskowitz/stoplight-timer/blob/20cc8ad87fa04e70f6ca057122f65a9baeb8a97c/manual_switch/manual_switch.ino) came in (commit `20cc8ad`).

I started by stripping the circuit down to just the ESP32 and a push button. The idea was to use `digitalRead()` to read the button's state, store the result in a `buttonState` variable, and print it to the Serial Monitor.

Pretty simple, right? Well, apparently not, because even that wasn't working properly.

After a bit of research, I realized I'd completely left out a resistor in the button's circuit. Without a pull-up or pull-down resistor, the input pin can be left floating, meaning it doesn't have a reliable HIGH or LOW reading.

I also found out that the ESP32 actually has internal pull-up resistors that can be enabled through the code, although I haven't tried that yet.

Once I added the resistor, I was finally able to read the button's state much more reliably.

### Third Attempt — Testing the Button With LEDs

Now that I could actually read the button's state, I wanted to take it a little further and see how reliable it was.

I wired up my three LEDs and added some code to track how many times the button had been pressed using a `timesPressed` variable.

The idea was to increment the variable every time the button was pressed, and once it reached 3, the next press would reset it back to 0.

I then used a `switch` statement to control which LEDs should light up depending on that value:

| `timesPressed` | LED State |
|---|---|
| 0 | All LEDs off |
| 1 | Green |
| 2 | Green + Yellow |
| 3 | Green + Yellow + Red |

This let me test a few things at once: reading the button's state, counting button presses, and controlling multiple GPIO output pins based on that count.

And as you can see in the photos and video below, **it actually worked!**

### Test Results

Here are the four states of the circuit:

**State 0 — All LEDs Off**

![All LEDs Off](https://raw.githubusercontent.com/Noam-Moskowitz/stoplight-timer/main/manual_switch/manual_switch_state_0.jpeg)

**State 1 — Green LED**

![Green LED](https://raw.githubusercontent.com/Noam-Moskowitz/stoplight-timer/main/manual_switch/manual_switch_state_1.jpeg)

**State 2 — Green + Yellow LEDs**

![Green and Yellow LEDs](https://raw.githubusercontent.com/Noam-Moskowitz/stoplight-timer/main/manual_switch/manual_switch_state_2.jpeg)

**State 3 — All Three LEDs**

![All Three LEDs](https://raw.githubusercontent.com/Noam-Moskowitz/stoplight-timer/main/manual_switch/manual_switch_state_3.jpeg)

**Video — Manual Switch in Action**

[Watch the button and LEDs in action](https://github.com/Noam-Moskowitz/stoplight-timer/blob/main/manual_switch/manual_switch_in_action.mp4)

