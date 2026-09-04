#include "ui/components/robot.h"

struct RobotParts {
    lv_obj_t* leftEye;
    lv_obj_t* rightEye;
    lv_obj_t* mouth;
};

static lv_color_t bodyColor = lv_color_hex(0x64748B);
static lv_color_t faceColor = lv_color_hex(0x86EFAC);
static lv_color_t darkColor = lv_color_hex(0x111827);

lv_obj_t* robotCreate(lv_obj_t* parent) {

    lv_obj_t* robot = lv_obj_create(parent);

    lv_obj_set_size(robot, 90, 100);

    lv_obj_set_style_bg_opa(
        robot,
        LV_OPA_TRANSP,
        0
    );

    lv_obj_set_style_border_width(
        robot,
        0,
        0
    );

    lv_obj_set_style_pad_all(
        robot,
        0,
        0
    );

    lv_obj_remove_flag(
        robot,
        LV_OBJ_FLAG_SCROLLABLE
    );

    // Antena
    lv_obj_t* antenna =
        lv_obj_create(robot);

    lv_obj_set_size(
        antenna,
        4,
        14
    );

    lv_obj_set_pos(
        antenna,
        43,
        0
    );

    lv_obj_set_style_bg_color(
        antenna,
        bodyColor,
        0
    );

    lv_obj_set_style_border_width(
        antenna,
        0,
        0
    );

    lv_obj_set_style_radius(
        antenna,
        2,
        0
    );

    // Punta antena
    lv_obj_t* antennaBall =
        lv_obj_create(robot);

    lv_obj_set_size(
        antennaBall,
        9,
        9
    );

    lv_obj_set_pos(
        antennaBall,
        40,
        0
    );

    lv_obj_set_style_bg_color(
        antennaBall,
        faceColor,
        0
    );

    lv_obj_set_style_border_width(
        antennaBall,
        0,
        0
    );

    lv_obj_set_style_radius(
        antennaBall,
        LV_RADIUS_CIRCLE,
        0
    );

    // Cabeza
    lv_obj_t* head =
        lv_obj_create(robot);

    lv_obj_set_size(
        head,
        70,
        48
    );

    lv_obj_set_pos(
        head,
        10,
        14
    );

    lv_obj_set_style_bg_color(
        head,
        bodyColor,
        0
    );

    lv_obj_set_style_border_width(
        head,
        0,
        0
    );

    lv_obj_set_style_radius(
        head,
        10,
        0
    );

    lv_obj_remove_flag(
        head,
        LV_OBJ_FLAG_SCROLLABLE
    );

    // Cara
    lv_obj_t* face =
        lv_obj_create(head);

    lv_obj_set_size(
        face,
        52,
        30
    );

    lv_obj_center(face);

    lv_obj_set_style_bg_color(
        face,
        darkColor,
        0
    );

    lv_obj_set_style_border_width(
        face,
        0,
        0
    );

    lv_obj_set_style_radius(
        face,
        7,
        0
    );

    lv_obj_remove_flag(
        face,
        LV_OBJ_FLAG_SCROLLABLE
    );

    // Ojo izquierdo
    lv_obj_t* leftEye =
        lv_obj_create(face);

    lv_obj_set_size(
        leftEye,
        7,
        7
    );

    lv_obj_set_pos(
        leftEye,
        10,
        8
    );

    lv_obj_set_style_bg_color(
        leftEye,
        faceColor,
        0
    );

    lv_obj_set_style_border_width(
        leftEye,
        0,
        0
    );

    lv_obj_set_style_radius(
        leftEye,
        LV_RADIUS_CIRCLE,
        0
    );

    // Ojo derecho
    lv_obj_t* rightEye =
        lv_obj_create(face);

    lv_obj_set_size(
        rightEye,
        7,
        7
    );

    lv_obj_set_pos(
        rightEye,
        33,
        8
    );

    lv_obj_set_style_bg_color(
        rightEye,
        faceColor,
        0
    );

    lv_obj_set_style_border_width(
        rightEye,
        0,
        0
    );

    lv_obj_set_style_radius(
        rightEye,
        LV_RADIUS_CIRCLE,
        0
    );

    // Boca
    lv_obj_t* mouth =
        lv_obj_create(face);

    lv_obj_set_size(
        mouth,
        18,
        3
    );

    lv_obj_set_pos(
        mouth,
        16,
        21
    );

    lv_obj_set_style_bg_color(
        mouth,
        faceColor,
        0
    );

    lv_obj_set_style_border_width(
        mouth,
        0,
        0
    );

    lv_obj_set_style_radius(
        mouth,
        2,
        0
    );

    // Cuerpo
    lv_obj_t* body =
        lv_obj_create(robot);

    lv_obj_set_size(
        body,
        48,
        30
    );

    lv_obj_set_pos(
        body,
        21,
        66
    );

    lv_obj_set_style_bg_color(
        body,
        bodyColor,
        0
    );

    lv_obj_set_style_border_width(
        body,
        0,
        0
    );

    lv_obj_set_style_radius(
        body,
        8,
        0
    );

    RobotParts* parts =
        new RobotParts{
            leftEye,
            rightEye,
            mouth
        };

    lv_obj_set_user_data(
        robot,
        parts
    );

    robotSetExpression(
        robot,
        RobotExpression::NORMAL
    );

    return robot;
}

void robotSetExpression(
    lv_obj_t* robot,
    RobotExpression expression
) {

    if (robot == nullptr) {
        return;
    }

    RobotParts* parts =
        static_cast<RobotParts*>(
            lv_obj_get_user_data(robot)
        );

    if (parts == nullptr) {
        return;
    }

    switch (expression) {

        case RobotExpression::NORMAL:

            lv_obj_set_size(
                parts->leftEye,
                7,
                7
            );

            lv_obj_set_size(
                parts->rightEye,
                7,
                7
            );

            lv_obj_set_pos(
                parts->leftEye,
                10,
                8
            );

            lv_obj_set_pos(
                parts->rightEye,
                33,
                8
            );

            lv_obj_set_size(
                parts->mouth,
                18,
                3
            );

            break;


        case RobotExpression::FOCUSED:

            lv_obj_set_size(
                parts->leftEye,
                10,
                3
            );

            lv_obj_set_size(
                parts->rightEye,
                10,
                3
            );

            lv_obj_set_pos(
                parts->leftEye,
                8,
                10
            );

            lv_obj_set_pos(
                parts->rightEye,
                32,
                10
            );

            lv_obj_set_size(
                parts->mouth,
                12,
                3
            );

            break;


        case RobotExpression::PAUSED:

            lv_obj_set_size(
                parts->leftEye,
                10,
                2
            );

            lv_obj_set_size(
                parts->rightEye,
                10,
                2
            );

            lv_obj_set_pos(
                parts->leftEye,
                8,
                11
            );

            lv_obj_set_pos(
                parts->rightEye,
                32,
                11
            );

            lv_obj_set_size(
                parts->mouth,
                8,
                2
            );

            break;


        case RobotExpression::HAPPY:

            lv_obj_set_size(
                parts->leftEye,
                8,
                4
            );

            lv_obj_set_size(
                parts->rightEye,
                8,
                4
            );

            lv_obj_set_pos(
                parts->leftEye,
                9,
                9
            );

            lv_obj_set_pos(
                parts->rightEye,
                33,
                9
            );

            lv_obj_set_size(
                parts->mouth,
                20,
                4
            );

            break;
    }
}