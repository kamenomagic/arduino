#include "quadbot.h"

Quadbot bot;

void setup() {
  Serial.begin(9600);
  bot.init(A5, A0, A1,
           4, 3, 2,
           7, 6, 5,
           A2, A3, A4);
  bot.a.hip.setLimits(45, 145);
  bot.b.hip.setLimits(35, 130);
  bot.c.hip.setLimits(50, 150);
  bot.d.hip.setLimits(45, 145);
}

void loop() {
  bot.flatten();
  bot.a.foot.set(90);
  bot.go();
  delay(4000);
  /* bot.stand(); */
  /* bot.a.foot.set(180); */
  /* delay(1000); */
}
