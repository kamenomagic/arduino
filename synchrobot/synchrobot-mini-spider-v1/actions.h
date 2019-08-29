Quadbot Quadbot::wait(int millis) {
  for(int i = 0; i < millis / 5; i++) {
    this->go();
    delay(4);
  }
  return *this;
}

Quadbot Quadbot::flatten() {
  for(int i = 0; i < 4; i++) {
    this->legs[i].middle();
  }
  return *this;
}

Quadbot Quadbot::stand() {
  for(int i = 0; i < 4; i++) {
    this->feet[i].set(30);
    this->thighs[i].set(100);
    Joint hip = this->hips[i];
    hip.set(hip.midPos);
  }
  return *this;
}

Quadbot Quadbot::walk() {
  return *this;
}

Quadbot Quadbot::dance() {
  return *this;
}

Quadbot Quadbot::wave() {
  return *this;
}
