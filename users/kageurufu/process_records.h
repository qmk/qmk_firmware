#pragma once
#include "kageurufu.h"

#define FN_ESC  LT(_FN, KC_ESC)
#define FN      MO(_FN)
#define ADJ     MO(_ADJ)

enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _COLEMAK_DH,
    _FN,
    _ADJ,
    ADDITIONAL_LAYER
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  CMAK_DH,
  RGBRST,
  KAGEURUFU_SAFE_RANGE
};


bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_rgb(uint16_t keycode, keyrecord_t *record);
