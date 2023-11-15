
#pragma once
#include "../__init__.h"

extern void (*tri_tap_actions[])(void);
extern void (*tri_hold_actions[])(void);
extern void (*double_tap_actions[])(void);
extern void (*double_hold_actions[])(void);

extern enum languages current_lang;
extern enum language_modes language_mode;
