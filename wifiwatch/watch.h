#include "screen.h"
#include "ota.h"
#include "motor.h"
#include "photoresistor.h"
#include "led.h"

void setupWatch() {
    setupLed();
    ledOn();
    setupMotor();
    setupScreen();
    splashScreen();
    setupOTA();
    ledOff();
}

void loopWatch() {
    handleOTA();
    display.clearDisplay();
    display.drawBitmap(112, 0,  clockBitmap, 16, 16, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(getVoltageString());
    display.println(getPercentageString());
    display.display();
    delay(1);
    for(int i = 0; i < 20; i++) {
        i % 2 == 0 ? motorOn() : motorOff();
        delay(100);
    }
    for(int i = 0; i < 20; i++) {
        i % 2 == 0 ? ledOn() : ledOff();
        delay(100);
    }
}
