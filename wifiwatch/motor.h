const int motorPin = 0;

void setupMotor() {
    pinMode(motorPin, OUTPUT);
}

void motorOn() {
    digitalWrite(motorPin, HIGH);
}

void motorOff() {
    digitalWrite(motorPin, LOW);
}
