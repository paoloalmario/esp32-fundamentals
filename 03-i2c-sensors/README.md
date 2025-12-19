# 03-i2c-sensors

I2C sensor communication on ESP32.

## Exercises

| Exercise | Concepts | Hardware |
|----------|----------|----------|
| [tof-sensor](tof-sensor/) | I2C, libraries | VL53L0X distance sensor |
| [tof-leds](tof-leds/) | Sensor + actuator integration | VL53L0X + 3 LEDs |

## Key Concepts

- **I2C**: Two-wire communication protocol (SDA, SCL)
- **Default pins**: SDA = GPIO 21, SCL = GPIO 22
- **Libraries**: External libraries for complex sensors
- **Sensor fusion**: Combining sensor input with output control
