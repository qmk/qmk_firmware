#pragma once

#include "quantum.h"
#if defined(RGBLIGHT_ENABLE) || defined(RGBMATRIX_ENABLE)
  #include "rgb.h"
#endif
#ifdef TAP_DANCE_ENABLE
  #include "tap_dance.h"
#endif
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
  #include "unicode.h"
#endif

#ifdef LAYER_FN
  #define FN      MO(L_FN)
  #define FN_CAPS LT(L_FN, KC_CAPS)
  #define FN_FNLK TT(L_FN)
#endif

#define KC_SYSR LALT(KC_PSCR)
#undef  KC_BRK
#define KC_BRK  LCTL(KC_PAUS)

#define MV_UP   LCTL(KC_UP)
#define MV_DOWN LCTL(KC_DOWN)
#define MV_LEFT LCTL(KC_LEFT)
#define MV_RGHT LCTL(KC_RGHT)
#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)
#define PRV_TAB LCTL(KC_PGUP)
#define NXT_TAB LCTL(KC_PGDN)

#define DST_ADD LCTL(LGUI(KC_D))
#define DST_REM LCTL(LGUI(KC_F4))
#define DST_PRV LCTL(LGUI(KC_LEFT))
#define DST_NXT LCTL(LGUI(KC_RGHT))
#ifndef DST_MOD_MASK
  #define DST_MOD_MASK MOD_MASK_CTRL
#endif

#define LCT_CPS LCTL_T(KC_CAPS)

#ifdef SEND_STRING_CLEAN
  #undef  SEND_STRING
  #define SEND_STRING(string) {     \
      uint8_t ss_mods = get_mods(); \
      clear_mods();                 \
      send_string_P(PSTR(string));  \
      set_mods(ss_mods);            \
    }
#endif

enum keycodes_user {
  CLEAR = SAFE_RANGE,
  DST_P_R,
  DST_N_A,
#ifdef LAYER_NUMPAD
  NUMPAD,
#endif

  RANGE_KEYMAP,
};

enum layers_user {
  L_BASE,
#ifdef LAYER_FN
  L_FN,
#endif
#ifdef LAYER_NUMPAD
  L_NUMPAD,
#endif

  L_RANGE_KEYMAP,
};

void keyboard_pre_init_keymap(void);
void eeconfig_init_keymap(void);
void keyboard_post_init_keymap(void);

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
uint32_t layer_state_set_keymap(uint32_t state);
