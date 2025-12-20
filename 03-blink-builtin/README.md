# Blink Builtin LED

The classic "Hello World" of embedded programming. Blinks the ESP32's built-in LED to verify programming workflow without external components.

## Schematic

![Wiring diagram](schematic.png)

No external wiring required. Uses onboard LED connected to GPIO 2.

## Hardware Required

- ESP32 development board (any model with onboard LED)
- USB cable

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| Built-in LED | GPIO 2 |

## Usage

### Arduino IDE
1. Open `arduino/blink/blink.ino`
2. Select board: ESP32 Dev Module
3. Upload

### PlatformIO
1. Open `platformio/` folder
2. Build and upload

## Expected Behavior

The built-in LED blinks with a 1-second on/off rhythm. LED turns on for 1 second, then off for 1 second, continuously.
