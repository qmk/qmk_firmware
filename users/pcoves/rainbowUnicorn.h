#pragma once

#include "quantum.h"

bool rainbowUnicornIsEnabled(void);
void rainbowUnicornEnable(void);
void rainbowUnicornDisable(void);
void rainbowUnicornToggle(void);

void rainbowUnicorn(uint16_t keycode, keyrecord_t *keyrecord);
