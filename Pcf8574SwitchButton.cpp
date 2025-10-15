/*
 * Pcf8574SwitchButton.cpp - Basic switch button library
 * Created by Halil İbrahim İvedi, October 15, 2025
 *  */

#include "PCF8574.h"
#include "Arduino.h"
#include "Pcf8574SwitchButton.h"

Pcf8574SwitchButton::Pcf8574SwitchButton(PCF8574 *pcf8574, uint8_t pin, uint8_t releasedPinState) {
  *pcf = *pcf8574;
  buttonPin = pin;
  pressed = false;
  released = true;
  _releasedPinState = releasedPinState;
  _currentState = releasedPinState;
  _lastFlickerableState = releasedPinState;
  _lastSteadyState = releasedPinState;
  _lastDebounceTime = 0;
}

void Pcf8574SwitchButton::begin() {
  pcf->pinMode(buttonPin, INPUT, LOW);
}

bool Pcf8574SwitchButton::stateChanged(bool forceReadNow, byte debounceTime) {
  bool stateChanged = false;
  // read the state of the button
  _currentState = pcf->digitalRead(buttonPin, forceReadNow);

  // check to see if you just pressed the button (LOW or HIGH)
  // and you've waited long enough
  // since the last press to ignore any noise:

  // If the button changed, due to noise or pressing
  if (_currentState != _lastFlickerableState) {
    // reset the bouncing timer
    _lastDebounceTime = millis();
    // save the last flickerable state
    _lastFlickerableState = _currentState;
  }

  if ((millis() - _lastDebounceTime) > debounceTime) {
    // whatever the reading is at, it's been there for longer than
    // debounce delay, so take it as the actual current state:

    // if the button has changed:
    if (_lastSteadyState != _releasedPinState && _currentState == _releasedPinState) {
      pressed = true;
      released = false;
      stateChanged = true;
    } else if (_lastSteadyState == _releasedPinState && _currentState != _releasedPinState) {
      pressed = false;
      released = true;
      stateChanged = true;
    }

    // save the last steady state
    _lastSteadyState = _currentState;
  }

  return stateChanged;
}
