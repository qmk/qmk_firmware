#pragma once
#include "xulkal.h"

#define RIS_ESC  LT(RAISE, KC_ESC)
#define RIS_CAPS LT(RAISE, KC_CAPS)

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  RGBRST
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_rgb(uint16_t keycode, keyrecord_t *record);
