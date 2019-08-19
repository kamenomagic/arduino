#include <Servo.h>

Servo a;
Servo b;
Servo c;

Servo d;
Servo e;
Servo f;

Servo g;
Servo h;
Servo i;

Servo j;
Servo k;
Servo l;


int aPos = 0;
int bPos = 0;
int cPos = 0;

int dPos = 0;
int ePos = 0;
int fPos = 0;

int gPos = 0;
int hPos = 0;
int iPos = 0;

int jPos = 0;
int kPos = 0;
int lPos = 0;

Servo test;
int pos;

void setup() {
  /* f.attach(2); */
  /* e.attach(3); */
  /* d.attach(4); */
  /*  */
  /* i.attach(5); */
  /* h.attach(6); */
  /* g.attach(7); */
  /*  */
  /* j.attach(A2); */
  /* k.attach(A3); */
  /* l.attach(A4); */
  /*  */
  /* a.attach(A5); */
  /* b.attach(A6); */
  /* c.attach(A7); */

  test.attach(A7);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    test.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    test.write(pos);
    delay(15);
  }
}
