# MQTT with Digital Sensors

Internet-based communication between ESP32 devices using MQTT publish/subscribe protocol. One ESP32 publishes button state to HiveMQ public broker, another ESP32 subscribes to the topic and controls an LED.

## Schematic

<img src="schematic-sender.png" alt="Sender" width="500">
<img src="schematic-receiver.png" alt="Receiver" width="500">

## Hardware Required

**Publisher ESP32:**
- ESP32-WROOM-32
- Push button
- 10kΩ resistor (pull-down)
- Jumper wires
- WiFi network access
- USB cable

**Subscriber ESP32:**
- ESP32-WROOM-32
- LED
- 220Ω resistor
- Jumper wires
- WiFi network access
- USB cable

## Pin Connections

**Publisher (Button):**

| Component | ESP32 Pin |
|-----------|-----------|
| Button (one side) | GPIO 5 |
| Button (other side) | GND |
| 10kΩ resistor (pull-down) | GPIO 5 to GND |

**Subscriber (LED):**

| Component | ESP32 Pin |
|-----------|-----------|
| LED Anode (+) | GPIO 2 |
| LED Cathode (-) | GND (via 220Ω resistor) |

## Usage

### Arduino IDE

**Publisher:**
1. Open `arduino/sender/sender.ino`
2. Modify `WIFI_SSID`, `WIFI_PASSWORD`, and `MQTT_PUBLISH_TOPIC` (use unique topic name)
3. Install PubSubClient library (Sketch > Include Library > Manage Libraries)
4. Select board: ESP32 Dev Module
5. Upload

**Subscriber:**
1. Open `arduino/receiver/receiver.ino`
2. Modify `WIFI_SSID`, `WIFI_PASSWORD`, and `MQTT_SUBSCRIBE_TOPIC` (must match publisher)
3. Install PubSubClient library
4. Select board: ESP32 Dev Module
5. Upload

### PlatformIO

**Publisher:**
1. Open `platformio-sender/` folder
2. Modify WiFi and MQTT settings in `src/main.cpp`
3. Build and upload

**Subscriber:**
1. Open `platformio-receiver/` folder
2. Modify WiFi and MQTT settings in `src/main.cpp`
3. Build and upload

## Expected Behavior

**Publisher:** Connects to WiFi and MQTT broker (broker.hivemq.com), reads button state, publishes 1 (pressed) or 0 (released) to topic every 500ms.

**Subscriber:** Connects to WiFi and MQTT broker, subscribes to topic, turns LED ON when button pressed (value > 0), OFF when released (value = 0).

**Important:** Change `MQTT_PUBLISH_TOPIC` to unique name (e.g., "students/yourname/button") to avoid conflicts with other users on public broker.
