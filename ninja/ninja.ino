#include "src/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "src/DHT/DHT.h"

const int width = 16;
const int height = 2;
char screen[][width] = {
    {'H', ':', ' ', ' ', '%', ' ', ' ', ' ', '.', ' ', char(223), ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};
const int humidityIndex = 2;
const int tempIndex = 6;
const int airPin = 2;

LiquidCrystal_I2C lcd(0x27, width, height);
DHT dht(airPin, DHT11);

void setup() {
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
    dht.begin();
}

void loop() {
    updateAir();
    render();
}

void updateAir() {
    twoDigitUpdate(int(dht.readHumidity()), humidityIndex, 0, false);
    threeDigitUpdate(int(((dht.readTemperature() * 9 / 5) + 32) * 10), tempIndex, 0, true);
}

void twoDigitUpdate(int value, int column, int row, boolean decimal) {
    value = value < 0 ? 0 : value;
    value = value > 99 ? 99 : value;
    int upperDigit = value / 10;
    screen[row][column] = char(upperDigit) + '0';
    screen[row][column + (decimal ? 2 : 1)] = char(value - upperDigit * 10) + '0';
}

void threeDigitUpdate(int value, int column, int row, boolean decimal) {
    value = value < 0 ? 0 : value;
    value = value > 999 ? 999 : value;
    int firstDigit = value / 100;
    int secondDigit = (value - firstDigit * 100) / 10;
    int thirdDigit = (value - (firstDigit * 100) - (secondDigit * 10));
    screen[row][column] = char(firstDigit) + '0';
    screen[row][column + 1] = char(secondDigit) + '0';
    screen[row][column + (decimal ? 3 : 2)] = char(thirdDigit) + '0';
}

void render() {
    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            lcd.setCursor(column, row);
            lcd.print(screen[row][column]);
        }
    }
}
