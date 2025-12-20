/*************************************************************
 * ESP-NOW Simple Sender
 * Author: Paolo Almario
 * PlatformIO version
 *************************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define WIFI_CHANNEL 1

// Replace with your receiver MAC addresses
uint8_t receiverList[][6] = {
  {0x44, 0x17, 0x93, 0x5A, 0x1E, 0x14},  // Receiver 1
  {0xB0, 0xA7, 0x32, 0x27, 0xE0, 0xEC},  // Receiver 2
};

int messageCounter = 0;

void sendToAllReceivers(uint8_t* data, int length) {
  int numReceivers = sizeof(receiverList) / 6;
  for (int i = 0; i < numReceivers; i++) {
    esp_err_t result = esp_now_send(receiverList[i], data, length);
    if (result == ESP_OK) {
      Serial.println("  + Delivered to receiver " + String(i+1));
    } else {
      Serial.println("  x Failed to send to receiver " + String(i+1));
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== ESP-NOW SENDER ===");

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error starting ESP-NOW");
    return;
  }

  int numReceivers = sizeof(receiverList) / 6;
  for (int i = 0; i < numReceivers; i++) {
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverList[i], 6);
    peerInfo.channel = WIFI_CHANNEL;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);
  }

  Serial.println("Ready!");
}

void loop() {
  Serial.println("\nMessage #" + String(messageCounter));

  int randomNumber = random(100);
  sendToAllReceivers((uint8_t*)&randomNumber, sizeof(randomNumber));
  Serial.println("Number: " + String(randomNumber));

  char textMessage[50];
  sprintf(textMessage, "Hello! Message #%d", messageCounter);
  sendToAllReceivers((uint8_t*)textMessage, strlen(textMessage));

  messageCounter++;
  delay(1000);
}
