#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306
#include "bitmaps.h"

Adafruit_SSD1306 display(LED_BUILTIN);
const int WIDTH = 128;
const int HEIGHT = 64;
const int ROWS = 8;
const int COLUMNS = 20;

void setupScreen() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void splashScreen() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    String splashText = "Synchronicity";
    display.setCursor(0, 0);
    display.println(splashText);
    display.display();
}

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
    int xPos = 0;
    int yPos = 1;
    int deltaY = 2;
    int numflakes = 10;
    uint8_t icons[numflakes][3];
    for (uint8_t f=0; f< numflakes; f++) {
        icons[f][xPos] = random(display.width());
        icons[f][yPos] = 0;
        icons[f][deltaY] = random(5) + 1;
        Serial.print("x: ");
        Serial.print(icons[f][xPos], DEC);
        Serial.print(" y: ");
        Serial.print(icons[f][yPos], DEC);
        Serial.print(" dy: ");
        Serial.println(icons[f][deltaY], DEC);
    }
    while (1) {
        for (uint8_t f=0; f< numflakes; f++) {
            display.drawBitmap(icons[f][xPos], icons[f][yPos], bitmap, w, h, WHITE);
        }
        display.display();
        delay(200);
        for (uint8_t f=0; f< numflakes; f++) {
            display.drawBitmap(icons[f][xPos], icons[f][yPos], bitmap, w, h, BLACK);
            icons[f][yPos] += icons[f][deltaY];
            if (icons[f][yPos] > display.height()) {
                icons[f][xPos] = random(display.width());
                icons[f][yPos] = 0;
                icons[f][deltaY] = random(5) + 1;
            }
        }
    }
}

void testdrawchar(void) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    for (uint8_t i=0; i < 168; i++) {
        if (i == '\n') continue;
        display.write(i);
        if ((i > 0) && (i % 21 == 0))
        display.println();
    }    
    display.display();
    delay(1);
}

void testdrawcircle(void) {
    for (int16_t i=0; i<display.height(); i+=2) {
        display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
        display.display();
        delay(1);
    }
}

void testfillrect(void) {
    uint8_t color = 1;
    for (int16_t i=0; i<display.height()/2; i+=3) {
        display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
        display.display();
        delay(1);
        color++;
    }
}

void testdrawtriangle(void) {
    for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
        display.drawTriangle(display.width()/2, display.height()/2-i,
        display.width()/2-i, display.height()/2+i,
        display.width()/2+i, display.height()/2+i, WHITE);
        display.display();
        delay(1);
    }
}

void testfilltriangle(void) {
    uint8_t color = WHITE;
    for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
        display.fillTriangle(display.width()/2, display.height()/2-i,
        display.width()/2-i, display.height()/2+i,
        display.width()/2+i, display.height()/2+i, WHITE);
        if (color == WHITE) color = BLACK;
        else color = WHITE;
        display.display();
        delay(1);
    }
}

void testdrawroundrect(void) {
    for (int16_t i=0; i<display.height()/2-2; i+=2) {
        display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
        display.display();
        delay(1);
    }
}

void testfillroundrect(void) {
    uint8_t color = WHITE;
    for (int16_t i=0; i<display.height()/2-2; i+=2) {
        display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
        if (color == WHITE) color = BLACK;
        else color = WHITE;
        display.display();
        delay(1);
    }
}

void testdrawrect(void) {
    for (int16_t i=0; i<display.height()/2; i+=2) {
        display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
        display.display();
        delay(1);
    }
}

void testdrawline() {  
    for (int16_t i=0; i<display.width(); i+=4) {
        display.drawLine(0, 0, i, display.height()-1, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=0; i<display.height(); i+=4) {
        display.drawLine(0, 0, display.width()-1, i, WHITE);
        display.display();
        delay(1);
    }
    delay(250);
    display.clearDisplay();
    for (int16_t i=0; i<display.width(); i+=4) {
        display.drawLine(0, display.height()-1, i, 0, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=display.height()-1; i>=0; i-=4) {
        display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
        display.display();
        delay(1);
    }
    delay(250);
    display.clearDisplay();
    for (int16_t i=display.width()-1; i>=0; i-=4) {
        display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=display.height()-1; i>=0; i-=4) {
        display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
        display.display();
        delay(1);
    }
    delay(250);
    display.clearDisplay();
    for (int16_t i=0; i<display.height(); i+=4) {
        display.drawLine(display.width()-1, 0, 0, i, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=0; i<display.width(); i+=4) {
        display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
        display.display();
        delay(1);
    }
    delay(250);
}

void testscrolltext(void) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10,0);
    display.clearDisplay();
    display.println("scroll");
    display.display();
    delay(1);
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);    
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
    display.stopscroll();
}

void demo() {
    display.display();
    delay(2000);
    display.clearDisplay();
    display.drawPixel(10, 10, WHITE);
    display.display();
    delay(2000);
    display.clearDisplay();
    testdrawline();
    display.display();
    delay(2000);
    display.clearDisplay();
    testdrawrect();
    display.display();
    delay(2000);
    display.clearDisplay();
    testfillrect();
    display.display();
    delay(2000);
    display.clearDisplay();
    testdrawcircle();
    display.display();
    delay(2000);
    display.clearDisplay();
    display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
    display.display();
    delay(2000);
    display.clearDisplay();
    testdrawroundrect();
    delay(2000);
    display.clearDisplay();
    testfillroundrect();
    delay(2000);
    display.clearDisplay();
    testdrawtriangle();
    delay(2000);
    display.clearDisplay();
    testfilltriangle();
    delay(2000);
    display.clearDisplay();
    testdrawchar();
    display.display();
    delay(2000);
    display.clearDisplay();
    testscrolltext();
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Hello, world!");
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println(3.141592);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("0x"); display.println(0xDEADBEEF, HEX);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.drawBitmap(30, 16,  clockBitmap, 16, 16, 1);
    display.display();
    delay(1);
    display.invertDisplay(true);
    delay(1000); 
    display.invertDisplay(false);
    delay(1000); 
    display.clearDisplay();
    testdrawbitmap(clockBitmap, 16, 16);
}

