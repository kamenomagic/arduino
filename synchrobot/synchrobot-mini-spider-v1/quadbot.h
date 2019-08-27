#ifndef Quadbot_h
#define Quadbot_h
#include <Arduino.h>
#include "leg.h"

// Legs start from front left leg (top left looking down with front of robot on top) and go clockwise
// when passing in pins, follow the legs in this pattern, front left clockwise looking down and end on back left, and
// each leg starts at the foot and goes inward such that the feet are a, d, g, j in clockwise-leg order

class Quadbot {
  public:
    void init(int pinA, int pinB, int pinC,
              int pinD, int pinE, int pinF,
              int pinG, int pinH, int pinI,
              int pinJ, int pinK, int pinL);
    void setLimits(Leg leg, int minimum, int maximum);
    void tick();
    void flat();
    void stand();
    Leg a;
    Leg b;
    Leg c;
    Leg d;
};

void Quadbot::init(int pinA, int pinB, int pinC,
                   int pinD, int pinE, int pinF,
                   int pinG, int pinH, int pinI,
                   int pinJ, int pinK, int pinL) {
  this->a.init(false, pinA,
                true, pinB,
                true, pinC);
  this->b.init(true, pinD,
                false, pinE,
                false, pinF);
  this->c.init(false, pinG,
                true, pinH,
                true, pinI);
  this->d.init(true, pinJ,
                false, pinK,
                false, pinL);
  this->a.hip.setLimits(45, 145);
  this->b.hip.setLimits(35, 130);
  this->c.hip.setLimits(50, 150);
  this->d.hip.setLimits(45, 145);
}

void Quadbot::tick() {
  this->a.tick();
  this->b.tick();
  this->c.tick();
  this->d.tick();
}

void Quadbot::flat() {
  this->a.flat();
  this->b.flat();
  this->c.flat();
  this->d.flat();
}

void Quadbot::stand() {
  this->a.stand();
  this->b.stand();
  this->c.stand();
  this->d.stand();
}
#endif
