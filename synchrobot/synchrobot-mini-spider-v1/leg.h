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
    this->joints[0] = new Joint(footClockwise, footPin);
    this->joints[1] = new Joint(thighClockwise, thighPin);
    this->joints[2] = new Joint(hipClockwise, hipPin);
  }

  Joint foot() {
    return this->joint(0);
  }

  Joint thigh() {
    return this->joint(1);
  }

  Joint hip() {
    return this->joint(2);
  }

  Joint joint(int i) {
    return *(this->joints[i]);
  }

  void go() {
    for(int i = 0; i < 3; i++) {
      this->joint(i).go();
    }
  }

  void middle() {
    for(int i = 0; i < 3; i++) {
      this->joint(i).middle();
    }
  }

  void set(int pos[3]) {
    for(int i = 0; i < 3; i++) {
      this->joint(i).set(pos[i]);
    }
  }

  void set(int foot, int thigh, int hip) {
    this->foot().set(foot);
    this->thigh().set(thigh);
    this->hip().set(hip);
  }

  void getPos(int pos[]) {
    for(int i = 0; i < 3; i++) {
      pos[i] = this->joint(i).pos;
    }
  }

  void getLastPos(int pos[]) {
    for(int i = 0; i < 3; i++) {
      pos[i] = this->joint(i).lastPos;
    }
  }
};
#endif
