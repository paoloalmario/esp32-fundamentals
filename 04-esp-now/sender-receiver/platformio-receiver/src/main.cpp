/*************************************************************
 * ESP-NOW Simple Receiver
 * Author: Paolo Almario
 * PlatformIO version
 *************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

int builtInLed = 2;

void blinkLed(int led, int duration) {
  digitalWrite(led, HIGH);
  delay(duration);
  digitalWrite(led, LOW);
  delay(duration);
}

void onMessageReceived(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  Serial.print("From: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(info->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.print(" | ");

  if (len == sizeof(int)) {
    int receivedNumber;
    memcpy(&receivedNumber, data, len);
    Serial.println(receivedNumber);
    blinkLed(builtInLed, 50);
  } else {
    for (int i = 0; i < len; i++) {
      Serial.print((char)data[i]);
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(builtInLed, OUTPUT);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onMessageReceived);
  Serial.println("=== ESP-NOW RECEIVER READY ===");
}

void loop() {
  delay(1000);
}
