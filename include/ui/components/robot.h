#pragma once

#include <lvgl.h>

enum class RobotExpression {
    NORMAL,
    FOCUSED,
    PAUSED,
    HAPPY
};

lv_obj_t* robotCreate(lv_obj_t* parent);

void robotSetExpression(
    lv_obj_t* robot,
    RobotExpression expression
);