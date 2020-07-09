#pragma once

#include QMK_KEYBOARD_H

#include "wrappers.h"
#include "eeprom.h"
#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE

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
  KC_QWERTY,
  KC_WINBASE,
  KC_GAMER,
  KC_GAMR1,
  KC_GAMR2,
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
  SAFE_RANGE_KEYMAP
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



#if RGBLIGHT_ENABLE
uint8_t RGB_current_mode;

#endif
