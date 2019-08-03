#ifndef Light_h
#define Light_h
#include "Arduino.h"

class Light {
  public:
    Light(int pin);
    int getReading();
  private:
    int pin;
};

Light::Light(int assignPin) {
  pin = assignPin;
}

int Light::getReading() {
  return analogRead(pin) / 1023.0 * 100;
}
#endif
