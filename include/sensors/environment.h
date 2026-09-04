#pragma once

void environmentInit();
void environmentUpdate();

float environmentGetTemperature();
float environmentGetHumidity();

bool environmentHasError();