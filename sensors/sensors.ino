#include "Pins.h"
#include "Sonar.h"
#include "IR.h"
#include "Light.h"
#include "Air.h"
#include "Motion.h"
#include "LED.h"

IR ir(irReceivePin);
Sonar sonar(trigPin, echoPin);
Light light(lightPin);
Air air(airPin);

void setup() {
  Serial.begin(115200);
  delay(50);
  initMotion(motionPin);
  initLed(redPin, greenPin, bluePin);
}

void loop() {
  String code = ir.handleReceive();
  if (code.length() > 0) {
    Serial.println("I" + String(code));
  }
  handleMotion();
  handleLed();
  Serial.println("U" + String(sonar.getDistanceReading()));
  Serial.println("L" + String(light.getReading()));
  Serial.println("T" + String(air.getTemperature()));
  Serial.println("H" + String(air.getHumidity()));
  delay(500);
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'I':
        ir.handleSend();
        break;
      case 'E':
        setLedColor();
        break;
      default:
        delay(50);
        while (Serial.available()) {
          Serial.read();
          delay(50);
        }
        break;
    }
  }
}

