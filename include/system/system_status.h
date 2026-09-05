#pragma once

#pragma once

#include <stdint.h>

unsigned long systemGetUptimeSeconds();

uint32_t systemGetFreeHeap();

uint32_t systemGetFlashSize();

uint32_t systemGetCpuFrequency();

uint32_t systemGetSketchSize();

uint32_t systemGetFreeSketchSpace();