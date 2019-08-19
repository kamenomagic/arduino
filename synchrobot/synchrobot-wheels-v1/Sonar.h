#ifndef Sonar_h
#define Sonar_h
#include "Arduino.h"
#include "src/NewPing/NewPing.h"

class Sonar {
  public:
    void init(int trig, int echo);
    String getDistanceReading();
    int getDistance();
  private:
    NewPing* sonar;
    String format(int inches);
    int toFeet(int inches);
    int toRemainingInches(int inches);
};

void Sonar::init(int trig, int echo) {
  sonar = new NewPing(trig, echo);
}

int Sonar::getDistance() {
    int distance = this->sonar->ping_in();
    while(distance == 0) {
        distance = this->sonar->ping_in();
    }
    return distance;
}

String Sonar::getDistanceReading() {
  return format(this->getDistance());
}

String Sonar::format(int inches) {
  return String(toFeet(inches)) + "\"" + String(toRemainingInches(inches)) + "'";
}

int Sonar::toFeet(int inches) {
  return inches / 12;
}

int Sonar::toRemainingInches(int inches) {
  return inches % 12;
}
#endif
