#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "keymap_french.h"

extern keymap_config_t keymap_config;

#define BASE 0
#define NUMB 1
#define SHORT 2

// Special keys
#define COPY     RGUI(BP_C)
#define PASTE    RGUI(BP_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT( \
    KC_TAB,    BP_B,    BP_EACU, BP_P,    BP_O,    BP_EGRV, KC_ESC,      KC_BSPC, BP_DCIR, BP_V,    BP_D,    BP_L,    BP_J,    BP_Z,    \
    BP_W,      BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM, _______,     _______, BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    BP_M,    \
    KC_LSFT,   BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    _______,     _______, BP_QUOT, BP_Q,    BP_G,    BP_H,    BP_F,    BP_CCED, \
    MO(SHORT), KC_LCTL, _______, KC_LALT, KC_LGUI, KC_SPC,  MO(NUMB),    KC_ENT , KC_RSFT, KC_SPC,  _______, _______, _______, _______  \
  ),

  [NUMB] = LAYOUT( \
    BP_HASH, BP_DQUO, BP_LDQU, BP_RDQU, BP_LPRN, BP_RPRN, BP_AT,         BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, BP_EQL,  BP_PERC, KC_BSPC, \
    BP_DLR,  BP_1,    BP_2,    BP_3,    BP_4,    BP_5,    KC_LBRC,       KC_RBRC, BP_6,    BP_7,    BP_8,    BP_9,    BP_0,    BP_DEG,  \
    _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______  \
  ),

  [SHORT] = LAYOUT( \
    _______, _______, _______, _______,  _______, _______, _______,    _______, _______, _______, _______, _______, _______, QK_BOOT, \
    _______, _______, KC_UP,   _______,  _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, COPY,    PASTE,    _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______  \
  )

};

