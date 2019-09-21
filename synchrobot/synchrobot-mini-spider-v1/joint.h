#include "quadbot.h"
#ifndef Joint_h
#define Joint_h
#include <Arduino.h>
#include <Servo.h>
class Quadbot;
class Leg;

// "clockwise" means standing the servo motor with the white join facing down, and on the top side of the view, looking straight down on the servo. This means the number gets greater as it goes clockwise in this manner, and less as it goes counter-clockwise. 
// This is used to orient the joints to understand the direction
// Clockwise means bigger, and if clockwise is false then it offsets in the other direction (lower number)

class Joint {
  private:
  int pos;
  int movePos;
  int lastPos;
  int minPos;
  int midPos;
  int maxPos;
  bool clockwise;

  public:
  Quadbot* bot;
  Leg* leg;
  Servo servo;

  Joint(Quadbot* inBot, Leg* inLeg, bool newClockwise, int pin) {
    bot = inBot;
    leg = inLeg;
    clockwise = newClockwise;
    servo.attach(pin);
    setLimits(0, 180);
    lastPos = midPos;
    movePos = lastPos;
    middle();
  }

  Joint* setLimits(int newMinPos, int newMaxPos) {
    minPos = newMinPos;
    maxPos = newMaxPos;
    midPos = 90;
    return this;
  }

  int getPos() {
    return clockwise ? pos : 180 - pos;
  }

  int getLastPos() {
    return clockwise ? lastPos : 180 - lastPos;
  }

  Joint* set(int newPos) {
    pos = clip(clockwise ? newPos : 180 - newPos);
    movePos = lastPos;
    return this;
  }

  Joint* offset(int offset) {
    return set(pos + offset);
  }

  Joint* offsetGo(int offset) {
    return set(pos + offset)->go();
  }

  Joint* setGo(int newPos) {
    pos = clip(clockwise ? newPos : 180 - newPos);
    movePos = lastPos;
    go();
    return this;
  }

  Joint* go() {
    go(180);
    return this;
  }

  bool go(int increment) {
    if(movePos == pos) return true;
    bool positive = (movePos < pos);
    movePos += positive ? increment : -increment;
    movePos = (positive && movePos >= pos) || (!positive && movePos <=pos) ? pos : movePos;
    servo.write(movePos);
    if(movePos == pos) {
      lastPos = pos;
      return true;
    } else {
      return false;
    }
  }

  int clip(int newPos) {
    newPos = newPos < minPos ? minPos : newPos;
    newPos = newPos > maxPos ? maxPos : newPos;
    return newPos;
  }

  Joint* minimum() {
    set(minPos);
    return this;
  }

  Joint* middle() {
    set(midPos);
    return this;
  }

  Joint* maximum() {
    set(maxPos);
    return this;
  }

  Joint* wait(int millis) {
    delay(millis);
    return this;
  }
};
#endif
