# Button Input

Reads a pushbutton state and displays values in Serial Monitor. First introduction to digital input and serial debugging.

## Schematic

Simple circuit: button between GPIO 13 and GND. Uses internal pull-up resistor (no external resistor needed).

## Hardware Required

- ESP32 development board
- Pushbutton (momentary switch)
- Breadboard and jumper wires
- USB cable

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| Button terminal 1 | GPIO 13 |
| Button terminal 2 | GND |

## Usage

### Arduino IDE
1. Open `arduino/button/button.ino`
2. Select board: ESP32 Dev Module
3. Upload
4. Open Serial Monitor (115200 baud)

### PlatformIO
1. Open `platformio/` folder
2. Build and upload
3. Open Serial Monitor (115200 baud)

## Expected Behavior

Serial Monitor displays button state continuously:
- **1** when button is released (pull-up keeps pin HIGH)
- **0** when button is pressed (pin pulled to GND)

State updates every 100ms to avoid flooding the serial output.
