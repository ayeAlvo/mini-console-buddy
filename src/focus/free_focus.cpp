#include "focus/free_focus.h"

#include <Arduino.h>

static bool running = false;
static bool paused = false;

static unsigned long startMillis = 0;
static unsigned long pausedElapsed = 0;

void freeFocusStart()
{
    running = true;
    paused = false;

    startMillis = millis();
    pausedElapsed = 0;
}

void freeFocusPause()
{
    if (!running)
    {
        return;
    }

    pausedElapsed = millis() - startMillis;

    running = false;
    paused = true;
}

void freeFocusResume()
{
    if (!paused)
    {
        return;
    }

    startMillis = millis() - pausedElapsed;

    running = true;
    paused = false;
}

void freeFocusStop()
{
    running = false;
    paused = false;

    startMillis = 0;
    pausedElapsed = 0;
}

bool freeFocusIsRunning()
{
    return running;
}

bool freeFocusIsPaused()
{
    return paused;
}

unsigned long freeFocusGetElapsedMillis()
{
    if (running)
    {
        return millis() - startMillis;
    }

    return pausedElapsed;
}