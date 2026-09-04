#include "ui/screen_focus.h"
#include "ui/screen_home.h"
#include "ui/components/robot.h"
#include "ui.h"
#include <lvgl.h>
#include <cstdio>
#include <Arduino.h>

static lv_obj_t* timerLabel = nullptr;
static lv_obj_t* stateLabel = nullptr;
static lv_obj_t* mainButtonLabel = nullptr;
static lv_obj_t* focusRobot = nullptr;

static bool running = false;
static bool paused = false;

static unsigned long startMillis = 0;
static unsigned long pausedElapsed = 0;


static void backEvent(lv_event_t* event) {

    if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
        uiShowHome();
    }
}

static void mainButtonEvent(lv_event_t* event) {
    if (lv_event_get_code(event) != LV_EVENT_CLICKED) {
        return;
    }

    if (!running && !paused) {
        running = true;
        paused = false;
        startMillis = millis();

        lv_label_set_text(stateLabel, "FOCUSING");
        lv_label_set_text(mainButtonLabel, "PAUSE");
        robotSetExpression(focusRobot, RobotExpression::FOCUSED);

    }
    else if (running) {
        pausedElapsed = millis() - startMillis;

        running = false;
        paused = true;

        lv_label_set_text(stateLabel, "PAUSED");
        lv_label_set_text(mainButtonLabel, "RESUME");
        robotSetExpression(focusRobot, RobotExpression::PAUSED);
    }
    else if (paused) {
        startMillis = millis() - pausedElapsed;

        running = true;
        paused = false;

        lv_label_set_text(stateLabel, "FOCUSING");
        lv_label_set_text(mainButtonLabel, "PAUSE");
        robotSetExpression(focusRobot, RobotExpression::FOCUSED);
    }
}

static void stopButtonEvent(lv_event_t* event) {
    if (lv_event_get_code(event) != LV_EVENT_CLICKED) {
        return;
    }

    running = false;
    paused = false;
    startMillis = 0;
    pausedElapsed = 0;

    lv_label_set_text(timerLabel, "00:00:00");
    lv_label_set_text(stateLabel, "READY");
    lv_label_set_text(mainButtonLabel, "START");
    robotSetExpression(focusRobot, RobotExpression::NORMAL);
}

void screenFocusCreate() {

    lv_obj_clean(lv_screen_active());

    lv_obj_t* screen = lv_screen_active();

    lv_obj_set_style_bg_color(
        screen,
        lv_color_hex(0x0F172A),
        0
    );

    lv_obj_set_style_bg_grad_color(
        screen,
        lv_color_hex(0x1E293B),
        0
    );

    lv_obj_set_style_bg_grad_dir(
        screen,
        LV_GRAD_DIR_VER,
        0
    );

    // Back
    lv_obj_t* backButton = lv_button_create(screen);
    lv_obj_set_size(backButton, 42, 34);
    lv_obj_set_pos(backButton, 10, 10);
    lv_obj_set_style_radius(backButton, 8, 0);

    lv_obj_add_event_cb(
        backButton,
        backEvent,
        LV_EVENT_CLICKED,
        nullptr
    );

    lv_obj_t* backLabel = lv_label_create(backButton);
    lv_label_set_text(backLabel, "<");
    lv_obj_center(backLabel);

    // Title
    lv_obj_t* title = lv_label_create(screen);

    lv_label_set_text(title, "FOCUS MODE");

    lv_obj_set_style_text_font(
        title,
        &lv_font_montserrat_18,
        0
    );

    lv_obj_set_style_text_color(
        title,
        lv_color_hex(0xF8FAFC),
        0
    );

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        12
    );


    focusRobot = robotCreate(screen);

    if (running) {
    robotSetExpression(
        focusRobot,
        RobotExpression::FOCUSED
    );
}
else if (paused) {
    robotSetExpression(
        focusRobot,
        RobotExpression::PAUSED
    );
}
else {
    robotSetExpression(
        focusRobot,
        RobotExpression::NORMAL
    );
}

    lv_obj_align(
        focusRobot,
        LV_ALIGN_TOP_MID,
        -4,
        40
    );

    // State
    stateLabel = lv_label_create(screen);

    lv_label_set_text(
        stateLabel,
        running ? "FOCUSING" :
        paused ? "PAUSED" :
        "READY"
    );

    lv_obj_set_style_text_color(
        stateLabel,
        lv_color_hex(0x86EFAC),
        0
    );

    lv_obj_align(
        stateLabel,
        LV_ALIGN_CENTER,
        0,
        48
    );

    // Timer
    timerLabel = lv_label_create(screen);

    lv_obj_set_style_text_font(
        timerLabel,
        &lv_font_montserrat_20,
        0
    );

    lv_obj_set_style_text_color(
        timerLabel,
        lv_color_hex(0xF8FAFC),
        0
    );

    lv_obj_align(
        timerLabel,
        LV_ALIGN_CENTER,
        0,
        // 26
        24
    );

    // Main button
    lv_obj_t* mainButton = lv_button_create(screen);

    lv_obj_set_size(mainButton, 105, 40);

    lv_obj_align(
        mainButton,
        LV_ALIGN_BOTTOM_MID,
        -58,
        -14
    );

    lv_obj_set_style_bg_color(
        mainButton,
        lv_color_hex(0x22C55E),
        0
    );

    lv_obj_add_event_cb(
        mainButton,
        mainButtonEvent,
        LV_EVENT_CLICKED,
        nullptr
    );

    mainButtonLabel = lv_label_create(mainButton);

    lv_label_set_text(
        mainButtonLabel,
        running ? "PAUSE" :
        paused ? "RESUME" :
        "START"
    );

    lv_obj_center(mainButtonLabel);

    // Stop button
    lv_obj_t* stopButton = lv_button_create(screen);

    lv_obj_set_size(stopButton, 105, 40);

    lv_obj_align(
        stopButton,
        LV_ALIGN_BOTTOM_MID,
        58,
        -14
    );

    lv_obj_set_style_bg_color(
        stopButton,
        lv_color_hex(0xEF4444),
        0
    );

    lv_obj_add_event_cb(
        stopButton,
        stopButtonEvent,
        LV_EVENT_CLICKED,
        nullptr
    );

    lv_obj_t* stopLabel = lv_label_create(stopButton);

    lv_label_set_text(stopLabel, "STOP");

    lv_obj_center(stopLabel);

    screenFocusUpdate();
}

void screenFocusUpdate() {

    if (timerLabel == nullptr) {
        return;
    }

    unsigned long elapsed = pausedElapsed;

    if (running) {
        elapsed = millis() - startMillis;
    }

    unsigned long totalSeconds = elapsed / 1000;

    unsigned long hours = totalSeconds / 3600;
    unsigned long minutes = (totalSeconds % 3600) / 60;
    unsigned long seconds = totalSeconds % 60;

    char buffer[16];

    snprintf(
        buffer,
        sizeof(buffer),
        "%02lu:%02lu:%02lu",
        hours,
        minutes,
        seconds
    );

    lv_label_set_text(timerLabel, buffer);
}