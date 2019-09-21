#include "quadbot.h"

Quadbot* bot;

void setup() {
  Serial.begin(9600);
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
}

void loop() {
  bot->
    a()->hip()->set(0)->bot->
    b()->hip()->set(0)->bot->
    c()->hip()->set(0)->bot->
    d()->hip()->set(0)->bot->
    go()->wait(1000);
  /*   goLiftFeet(1) */
  ;
}
