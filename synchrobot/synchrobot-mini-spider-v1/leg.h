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
    Joint foot;
    Joint thigh;
    Joint hip;
    Joint joints[3] = {foot, thigh, hip};
};

void Leg::init(bool footClockwise, int footPin,
               bool thighClockwise, int thighPin,
               bool hipClockwise, int hipPin) {
  this->foot.init(footClockwise, footPin);
  this->thigh.init(thighClockwise, thighPin);
  this->hip.init(hipClockwise, hipPin);
}

void Leg::go() {
  this->foot.go();
  this->thigh.go();
  this->hip.go();
}

void Leg::middle() {
  this->foot.middle();
  this->thigh.middle();
  this->hip.middle();
}

void Leg::set(int foot, int thigh, int hip) {
  this->foot.set(foot);
  this->thigh.set(thigh);
  this->hip.set(hip);
}

void Leg::getPos(int pos[]) {
  pos[0] = this->foot.pos;
  pos[1] = this->thigh.pos;
  pos[2] = this->hip.pos;
}

void Leg::getLastPos(int pos[]) {
  pos[0] = this->foot.lastPos;
  pos[1] = this->thigh.lastPos;
  pos[2] = this->hip.lastPos;
}
#endif
