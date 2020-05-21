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
extern rgblight_config_t rgblight_config;

#endif

enum layer_number {
    _WINBASE = 0,
    _MACBASE,
    _QWERTY,
    _GAMER,
    _GAMR1,
    _GAMR2,
    _NGMR,
    _NUMB,
    _MNMB,
    _SYMB,
    _FUNC,
    _MDIA,
    _MEME
};

enum userspace_custom_keycodes {
  KC_MACBASE = SAFE_RANGE,
  KC_PROTECT, //for some reason, this position does not work. This is just a placeholder
  KC_QWERTY,
  KC_WINBASE,
  KC_GAMER,
  KC_GAMR1,
  KC_GAMR2,
  SAFE_RANGE_KEYMAP
};

enum custom_keycodes {
  MACBASE = SAFE_RANGE_KEYMAP,
  WINBASE,
  QWERTY,
  NUMB,
  MNMB,
  SYMB,
  FUNC,
  MDIA,
  RGBRST,
  MAKEK,
  MAKEKF,
  SHRUG,
  //DYNAMIC_MACRO_RANGE,
};


/*
#ifdef UNICODEMAP_ENABLE
enum unicode_names {
  BANG,
  IRONY,
  SNEK,
};

const uint32_t PROGMEM unicode_map[] = {
  [BANG]  = 0x203D,  // ‽
  [IRONY] = 0x2E2E,  // ⸮
  [SNEK]  = 0x1F40D, // 🐍
};
#endif // UNICODEMAP_ENABLE
*/


//#include "dynamic_macro.h"



#define KC_____ KC_TRNS
#define KC_XXXXX KC_NO

int RGB_current_mode;

#endif
