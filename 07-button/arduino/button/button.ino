/*
  Button Reading

  Reads a pushbutton state and displays the value in Serial Monitor.
  Uses internal pull-up resistor: button pressed = LOW (0).

  Wiring:
  - Button between GPIO 13 and GND
  - No external resistor needed (uses INPUT_PULLUP)

  Author: Paolo Almario
  License: CC BY-SA 4.0
*/

const int BUTTON_PIN = 13;

void setup() {
  // Configure button with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize serial at 115200 baud
  Serial.begin(115200);

  Serial.println("Button reading started");
  Serial.println("Press button on GPIO 13");
  Serial.println("State: 0=pressed, 1=released");
}

void loop() {
  int state = digitalRead(BUTTON_PIN);
  Serial.println(state);
  delay(100);  // Avoid flooding serial monitor
}
