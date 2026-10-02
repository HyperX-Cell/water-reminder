# Water Reminder

A simple Arduino-based water reminder with a 16x2 I2C LCD, physical drink button, and buzzer.

## Hardware

- Arduino Nano
- 16x2 I2C LCD
- 5V active buzzer
- 12mm momentary push button
- 400-point breadboard
- Jumper wires
- USB cable/power

## Wiring

### LCD
- VCC -> 5V
- GND -> GND
- SDA -> A4
- SCL -> A5

### Button
- One side -> D2
- Other side -> GND

The code uses the Arduino's internal pull-up resistor.

### Buzzer
- Positive -> D8
- Negative -> GND

## Behaviour

The LCD shows the time since the last recorded drink. When the reminder interval is reached, the buzzer sounds and the display asks you to drink water.

Press the button after drinking. The timer resets and the daily drink count increases.

## Prototype

This project is designed to be built on a breadboard first. No soldering is required for the initial prototype.

## Future ideas

- Daily drink goal
- RTC module for keeping time after power loss
- Larger enclosure
- Adjustable reminder interval
- LED reminder
- Battery power
