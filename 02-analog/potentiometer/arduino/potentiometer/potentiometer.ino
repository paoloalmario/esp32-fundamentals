/*
  Analog Input Reading

  Reads an analog sensor (potentiometer, LDR, etc.) and displays
  raw ADC values (0-4095) in Serial Monitor.

  ESP32 ADC specs:
  - 12-bit resolution (0-4095)
  - Reference voltage: 3.3V
  - Resolution: ~0.8mV per unit

  Wiring:
  - Potentiometer center pin to GPIO 4
  - Outer pins to 3.3V and GND

  Author: Paolo Almario
  License: CC BY-SA 4.0
*/

const int ANALOG_PIN = 4;  // ADC1_CH0

void setup() {
  pinMode(ANALOG_PIN, INPUT);
  Serial.begin(115200);

  Serial.println("Analog reading started");
  Serial.println("Sensor on GPIO 4 (ADC1_CH0)");
  Serial.println("Raw ADC values (0-4095):");
}

void loop() {
  // Read analog value (0-4095)
  int value = analogRead(ANALOG_PIN);
  Serial.println(value);
  delay(100);
}
