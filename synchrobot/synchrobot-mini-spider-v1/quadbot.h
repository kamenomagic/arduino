#ifndef Quadbot_h
#define Quadbot_h
#include <Arduino.h>
#include "leg.h"

// Legs start from front left leg (top left looking down with front of robot on top) and go clockwise
// when passing in pins, follow the legs in this pattern, front left clockwise looking down and end on back left, and
// each leg starts at the foot and goes inward such that the feet are a, d, g, j in clockwise-leg order
//
enum level {
  slowest, slow, medium, fast, fastest
};

class Quadbot {
  private:
    Leg* legs[4];
    level speed = medium;

  public:
  Quadbot(int pinA, int pinB, int pinC,
                     int pinD, int pinE, int pinF,
                     int pinG, int pinH, int pinI,
                     int pinJ, int pinK, int pinL) {
    legs[0] = new Leg(false, pinA, true, pinB, true, pinC);
    legs[1] = new Leg(true, pinD, false, pinE, false, pinF);
    legs[2] = new Leg(false, pinG, true, pinH, true, pinI);
    legs[3] = new Leg(true, pinJ, false, pinK, false, pinL);
  }

  Leg leg(int i) {
    return *(legs[i]);
  }

  Leg a() {
    return leg(0);
  }

  Leg b() {
    return leg(1);
  }

  Leg c() {
    return leg(2);
  }

  Leg d() {
    return leg(3);
  }

  Quadbot go() {
    // int increment;
    // increment = speed == slowest ? 5 : increment;
    // increment = speed == slow ? 10 : increment;
    // increment = speed == medium ? 20 : increment;
    // increment = speed == fast ? 45 : increment;
    // increment = speed == fastest ? 180 : increment;
    // int pos[4][3];
    // getLastPos(pos);
    // int endPos[4][3];
    // getPos(endPos);
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
      //     legs[legIndex].joints[jointIndex].set(pos[legIndex][jointIndex]);
      //   }
      // }

    for(int i = 0; i < 4; i++) {
      leg(i).go();
    }

    //   delay(1);
    // }
    return *this;
  }

  Quadbot set(int pos[][3]) {
    for(int i = 0; i < 4; i++) {
      leg(i).set(pos[i]);
    }
    return *this;
  }

  Quadbot set(int aPos, int bPos, int cPos,
                    int dPos, int ePos, int fPos,
                    int gPos, int hPos, int iPos,
                    int jPos, int kPos, int lPos) {
    a().set(aPos, bPos, cPos);
    b().set(dPos, ePos, fPos);
    c().set(gPos, hPos, iPos);
    d().set(jPos, kPos, lPos);
    return *this;
  }

  Quadbot getPos(int pos[][3]) {
    int legPos[3];
    a().getPos(legPos);
    copyPos(legPos, pos[0]);
    b().getPos(legPos);
    copyPos(legPos, pos[1]);
    c().getPos(legPos);
    copyPos(legPos, pos[2]);
    d().getPos(legPos);
    copyPos(legPos, pos[3]);
    return *this;
  }

  Quadbot getLastPos(int pos[][3]) {
    int legPos[3];
    a().getLastPos(legPos);
    copyPos(legPos, pos[0]);
    b().getLastPos(legPos);
    copyPos(legPos, pos[1]);
    c().getLastPos(legPos);
    copyPos(legPos, pos[2]);
    d().getLastPos(legPos);
    copyPos(legPos, pos[3]);
    return *this;
  }

  void copyPos(int src[3], int des[3]) {
    for(int i = 0; i < 3; i++) {
      des[i] = src[i];
    }
    return *this;
  }

  Quadbot wait(int millis) {
    for(int i = 0; i < millis / 5; i++) {
      go();
      delay(4);
    }
    return *this;
  }

  Quadbot flatten() {
    for(int i = 0; i < 4; i++) {
      leg(i).middle();
    }
    return *this;
  }

  Quadbot stand() {
    for(int i = 0; i < 4; i++) {
      leg(i).foot().set(30);
      leg(i).thigh().set(100);
      leg(i).hip().middle();
    }
    return *this;
  }

  Quadbot walk() {
    return *this;
  }

  Quadbot dance() {
    return *this;
  }

  Quadbot wave() {
    return *this;
  }
};
#endif
