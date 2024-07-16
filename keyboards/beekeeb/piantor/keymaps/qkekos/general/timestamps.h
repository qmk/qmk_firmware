
#pragma once
#include "../__init__.h"

extern int prev_key_timestamp;
extern int current_key_timestamp;

extern int prev_key_layerstamp;
extern int current_key_layerstamp;

int timestamps_pr(uint16_t keycode, keyrecord_t *record);
