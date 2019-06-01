#pragma once
#include "quantum.h"

#define RIS_ESC  LT(_RAISE, KC_ESC)
#define RIS_CAPS LT(_RAISE, KC_CAPS)

#define QWERTY DF(_QWERTY)

#ifndef GAMELAYER_DISABLE
#define GAME DF(_GAME)
#else
#define GAME KC_TRANSPARENT
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#ifdef TAP_DANCE_ENABLE
#include "process_tap_dance.h"

//Tap Dance Declarations
enum {
  COMM_QUOT = 0,
  BACKSPACE,
  DELETE,
  DOT
};

#define TD_COMM TD(COMM_QUOT)
#define TD_BSPC TD(BACKSPACE)
#define TD_DEL TD(DELETE)
#define TD_DOT TD(DOT)
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
  RGBRST = SAFE_RANGE,
#ifndef TAP_DANCE_ENABLE
  TD_MIN,
  TD_COMM = TD_MIN,
  TD_BSPC,
  TD_DEL,
  TD_DOT,
  TD_MAX,
#endif
  KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
