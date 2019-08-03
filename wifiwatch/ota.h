#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "The Pink Rabbit";
const char* password = "walkingwithspiders";

void setupOTA() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        delay(5000);
        ESP.restart();
    }
    ArduinoOTA.setPassword("N1nt3nd0");
    ArduinoOTA.begin();
    for(int i = 0; i < 5; i++) {
        ArduinoOTA.handle();
        delay(100);
    }
}

void handleOTA() {
    ArduinoOTA.handle();
}
