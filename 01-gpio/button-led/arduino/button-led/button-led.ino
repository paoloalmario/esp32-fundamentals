/*
  Button-Controlled LED

  LED turns on when button is pressed, off when released.

  Wiring:
  - Button between GPIO 13 and GND (uses internal pull-up)
  - LED with 220 ohm resistor on GPIO 12

  Author: Paolo Almario
  License: CC BY-SA 4.0
*/

const int BUTTON_PIN = 13;
const int LED_PIN = 12;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("Button + LED started");
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    // Button pressed
    digitalWrite(LED_PIN, HIGH);
  } else {
    // Button released
    digitalWrite(LED_PIN, LOW);
  }

  delay(10);
}
