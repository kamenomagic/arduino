#ifndef Leg_h
#define Leg_h
#include <Arduino.h>
#include "joint.h"

class Leg {
  public:
    void init(bool footClockwise, int footPin,
              bool thighClockwise, int thighPin,
              bool hipClockwise, int hipPin);
    void go();
    void middle();
    void set(int foot, int thigh, int hip);
    void getPos(int pos[]);
    void getLastPos(int pos[]);
    Joint* foot();
    Joint* thigh();
    Joint* hip();
    Joint joints[3];
};

void Leg::init(bool footClockwise, int footPin,
               bool thighClockwise, int thighPin,
               bool hipClockwise, int hipPin) {
  this->foot()->init(footClockwise, footPin);
  this->thigh()->init(thighClockwise, thighPin);
  this->hip()->init(hipClockwise, hipPin);
}

Joint* Leg::foot() {
  return &(this->joints[0]);
}

Joint* Leg::thigh() {
  return &(this->joints[1]);
}

Joint* Leg::hip() {
  return &(this->joints[2]);
}

void Leg::go() {
  for(int i = 0; i < 3; i++) {
    this->joints[i].go();
  }
}

void Leg::middle() {
  for(int i = 0; i < 3; i++) {
    this->joints[i].middle();
  }
}

void Leg::set(int foot, int thigh, int hip) {
  this->foot()->set(foot);
  this->thigh()->set(thigh);
  this->hip()->set(hip);
}

void Leg::getPos(int pos[]) {
  for(int i = 0; i < 3; i++) {
    pos[i] = this->joints[i].pos;
  }
}

void Leg::getLastPos(int pos[]) {
  for(int i = 0; i < 3; i++) {
    pos[i] = this->joints[i].lastPos;
  }
}
#endif
