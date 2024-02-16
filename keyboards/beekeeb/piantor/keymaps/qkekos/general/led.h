
#pragma once
#include "../__init__.h"

void toggle_left_pin(void);
void toggle_right_pin(void);
void toggle_both_pins(void);

enum pr_response led_pr(uint16_t, keyrecord_t*);
void flick_leds(float time, int interval);
void caps_word_set_user(bool active);
void disable_left_pin(void);
