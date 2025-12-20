/*************************************************************
 * ESP-NOW Simple Sender
 * Author: Paolo Almario
 *
 * Sends messages to other ESP32 devices without WiFi network.
 *
 * How it works:
 * - Sends random numbers and text messages
 * - Works like a walkie-talkie for ESP32
 * - Sends every second
 *
 * Instructions:
 * 1. Modify the MAC addresses below
 * 2. Upload to your sender ESP32
 * 3. Open Serial Monitor (115200 baud)
 *************************************************************/

#include <WiFi.h>
#include <esp_now.h>

// ========== EASY CONFIGURATION ==========

// WiFi channel (1-13), all ESPs must use the same channel
#define WIFI_CHANNEL 1

// List of receiver MAC addresses - MODIFY THESE!
uint8_t receiverList[][6] = {
  // Replace with the actual MAC addresses of your ESP32 receivers
  {0x44, 0x17, 0x93, 0x5A, 0x1E, 0x14},  // Receiver 1 - MODIFY!
  {0xB0, 0xA7, 0x32, 0x27, 0xE0, 0xEC},  // Receiver 2 - MODIFY!

  // To add more receivers, uncomment lines below:
  // {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},  // Receiver 3
  // {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},  // Receiver 4
  // Maximum 20 receivers total
};

// ========== END CONFIGURATION ==========

int messageCounter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== ESP-NOW SIMPLE SENDER ===");
  Serial.println("Starting...");

  // Set WiFi to Station mode (required for ESP-NOW)
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error starting ESP-NOW");
    return;
  }

  // Calculate number of receivers in the list
  int numReceivers = sizeof(receiverList) / 6;
  Serial.println("Adding " + String(numReceivers) + " receivers...");

  // Add each receiver to the peer list
  for (int i = 0; i < numReceivers; i++) {
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverList[i], 6);
    peerInfo.channel = WIFI_CHANNEL;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) == ESP_OK) {
      Serial.println("+ Receiver " + String(i+1) + " added successfully");
    } else {
      Serial.println("x Error with receiver " + String(i+1));
    }
  }

  Serial.println("Ready! Sending messages every second...");
  Serial.println("==============================================");
}

void loop() {
  Serial.println();
  Serial.println("Message #" + String(messageCounter));

  // ========== SEND RANDOM NUMBER ==========
  int randomNumber = random(100);
  sendToAllReceivers((uint8_t*)&randomNumber, sizeof(randomNumber));
  Serial.println("Number sent: " + String(randomNumber));

  // ========== SEND TEXT MESSAGE ==========
  char textMessage[50];
  sprintf(textMessage, "Hello! Message #%d", messageCounter);
  sendToAllReceivers((uint8_t*)textMessage, strlen(textMessage));
  Serial.println("Text sent: " + String(textMessage));

  messageCounter++;
  delay(1000);

  // To send faster, change delay above:
  // delay(500) = 2 messages per second
  // delay(200) = 5 messages per second
  // delay(100) = 10 messages per second
}

// Function to send data to all receivers in the list
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
