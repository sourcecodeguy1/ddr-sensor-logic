/*
Arrow direction by button pin
2 = Left
3 = Right
4 = Up
5 = Down
*/
#include <Joystick1.h>
#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    60

CRGB leds[NUM_LEDS];

void setup() {
  // Initialize Button Pins
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();

  // Initialize LED Strip
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

// Constant that maps the physical pin to the joystick button.
const int pinToButtonMap[4] = {2, 3, 4, 5};

// Last state of the buttons
int lastButtonState[4] = {0, 0, 0, 0};

void loop() {

  // Read pin values
  for (int index = 0; index < 4; index++)
  {
    int currentButtonState = !digitalRead(pinToButtonMap[index]);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  // Update LED colors
  for (int i = 0; i < NUM_LEDS; i++) {
    if (lastButtonState[0] == 1 || lastButtonState[1] == 1) { // Left, Right
      leds[i] = CRGB::Blue;
    } else if (lastButtonState[2] == 1 || lastButtonState[3] == 1) { // Up, Down
      leds[i] = CRGB::Red;
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();

  delay(50);
}
