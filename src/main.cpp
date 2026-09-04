#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <DHT.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// DHT11
#define DHTPIN 27
#define DHTTYPE DHT11

// Touch XPT2046
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

TFT_eSPI tft = TFT_eSPI();

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);

    // Touch
    touchscreenSPI.begin(
        XPT2046_CLK,
        XPT2046_MISO,
        XPT2046_MOSI,
        XPT2046_CS
    );

    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(1);

    // Backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // TFT
    tft.init();
    tft.setRotation(1);

    // Test de colores
    tft.fillScreen(TFT_RED);
    delay(1000);

    tft.fillScreen(TFT_GREEN);
    delay(1000);

    tft.fillScreen(TFT_BLUE);
    delay(1000);

    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.drawCentreString(
        "MINI CONSOLE BUDDY",
        160,
        90,
        2
    );

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawCentreString(
        "SYSTEM READY",
        160,
        125,
        2
    );

    // Sensor
    dht.begin();

    Serial.println("Mini Console Buddy started");
}

void loop() {
    if (touchscreen.tirqTouched() && touchscreen.touched()) {

        TS_Point p = touchscreen.getPoint();

        int x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        int y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);

        Serial.print("Touch X: ");
        Serial.print(x);

        Serial.print(" Y: ");
        Serial.println(y);

        delay(150);
    }
}