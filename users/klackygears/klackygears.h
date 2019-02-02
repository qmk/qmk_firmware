#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#include "wrappers.h"

#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "wrappers.h"

#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
    _DVORAK = 0,
    _ALTDVK, //for use with Windows or Mac layouts, varies for which OS the keyboard is primarily used on
    _QUERTY,
    _NUMB,
    _MNMB,
    _SYMB,
    _MDIA
};

enum custom_keycodes {

  DVORAK = SAFE_RANGE,
  ALTDVK,
  QUERTY,
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

//#include "dynamic_macro.h"

#define KC_____ KC_TRNS
#define KC_XXXXX KC_NO

int RGB_current_mode;


/*

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  #include "rgb_stuff.h"
#endif
*/


//void my_custom_function(void);











#endif
