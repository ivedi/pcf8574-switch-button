/*
 * Pcf8574SwitchButton.h - Basic switch button library.
 * Created by Halil İbrahim İvedi, October 15, 2025
 *  */

#ifndef Pcf8574SwitchButton_h
#define Pcf8574SwitchButton_h

#include "PCF8574.h"
#include "Arduino.h"

class Pcf8574SwitchButton
{
  public:
    Pcf8574SwitchButton(PCF8574 *pcf8574, uint8_t pin, uint8_t releasedPinState);
    PCF8574 *pcf;
    uint8_t buttonPin;
    bool pressed;
    bool released;
    void begin();
    bool stateChanged(bool forceReadNow = false, byte debounceTime = 50);
  private:
    uint8_t _releasedPinState;
    uint8_t _currentState;
    uint8_t _lastFlickerableState;
    uint8_t _lastSteadyState;
    unsigned long _lastDebounceTime;
};

#endif
