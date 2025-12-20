/*
 * Blink External - ESP32 Fundamentals
 * First physical circuit: LED connected to pin 13 and GND
 *
 * This exercise teaches:
 * - Building a first external LED circuit
 * - Controlling a physical LED via GPIO
 * - Understanding LED polarity (anode + and cathode -)
 * - Using series resistors (220-330 Ohm) for LED protection
 *
 * Author: Paolo Almario
 * License: CC BY-SA 4.0
 * https://github.com/paoloalmario/esp32-fundamentals
 */

const int LED_PIN = 13;  // LED connected to pin 13 (or LED_BUILTIN)

void setup() {
  // Configure pin 13 as output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn on LED
  digitalWrite(LED_PIN, HIGH);
  // Wait 500 ms
  delay(500);
  // Turn off LED
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
