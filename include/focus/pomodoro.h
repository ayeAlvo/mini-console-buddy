#pragma once

enum class PomodoroPhase
{
    WORK,
    BREAK_READY,
    BREAK,
    WORK_READY,
    COMPLETED
};

void pomodoroStartWork();
void pomodoroStartBreak();

void pomodoroPause();
void pomodoroResume();
void pomodoroStop();

bool pomodoroIsRunning();
bool pomodoroIsPaused();
bool pomodoroIsCompleted();

PomodoroPhase pomodoroGetPhase();

unsigned long pomodoroGetElapsedMillis();
unsigned long pomodoroGetRemainingMillis();

int pomodoroGetCompletedCycles();
int pomodoroGetCurrentCycle();

void pomodoroUpdate();