# Button Controls LED

Combines digital input and output: button press controls LED state. Foundational pattern for interactive systems using conditional logic.

## Schematic

Two-component circuit: button with internal pull-up on GPIO 13, LED with resistor on GPIO 12.

## Hardware Required

- ESP32 development board
- Pushbutton (momentary switch)
- LED (any color)
- 220-330Ω resistor (for LED)
- Breadboard and jumper wires
- USB cable

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| Button terminal 1 | GPIO 13 |
| Button terminal 2 | GND |
| LED anode (via resistor) | GPIO 12 |
| LED cathode | GND |

## Usage

### Arduino IDE
1. Open `arduino/button-led/button-led.ino`
2. Select board: ESP32 Dev Module
3. Upload

### PlatformIO
1. Open `platformio/` folder
2. Build and upload

## Expected Behavior

LED follows button state:
- **LED ON** when button is pressed
- **LED OFF** when button is released

Serial Monitor displays "Button + LED started" message. This demonstrates the input-process-output model: ESP32 reads button state and decides LED behavior based on conditional logic.
