#ifndef Piezo_h
#define Piezo_h
#include "Arduino.h"
#include "tones.h"

class Piezo {
  public:
    void init(int pin);
    void beep(int note, int duration, int pause);
    void beep(int note, int duration);
    void beep(int tone);
    void sad();
    void happy();
    void beep();
    void error();
  private:
    int pin;
};

void Piezo::init(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Piezo::beep(int note, int duration, int pause) {
    tone(pin, note, duration);
    delay(pause);
    noTone(pin);
}

void Piezo::beep(int note, int duration) {
    this->beep(note, duration, 200);
}

void Piezo::beep(int note) {
    this->beep(note, 200, 200);
}

void Piezo::sad() {
    this->beep(NOTE_E3, 1000);
    this->beep(NOTE_DS3, 1000);
    this->beep(NOTE_D3, 1000);
    this->beep(NOTE_CS3, 1000);
    this->beep(NOTE_C3, 2000);
}

void Piezo::happy() {
    this->beep(NOTE_C3, 1000);
    this->beep(NOTE_E3, 1000);
    this->beep(NOTE_G3, 1000);
    this->beep(NOTE_C4, 600);
}

void Piezo::beep() {
    this->beep(NOTE_C3);
    this->beep(NOTE_G3, 1000);
}

void Piezo::error() {
    this->beep(NOTE_G3);
    this->beep(NOTE_C3, 1000);
}
#endif
