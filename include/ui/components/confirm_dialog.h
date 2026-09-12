#pragma once

#include <lvgl.h>

using ConfirmCallback = void (*)();

void confirmDialogShow(
    lv_obj_t *parent,
    const char *message,
    ConfirmCallback onConfirm
);