#ifndef Leg_h
#define Leg_h
#include <Arduino.h>
#include "joint.h"

class Leg {
  private:
    Joint* joints[3];

  public:
  Leg(bool footClockwise, int footPin,
                 bool thighClockwise, int thighPin,
                 bool hipClockwise, int hipPin) {
    joints[0] = new Joint(footClockwise, footPin);
    joints[1] = new Joint(thighClockwise, thighPin);
    joints[2] = new Joint(hipClockwise, hipPin);
  }

  Joint foot() {
    return joint(0);
  }

  Joint thigh() {
    return joint(1);
  }

  Joint hip() {
    return joint(2);
  }

  Joint joint(int i) {
    return *(joints[i]);
  }

  void go() {
    for(int i = 0; i < 3; i++) {
      joint(i).go();
    }
  }

  void middle() {
    for(int i = 0; i < 3; i++) {
      joint(i).middle();
    }
  }

  void set(int pos[3]) {
    for(int i = 0; i < 3; i++) {
      joint(i).set(pos[i]);
    }
  }

  void set(int footPos, int thighPos, int hipPos) {
    foot().set(footPos);
    thigh().set(thighPos);
    hip().set(hipPos);
  }

  void getPos(int pos[]) {
    for(int i = 0; i < 3; i++) {
      pos[i] = joint(i).pos;
    }
  }

  void getLastPos(int pos[]) {
    for(int i = 0; i < 3; i++) {
      pos[i] = joint(i).lastPos;
    }
  }
};
#endif
