/*
 * HTTP Requests and APIs - ESP32 Fundamentals
 * Connecting ESP32 to WiFi and fetching data from public APIs
 *
 * This exercise teaches:
 * - WiFi connection on ESP32
 * - Making HTTP GET requests
 * - Parsing JSON responses with ArduinoJson
 * - Working with public weather APIs (Open-Meteo)
 * - Extracting and displaying API data
 *
 * Libraries required:
 * - WiFi.h (built-in)
 * - HTTPClient.h (built-in)
 * - ArduinoJson.h (install via Library Manager)
 *
 * Author: Paolo Almario
 * License: CC BY-SA 4.0
 * https://github.com/paoloalmario/esp32-fundamentals
 */

#include <WiFi.h>          // WiFi connection management
#include <HTTPClient.h>    // Enables HTTP requests
#include <ArduinoJson.h>   // For parsing JSON responses

const char* WIFI_SSID = "YourNetworkName";     // WiFi network name
const char* WIFI_PASSWORD = "YourPassword";     // WiFi password

unsigned long lastRequest = 0;                  // Records last request time
const unsigned long interval = 10 * 1000;       // Interval between requests (10 seconds)

void setup() {
  Serial.begin(115200);                         // Start serial communication
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);         // Connect to WiFi network
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {       // Wait for complete connection
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi network!");
}

void loop() {
  unsigned long now = millis();                 // Get elapsed time since startup

  if (now - lastRequest >= interval) {          // Check if interval elapsed

    if (WiFi.status() == WL_CONNECTED) {        // Verify ESP32 is still connected
      HTTPClient http;                          // Create HTTPClient object

      // API endpoint to query: Open-Meteo
      http.begin("https://api.open-meteo.com/v1/forecast?latitude=48.4&longitude=-71.0&current_weather=true");

      int httpCode = http.GET();                // Send GET request to server

      if (httpCode > 0) {                       // If HTTP response is valid
        Serial.printf("HTTP %d\n", httpCode);   // Display response code (e.g., 200)
        String payload = http.getString();      // Get JSON response body

        // --- JSON parsing with ArduinoJson ---
        StaticJsonDocument<1024> doc;           // Create memory space for JSON
        DeserializationError error = deserializeJson(doc, payload);  // Convert text to JSON structure

        if (error) {
          Serial.print("JSON parsing failed: ");
          Serial.println(error.f_str());
        } else {
          // Extract useful fields from JSON
          float temperature   = doc["current_weather"]["temperature"];
          float windspeed     = doc["current_weather"]["windspeed"];
          int winddirection   = doc["current_weather"]["winddirection"];
          bool is_day         = doc["current_weather"]["is_day"];
          const char* timeStr = doc["current_weather"]["time"];

          // Display extracted values in serial monitor
          Serial.println("---- Current Weather ----");
          Serial.printf("Temperature: %.1f °C\n", temperature);
          Serial.printf("Wind speed: %.1f km/h\n", windspeed);
          Serial.printf("Wind direction: %d°\n", winddirection);
          Serial.printf("Daytime: %s\n", is_day ? "Yes" : "No");
          Serial.printf("Time: %s\n", timeStr);
          Serial.println("--------------------------\n");
        }
      } else {
        // If HTTP request failed
        Serial.printf("Request failed: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();                                // End HTTP session cleanly
    }

    lastRequest = now;                           // Record request time
  }

  delay(100);                                    // Small pause to avoid too-fast loop
}
