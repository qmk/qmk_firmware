#include "pollux.h"

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

enum custom_keycodes {
  KC_ACEL = SAFE_RANGE,
  KC_WEEL
};

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_D_MOUS  LT(MOUSE, KC_D)
#define KC_FUNC    MO(FUNCTION)
#define KC_BASE    TO(BASE)
#define KC_TENKEY  TG(TENKEY)
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

extern uint8_t mk_time_to_max, mk_wheel_time_to_max, mk_max_speed, mk_wheel_max_speed, mk_delay, mk_interval;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 #ifdef RGBLIGHT_ENABLE
  rgb_process_record(keycode, record);
 #endif
  switch (keycode) {
   case KC_ACEL:
    if (record->event.pressed) {
      mk_max_speed = MOUSEKEY_ACL_MAX_SPEED;
      mk_wheel_max_speed = MOUSEKEY_ACL_WHEEL_MAX_SPEED;
      mk_time_to_max = 0;
      mk_wheel_time_to_max = 0;
    } else {
      mk_max_speed = MOUSEKEY_MAX_SPEED;
      mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
      mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
      mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
    }
    return false;
   case KC_WEEL:
    if (record->event.pressed) {
      mk_delay = MOUSEKEY_WHEEL_DELAY / 10;
      mk_interval = MOUSEKEY_WHEEL_INTERVAL;
      layer_on(WHEEL);
    } else {
      mk_delay = MOUSEKEY_DELAY / 10;
      mk_interval = MOUSEKEY_INTERVAL;
      layer_off(WHEEL);
    }
    return false;
  }
  return true;
}
