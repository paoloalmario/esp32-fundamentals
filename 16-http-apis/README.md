# HTTP Requests and APIs

Connecting ESP32 to WiFi and fetching data from public APIs. Demonstrates HTTP GET requests, JSON parsing with ArduinoJson, and displaying weather data from Open-Meteo API.

## Hardware Required

- ESP32-WROOM-32
- WiFi network with internet access
- USB cable

## Pin Connections

No external components required. This module uses only WiFi connectivity.

## Usage

### Arduino IDE
1. Open `arduino/http-apis/http-apis.ino`
2. Modify `WIFI_SSID` and `WIFI_PASSWORD` in code
3. Install ArduinoJson library (Sketch > Include Library > Manage Libraries)
4. Select board: ESP32 Dev Module
5. Upload
6. Open Serial Monitor (115200 baud)

### PlatformIO
1. Open `platformio/` folder in VS Code
2. Modify `WIFI_SSID` and `WIFI_PASSWORD` in `src/main.cpp`
3. Build and upload (ArduinoJson dependency auto-installed)
4. Open Serial Monitor

## Expected Behavior

ESP32 connects to WiFi network, then queries Open-Meteo weather API every 10 seconds. Serial Monitor displays:
- HTTP response code (200 = success)
- Current temperature (°C)
- Wind speed (km/h)
- Wind direction (degrees)
- Daytime status (yes/no)
- Timestamp

Default location: Saguenay, Quebec (lat 48.4, lon -71.0). Modify coordinates in API URL to change location.
