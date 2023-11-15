
#pragma once
#include QMK_KEYBOARD_H

extern const int arrow_repeat_delay;
extern int arrow_repeat_rate;

bool send_repeated_arrow(bool key_down, void *context);
