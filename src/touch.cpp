#include "touch.h"

#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#define XPT2046_IRQ  36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK  25
#define XPT2046_CS   33

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

static SPIClass touchscreenSPI = SPIClass(VSPI);

static XPT2046_Touchscreen touchscreen(
    XPT2046_CS,
    XPT2046_IRQ
);

static void touchRead(
    lv_indev_t* indev,
    lv_indev_data_t* data
) {

    if (
        touchscreen.tirqTouched() &&
        touchscreen.touched()
    ) {

        TS_Point p = touchscreen.getPoint();

        int x = map(
            p.x,
            200,
            3700,
            1,
            SCREEN_WIDTH
        );

        int y = map(
            p.y,
            240,
            3800,
            1,
            SCREEN_HEIGHT
        );

        x = constrain(x, 0, SCREEN_WIDTH - 1);
        y = constrain(y, 0, SCREEN_HEIGHT - 1);

        data->state = LV_INDEV_STATE_PRESSED;

        data->point.x = x;
        data->point.y = y;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void touchInit() {

    touchscreenSPI.begin(
        XPT2046_CLK,
        XPT2046_MISO,
        XPT2046_MOSI,
        XPT2046_CS
    );

    touchscreen.begin(touchscreenSPI);

    // Esta era la orientación funcional del proyecto anterior
    touchscreen.setRotation(2);

    lv_indev_t* indev = lv_indev_create();

    lv_indev_set_type(
        indev,
        LV_INDEV_TYPE_POINTER
    );

    lv_indev_set_read_cb(
        indev,
        touchRead
    );
}