/*
 * Relay Control - ESP32 Fundamentals
 * Controlling a 5V relay via GPIO with transistor/MOSFET interface
 *
 * This exercise teaches:
 * - Controlling high-power devices (relays) from ESP32
 * - Using transistors (TIP120) or MOSFETs as interfaces
 * - Understanding voltage level conversion (3.3V GPIO to 5V relay)
 * - Proper relay circuit design with flyback diode
 *
 * Circuit: 5V relay commanded from pin 13 via transistor (e.g., TIP120)
 * Use base/gate resistor (1k for TIP120, 100-220 Ohm for MOSFET)
 * Ensure common ground (GND) between ESP32 and 5V power supply
 *
 * WARNING: NEVER connect AC mains voltage without qualified supervision
 *
 * Author: Paolo Almario
 * License: CC BY-SA 4.0
 * https://github.com/paoloalmario/esp32-fundamentals
 */

const int RELAY_PIN = 13;  // Control pin for relay driver (transistor/MOSFET)

void setup() {
  // Configure pin 13 as output for relay control
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Activate relay (transistor driver closed)
  digitalWrite(RELAY_PIN, HIGH);
  // Wait 500 ms
  delay(500);
  // Deactivate relay
  digitalWrite(RELAY_PIN, LOW);
  delay(500);
}
