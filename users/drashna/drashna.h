#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Define layer names 
#define _QWERTY 0
#define _NUMLOCK 0
#define _COLEMAK 1
#define _DVORAK 2
#define _WORKMAN 3
#define _NAV 5
#define _COVECUBE 6
#define _SYMB 8
#define _OVERWATCH 9
#define _DIABLO 10
#define _MOUS 11
#define _MACROS 12
#define _MEDIA 13
#define _LOWER 14
#define _RAISE 15
#define _ADJUST 16


//define modifiers
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

#ifdef RGBLIGHT_ENABLE
#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xC3,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#endif

__attribute__ ((weak))
bool is_overwatch = false;

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  KC_QWERTY,
  KC_COLEMAK,
  KC_DVORAK,
  KC_WORKMAN,
  LOWER,
  RAISE,
  ADJUST,
  KC_DIABLO_CLEAR,
  KC_OVERWATCH,
  KC_SALT,
  KC_MORESALT,
  KC_SALTHARD,
  KC_GOODGAME,
  KC_SYMM,
  KC_DOOMFIST,
  KC_JUSTGAME,
  KC_GLHF,
  KC_TORB,
  KC_AIM,
  KC_MAKE,
  KC_RESET,
  KC_P00,
  NEWPLACEHOLDER
};

#endif
