#ifndef Quadbot_h
#define Quadbot_h
#include <Arduino.h>
#include "leg.h"
#include "joint.h"

// Legs start from front left leg (top left looking down with front of robot on top) and go clockwise
// when passing in pins, follow the legs in this pattern, front left clockwise looking down and end on back left, and
// each leg starts at the foot and goes inward such that the feet are a, d, g, j in clockwise-leg order
//
enum level {
  slowest, slow, medium, fast, fastest
};

class Quadbot {
  public:
    void init(int pinA, int pinB, int pinC,
              int pinD, int pinE, int pinF,
              int pinG, int pinH, int pinI,
              int pinJ, int pinK, int pinL);
    Quadbot Quadbot::set(int pos[][3]);
    Quadbot Quadbot::set(int aPos, int bPos, int cPos,
                      int dPos, int ePos, int fPos,
                      int gPos, int hPos, int iPos,
                      int jPos, int kPos, int lPos);
    Quadbot Quadbot::getPos(int pos[][3]);
    Quadbot Quadbot::getLastPos(int pos[][3]);
    Quadbot wait(int millis);
    Quadbot go();
    Quadbot flatten();
    Quadbot stand();
    Quadbot walk();
    Quadbot dance();
    Quadbot wave();
    Leg* a();
    Leg* b();
    Leg* c();
    Leg* d();
    Leg legs[4];
    level speed = medium;
  private:
    void copyPos(int src[3], int des[3]);
};

void Quadbot::init(int pinA, int pinB, int pinC,
                   int pinD, int pinE, int pinF,
                   int pinG, int pinH, int pinI,
                   int pinJ, int pinK, int pinL) {
  this->a()->init(false, pinA, true, pinB, true, pinC);
  this->b()->init(true, pinD, false, pinE, false, pinF);
  this->c()->init(false, pinG, true, pinH, true, pinI);
  this->d()->init(true, pinJ, false, pinK, false, pinL);
  return *this;
}

Leg* Quadbot::a() {
  return &(this->legs[0]);
}

Leg* Quadbot::b() {
  return &(this->legs[1]);
}

Leg* Quadbot::c() {
  return &(this->legs[2]);
}

Leg* Quadbot::d() {
  return &(this->legs[3]);
}

Quadbot Quadbot::go() {
  // int increment;
  // increment = speed == slowest ? 5 : increment;
  // increment = speed == slow ? 10 : increment;
  // increment = speed == medium ? 20 : increment;
  // increment = speed == fast ? 45 : increment;
  // increment = speed == fastest ? 180 : increment;
  // int pos[4][3];
  // this->getLastPos(pos);
  // int endPos[4][3];
  // this->getPos(endPos);
  // bool moving = true;
  // while(moving) {
  //   moving = false;
    // for(int legIndex = 0; legIndex < 4; legIndex++) {
    //   for(int jointIndex = 0; jointIndex < 3; jointIndex++) {
    //     pos[legIndex][jointIndex] += pos[legIndex][jointIndex] > endPos[legIndex][jointIndex] ? increment : -increment;
    //     moving = pos[legIndex][jointIndex] < endPos[legIndex][jointIndex];
    //     if(!moving) {
    //       pos[legIndex][jointIndex] = endPos[legIndex][jointIndex];
    //     }
    //     this->legs[legIndex].joints[jointIndex].set(pos[legIndex][jointIndex]);
    //   }
    // }

  for(int i = 0; i < 4; i++) {
    this->legs[i].go();
  }

  //   delay(1);
  // }
  return *this;
}

Quadbot Quadbot::set(int pos[][3]) {
  for(int i = 0; i < 4; i++) {
    this->legs[i].set(pos[i]);
  }
  return *this;
}

Quadbot Quadbot::set(int aPos, int bPos, int cPos,
                  int dPos, int ePos, int fPos,
                  int gPos, int hPos, int iPos,
                  int jPos, int kPos, int lPos) {
  this->a()->set(aPos, bPos, cPos);
  this->b()->set(dPos, ePos, fPos);
  this->c()->set(gPos, hPos, iPos);
  this->d()->set(jPos, kPos, lPos);
  return *this;
}

Quadbot Quadbot::getPos(int pos[][3]) {
  int legPos[3];
  this->a()->getPos(legPos);
  this->copyPos(legPos, pos[0]);
  this->b()->getPos(legPos);
  this->copyPos(legPos, pos[1]);
  this->c()->getPos(legPos);
  this->copyPos(legPos, pos[2]);
  this->d()->getPos(legPos);
  this->copyPos(legPos, pos[3]);
  return *this;
}

Quadbot Quadbot::getLastPos(int pos[][3]) {
  int legPos[3];
  this->a()->getLastPos(legPos);
  this->copyPos(legPos, pos[0]);
  this->b()->getLastPos(legPos);
  this->copyPos(legPos, pos[1]);
  this->c()->getLastPos(legPos);
  this->copyPos(legPos, pos[2]);
  this->d()->getLastPos(legPos);
  this->copyPos(legPos, pos[3]);
  return *this;
}

void Quadbot::copyPos(int src[3], int des[3]) {
  for(int i = 0; i < 3; i++) {
    des[i] = src[i];
  }
  return *this;
}

#include "actions.h"
#endif
