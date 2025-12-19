/**************************************************************
 * MQTT Receiver for ESP32 - LED Control
 * Author: Paolo Almario
 * ------------------------------------------------------------
 * This program receives (subscribes to) data sent via MQTT
 * by another ESP32 (or any other MQTT client).
 *
 * When data is received on a given topic, it is displayed
 * in the Serial Monitor and a digital output (GPIO 2)
 * is turned on or off based on the received value.
 *
 * IMPORTANT:
 * Change the MQTT topic name to match your sender's topic.
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
const char* MQTT_CLIENTID = "ESP32-Receiver-01"; // Must be unique per device

// --- MQTT Topic ---
// Must match the sender's publish topic
const char* MQTT_SUBSCRIBE_TOPIC = "myproject/button";

// --- Output Configuration ---
const int OUTPUT_PIN = 2;          // Pin for LED or relay
const bool DEBUG_SERIAL = true;    // Show info in Serial Monitor

/* ============================================================
   END CONFIGURATION SECTION
   ============================================================ */

WiFiClient espClient;
PubSubClient client(espClient);

// Function declarations
void setup_wifi();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);

// --- Setup ---
void setup() {
  if (DEBUG_SERIAL) Serial.begin(115200);

  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
}

// --- Main Loop ---
void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}

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
      client.subscribe(MQTT_SUBSCRIBE_TOPIC);
      if (DEBUG_SERIAL) {
        Serial.print("Subscribed to topic: ");
        Serial.println(MQTT_SUBSCRIBE_TOPIC);
      }
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

// --- Callback function when message is received ---
void callback(char* topic, byte* payload, unsigned int length) {
  // Copy message to local buffer
  char msg[100];
  memcpy(msg, payload, length);
  msg[length] = '\0';

  // Convert to integer
  String value = String(msg);
  int dataReceived = value.toInt();

  if (DEBUG_SERIAL) {
    Serial.print("Message received on topic ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(dataReceived);
  }

  // Action logic based on received value
  // LED on if value > 0, off otherwise
  if (dataReceived > 0)
    digitalWrite(OUTPUT_PIN, LOW);
  else
    digitalWrite(OUTPUT_PIN, HIGH);
}
