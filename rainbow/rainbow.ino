#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid = "The Pink Rabbit";
const char* password = "walkingwithspiders";

const int RED = 0;
const int GREEN = 4;
const int BLUE = 5;

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  setRGB(0, 0, 0);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.on("/", handleRequest);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRequest() {
    if(server.hasArg("plain") == false) {
        server.send(400, "text/plain", "Invalid request.");
    } else {
        int rgb[] = {0, 0, 0};
        int rgbLength = 3;
        parseRGB(server.arg("plain"), rgb, rgbLength);
        setRGB(rgb);
        server.send(200, "text/plain", "Set RGB to: " + String(rgb[0]) + " " + String(rgb[1]) + " " + String(rgb[2]) + "\n");
    }
}

void parseRGB(String message, int rgb[], int rgbLength) {
    int bufferLength = 256;
    char buffer[256];
    message.toCharArray(buffer, bufferLength);
    int rgbIndex = 0;
    String current = "";
    for(int i = 0; i < bufferLength && rgbIndex < rgbLength; i++) {
        if(buffer[i] == ' ' || buffer[i] == '\0') {
            int value = current.toInt() * PWMRANGE / 255;
            value = value < 0 ? 0 : value;
            value = value > PWMRANGE ? PWMRANGE : value;
            rgb[rgbIndex++] = value;
            current = "";
        } else {
            current += buffer[i];
        }
    }
}

void setRGB(int rgb[]) {
  setRGB(rgb[0], rgb[1], rgb[2]);
}

void setRGB(int red, int green, int blue) {
  setRed(red);
  setGreen(green);
  setBlue(blue);
}

void setRed(int amount) {
  analogWrite(RED, amount);
}

void setGreen(int amount) {
  analogWrite(GREEN, amount);
}

void setBlue(int amount) {
  analogWrite(BLUE, amount);
}

void demo() {
  unsigned int rgbColor[3];
  rgbColor[0] = 255;
  rgbColor[1] = 0;
  rgbColor[2] = 0;
  for (int decColor = 0; decColor < 3; decColor += 1) {
    int incColor = decColor == 2 ? 0 : decColor + 1;
    for (int i = 0; i < 255; i += 1) {
      rgbColor[decColor] -= 1;
      rgbColor[incColor] += 1;
      setRGB(rgbColor[0], rgbColor[1], rgbColor[2]);
      delay(5);
    }
  }
}
