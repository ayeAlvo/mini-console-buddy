#pragma once

void freeFocusStart();
void freeFocusPause();
void freeFocusResume();
void freeFocusStop();

bool freeFocusIsRunning();
bool freeFocusIsPaused();

unsigned long freeFocusGetElapsedMillis();