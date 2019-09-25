#include "quadbot.h"

Quadbot* bot;

void setup() {
  Serial.begin(115200);
  Serial.println("Init...");
  bot = new Quadbot(A5, A0, A1,
                    4, 3, 2,
                    7, 6, 5,
                    A2, A3, A4);

  bot->
    a()->hip()->setLimits(45, 145)->bot->
    b()->hip()->setLimits(35, 130)->bot->
    c()->hip()->setLimits(50, 150)->bot->
    d()->hip()->setLimits(45, 145)->bot->
    setSpeed(fastest)->
    wait(2000)->
    goStand()->wait(2000)
  ;
  Serial.println("Ready.");
}

void loop() {
  if(Serial.available() > 0) {
    char jointLetter = Serial.read();
    String posString = Serial.readString();
    Serial.print(jointLetter);
    Serial.print(":");
    Serial.println(posString);
    setJoint(jointLetter, posString.toInt());
  }
  bot->
    goWalk(1)
  ;
}

void setJoint(char jointLetter, int pos) {
  int leg =
    jointLetter <= 'c' ? 0 :
    (jointLetter <= 'f' ? 1 :
    (jointLetter <= 'i' ? 2 :
    (jointLetter <= 'l' ? 3 : -1)));
  int joint =
    jointLetter == 'a' || jointLetter == 'd' || jointLetter == 'g' || jointLetter == 'j' ? 0 :
    (jointLetter == 'b' || jointLetter == 'e' || jointLetter == 'h' || jointLetter == 'k' ? 1 :
    (jointLetter == 'c' || jointLetter == 'f' || jointLetter == 'i' || jointLetter == 'l' ? 2 : -1));
  if(leg < 0 || joint < 0 || leg > 3 || joint > 2) {
    Serial.print("Error:");
    Serial.print(jointLetter);
    Serial.print(":");
    Serial.print(leg);
    Serial.print(":");
    Serial.println(joint);
  } else {
    bot->leg(leg)->joint(joint)->set(pos)->go();
  }
}
