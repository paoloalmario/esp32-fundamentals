# ESP-NOW MAC Address Discovery

Retrieve and display the ESP32's unique MAC addresses (STA and AP modes) for use in ESP-NOW peer-to-peer communication.

## Hardware Required

- ESP32 development board (any variant)
- USB cable

No external components required.

## Pin Connections

No physical wiring needed. This is a software-only exercise.

## Usage

### Arduino IDE
1. Open `arduino/mac-address/mac-address.ino`
2. Select board: ESP32 Dev Module
3. Upload and open Serial Monitor at 115200 baud

### PlatformIO
1. Open `platformio/` folder
2. Build and upload

## Expected Behavior

Serial Monitor displays two MAC addresses:
- **STA MAC**: Used when ESP32 acts as WiFi client (use this for ESP-NOW)
- **AP MAC**: Used when ESP32 acts as WiFi hotspot (typically STA MAC + 1 in last byte)

Example output:
```
STA MAC: 84:CC:A8:42:91:7B
AP  MAC: 84:CC:A8:42:91:7C
```

Record your STA MAC address for use in Module 15 (ESP-NOW communication).
