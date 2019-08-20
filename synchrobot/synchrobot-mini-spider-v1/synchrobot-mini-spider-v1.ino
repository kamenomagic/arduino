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

/* feet */
int aPos = 160;
int dPos = 20;
int gPos = 160;
int jPos = 20;

/* thigh */
int bPos = 140;
int ePos = 40;
int hPos = 140;
int kPos = 40;

/* hip */
int cPos = 140;
int fPos = 40;
int iPos = 140;
int lPos = 40;

void setup() {
  f.attach(2);
  e.attach(3);
  d.attach(4);

  i.attach(5);
  h.attach(6);
  g.attach(7);

  j.attach(A2);
  k.attach(A3);
  l.attach(A4);

  a.attach(A5);
  b.attach(A6);
  c.attach(A7);
}

void loop() {
  for(int i = 0; bPos > 90 && ePos < 110; i++) {
    bPos--;
    ePos++;
    hPos--;
    kPos++;

    aPos--;
    dPos++;
    gPos--;
    jPos++;
    
    adjust();
    delay(50);
  }
  for(int i = 0; bPos < 140 && ePos > 40; i++) {
    bPos++;
    ePos--;
    hPos++;
    kPos--;

    aPos++;
    dPos--;
    gPos++;
    jPos--;

    adjust();
    delay(50);
  }
}

void adjust() {
  a.write(aPos);
  b.write(bPos);
  c.write(cPos);
  g.write(gPos);
  h.write(hPos);
  i.write(iPos);
  d.write(dPos);
  e.write(ePos);
  f.write(fPos);
  j.write(jPos);
  k.write(kPos);
  l.write(lPos);

}
