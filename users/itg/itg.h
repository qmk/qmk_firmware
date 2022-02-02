#pragma once

#include QMK_KEYBOARD_H

#define QWE 0
#define OSX 1
#define SYM 2
#define MED 3  // media keys
#define MAX 4

#define LG_TRNS LGUI(KC_TRANSPARENT)

enum custom_keycodes {
    LK_QWE = SAFE_RANGE,
    LK_OSX,
    VRSN,
    SCREENSHOT,
    KC_SCT1,
    KC_SCT2,
    KC_SCT3,
    KC_SCT4,
    KC_SCT5,
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
