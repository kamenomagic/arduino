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
    void tick();
    void middle();
    void set(int pos);
    bool clockwise;
    int minPos;
    int midPos;
    int maxPos;
    int pos;
    Servo servo;
};

void Joint::init(bool clockwise, int pin) {
  this->clockwise = clockwise;
  this->servo.attach(pin);
  this->setLimits(0, 180);
}

void Joint::setLimits(int minPos, int maxPos) {
  this->minPos = minPos;
  this->maxPos = maxPos;
  this->midPos = 90;
}

void Joint::tick() {
  this->servo.write(this->pos);
}

void Joint::middle() {
  this->pos = this->midPos;
}

void Joint::set(int pos) {
  this->pos = this->clockwise ? pos : 180 - pos;
  this->pos = this->pos < this->minPos ? this->minPos : this->pos;
  this->pos = this->pos > this->maxPos ? this->maxPos : this->pos;
}
#endif
