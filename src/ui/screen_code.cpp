#include "ui/screen_code.h"
#include "code/code_service.h"

#include "ui.h"

#include <lvgl.h>
#include <Arduino.h>
#include <cstdio>

static lv_obj_t *commandLabel = nullptr;
static lv_obj_t *descriptionLabel = nullptr;
static bool cursorVisible = true;
static unsigned long lastCursorBlink = 0;

static void nextEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) == LV_EVENT_CLICKED)
    {
        const CodeItem &item = codeGetNextItem();

        lv_label_set_text(
            commandLabel,
            item.command);

        lv_label_set_text(
            descriptionLabel,
            item.description);
    }
}

static void backEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) == LV_EVENT_CLICKED)
    {
        uiShowHome();
    }
}

void screenCodeCreate()
{
    lv_obj_clean(lv_screen_active());

    lv_obj_t *screen = lv_screen_active();

    // Fondo
    lv_obj_set_style_bg_color(
        screen,
        lv_color_hex(0x0F172A),
        0);

    lv_obj_set_style_bg_grad_color(
        screen,
        lv_color_hex(0x1E293B),
        0);

    lv_obj_set_style_bg_grad_dir(
        screen,
        LV_GRAD_DIR_VER,
        0);

    // Botón volver
    lv_obj_t *backButton =
        lv_button_create(screen);

    lv_obj_set_size(
        backButton,
        38,
        32);

    lv_obj_set_pos(
        backButton,
        10,
        10);

    lv_obj_add_event_cb(
        backButton,
        backEvent,
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t *backLabel =
        lv_label_create(backButton);

    lv_label_set_text(
        backLabel,
        "<");

    lv_obj_center(backLabel);

    // Título
    lv_obj_t *title =
        lv_label_create(screen);

    lv_label_set_text(
        title,
        "CODE MODE");

    lv_obj_set_style_text_color(
        title,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        title,
        &lv_font_montserrat_18,
        0);

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        16);

    // Terminal
    lv_obj_t *terminal =
        lv_obj_create(screen);

    lv_obj_set_size(
        terminal,
        270,
        130);

    lv_obj_align(
        terminal,
        LV_ALIGN_CENTER,
        0,
        5);

    lv_obj_set_style_bg_color(
        terminal,
        lv_color_hex(0x020617),
        0);

    lv_obj_set_style_border_color(
        terminal,
        lv_color_hex(0x8B5CF6),
        0);

    lv_obj_set_style_border_width(
        terminal,
        2,
        0);

    lv_obj_set_style_radius(
        terminal,
        10,
        0);

    lv_obj_set_style_pad_all(
        terminal,
        12,
        0);

    lv_obj_remove_flag(
        terminal,
        LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *nextButton =
        lv_button_create(screen);

    lv_obj_set_size(
        nextButton,
        90,
        38);

    lv_obj_align(
        nextButton,
        LV_ALIGN_BOTTOM_MID,
        0,
        -18);

    lv_obj_set_style_bg_color(
        nextButton,
        lv_color_hex(0x8B5CF6),
        0);

    lv_obj_set_style_radius(
        nextButton,
        10,
        0);

    lv_obj_add_event_cb(
        nextButton,
        nextEvent,
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t *nextLabel =
        lv_label_create(nextButton);

    lv_label_set_text(
        nextLabel,
        "NEXT");

    lv_obj_center(nextLabel);

    commandLabel =
        lv_label_create(terminal);

    lv_label_set_text(
        commandLabel,
        "> git status");

    lv_obj_set_style_text_color(
        commandLabel,
        lv_color_hex(0x86EFAC),
        0);

    lv_obj_set_style_text_font(
        commandLabel,
        &lv_font_montserrat_14,
        0);

    lv_obj_align(
        commandLabel,
        LV_ALIGN_TOP_LEFT,
        0,
        0);

    // Descripción
    descriptionLabel =
        lv_label_create(terminal);

    lv_label_set_text(
        descriptionLabel,
        "Shows the current state\nof your repository.");

    lv_obj_set_style_text_color(
        descriptionLabel,
        lv_color_hex(0xCBD5E1),
        0);

    lv_obj_set_style_text_font(
        descriptionLabel,
        &lv_font_montserrat_12,
        0);

    lv_obj_align(
        descriptionLabel,
        LV_ALIGN_TOP_LEFT,
        0,
        35);

    // Cargar item actual
    const CodeItem &item = codeGetCurrentItem();

    lv_label_set_text(
        commandLabel,
        item.command);

    lv_label_set_text(
        descriptionLabel,
        item.description);
}

void screenCodeUpdate()
{
    if (commandLabel == nullptr)
    {
        return;
    }

    if (millis() - lastCursorBlink >= 500)
    {
        lastCursorBlink = millis();
        cursorVisible = !cursorVisible;

        const CodeItem &item = codeGetCurrentItem();

        char buffer[64];

        snprintf(
            buffer,
            sizeof(buffer),
            "%s%s",
            item.command,
            cursorVisible ? "_" : "");

        lv_label_set_text(
            commandLabel,
            buffer);
    }
}