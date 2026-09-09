#pragma once

enum class PomodoroPhase
{
    WORK,
    BREAK_READY,
    BREAK,
    WORK_READY
};

void pomodoroStartWork();
void pomodoroStartBreak();

void pomodoroPause();
void pomodoroResume();
void pomodoroStop();

bool pomodoroIsRunning();
bool pomodoroIsPaused();

PomodoroPhase pomodoroGetPhase();

unsigned long pomodoroGetElapsedMillis();
unsigned long pomodoroGetRemainingMillis();

void pomodoroUpdate();