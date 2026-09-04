#include "ui.h"

#include <lvgl.h>

static lv_obj_t* statusLabel;

static void buttonEvent(lv_event_t* event) {

    if (lv_event_get_code(event) == LV_EVENT_CLICKED) {

        lv_label_set_text(
            statusLabel,
            "HELLO DEV :)"
        );
    }
}

void uiInit() {

    lv_obj_t* screen = lv_screen_active();

    // Fondo
    lv_obj_set_style_bg_color(
        screen,
        lv_color_hex(0x111827),
        0
    );

    // Título
    lv_obj_t* title = lv_label_create(screen);

    lv_label_set_text(
        title,
        "MINI CONSOLE BUDDY"
    );

    lv_obj_set_style_text_color(
        title,
        lv_color_hex(0xF9FAFB),
        0
    );

    lv_obj_set_style_text_font(
        title,
        &lv_font_montserrat_18,
        0
    );

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        25
    );

    // Botón
    lv_obj_t* button = lv_button_create(screen);

    lv_obj_set_size(
        button,
        150,
        55
    );

    lv_obj_align(
        button,
        LV_ALIGN_CENTER,
        0,
        0
    );

    lv_obj_set_style_radius(
        button,
        12,
        0
    );

    lv_obj_set_style_bg_color(
        button,
        lv_color_hex(0x6366F1),
        0
    );

    lv_obj_add_event_cb(
        button,
        buttonEvent,
        LV_EVENT_CLICKED,
        nullptr
    );

    // Texto botón
    lv_obj_t* buttonLabel =
        lv_label_create(button);

    lv_label_set_text(
        buttonLabel,
        "TOUCH ME"
    );

    lv_obj_center(buttonLabel);

    // Estado
    statusLabel = lv_label_create(screen);

    lv_label_set_text(
        statusLabel,
        "SYSTEM READY"
    );

    lv_obj_set_style_text_color(
        statusLabel,
        lv_color_hex(0x86EFAC),
        0
    );

    lv_obj_align(
        statusLabel,
        LV_ALIGN_BOTTOM_MID,
        0,
        -30
    );
}