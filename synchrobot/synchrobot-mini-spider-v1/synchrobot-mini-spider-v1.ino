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
  delay(100);
}
