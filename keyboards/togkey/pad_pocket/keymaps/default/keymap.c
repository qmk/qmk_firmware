// Copyright 2025 TogKey
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//Tap Dances
enum {
    TD_VOLDOWN_MEDIAPREV,
    TD_VOLUP_MEDIANEXT
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_VOLDOWN_MEDIAPREV] = ACTION_TAP_DANCE_DOUBLE(KC_AUDIO_VOL_DOWN, KC_MEDIA_PREV_TRACK),
    [TD_VOLUP_MEDIANEXT] = ACTION_TAP_DANCE_DOUBLE(KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK)
};

//Combos
const uint16_t PROGMEM media_combo[] = {TD(TD_VOLDOWN_MEDIAPREV), TD(TD_VOLUP_MEDIANEXT), COMBO_END};

combo_t key_combos[] = {
    COMBO(media_combo, KC_MEDIA_PLAY_PAUSE)
};

//Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
         TD(TD_VOLDOWN_MEDIAPREV),  TD(TD_VOLUP_MEDIANEXT)
    )
};
