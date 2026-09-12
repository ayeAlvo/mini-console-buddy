#include "focus/pomodoro.h"

#include <Arduino.h>

// static const unsigned long POMODORO_WORK_MS =
//     25UL * 60UL * 1000UL;

// static const unsigned long POMODORO_BREAK_MS =
//     5UL * 60UL * 1000UL;

static const unsigned long POMODORO_WORK_MS = 10UL * 1000UL;
static const unsigned long POMODORO_BREAK_MS = 5UL * 1000UL;

static bool running = false;
static bool paused = false;

static unsigned long startMillis = 0;
static unsigned long pausedElapsed = 0;

static const int TOTAL_CYCLES = 4;
static int completedCycles = 0;

static PomodoroPhase phase =
    PomodoroPhase::WORK;

static unsigned long getCurrentDuration()
{
    if (
        phase == PomodoroPhase::BREAK ||
        phase == PomodoroPhase::BREAK_READY)
    {
        return POMODORO_BREAK_MS;
    }

    return POMODORO_WORK_MS;
}

void pomodoroStartWork()
{
    phase = PomodoroPhase::WORK;

    running = true;
    paused = false;

    startMillis = millis();
    pausedElapsed = 0;
}

void pomodoroStartBreak()
{
    phase = PomodoroPhase::BREAK;

    running = true;
    paused = false;

    startMillis = millis();
    pausedElapsed = 0;
}

void pomodoroPause()
{
    if (!running)
    {
        return;
    }

    pausedElapsed =
        millis() - startMillis;

    running = false;
    paused = true;
}

void pomodoroResume()
{
    if (!paused)
    {
        return;
    }

    startMillis =
        millis() - pausedElapsed;

    running = true;
    paused = false;
}

void pomodoroStop()
{
    running = false;
    paused = false;

    startMillis = 0;
    pausedElapsed = 0;

    phase = PomodoroPhase::WORK;
    completedCycles = 0;
}

bool pomodoroIsRunning()
{
    return running;
}

bool pomodoroIsPaused()
{
    return paused;
}

PomodoroPhase pomodoroGetPhase()
{
    return phase;
}

unsigned long pomodoroGetElapsedMillis()
{
    if (running)
    {
        return millis() - startMillis;
    }

    return pausedElapsed;
}

unsigned long pomodoroGetRemainingMillis()
{
    if (phase == PomodoroPhase::COMPLETED)
    {
        return 0;
    }

    unsigned long duration =
        getCurrentDuration();

    unsigned long elapsed =
        pomodoroGetElapsedMillis();

    if (elapsed >= duration)
    {
        return 0;
    }

    return duration - elapsed;
}

void pomodoroUpdate()
{
    if (!running)
    {
        return;
    }

    unsigned long duration =
        getCurrentDuration();

    if (pomodoroGetElapsedMillis() < duration)
    {
        return;
    }

    running = false;
    paused = false;
    pausedElapsed = 0;

    if (phase == PomodoroPhase::WORK)
    {
        phase = PomodoroPhase::BREAK_READY;
    }
    else if (phase == PomodoroPhase::BREAK)
    {
        completedCycles++;

        if (completedCycles >= TOTAL_CYCLES)
        {
            phase = PomodoroPhase::COMPLETED;
        }
        else
        {
            phase = PomodoroPhase::WORK_READY;
        }
    }
}

int pomodoroGetCompletedCycles()
{
    return completedCycles;
}

int pomodoroGetCurrentCycle()
{
    if (completedCycles >= TOTAL_CYCLES)
    {
        return TOTAL_CYCLES;
    }

    return completedCycles + 1;
}

bool pomodoroIsCompleted()
{
    return phase == PomodoroPhase::COMPLETED;
}