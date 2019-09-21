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
  level speed = medium;

  public:
  Leg* legs[4];
  Quadbot(int pinA, int pinB, int pinC,
                     int pinD, int pinE, int pinF,
                     int pinG, int pinH, int pinI,
                     int pinJ, int pinK, int pinL) {
    legs[0] = new Leg(false, pinA, true, pinB, true, pinC);
    legs[1] = new Leg(true, pinD, false, pinE, false, pinF);
    legs[2] = new Leg(false, pinG, true, pinH, true, pinI);
    legs[3] = new Leg(true, pinJ, false, pinK, false, pinL);
  }

  Leg* leg(int i) {
    return legs[i];
  }

  Leg* a() {
    return leg(0);
  }

  Leg* b() {
    return leg(1);
  }

  Leg* c() {
    return leg(2);
  }

  Leg* d() {
    return leg(3);
  }

  Quadbot* go() {
    bool moved = false;
    while(!moved) {
      for(int i = 0; i < 4; i++) {
        moved = leg(i)->go(speedIncrement()) || moved;
        delay(50);
      }
    }
    return this;
  }

  int speedIncrement() {
    int increment;
    increment = speed == slowest ? 1 : increment;
    increment = speed == slow ? 5 : increment;
    increment = speed == medium ? 20 : increment;
    increment = speed == fast ? 75 : increment;
    increment = speed == fastest ? 180 : increment;
    return increment;
  }

  Quadbot* set(int pos[][3]) {
    for(int i = 0; i < 4; i++) {
      leg(i)->set(pos[i]);
    }
    return this;
  }

  Quadbot* set(int aPos, int bPos, int cPos,
                    int dPos, int ePos, int fPos,
                    int gPos, int hPos, int iPos,
                    int jPos, int kPos, int lPos) {
    a()->set(aPos, bPos, cPos);
    b()->set(dPos, ePos, fPos);
    c()->set(gPos, hPos, iPos);
    d()->set(jPos, kPos, lPos);
    return this;
  }

  Quadbot* getPos(int pos[][3]) {
    int legPos[3];
    a()->getPos(legPos);
    copyPos(legPos, pos[0]);
    b()->getPos(legPos);
    copyPos(legPos, pos[1]);
    c()->getPos(legPos);
    copyPos(legPos, pos[2]);
    d()->getPos(legPos);
    copyPos(legPos, pos[3]);
    return this;
  }

  Quadbot* getLastPos(int pos[][3]) {
    int legPos[3];
    a()->getLastPos(legPos);
    copyPos(legPos, pos[0]);
    b()->getLastPos(legPos);
    copyPos(legPos, pos[1]);
    c()->getLastPos(legPos);
    copyPos(legPos, pos[2]);
    d()->getLastPos(legPos);
    copyPos(legPos, pos[3]);
    return this;
  }

  Quadbot* copyPos(int src[3], int des[3]) {
    for(int i = 0; i < 3; i++) {
      des[i] = src[i];
    }
    return this;
  }

  Quadbot* wait(int millis) {
    delay(millis);
    return this;
  }

  Quadbot* setSpeed(level newSpeed) {
    speed = newSpeed;
    return this;
  }

  Quadbot* flatten() {
    for(int i = 0; i < 4; i++) {
      leg(i)->middle();
    }
    return this;
  }

  Quadbot* stand() {
    for(int i = 0; i < 4; i++) {
      leg(i)->foot()->set(30);
      leg(i)->thigh()->set(100);
      leg(i)->hip()->middle();
    }
    return this;
  }
  Quadbot* goStand() {
    return stand()->go();
  }

  Quadbot* goWave(int cycles) {
    for(int c = 0; c < cycles; c++) {
      stand()->go()->wait(1000);
      leg(0)->hip()->offset(20);
      leg(1)->thigh()->offset(50);
      leg(1)->foot()->offset(50);
      leg(2)->hip()->offset(-20);
      leg(3)->thigh()->offset(40);
      leg(3)->foot()->offset(-20);
      go()->wait(1000);
      leg(1)->hip()->offsetGo(20)->wait(200);
      leg(1)->hip()->offsetGo(-40)->wait(200);
      leg(1)->hip()->offsetGo(40)->wait(200);
      leg(1)->hip()->offsetGo(-40)->wait(200);
      leg(1)->hip()->offsetGo(40)->wait(200);
      goStand()->wait(1000);

      // int pos = leg(1)->hip()->getPos();
      // leg(1)->hip()->setGo(0)->wait(1000);
      // leg(1)->hip()->setGo(pos)->wait(1000);
    }
    return this;
  }

  Quadbot* goLiftFeet(int cycles) {
    for(int c = 0; c < cycles; c++) {
      for(int i = 0; i < 4; i++) {
        int pos = leg(i)->foot()->getPos();
        leg(i)->foot()->
          middle()->go()->wait(1000)->
          set(pos)->go()
        ;
      }
    }
    return this;
  }

  Quadbot* goWalk(int cycles) {
    for(int c = 0; c < cycles; c++) {
    }
    return this;
  }

  Quadbot* goDance() {
    return this;
  }
};
#endif
