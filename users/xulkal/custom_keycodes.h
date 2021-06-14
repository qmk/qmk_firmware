#pragma once

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
#ifdef ENCODER_ENABLE
  RGB_ENC,
#endif
  KEYMAP_SAFE_RANGE
};

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


#ifdef ENCODER_ENABLE
#define KC_ENC1 RGB_ENC
#define KC_ENC2 KC_MPLY
#else
#define KC_ENC1 RGB_RMOD
#define KC_ENC2 RGB_MOD
#endif
