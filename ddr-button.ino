/*
Arrow direction by button pin
2 = Left
3 = Right
4 = Up
5 = Down
*/
#include <Joystick1.h>
#include <FastLED.h>

#define LED_PIN_LEFT     6
#define LED_PIN_RIGHT    7
#define LED_PIN_UP       8
#define LED_PIN_DOWN     9

#define NUM_LEDS    19

CRGB ledsLeft[NUM_LEDS];
CRGB ledsRight[NUM_LEDS];
CRGB ledsUp[NUM_LEDS];
CRGB ledsDown[NUM_LEDS];

void setup() {
  // Initialize Button Pins
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();

  // Initialize LED Strips
  FastLED.addLeds<WS2812, LED_PIN_LEFT, GRB>(ledsLeft, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_RIGHT, GRB>(ledsRight, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_UP, GRB>(ledsUp, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_DOWN, GRB>(ledsDown, NUM_LEDS);
}

// Constant that maps the physical pin to the joystick button.
const int pinToButtonMap[4] = {2, 3, 4, 5};

// Last state of the buttons
int lastButtonState[4] = {0, 0, 0, 0};

void loop() {
  // Read pin values
  for (int index = 0; index < 4; index++) {
    int currentButtonState = !digitalRead(pinToButtonMap[index]);
    if (currentButtonState != lastButtonState[index]) {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  // Update LED colors
  for (int i = 0; i < NUM_LEDS; i++) {
    if (lastButtonState[0] == 1) { // Left
      ledsLeft[i] = CRGB::Blue;
    } else {
      ledsLeft[i] = CRGB::Black;
    }

    if (lastButtonState[1] == 1) { // Right
      ledsRight[i] = CRGB::Blue;
    } else {
      ledsRight[i] = CRGB::Black;
    }

    if (lastButtonState[2] == 1) { // Up
      ledsUp[i] = CRGB::Red;
    } else {
      ledsUp[i] = CRGB::Black;
    }

    if (lastButtonState[3] == 1) { // Down
      ledsDown[i] = CRGB::Red;
    } else {
      ledsDown[i] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(50);
}
