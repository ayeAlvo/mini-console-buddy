#include <Arduino.h>
#include <lvgl.h>

#include "display.h"
#include "touch.h"
#include "ui.h"
#include "sensors/environment.h"

#include "sensors/environment.h"

void setup() {

    Serial.begin(115200);

    Serial.println();
    Serial.println("Mini Console Buddy");
    Serial.printf(
        "LVGL %d.%d.%d\n",
        lv_version_major(),
        lv_version_minor(),
        lv_version_patch()
    );

    lv_init();

    displayInit();
    touchInit();
    uiInit();
    environmentInit();

    Serial.println("System ready");
}

void loop() {
    environmentUpdate();
    uiUpdate();

    lv_timer_handler();

    lv_tick_inc(5);

    delay(5);
}