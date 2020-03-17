
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "rgblight.h"
#include "tominabox1.h"
#include "mini.h"

#define XXX KC_NO

#define LAYOUT_handwired( \
  k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, \
  k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, \
  k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, \
  k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, \
  k43, k44,      k46,      k48             \
) \
{ \
  { k01, k02, k03, k04, k05, k06, k07, k08, k09, k010 }, \
  { k11, k12, k13, k14, k15, k16, k17, k18, k19, k110 }, \
  { k21, k22, k23, k24, k25, k26, k27, k28, k29, k210 }, \
  { k31, k32, k33, k34, k35, k36, k37, k38, k39, k310 }, \
  { XXX, XXX, k43, k44, XXX, k46, XXX, k48, XXX, XXX  }  \
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_handwired(
    KC_GRV,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_BSPC,
    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,KC_QUOT, //Y+QUOTE = KC_BSPC
    LGUI_T(KC_A), LALT_T(KC_R),     LCTL_T(KC_S),     LSFT_T(KC_T),     KC_D,     KC_H,     RSFT_T(KC_N),     RCTL_T(KC_E),     RALT_T(KC_I),     RGUI_T(KC_O),
    KC_Z_SF,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
    KC_LALT, KC_ENT, KC_NUM_SPC, KC_NAV_ENT
  ),

  [_NUM_SYM] = LAYOUT_handwired(
    KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0, //0 + 9 = KC_BSPC
    KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,   KC_EQL,  KC_MINS,
    KC_BSLS,  KC_LCBR,  KC_LBRC,  KC_LPRN,   KC_UNDS, KC_RPRN,  KC_RBRC,  KC_RCBR,  KC_DOT,  KC_GRV,
    KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT_handwired(
    KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    RESET,   RGBRST,  AG_NORM,  AG_SWAP,  DEBUG,  KC_GRV ,KC_PGDN,    KC_UP,  KC_PGUP,    KC_SCLN,
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  SPONGEBOB,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  AESTHETIC,  KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_BSLS,
    KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  ),

  [_GAME] = LAYOUT_handwired(
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_L, KC_U, KC_Y, TO(_BASE),
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_N, KC_E, KC_I, KC_O,
  KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_M, KC_COMM, KC_DOT, KC_SLSH,
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO,KC_NO,KC_NO,
    KC_LSFT, KC_SPACE, KC_NAV_ENT, KC_NO
  ),
};
