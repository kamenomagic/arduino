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
    int lastPos;
    Servo servo;

  Joint(bool newClockwise, int pin) {
    clockwise = newClockwise;
    servo.attach(pin);
    setLimits(0, 180);
    lastPos = midPos;
    middle();
  }

  void setLimits(int newMinPos, int newMaxPos) {
    minPos = newMinPos;
    maxPos = newMaxPos;
    midPos = 90;
  }

  void set(int newPos) {
    pos = clockwise ? newPos : 180 - newPos;
    pos = pos < minPos ? minPos : pos;
    pos = pos > maxPos ? maxPos : pos;
    Serial.print("set:");
    Serial.println(pos);
  }

  void go() {
    Serial.print("go:");
    Serial.println(pos);
    servo.write(pos);
    lastPos = pos;
    Serial.print("lastpos is now:");
    Serial.println(pos);
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
