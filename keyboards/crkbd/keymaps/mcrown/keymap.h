#ifndef QMK_KEYBOARD_H_LIB
#define QMK_KEYBOARD_H_LIB

#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "rgb.h"

extern keymap_config_t keymap_config;
extern uint8_t is_master;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

/* Layout blocks */

#define _____________MOD_LEFT_____________ KC_GUIEI, KC_LOWER, KC_SPC
#define _____________MOD_RIGHT____________ KC_ENT,   KC_RAISE, KC_ALTKN


#define   _____________________QWERTY_L1______________________ KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define   _____________________QWERTY_L2______________________ KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define   _____________________QWERTY_L3______________________ KC_CTLTB, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define   _____________________QWERTY_R1______________________ KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC
#define   _____________________QWERTY_R2______________________ KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define   _____________________QWERTY_R3______________________ KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT

#define   _____________________ADJUST_L1______________________ XXXXXXX,  EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
  #define _____________________ADJUST_L2______________________ XXXXXXX,  XXXXXXX, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI
  #define _____________________ADJUST_L3______________________ XXXXXXX,  XXXXXXX, RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD
#else
  #define _____________________ADJUST_L2______________________ M_VRSN,   M_MALL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  #define _____________________ADJUST_L3______________________ M_FLSH,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
  #define _____________________ADJUST_R1______________________ RGB_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  #define _____________________ADJUST_R3______________________ RGB_MOD,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#else
  #define _____________________ADJUST_R1______________________ XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  #define _____________________ADJUST_R3______________________ XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif
#define   _____________________ADJUST_R2______________________ RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

extern uint8_t is_master;

/* Each layer gets a name for readability */
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#endif /* End of #ifndef QMK_KEYBOARD_H_LIB */
