/*
  Blink

  The classic "Hello World" of microcontrollers.
  Turns the built-in LED on for one second, then off for one second.

  ESP32 built-in LED is typically on GPIO 2.
  Change LED_PIN if your board uses a different pin.

  Author: Paolo Almario
  License: CC BY-SA 4.0
*/

const int LED_PIN = 2;  // Built-in LED pin (GPIO 2 on most ESP32 boards)

// Runs once at startup
void setup() {
  pinMode(LED_PIN, OUTPUT);
}

// Runs repeatedly
void loop() {
  digitalWrite(LED_PIN, HIGH);  // LED on
  delay(1000);                  // Wait 1 second
  digitalWrite(LED_PIN, LOW);   // LED off
  delay(1000);                  // Wait 1 second
}
