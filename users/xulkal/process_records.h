#pragma once
#include "quantum.h"

#define RIS_ESC  LT(RAISE, KC_ESC)
#define RIS_CAPS LT(RAISE, KC_CAPS)

#ifdef TAP_DANCE_ENABLE
#include "process_tap_dance.h"

//Tap Dance Declarations
enum {
  COMM_QUOT = 0,
  BACKSPACE,
  TAP_TAB
} tap_dances;

#define TD_COMM TD(COMM_QUOT)
#define TD_BSPC TD(BACKSPACE)
#define TD_TAB TD(TAP_TAB)
#else
#define TD_COMM KC_COMM
#define TD_BSPC KC_BSPACE
#define TD_TAB KC_TAB
#endif

enum layer_number {
    _QWERTY = 0,
    _GAME,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  LOWER,
  RAISE,
  RGBRST
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_rgb(uint16_t keycode, keyrecord_t *record);
