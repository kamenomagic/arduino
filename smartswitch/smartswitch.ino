#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid = "The Pink Rabbit";
const char* password = "walkingwithspiders";
const int pin = 2;
boolean on = true;

void setup() {
  pinMode(pin, OUTPUT);
  WiFi.hostname("Orange");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.on("/", switchToggle);
  server.on("/toggle", switchToggle);
  server.on("/on", switchOn);
  server.on("/off", switchOff);
  server.begin();
}

void sendState() {
  server.send(200, "text/plain", "The switch is now " + String(on ? "on" : "off") + ".\n");
}

void switchOn() {
  digitalWrite(pin, LOW);
  on = true;
  sendState();
}

void switchOff() {
  digitalWrite(pin, HIGH);
  on = false;
  sendState();
}

void switchToggle() {
  on ? switchOff() : switchOn();
}

void loop() {
  server.handleClient();
}
