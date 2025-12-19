/*
  Distance-Controlled LED Indicator

  Uses VL53L0X ToF sensor to measure distance and control 3 LEDs
  as a visual proximity indicator.

  LED thresholds:
  - < 150mm:  3 LEDs on (very close)
  - 150-249mm: 2 LEDs on (close)
  - 250-499mm: 1 LED on (medium)
  - >= 500mm: 0 LEDs on (far)

  Wiring:
  VL53L0X:
  - SDA -> GPIO 21
  - SCL -> GPIO 22
  - VIN -> 3.3V
  - GND -> GND

  LEDs (with 220 ohm resistors):
  - LED1 -> GPIO 13
  - LED2 -> GPIO 12
  - LED3 -> GPIO 14

  Author: Paolo Almario
  License: CC BY-SA 4.0
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 14;

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();
int distance = 0;

void updateLEDs();

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!sensor.begin()) {
    Serial.println("ERROR: VL53L0X not found!");
    while (1);
  }

  Serial.println("ToF + LEDs started");

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  sensor.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    distance = measure.RangeMilliMeter;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" mm");
  } else {
    distance = 0;
    Serial.println("Out of range");
  }

  updateLEDs();
  delay(50);
}

void updateLEDs() {
  if (distance == 0) {
    // Out of range: all off
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } else if (distance < 150) {
    // Very close: 3 LEDs
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  } else if (distance < 250) {
    // Close: 2 LEDs
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  } else if (distance < 500) {
    // Medium: 1 LED
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } else {
    // Far: all off
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
}
