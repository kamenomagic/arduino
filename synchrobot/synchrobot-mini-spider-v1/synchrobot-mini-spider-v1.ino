#include "quadbot.h"

Quadbot* bot;

void setup() {
  Serial.begin(9600);
  bot = new Quadbot(A5, A0, A1,
                    4, 3, 2,
                    7, 6, 5,
                    A2, A3, A4);
  bot->
    setSpeed(fastest)->
    wait(2000)->
    goStand()->wait(2000)
  ;
}

void loop() {
  bot->
    leg(0)->hip()->set(0)->bot->
    leg(1)->hip()->set(0)->bot->
    leg(2)->hip()->set(0)->bot->
    leg(3)->hip()->set(0)->bot->
    go();
  /*   goLiftFeet(1) */
  ;
}
