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

  Joint(bool clockwise, int pin) {
    this->clockwise = clockwise;
    this->servo.attach(pin);
    this->setLimits(0, 180);
    this->lastPos = this->midPos;
    this->middle();
  }

  void setLimits(int minPos, int maxPos) {
    this->minPos = minPos;
    this->maxPos = maxPos;
    this->midPos = 90;
  }

  void go() {
    Serial.print("go:");
    Serial.println(this->pos);
    this->servo.write(this->pos);
    this->lastPos = this->pos;
    Serial.print("lastpos is now:");
    Serial.println(this->pos);
  }

  void minimum() {
    this->set(this->minPos);
  }

  void middle() {
    this->set(this->midPos);
  }

  void maximum() {
    this->set(this->maxPos);
  }

  void set(int pos) {
    this->pos = this->clockwise ? pos : 180 - pos;
    this->pos = this->pos < this->minPos ? this->minPos : this->pos;
    this->pos = this->pos > this->maxPos ? this->maxPos : this->pos;
    Serial.print("set:");
    Serial.println(this->pos);
  }
};
#endif
