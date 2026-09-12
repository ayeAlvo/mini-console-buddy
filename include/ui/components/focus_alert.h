#pragma once

#include <lvgl.h>

enum class FocusAlertType
{
    WORK_DONE,
    BREAK_DONE,
    CYCLE_COMPLETE
};

void focusAlertShow(
    lv_obj_t *parent,
    FocusAlertType type
);

bool focusAlertIsActive();