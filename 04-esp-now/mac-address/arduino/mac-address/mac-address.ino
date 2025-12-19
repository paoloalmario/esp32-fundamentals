/*************************************************************
 * ESP32 MAC Address Reader
 * Author: Paolo Almario
 *
 * ------------------------------------------------------------------
 * DESCRIPTION:
 * ------------------------------------------------------------------
 * This program reads and displays the ESP32's MAC addresses
 * in two different modes:
 *
 * 1) STA (Station) Mode:
 *    - The ESP32 acts as a Wi-Fi client
 *    - Same role as a laptop or phone connecting to a router
 *    - This is the MAC address used for ESP-NOW communication
 *
 * 2) AP (Access Point) Mode:
 *    - The ESP32 becomes a Wi-Fi hotspot
 *    - Other devices can connect to it
 *    - AP MAC is usually STA MAC with last byte +1
 *
 * Why is this useful?
 * - ESP-NOW projects need the MAC address of communicating ESPs
 * - Run this first to get the address for sender/receiver sketches
 *
 * ------------------------------------------------------------------
 * NOTE: For ESP-NOW, always use the STA MAC address
 * ------------------------------------------------------------------
 *************************************************************/

#include <WiFi.h>

// -----------------------------------------------------------
// Helper function to print a MAC address
// -----------------------------------------------------------
// Parameters:
//   - label: text to display before the address
//   - mac: array of 6 bytes representing the MAC address
// -----------------------------------------------------------
void printMac(const char* label, const uint8_t mac[6]) {
  Serial.print(label);

  // MAC addresses are 6 bytes (hexadecimal values)
  for (int i = 0; i < 6; ++i) {
    if (i) Serial.print(":");           // Add ":" between bytes
    if (mac[i] < 16) Serial.print("0"); // Add leading zero if needed
    Serial.print(mac[i], HEX);          // Print byte in hexadecimal
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(200);

  // -----------------------------------------------------------
  // Read STA (Station) MAC address
  // -----------------------------------------------------------
  WiFi.mode(WIFI_STA);
  delay(100);
  uint8_t sta[6];
  WiFi.macAddress(sta);
  printMac("STA MAC: ", sta);

  // -----------------------------------------------------------
  // Read AP (Access Point) MAC address
  // -----------------------------------------------------------
  WiFi.mode(WIFI_AP);
  delay(100);
  uint8_t ap[6];
  WiFi.softAPmacAddress(ap);
  printMac("AP  MAC: ", ap);

  // -----------------------------------------------------------
  // Return to STA mode (required for ESP-NOW)
  // -----------------------------------------------------------
  WiFi.mode(WIFI_STA);
}

void loop() {
  // Nothing to do in loop
  // Program runs once at startup, displays MAC addresses, then waits
}
