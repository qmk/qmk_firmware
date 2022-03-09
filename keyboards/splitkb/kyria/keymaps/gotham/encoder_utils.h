#pragma once

#include <stdbool.h>

#include "quantum.h"

typedef enum {
    ENC_MODE_VOLUME = 0,
    ENC_MODE_WORD_NAV,
    ENC_MODE_LEFT_RIGHT,
    ENC_MODE_UP_DOWN,
    ENC_MODE_PAGING,
    _ENC_MODE_LAST  // Do not use, except for looping through enum values
} encoder_mode_t;

encoder_mode_t encoder_left_mode;
encoder_mode_t encoder_right_mode;

void encoder_utils_init(void);

void set_encoder_mode(bool left, encoder_mode_t mode);

encoder_mode_t get_encoder_mode(bool left);

void cycle_encoder_mode(bool left, bool reverse);

void encoder_action_volume(uint8_t clockwise);

void encoder_action_word_nav(uint8_t clockwise);

void encoder_action_left_right(uint8_t clockwise);

void encoder_action_up_down(uint8_t clockwise);

void encoder_action_paging(uint8_t clockwise);

void encoder_action(encoder_mode_t mode, uint8_t clockwise);
