#include "ui/screen_home.h"
#include "ui/components/robot.h"
#include "sensors/environment.h"
#include <cstdio>
#include "ui/screen_focus.h"
#include "ui.h"

static lv_obj_t *statusLabel = nullptr;
static lv_obj_t *environmentLabel = nullptr;
static lv_obj_t *homeRobot = nullptr;

// ---------- Eventos ----------

static void restoreHomeRobot(lv_timer_t *timer)
{
    lv_timer_delete(timer);

    if (homeRobot != nullptr)
    {
        robotSetExpression(
            homeRobot,
            RobotExpression::NORMAL);
    }
}

static void robotClickEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) == LV_EVENT_CLICKED)
    {

        robotSetExpression(
            homeRobot,
            RobotExpression::HAPPY);

        lv_timer_create(
            restoreHomeRobot,
            700,
            nullptr);
    }
}

static void openFocusDelayed(lv_timer_t *timer)
{
    lv_timer_delete(timer);
    uiShowFocus();
}

static void focusEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) == LV_EVENT_CLICKED)
    {
        lv_timer_create(openFocusDelayed, 153, nullptr);
    }
}

static void codeEvent(lv_event_t* event)
{
    if (lv_event_get_code(event) == LV_EVENT_CLICKED)
    {
        uiShowCode();
    }
}

static void statusEvent(lv_event_t* event) {
    if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
        uiShowStatus();
    }
}

// ---------- Botón reutilizable ----------

static lv_obj_t *createButton(
    lv_obj_t *parent,
    const char *text,
    lv_color_t color,
    int x,
    int y,
    lv_event_cb_t eventCallback)
{

    lv_obj_t *button = lv_button_create(parent);

    lv_obj_set_size(button, 82, 38);

    lv_obj_set_pos(
        button,
        x,
        y);

    lv_obj_set_style_bg_color(
        button,
        color,
        0);

    lv_obj_set_style_radius(
        button,
        10,
        0);

    lv_obj_set_style_shadow_width(
        button,
        0,
        0);

    lv_obj_add_event_cb(
        button,
        eventCallback,
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t *label =
        lv_label_create(button);

    lv_label_set_text(
        label,
        text);

    lv_obj_set_style_text_font(
        label,
        &lv_font_montserrat_14,
        0);

    lv_obj_center(label);

    return button;
}

// ---------- Home ----------

void screenHomeCreate()
{

    lv_obj_clean(lv_screen_active());

    lv_obj_t *screen =
        lv_screen_active();

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

    // Título
    lv_obj_t *title =
        lv_label_create(screen);

    lv_label_set_text(
        title,
        "MINI CONSOLE BUDDY");

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
        12);

    // Robot
    homeRobot = robotCreate(screen);

    lv_obj_align(
        homeRobot,
        LV_ALIGN_TOP_MID,
        -4,
        42);

    lv_obj_add_flag(
        homeRobot,
        LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(
        homeRobot,
        robotClickEvent,
        LV_EVENT_CLICKED,
        nullptr);

    // Primera fila botones

    createButton(
        screen,
        "FOCUS",
        lv_color_hex(0x22C55E),
        20,
        155,
        focusEvent);

    createButton(
        screen,
        "CODE",
        lv_color_hex(0x8B5CF6),
        119,
        155,
        codeEvent);

    // Botón inferior
    createButton(
        screen,
        "STATUS",
        lv_color_hex(0x0EA5E9),
        218,
        155,
        statusEvent);

    // Estado inferior
    statusLabel =
        lv_label_create(screen);

    lv_label_set_text(
        statusLabel,
        "SYSTEM READY");

    lv_obj_set_style_text_color(
        statusLabel,
        lv_color_hex(0x86EFAC),
        0);

    lv_obj_set_style_text_font(
        statusLabel,
        &lv_font_montserrat_12,
        0);

    lv_obj_align(
        statusLabel,
        LV_ALIGN_BOTTOM_MID,
        0,
        -12);

    environmentLabel = lv_label_create(screen);

    lv_label_set_text(
        environmentLabel,
        "TEMP -- C   HUM -- %");

    lv_obj_set_style_text_color(
        environmentLabel,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        environmentLabel,
        &lv_font_montserrat_12,
        0);

    lv_obj_align(
        environmentLabel,
        LV_ALIGN_BOTTOM_MID,
        0,
        -28);
}

void screenHomeUpdate()
{

    if (environmentLabel == nullptr)
    {
        return;
    }

    if (environmentHasError())
    {

        lv_label_set_text(
            environmentLabel,
            "TEMP -- C   HUM -- %   SENSOR ERR");

        return;
    }

    char buffer[64];

    snprintf(
        buffer,
        sizeof(buffer),
        "TEMP %.0f° C  HUM %.0f %%",
        environmentGetTemperature(),
        environmentGetHumidity());

    lv_label_set_text(
        environmentLabel,
        buffer);
}