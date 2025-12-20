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

Complete tutorials organized in progressive learning order.

**Note:** Modules 00-02 and 13 are conceptual introductions (no code). See the [full curriculum](https://paoloalmario.com/open-pedagogy/) for written content.

| Module | Title | Description | Status |
|--------|-------|-------------|--------|
| 00 | Physical Computing | Foundational concepts | Conceptual |
| 01 | ESP32 Introduction | Hardware specs and pinouts | Conceptual |
| 02 | Workflow | Arduino IDE and PlatformIO setup | Conceptual |
| 03 | Blink Builtin | Built-in LED blinking | Complete |
| 04 | Blink External | External LED control | Planned |
| 05 | Blink Multiple | Multiple LED patterns | Planned |
| 06 | Relay | High-power device control | Planned |
| 07 | Button | Digital input with serial output | Complete |
| 08 | Button LED | Button-controlled LED | Complete |
| 09 | Analog Sensors | Potentiometer/sensor reading | Complete |
| 10 | LDR LEDs | Light-dependent resistor control | Planned |
| 11 | ToF Sensor | VL53L0X distance sensor | Complete |
| 12 | ToF LEDs | Distance-controlled LED indicator | Complete |
| 13 | ESP-NOW Intro | Peer-to-peer protocol basics | Conceptual |
| 14 | ESP-NOW MAC | Get MAC address for pairing | Complete |
| 15 | ESP-NOW ToF | Wireless sensor communication | Complete |
| 16 | HTTP APIs | Web API consumption | Planned |
| 17 | MQTT Digital | Digital sensor via MQTT | Complete |
| 18 | MQTT Analog | Analog sensor via MQTT | Complete |

## Getting Started

### Arduino IDE

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support: File > Preferences > Additional Board URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Install ESP32: Tools > Board > Boards Manager > "esp32"
4. Select: Tools > Board > ESP32 Dev Module
5. Some boards require setting baud rate: Tools > Upload Speed > 115200
6. Open `.ino` file and upload

### PlatformIO

1. Install [VS Code](https://code.visualstudio.com/) + [PlatformIO extension](https://platformio.org/install/ide?install=vscode)
2. Open exercise folder containing `platformio.ini`
3. Click Upload (arrow icon)

## License

[CC BY-SA 4.0](LICENSE) - Free to use, adapt, and share with attribution.

## Author

**Paolo Almario** - [paoloalmario.com](https://paoloalmario.com)
