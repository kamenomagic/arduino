#ifndef Leg_h
#define Leg_h
#include <Arduino.h>
#include "joint.h"
class Quadbot;

class Leg {
  public:
  Joint* joints[3];
  Quadbot* bot;
  Leg(Quadbot* inBot,
      bool footClockwise, int footPin,
      bool thighClockwise, int thighPin,
      bool hipClockwise, int hipPin) {
    bot = inBot;
    joints[0] = new Joint(bot, this, footClockwise, footPin);
    joints[1] = new Joint(bot, this, thighClockwise, thighPin);
    joints[2] = new Joint(bot, this, hipClockwise, hipPin);
  }

  Joint* joint(int i) {
    return joints[i];
  }

  Joint* foot() {
    return joint(0);
  }

  Joint* thigh() {
    return joint(1);
  }

  Joint* hip() {
    return joint(2);
  }

  Leg* go() {
    go(180);
    return this;
  }

  bool go(int increment) {
    bool moved = true;
    for(int i = 0; i < 3; i++) {
      moved = joint(i)->go(increment) && moved;
    }
    return moved;
  }

  Leg* goRaise() {
    thigh()->set(130)->go();
  }

  Leg* goLower() {
    thigh()->set(100)->go();
  }

  Leg* middle() {
    for(int i = 0; i < 3; i++) {
      joint(i)->middle();
    }
    return this;
  }

  Leg* set(int pos[3]) {
    for(int i = 0; i < 3; i++) {
      joint(i)->set(pos[i]);
    }
    return this;
  }

  Leg* set(int footPos, int thighPos, int hipPos) {
    foot()->set(footPos);
    thigh()->set(thighPos);
    hip()->set(hipPos);
    return this;
  }

  Leg* wait(int millis) {
    delay(millis);
    return this;
  }

  Leg* getPos(int pos[]) {
    for(int i = 0; i < 3; i++) {
      pos[i] = joint(i)->getPos();
    }
    return this;
  }

  Leg* getLastPos(int pos[]) {
    for(int i = 0; i < 3; i++) {
      pos[i] = joint(i)->getLastPos();
    }
    return this;
  }
};
#endif
