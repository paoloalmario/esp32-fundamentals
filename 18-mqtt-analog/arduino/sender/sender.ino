/**************************************************************
 * MQTT Sender for ESP32 - Analog Sensor
 * Author: Paolo Almario
 * ------------------------------------------------------------
 * Reads an analog sensor (photoresistor, potentiometer, etc.)
 * and publishes the value to an MQTT broker.
 *
 * IMPORTANT:
 * Change the MQTT topic name to be unique to your project.
 ***************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>

/* ============================================================
   CONFIGURATION SECTION
   ============================================================ */

// --- WiFi Credentials ---
const char* WIFI_SSID     = "YourNetworkName";
const char* WIFI_PASSWORD = "YourPassword";

// --- MQTT Server Settings ---
const char* MQTT_SERVER   = "broker.hivemq.com";
const int   MQTT_PORT     = 1883;
const char* MQTT_CLIENTID = "ESP32-AnalogSender-01";

// --- MQTT Topics ---
const char* MQTT_PUBLISH_TOPIC = "myproject/light";

// --- Send Interval (milliseconds) ---
const unsigned long PUBLISH_INTERVAL = 500;

// --- Sensor Configuration ---
const int SENSOR_PIN = 34;        // Analog pin (GPIO 34, 35, 36, or 39)
const bool DEBUG_SERIAL = true;

/* ============================================================
   END CONFIGURATION SECTION
   ============================================================ */

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

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

void reconnect() {
  while (!client.connected()) {
    if (DEBUG_SERIAL) Serial.print("Connecting to MQTT server...");
    if (client.connect(MQTT_CLIENTID)) {
      if (DEBUG_SERIAL) Serial.println("connected.");
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

void setup() {
  if (DEBUG_SERIAL) Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > PUBLISH_INTERVAL) {
    lastMsg = now;

    // Read analog value (0-4095 on ESP32)
    int sensorValue = analogRead(SENSOR_PIN);
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
