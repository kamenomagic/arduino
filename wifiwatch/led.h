const int ledPin = 2;

void setupLed() {
    pinMode(ledPin, OUTPUT);
}

void ledOn() {
    digitalWrite(ledPin, LOW);
}

void ledOff() {
    digitalWrite(ledPin, HIGH);
}
