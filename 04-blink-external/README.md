# Blink External LED

First physical circuit: connecting an external LED to an ESP32 GPIO pin. Introduces breadboard wiring, LED polarity, and current-limiting resistors.

## Schematic

<img src="schematic.png" alt="Wiring diagram" width="500">

## Hardware Required

- ESP32 development board
- Breadboard
- LED (any color)
- 220-330Ω resistor
- Jumper wires
- USB cable

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| LED (via resistor) | GPIO 13 |
| LED cathode (short leg) | GND |

## Usage

### Arduino IDE
1. Open `arduino/blink-external/blink-external.ino`
2. Select board: ESP32 Dev Module
3. Upload

### PlatformIO
1. Open `platformio/` folder
2. Build and upload

## Expected Behavior

The external LED blinks with a 500ms on/off rhythm. LED turns on for 500ms, then off for 500ms, continuously.
