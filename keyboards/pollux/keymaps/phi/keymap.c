#include QMK_KEYBOARD_H

extern uint8_t is_master;

/* GLOBAL VARS */

#define BASE      0
#define RAISE     1
#define FUNCTION  2
#define TENKEY    3
#define MOUSE     4
#define WHEEL     5

#define L_BASE      0
#define L_RAISE     (2 << (RAISE - 1))
#define L_FUNCTION  (2 << (FUNCTION - 1))
#define L_TENKEY    (2 << (TENKEY - 1))
#define L_MOUSE     (2 << (MOUSE - 1))
#define L_WHEEL     (2 << (WHEEL - 1))

/* FEATURES */

#ifdef RGBLIGHT_ENABLE
#include "./rgb.c"
#endif

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_D_MOUS  LT(MOUSE, KC_D)
#define KC_FUNC    MO(FUNCTION)
#define KC_BASE    TO(BASE)
#define KC_TENKEY  TG(TENKEY)
#define KC_WEEL    MO(WHEEL)
#define KC_ALT_ES  LALT_T(KC_ESC)
#define KC_ALT_SP  LALT_T(KC_ENT)
#define KC_CTL_TB  LCTL_T(KC_TAB)
#define KC_RAI_EN  LT(RAISE, KC_ENT)

#define KC_RST  RESET
#define KC_MUP  KC_MS_U
#define KC_MDN  KC_MS_D
#define KC_MLFT KC_MS_L
#define KC_MRGT KC_MS_R
#define KC_WUP  KC_WH_U
#define KC_WDN  KC_WH_D
#define KC_WLFT KC_WH_L
#define KC_WRGT KC_WH_R
#define KC_ACEL KC_MS_ACCEL2

/* KEYMAPS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_kc(                                                   \
    JYEN, Q,    W, E,      R, T,      Y,  /**/ Y,   U, I,   O,    P,   MINS, EQL, \
    LCTL, A,    S, D_MOUS, F, G,          /**/      H, J,   K,    L,   SCLN, QUOT, \
    LSFT, FUNC ,Z, X,      C, V,      B,  /**/ B,   N, M,   COMM, DOT, SLSH, BSLS, \
    /*                     */ ALT_ES, SPC,     TAB, RAI_EN              \
  ),

  [RAISE] = LAYOUT_kc(                                                  \
    BSPC, 1,     2,    3,    4,     5,     6,   /**/ 6,    7,     8,    9,    0,    ____, ____, \
    ____, ____, ____, LCBR, LPRN,  LBRC,        /**/       RBRC,  RPRN, RCBR, ____, UP,   ____, \
    ____, ____, EXLM, AT,   HASH, DLR,   PERC,  /**/ PERC, CIRC, AMPR,  ASTR, LEFT, DOWN, RGHT, \
    /*                           */ LANG2, LANG1,     ____, ____        \
  ),

  [FUNCTION] = LAYOUT_kc(                                               \
    ____, F1,   F2,   F3,   F4,   F5,   F6,   /**/ F6,   F7,    F8,   F9,   PSCR, ____, ____, \
    RST,  ____, ____, ____, ____, LGUI,       /**/       ____,  ____, ____, ____, PGUP, ____, \
    ____, ____, ____, ____, ____, ____, ____, /**/ ____, ____,  ____, ____, HOME, PGDN, END, \
    /*                         */ ____, ____,      ____, ____           \
  ),

  [MOUSE] = LAYOUT_kc(                                               \
    ____, ____, ____, ____, ____, ____, ____, /**/ ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, WEEL, ____, ACEL, ____,       /**/       MLFT, MDN,  MUP,  MRGT, ____, ____, \
    ____, ____, ____, ____, BTN1, BTN2, ____, /**/ ____, ____, ____, ____, ____, ____, ____, \
    /*                         */ ____, ____,      ____, ____           \
  ),

  [WHEEL] = LAYOUT_kc(                                               \
    ____, ____, ____, ____, ____, ____, ____, /**/ ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____,       /**/       WRGT, WUP,  WDN,  WLFT, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, /**/ ____, ____, ____, ____, ____, ____, ____, \
    /*                         */ ____, ____,      ____, ____           \
  ),

};

/* USER TASKS */

void matrix_scan_user (void) {
 #ifdef RGBLIGHT_ENABLE
  rgb_update(false);
 #endif
}

void keybaord_post_init_user (void) {
 #ifdef RGBLIGHT_ENABLE
  rgb_update(false);
 #endif
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
 #ifdef RGBLIGHT_ENABLE
  rgb_process_record(keycode, record);
 #endif
  return true;
}
