// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// #include "damo9.h"

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