#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <base64.h>
const char* ssid = "The Pink Rabbit";
const char* password = "walkingwithspiders";
const char* host = "synchronicity.tools";
const char* fingerprint = "01 30 77 D0 94 90 62 8F A9 D7 DB 96 22 50 81 2A 27 56 47 89";
const char* auth = "kamenomagic:cpUm2MespTB3cB3N";
const char* url = "https://synchronicity.tools/events/doorbell";

void setup() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClientSecure client;
        if(client.connect(host, 443)) {
            String header = "Authorization: Basic " + String(base64::encode(auth)) + "\r\n";
            client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    header +
                    "Connection: close\r\n\r\n");
        }
    }
}

void loop() {
}
