#ifndef Sonar_h
#define Sonar_h
#include "Arduino.h"
#include "src/NewPing/NewPing.h"

class Sonar {
  public:
    Sonar(int trig, int echo);
    String getDistanceReading();
  private:
    NewPing sonar;
    String format(int inches);
    int toFeet(int inches);
    int toRemainingInches(int inches);
};

Sonar::Sonar(int trig, int echo): sonar(trig, echo) {
}

String Sonar::getDistanceReading() {
  return format(sonar.ping_in());
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
