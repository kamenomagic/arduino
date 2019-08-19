#ifndef Explorer_h
#define Explorer_h
#include "Arduino.h"
#include "Motors.h"
#include "Sonar.h"
#include "Piezo.h"
#include <Servo.h>

class Explorer {
  public:
    void init();
    void explore();
    void servoLeft();
    void servoFrontLeft();
    void servoFront();
    void servoFrontRight();
    void servoRight();
    Motors motors;
    Servo servo;
    Sonar sonar;
    Piezo piezo;
};

void Explorer::init() {
    this->piezo.init(1);
    this->sonar.init(12, 13);
    this->servo.attach(10);
}

void Explorer::explore() {
    while(true) {
        this->piezo.beep();
        this->servoFront();
        int distance = this->sonar.getDistance();
        while(distance > 10) {
            this->motors.forward();
            distance = this->sonar.getDistance();
        }
        this->motors.stop();
        delay(2000);
        this->servoLeft();
        delay(5000);
        this->servoRight();
        delay(5000);
        this->piezo.happy();
        this->motors.clockwise();
        delay(3000);
        this->motors.stop();
        delay(3000);
    }
    // this->piezo.beep();
    // while(true) {
    //     int distance = this->sonar.getDistance();
    //     if(distance < 10) {
    //         this->motors.stop();
    //         this->piezo.happy();
    //         int distances[5];
    //         this->servoLeft();
    //         distances[0] = this->sonar.getDistance();
    //         this->servoFrontLeft();
    //         distances[1] = this->sonar.getDistance();
    //         this->servoFront();
    //         distances[2] = this->sonar.getDistance();
    //         this->servoFrontRight();
    //         distances[3] = this->sonar.getDistance();
    //         this->servoRight();
    //         distances[4] = this->sonar.getDistance();
    //         this->servoFront();
    //         int longest = 0;
    //         for(int i = 1; i < 5; i++) {
    //             longest = distances[i] > longest ? i : longest;
    //         }
    //         this->piezo.error();
    //         switch(longest) {
    //             case 0:
    //                 this->motors.counterclockwise();
    //                 delay(500);
    //             case 1:
    //                 this->motors.counterclockwise();
    //                 delay(500);
    //                 break;
    //             case 4:
    //                 this->motors.clockwise();
    //                 delay(500);
    //             case 3:
    //                 this->motors.clockwise();
    //                 delay(500);
    //                 break;
    //             case 2:
    //             default:
    //                 break;
    //         }
    //         this->piezo.beep();
    //     } else {
    //         this->piezo.beep();
    //         this->motors.forward();
    //         delay(50);
    //     }
    // }
    // this->piezo.sad();
}

void Explorer::servoLeft() {
    this->servo.write(180);
}

void Explorer::servoFrontLeft() {
    this->servo.write(135);
}

void Explorer::servoFront() {
    this->servo.write(95);
}

void Explorer::servoFrontRight() {
    this->servo.write(45);
}

void Explorer::servoRight() {
    this->servo.write(10);
}
#endif
