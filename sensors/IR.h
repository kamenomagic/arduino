#ifndef IR_h
#define IR_h
#include "Arduino.h"
#include "src/IRremote/IRremote.h"

class IR {
  public:
    IR(int receivePin);
    void init(int receivePin);
    String handleReceive();
    void handleSend();
    decode_results test();
  private:
    IRsend irsend;
    IRrecv irrecv;
    decode_results results;
};

IR::IR(int receivePin): irrecv(receivePin) {
  irrecv.enableIRIn();
}

String IR::handleReceive() {
  String code = "";
  if (irrecv.decode(&results)) {
    switch (results.decode_type) {
      case NEC: code += 'N'; break;
      case SONY: code += 'S'; break;
      case RC5: code += '5'; break;
      case RC6: code += '6'; break;
      default: code += 'R'; break;
    }
    code += String(results.value, HEX);
    irrecv.resume();
  }
  code.toUpperCase();
  return code;
}

void IR::handleSend() {
  delay(50);
  if (Serial.available()) {
    int format = Serial.read();
    char codeArray[128];
    int bitCount = 0;
    delay(50);
    for (int i = 0; Serial.available() && i < sizeof(codeArray); i++) {
      codeArray[i] = (char) Serial.read();
      bitCount += 4;
      delay(50);
    }
    long code = strtol(codeArray, (char **) '\0', 16);
    switch (format) {
      case 'N': irsend.sendNEC(code, bitCount); break;
      case 'S':
                for(int i = 0; i < 4; i++) {
                irsend.sendSony(code, bitCount);
                }
                break;
      case '5': irsend.sendRC5(code, bitCount); break;
      case '6': irsend.sendRC6(code, bitCount); break;
    }
    irrecv.enableIRIn();
  }
}

#endif
