#ifndef Air_h
#define Air_h
#include "Arduino.h"
#include "src/DHT/DHT.h"

class Air {
  public:
    Air(int pin);
    float getTemperature();
    float getHumidity();
  private:
    DHT dht;
};

Air::Air(int pin): dht(pin, DHT11) {
  dht.begin();
}

float Air::getTemperature() {
  return ((dht.readTemperature() * 9 / 5) + 32) ;
}

float Air::getHumidity() {
  return dht.readHumidity();
}
#endif
