#include "display.h"

#include <Arduino.h>

#define DRAW_BUF_SIZE \
    (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

static uint32_t drawBuffer[DRAW_BUF_SIZE / 4];

static lv_display_t* display = nullptr;

void displayInit() {

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    display = lv_tft_espi_create(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        drawBuffer,
        sizeof(drawBuffer)
    );

    // Queremos landscape: 320 x 240
    lv_display_set_rotation(
        display,
        LV_DISPLAY_ROTATION_90
    );
}

lv_display_t* getDisplay() {
    return display;
}