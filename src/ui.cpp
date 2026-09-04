#include "ui.h"
#include "ui/screen_home.h"
#include "ui/screen_focus.h"

enum class Screen {
    HOME,
    FOCUS
};

static Screen currentScreen = Screen::HOME;

void uiInit() {
    uiShowHome();
}

void uiShowHome() {
    currentScreen = Screen::HOME;
    screenHomeCreate();
}

void uiShowFocus() {
    currentScreen = Screen::FOCUS;
    screenFocusCreate();
}

void uiUpdate() {

    switch (currentScreen) {

        case Screen::HOME:
            screenHomeUpdate();
            break;

        case Screen::FOCUS:
            screenFocusUpdate();
            break;
    }
}