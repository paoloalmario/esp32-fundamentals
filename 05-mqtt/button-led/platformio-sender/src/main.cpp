/**************************************************************
 * MQTT Sender - Digital Sensor (PlatformIO)
 * Author: Paolo Almario
 ***************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID     = "YourNetworkName";
const char* WIFI_PASSWORD = "YourPassword";
const char* MQTT_SERVER   = "broker.hivemq.com";
const int   MQTT_PORT     = 1883;
const char* MQTT_CLIENTID = "ESP32-Sender-01";
const char* MQTT_PUBLISH_TOPIC = "myproject/button";

const int SENSOR_PIN = 5;
const unsigned long PUBLISH_INTERVAL = 500;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect(MQTT_CLIENTID)) {
      Serial.println("connected.");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

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
    Serial.print("Published: ");
    Serial.println(msg);
  }
}
