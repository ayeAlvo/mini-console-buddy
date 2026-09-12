#include "ui/components/confirm_dialog.h"

static lv_obj_t *dialogOverlay = nullptr;
static ConfirmCallback confirmCallback = nullptr;

static void closeDialog()
{
    if (dialogOverlay != nullptr)
    {
        lv_obj_delete(dialogOverlay);
        dialogOverlay = nullptr;
    }

    confirmCallback = nullptr;
}

static void cancelEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) != LV_EVENT_CLICKED)
    {
        return;
    }

    closeDialog();
}

static void confirmEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) != LV_EVENT_CLICKED)
    {
        return;
    }

    ConfirmCallback callback = confirmCallback;

    closeDialog();

    if (callback != nullptr)
    {
        callback();
    }
}

void confirmDialogShow(
    lv_obj_t *parent,
    const char *message,
    ConfirmCallback onConfirm)
{
    if (dialogOverlay != nullptr)
    {
        return;
    }

    confirmCallback = onConfirm;

    dialogOverlay = lv_obj_create(parent);

    lv_obj_set_size(
        dialogOverlay,
        220,
        110);

    lv_obj_center(dialogOverlay);

    lv_obj_set_style_bg_color(
        dialogOverlay,
        lv_color_hex(0x1E293B),
        0);

    lv_obj_set_style_border_color(
        dialogOverlay,
        lv_color_hex(0xEF4444),
        0);

    lv_obj_set_style_border_width(
        dialogOverlay,
        2,
        0);

    lv_obj_set_style_radius(
        dialogOverlay,
        12,
        0);

    lv_obj_t *messageLabel =
        lv_label_create(dialogOverlay);

    lv_label_set_text(
        messageLabel,
        message);

    lv_obj_set_style_text_color(
        messageLabel,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        messageLabel,
        &lv_font_montserrat_14,
        0);

    lv_obj_align(
        messageLabel,
        LV_ALIGN_TOP_MID,
        0,
        8);

    // CANCEL
    lv_obj_t *cancelButton =
        lv_button_create(dialogOverlay);

    lv_obj_set_size(
        cancelButton,
        85,
        36);

    lv_obj_align(
        cancelButton,
        LV_ALIGN_BOTTOM_LEFT,
        8,
        -8);

    lv_obj_add_event_cb(
        cancelButton,
        cancelEvent,
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t *cancelLabel =
        lv_label_create(cancelButton);

    lv_label_set_text(
        cancelLabel,
        "CANCEL");

    lv_obj_center(cancelLabel);

    // CONFIRM
    lv_obj_t *confirmButton =
        lv_button_create(dialogOverlay);

    lv_obj_set_size(
        confirmButton,
        85,
        36);

    lv_obj_align(
        confirmButton,
        LV_ALIGN_BOTTOM_RIGHT,
        -8,
        -8);

    lv_obj_set_style_bg_color(
        confirmButton,
        lv_color_hex(0xEF4444),
        0);

    lv_obj_add_event_cb(
        confirmButton,
        confirmEvent,
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t *confirmLabel =
        lv_label_create(confirmButton);

    lv_label_set_text(
        confirmLabel,
        "STOP");

    lv_obj_center(confirmLabel);
}