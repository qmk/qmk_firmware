#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#include "wrappers.h"

#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"

#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings

//#include "rgblight.h"
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
    _DVORAK = 0,
    _ALTDVK, //for use with Windows or Mac layouts, varies for which OS the keyboard is primarily used on
    _QWERTY,
    _NUMB,
    _MNMB,
    _SYMB,
    _MDIA
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  ALTDVK,
  QWERTY,
  NUMB,
  MNMB,
  SYMB,
  MDIA,
  //BACKLIT,
  //EISU,
  //KANA,
  RGBRST,
  MAKEK,
  MAKEKF,
  //DYNAMIC_MACRO_RANGE,
};

enum userspace_custom_keycodes {
  KC_DVORAK,
  KC_ALTDVK,
  KC_QWERTY,
  //NEW_SAFE_RANGE
};


//#include "dynamic_macro.h"

#define KC_____ KC_TRNS
#define KC_XXXXX KC_NO

int RGB_current_mode;

#endif
