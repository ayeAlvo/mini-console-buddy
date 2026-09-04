#include "sensors/environment.h"

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 27
#define DHTTYPE DHT11

static DHT dht(DHTPIN, DHTTYPE);

static float temperature = NAN;
static float humidity = NAN;

static bool sensorError = true;

static unsigned long lastRead = 0;

static const unsigned long READ_INTERVAL = 3000;

void environmentInit()
{
    dht.begin();
}

void environmentUpdate()
{

    if (millis() - lastRead < READ_INTERVAL)
    {
        return;
    }

    lastRead = millis();

    float newTemperature = dht.readTemperature();
    float newHumidity = dht.readHumidity();

    if (isnan(newTemperature) || isnan(newHumidity))
    {
        Serial.println("DHT read error");
        sensorError = true;
        return;
    }

    temperature = newTemperature;
    humidity = newHumidity;

    sensorError = false;

    Serial.print("Temp: ");
    Serial.print(newTemperature);
    Serial.print(" C | Hum: ");
    Serial.print(newHumidity);
    Serial.println(" %");
}

float environmentGetTemperature()
{
    return temperature;
}

float environmentGetHumidity()
{
    return humidity;
}

bool environmentHasError()
{
    return sensorError;
}