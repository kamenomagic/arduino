/* curl -XPOST 192.168.1.112 -H'Content-Type: plain/text' -d'Hello, World|Hi' */
#include "src/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid = "The Pink Rabbit";
const char* password = "walkingwithspiders";

const int width = 16;
const int height = 2;
const int bufferLength = 256;
LiquidCrystal_I2C lcd(0x27, width, height);

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.on("/", handleRequest);
  server.begin();
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}

void displayMessage(String message) {
    if(message == "") {
        return;
    }
    int pipeIndex = message.indexOf('|');
    String longMessage;
    String shortMessage;
    if(pipeIndex == -1 || message.length() <= pipeIndex + 1) {
        longMessage = shortMessage = message + ' ';
    } else {
        longMessage = message.substring(0, pipeIndex) + ' ';
        shortMessage = message.substring(pipeIndex + 1).substring(0, width);
    }
    for(int i = 0; i < width; i++) {
        longMessage = ' ' + longMessage;
    }
    for(int i = 0; i < (width - shortMessage.length()) / 2; i++) {
        shortMessage = ' ' + shortMessage;
    }
    for(int i = 0; i < 3; i++) {
        flash();
        lcd.setCursor(0, 0);
        lcd.print(shortMessage);
        for(int j = 0; j < longMessage.length(); j++) {
          lcd.setCursor(0, 1);
          lcd.print(longMessage.substring(j, j + 16));
          delay(400);
        }
    }
}

void flash() {
    for(int i = 0; i < 5; i++) {
        lcd.backlight();
        delay(100);
        lcd.noBacklight();
        delay(100);
    }
    lcd.backlight();
}

void waitingAnimation() {
  lcd.clear();
  for(int i = 0; i < width; i++) {
      lcd.setCursor(i, 0);
      lcd.print((char)126);
      delay(100);
      lcd.clear();
  }
  for(int i = width - 1; i >= 0; i--) {
      lcd.setCursor(i, 1);
      lcd.print((char)127);
      delay(100);
      lcd.clear();
  }
}

void handleRequest() {
  String message = "";
  if(server.hasArg("plain")) {
      message = server.arg("plain");
      message.trim();
      if(message == "") {
          server.send(400, "text/plain", "Invalid request.");
          return;
      }
  }
  server.send(200, "text/plain", "Displaying message \"" + message + "\"\n");
  displayMessage(message);
}

void loop() {
  server.handleClient();
  waitingAnimation();
}
