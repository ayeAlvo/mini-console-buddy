#include "system/system_status.h"

#include <Arduino.h>
#include <ESP.h>

unsigned long systemGetUptimeSeconds()
{
    return millis() / 1000;
}

uint32_t systemGetFreeHeap()
{
    return ESP.getFreeHeap();
}

uint32_t systemGetFlashSize()
{
    return ESP.getFlashChipSize();
}

uint32_t systemGetCpuFrequency()
{
    return ESP.getCpuFreqMHz();
}

uint32_t systemGetSketchSize()
{
    return ESP.getSketchSize();
}

uint32_t systemGetFreeSketchSpace()
{
    return ESP.getFreeSketchSpace();
}