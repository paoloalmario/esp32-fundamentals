# ESP-NOW with ToF Sensor

Wireless distance sensing with ESP-NOW communication protocol. One ESP32 reads a VL53L0X ToF sensor and transmits distance measurements to one or more receiver ESP32s without requiring WiFi network infrastructure.

## Schematic

![Sender](schematic-sender.png)
![Receiver](schematic-receiver.png)

## Hardware Required

**Sender ESP32:**
- ESP32-WROOM-32
- VL53L0X ToF sensor
- Jumper wires
- USB cable

**Receiver ESP32:**
- ESP32-WROOM-32
- LED (optional)
- 220Ω resistor (optional)
- Jumper wires
- USB cable

## Pin Connections

**Sender (ESP32 + ToF):**

| Component | ESP32 Pin |
|-----------|-----------|
| VL53L0X SDA | GPIO 21 |
| VL53L0X SCL | GPIO 22 |
| VL53L0X VCC | 3.3V |
| VL53L0X GND | GND |

**Receiver (ESP32 + LED):**

| Component | ESP32 Pin |
|-----------|-----------|
| LED Anode (+) | GPIO 2 (built-in) |
| LED Cathode (-) | GND (via 220Ω resistor) |

## Usage

### Arduino IDE

**Sender:**
1. Open `arduino/sender/sender.ino`
2. Update MAC addresses in `receiverList[][]` (get from receiver's Serial Monitor)
3. Select board: ESP32 Dev Module
4. Upload

**Receiver:**
1. Open `arduino/receiver/receiver.ino`
2. Select board: ESP32 Dev Module
3. Upload
4. Open Serial Monitor (115200 baud) to see MAC address

### PlatformIO

**Sender:**
1. Open `platformio-sender/` folder in VS Code
2. Update MAC addresses in `src/main.cpp`
3. Build and upload

**Receiver:**
1. Open `platformio-receiver/` folder in VS Code
2. Build and upload

## Expected Behavior

**Sender:** Reads distance from ToF sensor every second, transmits to all receivers, displays confirmation in Serial Monitor.

**Receiver:** Receives distance values, displays in Serial Monitor, blinks LED when distance < 200mm (threshold configurable).
