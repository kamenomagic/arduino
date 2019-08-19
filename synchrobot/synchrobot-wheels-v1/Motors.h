#ifndef motors_h
#define motors_h
#include "Arduino.h"

const int enA = 3;
const int in1 = 2;
const int in2 = 4;
const int in3 = 8;
const int in4 = 7;
const int enB = 6;
const boolean A = true;
const boolean B = false;
const boolean FORWARD = false;
const boolean BACKWARD = true; 
const int topSpeed = 200;
const int middleSpeed = 150;
const int bottomSpeed = 100;
const int normalSpeed = middleSpeed;

class Motors {
  public:
    Motors();
    void stop();
    void forward();
    void forward(boolean a);
    void backward();
    void backward(boolean a);
    void clockwise();
    void counterclockwise();
    void stopMotor(boolean a);
    void setMotor(boolean a, boolean forward, int speed);
    void setMotorDirection(boolean a, boolean forward);
    void setMotorSpeed(boolean a, int speed);
    void demo();
};

Motors::Motors() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
}

void Motors::stop() {
    stopMotor(A);
    stopMotor(B);
}

void Motors::forward() {
    setMotor(A, FORWARD, normalSpeed);
    setMotor(B, FORWARD, normalSpeed);
}

void Motors::backward() {
    setMotor(A, BACKWARD, normalSpeed);
    setMotor(B, BACKWARD, normalSpeed);
}

void Motors::forward(boolean a) {
    setMotor(a ? A : B, FORWARD, normalSpeed);
}

void Motors::backward(boolean a) {
    setMotor(a ? A : B, BACKWARD, normalSpeed);
}

void Motors::clockwise() {
    setMotor(A, FORWARD, normalSpeed);
    setMotor(B, BACKWARD, normalSpeed);
}

void Motors::counterclockwise() {
    setMotor(A, BACKWARD, normalSpeed);
    setMotor(B, FORWARD, normalSpeed);
}

void Motors::stopMotor(boolean a) {
    digitalWrite(a ? in1 : in3, LOW);
    digitalWrite(a ? in2 : in4, LOW);
}

void Motors::setMotor(boolean a, boolean forward, int speed) {
    setMotorDirection(a, forward);
    setMotorSpeed(a, speed);
}

void Motors::setMotorDirection(boolean a, boolean forward) {
    digitalWrite(a ? in1 : in3, forward ? HIGH : LOW);
    digitalWrite(a ? in2 : in4, forward ? LOW : HIGH);
}

void Motors::setMotorSpeed(boolean a, int speed) {
    analogWrite(a ? enA : enB, speed);
}

void Motors::demo() {
    this->forward();
    delay(2000);
    this->stop();
    delay(2000);
    this->backward();
    delay(2000);
    this->stop();
    delay(2000);
    this->clockwise();
    delay(2000);
    this->stop();
    delay(2000);
    this->counterclockwise();
    delay(2000);
    this->stop();
    delay(2000);
    this->forward(A);
    delay(2000);
    this->stop();
    delay(2000);
    this->forward(B);
    delay(2000);
    this->stop();
    delay(5000);
}

#endif
