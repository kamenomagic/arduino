#include "quadbot.h"

Quadbot bot;

void setup() {
  Serial.begin(9600);

  bot.init(A5, A0, A1,
           4, 3, 2,
           7, 6, 5,
           A2, A3, A4);
}

void loop() {
  for(int i = 0; i < 1000; i++) {
    bot.flat();
    bot.tick();
    delay(5);
  }
  for(int i = 0; i < 1000; i++) {
    bot.stand();
    bot.tick();
    delay(5);
  }
}
