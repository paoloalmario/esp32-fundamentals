# ESP32 Fundamentals

Open-source tutorials for microcontroller programming with ESP32.

## Structure

Each exercise includes both **Arduino IDE** and **PlatformIO** versions:

```
exercise-name/
├── arduino/
│   └── exercise-name/
│       └── exercise-name.ino
├── platformio/
│   ├── platformio.ini
│   └── src/
│       └── main.cpp
└── schematic.png
```

## Modules

### 01-gpio
Digital input/output fundamentals.

| Exercise | Description |
|----------|-------------|
| blink | Built-in LED blinking |
| button | Button reading with serial output |
| button-led | Button-controlled LED |

### 02-analog
Analog input reading.

| Exercise | Description |
|----------|-------------|
| potentiometer | Read potentiometer/sensor values |

### 03-i2c-sensors
I2C sensor communication.

| Exercise | Description |
|----------|-------------|
| tof-sensor | VL53L0X distance sensor |
| tof-leds | Distance-controlled LED indicator |

## Coming Soon

- **04-esp-now** - Peer-to-peer communication
- **05-mqtt** - Network messaging

## Getting Started

### Arduino IDE

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support: File > Preferences > Additional Board URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Install ESP32: Tools > Board > Boards Manager > "esp32"
4. Select: Tools > Board > ESP32 Dev Module
5. Open `.ino` file and upload

### PlatformIO

1. Install [VS Code](https://code.visualstudio.com/) + [PlatformIO extension](https://platformio.org/install/ide?install=vscode)
2. Open exercise folder containing `platformio.ini`
3. Click Upload (arrow icon)

## License

[CC BY-SA 4.0](LICENSE) - Free to use, adapt, and share with attribution.

## Author

**Paolo Almario** - [paoloalmario.com](https://paoloalmario.com)
