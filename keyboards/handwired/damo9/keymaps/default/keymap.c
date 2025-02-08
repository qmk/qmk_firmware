// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "damo9.h"

enum layer_names {
    _BL,
    _FL,
    _CL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT_ortho_3x3(
        KC_AUDIO_MUTE,   KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,
        KC_MEDIA_REWIND,   KC_MEDIA_SELECT,   KC_MEDIA_FAST_FORWARD,
        KC_MEDIA_PREV_TRACK,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK
    ),
    [_FL] = LAYOUT_ortho_3x3(
        XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX
    ),
    [_CL] = LAYOUT_ortho_3x3(
        XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX
    )        
};

bool oled_task_user(void) {
    display_text("Hello from damo9!");
    return false;

    // if (is_keyboard_master()) {
    //     render_status();
    // } else {
    //     render_logo();
    // }
    // return false;
}

void display_text(const char *text) {
    oled_clear();
    oled_set_cursor(0,1);
    oled_write_ln_P(text, false);
}    