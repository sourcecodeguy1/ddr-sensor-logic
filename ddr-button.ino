#include <Joystick1.h>

// Constants that map the physical pin to the joystick button.
const int pinToButtonMap[4] = {2, 3, 4, 5};

// Last state of the buttons
int lastButtonState[4] = {0, 0, 0, 0};

// LED pins
const int leftLedPin = 6;
const int rightLedPin = 7;
const int upLedPin = 8;
const int downLedPin = 9;

void setup() {
  // Initialize Button Pins
  pinMode(pinToButtonMap[0], INPUT_PULLUP);
  pinMode(pinToButtonMap[1], INPUT_PULLUP);
  pinMode(pinToButtonMap[2], INPUT_PULLUP);
  pinMode(pinToButtonMap[3], INPUT_PULLUP);

  // Initialize LED pins
  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);
  pinMode(upLedPin, OUTPUT);
  pinMode(downLedPin, OUTPUT);

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  // Read pin values
  for (int index = 0; index < 4; index++) {
    int currentButtonState = !digitalRead(pinToButtonMap[index]);
    if (currentButtonState != lastButtonState[index]) {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  // Control LED bulbs based on button states
  digitalWrite(leftLedPin, lastButtonState[0]);
  digitalWrite(rightLedPin, lastButtonState[1]);
  digitalWrite(upLedPin, lastButtonState[2]);
  digitalWrite(downLedPin, lastButtonState[3]);

  delay(50);
}
