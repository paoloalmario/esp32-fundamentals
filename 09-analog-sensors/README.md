# Analog Sensors (Potentiometer and Photoresistor)

Learn to read continuous analog values using the ESP32's 12-bit ADC (0-4095 range) with potentiometer and photoresistor sensors.

## Schematic

![Wiring diagram](schematic.png)

## Hardware Required

- ESP32-WROOM-32 development board
- Potentiometer module (DFRobot, 3-pin: VCC/Signal/GND)
- Photoresistor module (LDR) (DFRobot, 3-pin: VCC/Signal/GND)
- 3x jumper wires per sensor
- USB cable

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| Potentiometer/LDR Signal | GPIO 4 (ADC1_CH0) |
| Sensor VCC | 3.3V |
| Sensor GND | GND |

## Usage

### Arduino IDE
1. Open `arduino/potentiometer/potentiometer.ino`
2. Select board: ESP32 Dev Module
3. Upload and open Serial Monitor at 115200 baud

### PlatformIO
1. Open `platformio/` folder
2. Build and upload

## Expected Behavior

Serial Monitor displays continuous analog readings (0-4095) at 10 samples per second. Turning the potentiometer knob or covering the photoresistor changes the values in real-time.
