#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <IRrecv.h>

const char* ssid = "The Pink Rabbit";
const char* password = "walkingwithspiders";
String strawberry_url = "http://192.168.0.126:5798/ir/in";
 
IRrecv ir(D5);
 
decode_results results;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  ir.enableIRIn();
  led(false);
  delay(2000);
  morse_o(); morse_k();
  Serial.println("Ready.");
}

void push(uint64_t code) {
  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, strawberry_url.c_str());
    int status = http.POST(String(code, HEX));
    Serial.println("");
    Serial.println("");
    Serial.println("-----------------------------------------------");
    Serial.print("HTTP Response code: ");
    Serial.println(status);
    if (status > 0) {
      Serial.println(http.getString());
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
    morse_s(); morse_o(); morse_s();
  }
}
 
void loop() {
  if (ir.decode(&results)) {
    // Serial.println(results.value, HEX);
    led(true); delay(100); led(false); delay(100);
    if(results.value <= 0xffffff) {
      led(true); delay(100); led(false); delay(100);
      push(results.value);
    }
    ir.resume();
  }
  delay(100);
}

void led(bool on) {
  digitalWrite(LED_BUILTIN, on ? LOW : HIGH);
}

void dit() {
  led(true);
  delay(200);
  led(false);
  delay(200);
}

void dah() {
  led(true);
  delay(800);
  led(false);
  delay(200);
}

void morse_s() {
  dit(); dit(); dit();
}

void morse_o() {
  dah(); dah(); dah();
}

void morse_k() {
  dah(); dit(); dah();
}