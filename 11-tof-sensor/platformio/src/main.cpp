/*
  VL53L0X Time-of-Flight Distance Sensor

  Reads distance measurements from VL53L0X sensor via I2C
  and displays values in Serial Monitor.

  Range: 30-1200mm (typical)

  Wiring:
  - VL53L0X SDA -> GPIO 21
  - VL53L0X SCL -> GPIO 22
  - VL53L0X VIN -> 3.3V
  - VL53L0X GND -> GND

  Author: Paolo Almario
  License: CC BY-SA 4.0
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize sensor
  if (!sensor.begin()) {
    Serial.println("ERROR: VL53L0X not found!");
    Serial.println("Check I2C connections (SDA/SCL)");
    while (1);
  }

  Serial.println("VL53L0X initialized");
  Serial.println("Distance measurements:");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  sensor.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    // Valid measurement
    Serial.print("Distance: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Out of range");
  }

  delay(100);
}
