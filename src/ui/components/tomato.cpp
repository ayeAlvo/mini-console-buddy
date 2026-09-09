#include "ui/components/tomato.h"

lv_obj_t* tomatoCreate(lv_obj_t* parent)
{
    lv_obj_t* tomato = lv_obj_create(parent);

    lv_obj_set_size(
        tomato,
        24,
        24
    );

    lv_obj_set_style_bg_opa(
        tomato,
        LV_OPA_TRANSP,
        0
    );

    lv_obj_set_style_border_width(
        tomato,
        0,
        0
    );

    lv_obj_set_style_pad_all(
        tomato,
        0,
        0
    );

    lv_obj_remove_flag(
        tomato,
        LV_OBJ_FLAG_SCROLLABLE
    );

    // Cuerpo
    lv_obj_t* body = lv_obj_create(tomato);

    lv_obj_set_size(
        body,
        18,
        18
    );

    lv_obj_align(
        body,
        LV_ALIGN_BOTTOM_MID,
        0,
        0
    );

    lv_obj_set_style_bg_color(
        body,
        lv_color_hex(0xEF4444),
        0
    );

    lv_obj_set_style_border_width(
        body,
        0,
        0
    );

    lv_obj_set_style_radius(
        body,
        LV_RADIUS_CIRCLE,
        0
    );

    // Hoja izquierda
    lv_obj_t* leafLeft = lv_obj_create(tomato);

    lv_obj_set_size(
        leafLeft,
        6,
        6
    );

    lv_obj_set_pos(
        leafLeft,
        6,
        2
    );

    lv_obj_set_style_bg_color(
        leafLeft,
        lv_color_hex(0x22C55E),
        0
    );

    lv_obj_set_style_border_width(
        leafLeft,
        0,
        0
    );

    lv_obj_set_style_radius(
        leafLeft,
        2,
        0
    );

    // Hoja centro
    lv_obj_t* leafCenter = lv_obj_create(tomato);

    lv_obj_set_size(
        leafCenter,
        6,
        6
    );

    lv_obj_set_pos(
        leafCenter,
        9,
        0
    );

    lv_obj_set_style_bg_color(
        leafCenter,
        lv_color_hex(0x16A34A),
        0
    );

    lv_obj_set_style_border_width(
        leafCenter,
        0,
        0
    );

    lv_obj_set_style_radius(
        leafCenter,
        2,
        0
    );

    // Hoja derecha
    lv_obj_t* leafRight = lv_obj_create(tomato);

    lv_obj_set_size(
        leafRight,
        6,
        6
    );

    lv_obj_set_pos(
        leafRight,
        12,
        2
    );

    lv_obj_set_style_bg_color(
        leafRight,
        lv_color_hex(0x22C55E),
        0
    );

    lv_obj_set_style_border_width(
        leafRight,
        0,
        0
    );

    lv_obj_set_style_radius(
        leafRight,
        2,
        0
    );

    return tomato;
}