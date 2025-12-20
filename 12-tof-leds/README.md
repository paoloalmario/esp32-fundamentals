# ToF Controls LEDs (Distance-Based Feedback)

Combine VL53L0X distance sensor with LEDs to create a visual proximity indicator, demonstrating distance-to-output mapping.

## Schematic

Schematic includes both VL53L0X ToF sensor wiring (I2C) and 3 LEDs with current-limiting resistors.

## Hardware Required

- ESP32-WROOM-32 development board
- VL53L0X ToF sensor (Time-of-Flight distance sensor)
- 3x LEDs (any color)
- 3x resistors (220-330Ω for LED current limiting)
- Jumper wires
- USB cable

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| VL53L0X SDA | GPIO 21 |
| VL53L0X SCL | GPIO 22 |
| VL53L0X VIN | 3.3V |
| VL53L0X GND | GND |
| LED1 (Medium distance) | GPIO 13 |
| LED2 (Close distance) | GPIO 12 |
| LED3 (Very close distance) | GPIO 14 |

## Usage

### Arduino IDE
1. Install library: Adafruit_VL53L0X (via Library Manager)
2. Open `arduino/tof-leds/tof-leds.ino`
3. Select board: ESP32 Dev Module
4. Upload and open Serial Monitor at 115200 baud

### PlatformIO
1. Open `platformio/` folder
2. Build and upload (library auto-installed via platformio.ini)

## Expected Behavior

LEDs illuminate based on distance measurements:
- 0-149mm: 3 LEDs (very close)
- 150-249mm: 2 LEDs (close)
- 250-499mm: 1 LED (medium)
- 500mm+: 0 LEDs (far)

Serial Monitor displays distance in millimeters at 20 samples per second. Move your hand toward/away from sensor to see LEDs respond like a parking sensor.
