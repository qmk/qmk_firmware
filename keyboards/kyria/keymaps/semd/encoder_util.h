#pragma once

#include <stdbool.h>

#include "quantum.h"

typedef enum {
    ENC_MODE_UP_DOWN = 0,
    ENC_MODE_WORD_NAV,
    ENC_MODE_VOLUME,
    ENC_MODE_PAGING,
    ENC_MODE_LEFT_RIGHT,
    _ENC_MODE_LAST  // Do not use, except for looping through enum values
} encoder_mode_t;

encoder_mode_t encoder_mode;

void encoder_utils_init(void);

void cycle_encoder_mode(bool reverse);

void encoder_action_volume(uint8_t clockwise);

void encoder_action_word_nav(uint8_t clockwise);

void encoder_action_left_right(uint8_t clockwise);

void encoder_action_up_down(uint8_t clockwise);

void encoder_action_paging(uint8_t clockwise);

void encoder_action(uint8_t clockwise);

void encoder_shift(bool pressed);
