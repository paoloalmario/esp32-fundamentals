/*
 * Blink Multiple - ESP32 Fundamentals
 * Controlling multiple LEDs with different patterns
 *
 * This exercise teaches:
 * - Controlling multiple LEDs simultaneously
 * - Creating sequential LED patterns
 * - Creating ping-pong/sweep effects
 *
 * Circuit: 3 LEDs connected to pins 13, 14, 12 with series resistors (220-330 Ohm)
 *
 * Author: Paolo Almario
 * License: CC BY-SA 4.0
 * https://github.com/paoloalmario/esp32-fundamentals
 */

const int LED1_PIN = 13;
const int LED2_PIN = 14;
const int LED3_PIN = 12;

void setup() {
  // Configure all pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
}

void loop() {
  // Example 1: Blink all 3 LEDs simultaneously (500 ms tempo)
  // Uncomment to test:
  /*
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED3_PIN, HIGH);
  delay(500);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  delay(500);
  */

  // Example 2: Blink LEDs one at a time in sequence
  // Uncomment to test:
  /*
  digitalWrite(LED1_PIN, HIGH);
  delay(500);
  digitalWrite(LED1_PIN, LOW);
  delay(500);

  digitalWrite(LED2_PIN, HIGH);
  delay(500);
  digitalWrite(LED2_PIN, LOW);
  delay(500);

  digitalWrite(LED3_PIN, HIGH);
  delay(500);
  digitalWrite(LED3_PIN, LOW);
  delay(500);
  */

  // Example 3: Ping-pong/sweep effect
  // Turn on LEDs one after another, then turn off in reverse order
  digitalWrite(LED1_PIN, HIGH);
  delay(200);
  digitalWrite(LED2_PIN, HIGH);
  delay(200);
  digitalWrite(LED3_PIN, HIGH);
  delay(200);

  digitalWrite(LED3_PIN, LOW);
  delay(200);
  digitalWrite(LED2_PIN, LOW);
  delay(200);
  digitalWrite(LED1_PIN, LOW);
  delay(200);
}
