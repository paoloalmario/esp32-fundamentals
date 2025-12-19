/*************************************************************
 * ESP-NOW Simple Receiver
 * Author: Paolo Almario
 *
 * Receives messages from other ESP32 devices without WiFi.
 *
 * How it works:
 * - Receives numbers and text messages from a sender
 * - Displays everything in Serial Monitor
 * - Blinks LED on each received message
 *
 * Instructions:
 * 1. Upload this code to your receiver ESP32
 * 2. Open Serial Monitor (115200 baud)
 * 3. Built-in LED blinks on each message
 *************************************************************/

#include <WiFi.h>
#include <esp_now.h>

// Built-in LED pin (usually GPIO 2 on ESP32)
int builtInLed = 2;

/*************************************************************
 * SETUP - Runs once at startup
 * Configures ESP32 to receive messages
 *************************************************************/
void setup() {
  Serial.begin(115200);

  // Configure LED pin as output
  pinMode(builtInLed, OUTPUT);

  // Set WiFi to Station mode (required for ESP-NOW)
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR: ESP-NOW could not start");
    return;
  }

  // Register the callback function for receiving messages
  esp_now_register_recv_cb(onMessageReceived);

  Serial.println("=== ESP-NOW RECEIVER READY ===");
  Serial.println("Waiting for messages...");
  Serial.println("LED will blink on each message");
  Serial.println("=================================");
}

/*************************************************************
 * LOOP - Runs continuously
 * Nothing here since everything happens in the callback
 *************************************************************/
void loop() {
  delay(1000);
}

/*************************************************************
 * ON MESSAGE RECEIVED - Called automatically on each message
 *
 * Parameters:
 * - info: sender information (MAC address, etc.)
 * - data: the received message data
 * - len: message size in bytes
 *************************************************************/
void onMessageReceived(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  // ========== DISPLAY SENDER ADDRESS ==========
  Serial.print("Message from: ");

  // Print sender MAC address in hexadecimal
  for (int i = 0; i < 6; i++) {
    Serial.print(info->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }

  Serial.print(" | Content: ");

  // ========== DETERMINE MESSAGE TYPE ==========

  // CASE 1: IT'S A NUMBER (size = 4 bytes)
  if (len == sizeof(int)) {
    int receivedNumber;
    memcpy(&receivedNumber, data, len);
    Serial.println(receivedNumber);
    blinkLed(builtInLed, 50);
  }

  // CASE 2: IT'S TEXT (size != 4 bytes)
  else {
    for (int i = 0; i < len; i++) {
      Serial.print((char)data[i]);
    }
    Serial.println();
  }
}

/*************************************************************
 * BLINK LED - Flashes an LED
 *
 * Parameters:
 * - led: the LED pin to blink
 * - duration: on/off time in milliseconds
 *************************************************************/
void blinkLed(int led, int duration) {
  digitalWrite(led, HIGH);
  delay(duration);
  digitalWrite(led, LOW);
  delay(duration);
}
