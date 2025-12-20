/*
 * LDR to LEDs - ESP32 Fundamentals
 * Analog light sensor (LDR) controlling 3 LEDs with threshold levels
 *
 * This exercise teaches:
 * - Reading analog sensors with ESP32 12-bit ADC (0-4095)
 * - Converting analog readings to discrete outputs
 * - Using threshold logic for multi-level indicators
 * - Practical sensor calibration
 *
 * Circuit:
 * - LDR Sensor (DFRobot): VCC -> 3.3V, Signal -> GPIO 4, GND -> GND
 * - LEDs: anode -> GPIO 13/12/14 (with series resistors), cathode -> GND
 *
 * Default thresholds (adjust based on your environment):
 * - > 4000: 3 LEDs (very high level)
 * - 2801-4000: 2 LEDs (high level)
 * - 1001-2800: 1 LED (medium level)
 * - <= 1000: 0 LEDs (low level)
 *
 * Author: Paolo Almario
 * License: CC BY-SA 4.0
 * https://github.com/paoloalmario/esp32-fundamentals
 */

const int LED1 = 13;  // Medium level indicator (1001-2800)
const int LED2 = 12;  // High level indicator (2801-4000)
const int LED3 = 14;  // Very high level indicator (>4000)

int analogSensor = 0;  // ADC value read (0-4095)

void controlLEDs();  // Function declaration

void setup() {
  // Analog input (GPIO 4 - ADC1_CH0)
  pinMode(4, INPUT);

  // Serial communication
  Serial.begin(115200);

  // Configure LEDs as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Initialize LEDs: all off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  Serial.println("=== ANALOG MONITORING SYSTEM ===");
  Serial.println("Sensor connected on GPIO 4 (ADC1_CH0)");
  Serial.println("LED Thresholds:");
  Serial.println("  > 4000 : ███ (3 LEDs) - VERY HIGH Level");
  Serial.println("  2801-4000 : ██ (2 LEDs) - HIGH Level");
  Serial.println("  1001-2800 : █ (1 LED) - MEDIUM Level");
  Serial.println("  <= 1000 : (0 LEDs) - LOW Level");
  Serial.println("----------------------------------------");
  Serial.println("ADC Values:");
}

void loop() {
  // Read analog value (0-4095)
  analogSensor = analogRead(4);

  // Display value
  Serial.println(analogSensor);

  // Update LEDs
  controlLEDs();

  // 10 samples per second
  delay(100);
}

void controlLEDs() {
  if (analogSensor > 4000) {
    // Very high: 3 LEDs
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  } else if (analogSensor > 2800) {
    // High: 2 LEDs
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  } else if (analogSensor > 1000) {
    // Medium: 1 LED
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } else {
    // Low: 0 LEDs
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
}
