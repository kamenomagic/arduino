#ifndef Leg_h
#define Leg_h
#include <Arduino.h>
#include "joint.h"

class Leg {
  public:
    void init(bool footClockwise, int footPin,
              bool thighClockwise, int thighPin,
              bool hipClockwise, int hipPin);
    Joint foot;
    Joint thigh;
    Joint hip;
};

void Leg::init(bool footClockwise, int footPin,
               bool thighClockwise, int thighPin,
               bool hipClockwise, int hipPin) {
  this->foot.init(footClockwise, footPin);
  this->thigh.init(thighClockwise, thighPin);
  this->hip.init(hipClockwise, hipPin);
}
#endif
