#ifndef Motion_h
#define Motion_h
#include "Arduino.h"

volatile bool lastReadingValue = false;
bool changed = false;
int internalMotionPin;

void initMotion();
void handleMotion();
void motionChange();
bool getMotionReading();

void initMotion(int motionPin) {
  internalMotionPin = motionPin;
  pinMode(internalMotionPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(internalMotionPin), motionChange, CHANGE);
}

void handleMotion() {
  if(changed) {
    Serial.println("M" + String(lastReadingValue));
    changed = false;
  }
}

void motionChange() {
    lastReadingValue = getMotionReading();
    changed = true;
}

bool getMotionReading() {
  return digitalRead(internalMotionPin) == HIGH;
}

#endif
