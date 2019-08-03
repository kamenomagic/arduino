#ifndef LED_h
#define LED_h
#include "Arduino.h"

int internalRedPin;
int internalGreenPin;
int internalBluePin;
int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int stepValue = 5;
bool displayingColor = false;

void initLed();
void setLedColor();
void setRGB();
void handleLed();

void initLed(int redPin, int greenPin, int bluePin) {
  internalRedPin = redPin;
  internalGreenPin = greenPin;
  internalBluePin = bluePin;
  pinMode(internalRedPin, OUTPUT);
  pinMode(internalGreenPin, OUTPUT);
  pinMode(internalBluePin, OUTPUT);
}

void setLedColor() {
  delay(50);
  if (Serial.available()) {
    redValue = -1;
    greenValue = -1;
    blueValue = -1;
    String current = "";
    while(Serial.available()) {
      char currentChar = (char) Serial.read();
      if(currentChar == ',') {
        if(redValue == -1) {
          redValue = current.toInt();
          current = "";
        } else if(greenValue == -1) {
          greenValue = current.toInt();
          current = "";
        }
      } else {
        current += currentChar;
      }
    }
    blueValue = current.toInt();
    displayingColor = true;
  } else {
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
    displayingColor = false;
  }
}

void handleLed() {
  if(!displayingColor) {
    if(redValue == 0 && greenValue == 0 && blueValue == 0) {
        redValue = 255;
    } else if(redValue > 0 && greenValue < 255 && blueValue == 0) {
        redValue -= stepValue;
        greenValue += stepValue;
    } else if(redValue == 0 && greenValue > 0 && blueValue < 255) {
        greenValue -= stepValue;
        blueValue += stepValue;
    } else if(redValue < 255 && greenValue == 0 && blueValue > 0) {
        redValue += stepValue;
        blueValue -= stepValue;
    }
  }
  setRGB();
}

void setRGB() {
  analogWrite(internalRedPin, redValue);
  analogWrite(internalGreenPin, greenValue);
  analogWrite(internalBluePin, blueValue);
}
#endif
