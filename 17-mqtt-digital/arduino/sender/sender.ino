/**************************************************************
 * MQTT Sender for ESP32 - Digital Sensor
 * Author: Paolo Almario
 * ------------------------------------------------------------
 * This program sends (publishes) sensor data to an online
 * MQTT broker (default: broker.hivemq.com).
 *
 * Designed for educational and artistic projects where multiple
 * ESP32s communicate with each other or with other systems
 * (TouchDesigner, Node-RED, n8n, etc.) via the Internet.
 *
 * IMPORTANT:
 * Change the MQTT topic name to be unique to your project
 * (e.g., "myproject/sensor1" or "workshop/group1/button").
 ***************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>

/* ============================================================
   CONFIGURATION SECTION - Modify according to your needs
   ============================================================ */

// --- WiFi Credentials ---
const char* WIFI_SSID     = "YourNetworkName";  // WiFi network name
const char* WIFI_PASSWORD = "YourPassword";      // WiFi password

// --- MQTT Server Settings ---
const char* MQTT_SERVER   = "broker.hivemq.com"; // Free public broker
const int   MQTT_PORT     = 1883;                // Port: 1883 (unencrypted)
const char* MQTT_CLIENTID = "ESP32-Sender-01";   // Must be unique per device

// --- MQTT Topics ---
// Change this value to avoid conflicts with other users
const char* MQTT_PUBLISH_TOPIC   = "myproject/button";
const char* MQTT_SUBSCRIBE_TOPIC = "";  // Leave empty if not receiving

// --- Send Interval (milliseconds) ---
const unsigned long PUBLISH_INTERVAL = 500;  // 500 ms = 2 sends per second

// --- Sensor Configuration ---
const int SENSOR_PIN = 5;         // Digital pin for the sensor/button
const bool DEBUG_SERIAL = true;   // Show info in Serial Monitor

/* ============================================================
   END CONFIGURATION SECTION
   ============================================================ */

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

// --- WiFi Connection ---
void setup_wifi() {
  if (DEBUG_SERIAL) {
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);
  }
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (DEBUG_SERIAL) Serial.print(".");
  }
  if (DEBUG_SERIAL) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

// --- MQTT Reconnection ---
void reconnect() {
  while (!client.connected()) {
    if (DEBUG_SERIAL) Serial.print("Connecting to MQTT server...");
    if (client.connect(MQTT_CLIENTID)) {
      if (DEBUG_SERIAL) Serial.println("connected.");
      if (strlen(MQTT_SUBSCRIBE_TOPIC) > 0)
        client.subscribe(MQTT_SUBSCRIBE_TOPIC);
    } else {
      if (DEBUG_SERIAL) {
        Serial.print("Failed, error code = ");
        Serial.print(client.state());
        Serial.println(" -> retrying in 5 seconds");
      }
      delay(5000);
    }
  }
}

// --- Setup ---
void setup() {
  pinMode(SENSOR_PIN, INPUT);
  if (DEBUG_SERIAL) Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

// --- Main Loop ---
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > PUBLISH_INTERVAL) {
    lastMsg = now;

    int sensorValue = digitalRead(SENSOR_PIN);
    char msg[16];
    snprintf(msg, sizeof(msg), "%d", sensorValue);

    client.publish(MQTT_PUBLISH_TOPIC, msg);

    if (DEBUG_SERIAL) {
      Serial.print("Published to ");
      Serial.print(MQTT_PUBLISH_TOPIC);
      Serial.print(": ");
      Serial.println(msg);
    }
  }
}
