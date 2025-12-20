/*************************************************************
 * ESP32 MAC Address Reader
 * Author: Paolo Almario
 *
 * Reads and displays the ESP32's MAC addresses in STA and AP modes.
 * Use the STA MAC address for ESP-NOW communication.
 *************************************************************/

#include <Arduino.h>
#include <WiFi.h>

void printMac(const char* label, const uint8_t mac[6]) {
  Serial.print(label);
  for (int i = 0; i < 6; ++i) {
    if (i) Serial.print(":");
    if (mac[i] < 16) Serial.print("0");
    Serial.print(mac[i], HEX);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(200);

  // Read STA MAC
  WiFi.mode(WIFI_STA);
  delay(100);
  uint8_t sta[6];
  WiFi.macAddress(sta);
  printMac("STA MAC: ", sta);

  // Read AP MAC
  WiFi.mode(WIFI_AP);
  delay(100);
  uint8_t ap[6];
  WiFi.softAPmacAddress(ap);
  printMac("AP  MAC: ", ap);

  // Return to STA mode for ESP-NOW
  WiFi.mode(WIFI_STA);
}

void loop() {
  // Nothing to do
}
