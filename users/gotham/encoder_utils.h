#pragma once

#include <stdbool.h>

#include "quantum.h"
#ifdef SPLIT_KEYBOARD
#    include <string.h> // for memcopy
#endif

#ifdef OLED_DRIVER_ENABLE
#    include "oled_utils.h"
#endif

typedef enum {
    ENC_MODE_VOLUME = 0,
    ENC_MODE_WORD_NAV,
    ENC_MODE_LEFT_RIGHT,
    ENC_MODE_UP_DOWN,
    ENC_MODE_PAGING,
    _ENC_MODE_COUNT  // Do not use, except for looping through enum values
} encoder_mode_t;

void encoder_init_user(void);
void encoder_init_keymap(void);
void encoder_update_keymap(int8_t index, bool clockwise);
bool process_record_keymap_encoder(uint16_t keycode, keyrecord_t *record);

void encoder_mode_set(uint8_t index, encoder_mode_t mode);
encoder_mode_t encoder_mode_get(uint8_t index);

#ifdef SPLIT_KEYBOARD
void encoder_get_modes_raw(encoder_mode_t* target_list);
void encoder_set_modes_raw(encoder_mode_t* source_list);
#endif

void encoder_mode_next(uint8_t index);
void encoder_mode_previous(uint8_t index);

void encoder_action_volume(uint8_t clockwise);
void encoder_action_word_nav(uint8_t clockwise);
void encoder_action_left_right(uint8_t clockwise);
void encoder_action_up_down(uint8_t clockwise);
void encoder_action_paging(uint8_t clockwise);

void encoder_action(encoder_mode_t mode, uint8_t clockwise);
