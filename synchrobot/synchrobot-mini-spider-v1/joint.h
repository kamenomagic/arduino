#ifndef Joint_h
#define Joint_h
#include <Arduino.h>
#include <Servo.h>

// "clockwise" means standing the servo motor with the white join facing down, and on the top side of the view, looking straight down on the servo. This means the number gets greater as it goes clockwise in this manner, and less as it goes counter-clockwise. 
// This is used to orient the joints to understand the direction
// Clockwise means bigger, and if clockwise is false then it offsets in the other direction (lower number)

class Joint {
  public:
  bool clockwise;
  int minPos;
  int midPos;
  int maxPos;
  int pos;
  int movePos;
  int lastPos;
  Servo servo;

  Joint(bool newClockwise, int pin) {
    clockwise = newClockwise;
    servo.attach(pin);
    setLimits(0, 180);
    lastPos = midPos;
    movePos = lastPos;
    middle();
  }

  void setLimits(int newMinPos, int newMaxPos) {
    minPos = newMinPos;
    maxPos = newMaxPos;
    midPos = 90;
  }

  void set(int newPos) {
    pos = clip(clockwise ? newPos : 180 - newPos);
    movePos = lastPos;
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

  void minimum() {
    set(minPos);
  }

  void middle() {
    set(midPos);
  }

  void maximum() {
    set(maxPos);
  }
};
#endif
