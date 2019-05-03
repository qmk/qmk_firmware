#pragma once
#include "quantum.h"

#define RIS_ESC  LT(_RAISE, KC_ESC)
#define RIS_CAPS LT(_RAISE, KC_CAPS)

#ifdef TAP_DANCE_ENABLE
#include "process_tap_dance.h"

//Tap Dance Declarations
enum {
  COMM_QUOT = 0,
  BACKSPACE,
  TAP_TAB,
  CTRL_MINUS,
  CTRL_PLUS
};

#define TD_COMM TD(COMM_QUOT)
#define TD_BSPC TD(BACKSPACE)
#define TD_TAB TD(TAP_TAB)
#define TD_LCTL TD(CTRL_MINUS)
#define TD_RCTL TD(CTRL_PLUS)
#else
#define TD_COMM KC_COMM
#define TD_BSPC KC_BSPACE
#define TD_TAB KC_TAB
#define TD_LCTL KC_LCTL
#define TD_RCTL KC_RCTL
#endif

enum layer_number {
    _QWERTY = 0,
#ifndef GAMELAYER_DISABLE
    _GAME,
#endif
    _LOWER,
    _RAISE,
#ifdef TRILAYER_ENABLED
    _ADJUST
#endif
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
