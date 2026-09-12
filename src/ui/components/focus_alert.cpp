#include "ui/components/focus_alert.h"

static lv_obj_t *alertOverlay = nullptr;
static lv_timer_t *alertTimer = nullptr;

static int flashStep = 0;

static void alertDeleteEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) == LV_EVENT_DELETE)
    {
        alertOverlay = nullptr;
    }
}

static void closeAlert()
{
    if (alertTimer != nullptr)
    {
        lv_timer_delete(alertTimer);
        alertTimer = nullptr;
    }

    if (alertOverlay != nullptr)
    {
        lv_obj_delete(alertOverlay);
        alertOverlay = nullptr;
    }

    flashStep = 0;
}

static void flashTimerCallback(lv_timer_t *timer)
{
    if (alertOverlay == nullptr)
    {
        lv_timer_delete(timer);
        alertTimer = nullptr;
        return;
    }

    flashStep++;

    // alterna visible / invisible
    if (flashStep % 2 == 0)
    {
        lv_obj_remove_flag(
            alertOverlay,
            LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(
            alertOverlay,
            LV_OBJ_FLAG_HIDDEN);
    }

    // 3 flashes completos
    if (flashStep >= 6)
    {
        closeAlert();
    }
}

bool focusAlertIsActive()
{
    return alertOverlay != nullptr;
}

void focusAlertShow(
    lv_obj_t *parent,
    FocusAlertType type)
{
    if (alertOverlay != nullptr)
    {
        return;
    }

    const char *message = "";
    const char *subtitle = "";
    lv_color_t backgroundColor;

    switch (type)
    {
        case FocusAlertType::WORK_DONE:
            message = "BREAK TIME!";
            subtitle = "WORK DONE";
            backgroundColor = lv_color_hex(0x16A34A);
            break;

        case FocusAlertType::BREAK_DONE:
            message = "FOCUS TIME!";
            subtitle = "BREAK DONE";
            backgroundColor = lv_color_hex(0x0284C7);
            break;

        case FocusAlertType::CYCLE_COMPLETE:
            message = "GREAT JOB!";
            subtitle = "4/4 COMPLETE";
            backgroundColor = lv_color_hex(0x7C3AED);
            break;
    }

    alertOverlay = lv_obj_create(parent);

    lv_obj_set_size(
        alertOverlay,
        LV_PCT(100),
        LV_PCT(100));

    lv_obj_center(alertOverlay);

    lv_obj_set_style_bg_color(
        alertOverlay,
        backgroundColor,
        0);

    lv_obj_set_style_bg_opa(
        alertOverlay,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_border_width(
        alertOverlay,
        0,
        0);

    lv_obj_set_style_radius(
        alertOverlay,
        0,
        0);

    lv_obj_set_style_pad_all(
        alertOverlay,
        0,
        0);

    lv_obj_clear_flag(
        alertOverlay,
        LV_OBJ_FLAG_SCROLLABLE);

    // evita tocar botones de abajo mientras aparece la alerta
    lv_obj_add_flag(
        alertOverlay,
        LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(
        alertOverlay,
        alertDeleteEvent,
        LV_EVENT_DELETE,
        nullptr);

    // texto principal
    lv_obj_t *messageLabel =
        lv_label_create(alertOverlay);

    lv_label_set_text(
        messageLabel,
        message);

    lv_obj_set_style_text_color(
        messageLabel,
        lv_color_hex(0xFFFFFF),
        0);

    lv_obj_set_style_text_font(
        messageLabel,
        &lv_font_montserrat_20,
        0);

    lv_obj_align(
        messageLabel,
        LV_ALIGN_CENTER,
        0,
        -10);

    // texto secundario
    lv_obj_t *subtitleLabel =
        lv_label_create(alertOverlay);

    lv_label_set_text(
        subtitleLabel,
        subtitle);

    lv_obj_set_style_text_color(
        subtitleLabel,
        lv_color_hex(0xFFFFFF),
        0);

    lv_obj_set_style_text_font(
        subtitleLabel,
        &lv_font_montserrat_14,
        0);

    lv_obj_align(
        subtitleLabel,
        LV_ALIGN_CENTER,
        0,
        22);

    lv_obj_move_foreground(alertOverlay);

    flashStep = 0;

    alertTimer = lv_timer_create(
        flashTimerCallback,
        350,
        nullptr);
}