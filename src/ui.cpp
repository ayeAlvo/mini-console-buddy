#include "ui.h"
#include "ui/screen_home.h"
#include "ui/screen_focus.h"
#include "ui/screen_status.h"
#include "ui/screen_code.h"

enum class Screen
{
    HOME,
    FOCUS,
    STATUS,
    CODE
};

static Screen currentScreen = Screen::HOME;

void uiInit()
{
    uiShowHome();
}

void uiShowHome()
{
    currentScreen = Screen::HOME;
    screenHomeCreate();
}

void uiShowFocus()
{
    currentScreen = Screen::FOCUS;
    screenFocusCreate();
}

void uiShowStatus()
{
    currentScreen = Screen::STATUS;
    screenStatusCreate();
}

void uiUpdate()
{

    switch (currentScreen)
    {

    case Screen::HOME:
        screenHomeUpdate();
        break;

    case Screen::FOCUS:
        screenFocusUpdate();
        break;

    case Screen::STATUS:
        screenStatusUpdate();
        break;

    case Screen::CODE:
        screenCodeUpdate();
        break;
    }
    
}

void uiShowCode()
{
    currentScreen = Screen::CODE;
    screenCodeCreate();
}