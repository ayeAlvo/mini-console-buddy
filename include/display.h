#pragma once

#include <lvgl.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

void displayInit();
lv_display_t* getDisplay();