#ifndef Leg_h
#define Leg_h
#include <Arduino.h>
#include "joint.h"

class Leg {
  public:
    void init(bool footClockwise, int footPin,
              bool thighClockwise, int thighPin,
              bool hipClockwise, int hipPin);
    void tick();
    void flat();
    void stand();
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

void Leg::tick() {
  this->foot.tick();
  this->thigh.tick();
  this->hip.tick();
}

void Leg::flat() {
  this->foot.middle();
  this->thigh.middle();
  this->hip.middle();
}

void Leg::stand() {
  this->foot.set(30);
  this->thigh.set(100);
  this->hip.set(this->hip.midPos);
}
#endif
