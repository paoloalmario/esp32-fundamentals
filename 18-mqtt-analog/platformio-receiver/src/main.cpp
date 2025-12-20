/**************************************************************
 * MQTT Receiver - Analog to LED (PlatformIO)
 * Author: Paolo Almario
 ***************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID     = "YourNetworkName";
const char* WIFI_PASSWORD = "YourPassword";
const char* MQTT_SERVER   = "broker.hivemq.com";
const int   MQTT_PORT     = 1883;
const char* MQTT_CLIENTID = "ESP32-AnalogReceiver-01";
const char* MQTT_SUBSCRIBE_TOPIC = "myproject/light";

const int OUTPUT_PIN = 2;
const int THRESHOLD = 2000;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  char msg[100];
  memcpy(msg, payload, length);
  msg[length] = '\0';
  int dataReceived = String(msg).toInt();

  Serial.print("Received: ");
  Serial.println(dataReceived);

  if (dataReceived > THRESHOLD)
    digitalWrite(OUTPUT_PIN, HIGH);
  else
    digitalWrite(OUTPUT_PIN, LOW);
}

void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect(MQTT_CLIENTID)) {
      Serial.println("connected.");
      client.subscribe(MQTT_SUBSCRIBE_TOPIC);
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
