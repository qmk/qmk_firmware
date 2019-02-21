#pragma once
#include "quantum.h"

#define RIS_ESC  LT(RAISE, KC_ESC)
#define RIS_CAPS LT(RAISE, KC_CAPS)

#ifdef TAP_DANCE_ENABLE
#include "process_tap_dance.h"

//Tap Dance Declarations
enum {
  TD_COMM_QUOT = 0
};

#define TD_COMM TD(TD_COMM_QUOT)
#else
#define TD_COMM KC_COMM
#endif

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
