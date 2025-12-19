/**************************************************************
 * MQTT Receiver for ESP32 - Analog to LED
 * Author: Paolo Almario
 * ------------------------------------------------------------
 * Receives analog values via MQTT and controls LED brightness
 * or on/off state based on a threshold.
 *
 * IMPORTANT:
 * Change the MQTT topic name to match your sender's topic.
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
const char* MQTT_CLIENTID = "ESP32-AnalogReceiver-01";

// --- MQTT Topic ---
const char* MQTT_SUBSCRIBE_TOPIC = "myproject/light";

// --- Output Configuration ---
const int OUTPUT_PIN = 2;
const int THRESHOLD = 2000;       // Value threshold for LED on/off
const bool DEBUG_SERIAL = true;

/* ============================================================
   END CONFIGURATION SECTION
   ============================================================ */

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  if (DEBUG_SERIAL) Serial.begin(115200);

  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}

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

void callback(char* topic, byte* payload, unsigned int length) {
  char msg[100];
  memcpy(msg, payload, length);
  msg[length] = '\0';

  int dataReceived = String(msg).toInt();

  if (DEBUG_SERIAL) {
    Serial.print("Message received on topic ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(dataReceived);
  }

  // Turn LED on if value exceeds threshold
  if (dataReceived > THRESHOLD)
    digitalWrite(OUTPUT_PIN, HIGH);
  else
    digitalWrite(OUTPUT_PIN, LOW);
}
