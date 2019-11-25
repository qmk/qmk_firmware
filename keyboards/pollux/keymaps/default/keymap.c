#include QMK_KEYBOARD_H

/* LAYERS */

enum layer_number {
  BASE = 0,
  RAISE,
  FUNCTION
};

/* KEYCODES */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_FUNC   MO(FUNCTION)
#define KC_ALT_ES LALT_T(KC_ESC)
#define KC_RAI_EN LT(RAISE, KC_ENT)

#define KC_RST  RESET
#define KC_ZNHN A(KC_ZKHK)

#ifdef RGBLIGHT_ENABLE
#    define KC_TOGG RGB_TOG
#    define KC_MODE RGB_MOD
#    define KC_H_UP RGB_HUI
#    define KC_H_DN RGB_HUD
#    define KC_S_UP RGB_SAI
#    define KC_S_DN RGB_SAD
#    define KC_V_UP RGB_VAI
#    define KC_V_DN RGB_VAD
#else
#    define KC_TOGG KC_TRNS
#    define KC_MODE KC_TRNS
#    define KC_H_UP KC_TRNS
#    define KC_H_DN KC_TRNS
#    define KC_S_UP KC_TRNS
#    define KC_S_DN KC_TRNS
#    define KC_V_UP KC_TRNS
#    define KC_V_DN KC_TRNS
#endif

/* KEYMAPS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_kc(                                                   \
    JYEN, Q,    W, E, R, T,      Y,  /**/ Y,   U,      I,   O,    P,   MINS, EQL, \
    LCTL, A,    S, D, F, G,          /**/      H,      J,   K,    L,   SCLN, QUOT, \
    LSFT, FUNC ,Z, X, C, V,      B,  /**/ B,   N,      M,   COMM, DOT, SLSH, BSLS, \
    /*                */ ALT_ES, SPC,     TAB, RAI_EN              \
  ),

  [RAISE] = LAYOUT_kc(                                                  \
    ZNHN, 1,    2,    3,    4,    5,     6,    /**/ 6,    7,     8,    9,    0,    ____, BSPC, \
    ____, ____, ____, LCBR, LPRN, LBRC,        /**/       RBRC,  RPRN, RCBR, ____, UP,   ____, \
    ____, ____, EXLM, AT,   HASH, DLR,   PERC, /**/ PERC, CIRC,  AMPR, ASTR, LEFT, DOWN, RGHT, \
    /*                         */ LANG2, LANG1,     ____, ____          \
  ),

  [FUNCTION] = LAYOUT_kc(                                               \
    ____, F1,   F2,   F3,   F4,   F5,   F6,   /**/ F6,   F7,    F8,   F9,   PSCR, ____, ____, \
    RST,  TOGG, H_UP, S_UP, V_UP, LGUI,       /**/       ____,  ____, ____, ____, PGUP, ____, \
    ____, XXXX, MODE, H_DN, S_DN, V_DN, ____, /**/ ____, ____,  ____, ____, HOME, PGDN, END, \
    /*                         */ ____, ____,      ____, ____           \
  ),

};
