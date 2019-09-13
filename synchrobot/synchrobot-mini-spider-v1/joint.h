#ifndef Joint_h
#define Joint_h
#include <Arduino.h>
#include <Servo.h>

// "clockwise" means standing the servo motor with the white join facing down, and on the top side of the view, looking straight down on the servo. This means the number gets greater as it goes clockwise in this manner, and less as it goes counter-clockwise. 
// This is used to orient the joints to understand the direction
// Clockwise means bigger, and if clockwise is false then it offsets in the other direction (lower number)

class Joint {
  public:
    void init(bool clockwise, int pin);
    void setLimits(int minPos, int maxPos);
    void go();
    void minimum();
    void middle();
    void maximum();
    void set(int pos);
    bool clockwise;
    int minPos;
    int midPos;
    int maxPos;
    int pos;
    int lastPos;
    int pin;
    Servo servo;
};

void Joint::init(bool clockwise, int pin) {
  this->clockwise = clockwise;
  this->pin = pin;
  this->servo.attach(pin);
  this->setLimits(0, 180);
  this->set(this->midPos);
}

void Joint::setLimits(int minPos, int maxPos) {
  this->minPos = minPos;
  this->maxPos = maxPos;
  this->midPos = 90;
}

void Joint::go() {
  this->servo.write(this->pos);
  this->lastPos = this->pos;
}

void Joint::minimum() {
  this->set(this->minPos);
}

void Joint::middle() {
  this->set(this->midPos);
}

void Joint::maximum() {
  this->set(this->maxPos);
}

void Joint::set(int pos) {
  this->pos = this->clockwise ? pos : 180 - pos;
  this->pos = this->pos < this->minPos ? this->minPos : this->pos;
  this->pos = this->pos > this->maxPos ? this->maxPos : this->pos;
}
#endif
