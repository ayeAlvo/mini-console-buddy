#include "ui/screen_status.h"

#include "ui.h"
#include "sensors/environment.h"
#include "system/system_status.h"

#include <lvgl.h>
#include <cstdio>

static lv_obj_t *uptimeLabel = nullptr;
static lv_obj_t *heapLabel = nullptr;
static lv_obj_t *flashLabel = nullptr;
static lv_obj_t *cpuLabel = nullptr;

static void backEvent(lv_event_t *event)
{
    if (lv_event_get_code(event) == LV_EVENT_CLICKED)
    {
        uiShowHome();
    }
}

static lv_obj_t *createStatusCard(
    lv_obj_t *parent,
    const char *title,
    int x,
    int y,
    int width,
    int height,
    lv_color_t color)
{
    lv_obj_t *card = lv_obj_create(parent);

    lv_obj_set_size(card, width, height);
    lv_obj_set_pos(card, x, y);

    lv_obj_set_style_bg_color(
        card,
        lv_color_hex(0x1E293B),
        0);

    lv_obj_set_style_border_color(
        card,
        color,
        0);

    lv_obj_set_style_border_width(
        card,
        2,
        0);

    lv_obj_set_style_radius(
        card,
        10,
        0);

    lv_obj_set_style_pad_all(
        card,
        8,
        0);

    lv_obj_remove_flag(
        card,
        LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *titleLabel = lv_label_create(card);

    lv_label_set_text(
        titleLabel,
        title);

    lv_obj_set_style_text_color(
        titleLabel,
        color,
        0);

    lv_obj_set_style_text_font(
        titleLabel,
        &lv_font_montserrat_12,
        0);

    lv_obj_align(
        titleLabel,
        LV_ALIGN_TOP_LEFT,
        0,
        0);

    return card;
}

void screenStatusCreate()
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
    lv_obj_t *backButton = lv_button_create(screen);

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

    lv_obj_t *backLabel = lv_label_create(backButton);

    lv_label_set_text(
        backLabel,
        "<");

    lv_obj_center(backLabel);

    // Título
    lv_obj_t *title = lv_label_create(screen);

    lv_label_set_text(
        title,
        "SYSTEM STATUS");

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

    // Uptime
    lv_obj_t *uptimeCard = createStatusCard(
        screen,
        "UPTIME",
        35,
        125,
        250,
        50,
        lv_color_hex(0x8B5CF6));

    uptimeLabel = lv_label_create(uptimeCard);

    lv_obj_set_style_text_color(
        uptimeLabel,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        uptimeLabel,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        uptimeLabel,
        LV_ALIGN_BOTTOM_LEFT,
        0,
        0);

    // Free RAM
    lv_obj_t *heapCard = createStatusCard(
        screen,
        "FREE RAM",
        35,
        185,
        250,
        50,
        lv_color_hex(0xF59E0B));

    heapLabel = lv_label_create(heapCard);

    lv_obj_set_style_text_color(
        heapLabel,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        heapLabel,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        heapLabel,
        LV_ALIGN_BOTTOM_LEFT,
        0,
        0);

    // Flash
    lv_obj_t *flashCard = createStatusCard(
        screen,
        "FLASH",
        35,
        60,
        120,
        55,
        lv_color_hex(0x14B8A6));

    flashLabel = lv_label_create(flashCard);

    lv_obj_set_style_text_color(
        flashLabel,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        flashLabel,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        flashLabel,
        LV_ALIGN_BOTTOM_LEFT,
        0,
        0);

    // CPU
    lv_obj_t *cpuCard = createStatusCard(
        screen,
        "CPU",
        165,
        60,
        120,
        55,
        lv_color_hex(0xEC4899));

    cpuLabel = lv_label_create(cpuCard);

    lv_obj_set_style_text_color(
        cpuLabel,
        lv_color_hex(0xF8FAFC),
        0);

    lv_obj_set_style_text_font(
        cpuLabel,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        cpuLabel,
        LV_ALIGN_BOTTOM_LEFT,
        0,
        0);
}

void screenStatusUpdate()
{

    if (
        uptimeLabel == nullptr ||
        heapLabel == nullptr ||
        flashLabel == nullptr ||
        cpuLabel == nullptr)
    {
        return;
    }

    char buffer[64];

    unsigned long totalSeconds =
        systemGetUptimeSeconds();

    unsigned long hours =
        totalSeconds / 3600;

    unsigned long minutes =
        (totalSeconds % 3600) / 60;

    unsigned long seconds =
        totalSeconds % 60;

    snprintf(
        buffer,
        sizeof(buffer),
        "%02lu:%02lu:%02lu",
        hours,
        minutes,
        seconds);

    lv_label_set_text(
        uptimeLabel,
        buffer);

    snprintf(
        buffer,
        sizeof(buffer),
        "%lu KB",
        systemGetFreeHeap() / 1024);

    lv_label_set_text(
        heapLabel,
        buffer);

    snprintf(
        buffer,
        sizeof(buffer),
        "%lu MB",
        systemGetFlashSize() / (1024 * 1024));

    lv_label_set_text(
        flashLabel,
        buffer);

    snprintf(
        buffer,
        sizeof(buffer),
        "%lu MHz",
        systemGetCpuFrequency());

    lv_label_set_text(
        cpuLabel,
        buffer);
}