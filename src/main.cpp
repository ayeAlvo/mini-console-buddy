#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <DHT.h>

// DHT11 sensor
#define DHTPIN 27
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Touchscreen pins
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

TFT_eSPI tft = TFT_eSPI();

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

void setup() {
    dht.begin();
    Serial.begin(115200);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // Touch
    touchscreenSPI.begin(
        XPT2046_CLK,
        XPT2046_MISO,
        XPT2046_MOSI,
        XPT2046_CS
    );

    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(1);

    // Display
    tft.init();
    tft.setRotation(1);

    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    tft.drawCentreString(
        "TOUCH TEST",
        SCREEN_WIDTH / 2,
        30,
        2
    );

    tft.drawCentreString(
        "Touch the screen",
        SCREEN_WIDTH / 2,
        110,
        2
    );

    Serial.println("Touch test started");
}

void loop() {
    static unsigned long lastRead = 0;

if (millis() - lastRead >= 3000) {
    lastRead = millis();

    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();

    Serial.print("Temp: ");
    Serial.print(temperatura);
    Serial.print(" C | Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");
}

    if (touchscreen.touched()) {

        TS_Point p = touchscreen.getPoint();

        int x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        int y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
        int z = p.z;

        Serial.print("X = ");
        Serial.print(x);
        Serial.print(" | Y = ");
        Serial.print(y);
        Serial.print(" | Pressure = ");
        Serial.println(z);

        tft.fillScreen(TFT_WHITE);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);

        tft.drawCentreString(
            "X = " + String(x),
            SCREEN_WIDTH / 2,
            70,
            2
        );

        tft.drawCentreString(
            "Y = " + String(y),
            SCREEN_WIDTH / 2,
            100,
            2
        );

        tft.drawCentreString(
            "Pressure = " + String(z),
            SCREEN_WIDTH / 2,
            130,
            2
        );

        delay(100);
    }
}