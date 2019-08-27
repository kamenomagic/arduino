#ifndef Joint_h
#define Joint_h
#include <Arduino.h>
#include <Servo.h>

// "clockwise" means standing the servo motor with the white join facing down, and on the top side of the view, looking straight down on the servo. This means the number gets greater as it goes clockwise in this manner, and less as it goes counter-clockwise. 
// This is used to orient the joints to understand the direction
// Clockwise means bigger

class Joint {
  public:
    void init(bool clockwise, int pin);
    void setLimits(int minimum, int maximum);
    bool clockwise;
    int minimum;
    int middle;
    int maximum;
    int pos;
    Servo servo;
};

void Joint::init(bool clockwise, int pin) {
  this->clockwise = clockwise;
  this->servo.attach(pin);
  this->setLimits(0, 180);
}

void Joint::setLimits(int minimum, int maximum) {
  this->minimum = minimum;
  this->maximum = maximum;
  this->middle = ((maximum - minimum) + 2) / 5 * 5;
}
#endif
