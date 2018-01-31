#include QMK_KEYBOARD_H
#include "action.h"
#include "users/jrolfs/jrolfs.h"

// Layer names
#define _BASE     0
#define _LOWER    1
#define _RAISE    2
#define _BOTH     3
#define _FUNCTION 4

enum custom_keycodes {
  BASE = KEYMAP_SAFE_RANGE,
  LOWER,
  RAISE,
  BOTH,
  FUNCTION
};

// Layer keycodes
#define LOWER    M(_LOWER)
#define RAISE    M(_RAISE)
#define FUNCTION M(_FUNCTION)

// Function macro keycodes
#define ESC_CTL FUNC(0) // Tap for Esc, hold for Ctrl
#define SFT_ENT FUNC(1) // Tap for Enter, hold for Shift

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [1] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_4x12( \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, \
    ESC_CTL,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT, \
    FUNCTION, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_LCTL, KC_LPRN, KC_RPRN, FUNCTION
  ),

  [_LOWER] = LAYOUT_ortho_4x12( \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, \
    _______, _______, KC_SLCK, KC_PAUS, _______, KC_PGDN, KC_PGDN, _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR
  ),

  [_RAISE] = LAYOUT_ortho_4x12( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,    KC_0,    _______, \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,   KC_LBRC, KC_RBRC, KC_BSLS, \
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, _______,  _______, _______, _______, \
    _______, _______, _______, _______, _______, KC_PGUP, KC_PGUP, _______, KC__MUTE, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  [_BOTH] = LAYOUT_ortho_4x12( \
    _______, _______, _______, _______, KC_RESET, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______,  _______, _______, _______, BL_DEC,  BL_INC,  _______, BL_TOGG
  ),

  [_FUNCTION] = LAYOUT_ortho_4x12( \
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    RGB_TOG, RGB_RMOD, RGB_MOD, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case RAISE: // Raised layer
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _BOTH);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _BOTH);
      }
      return false;

    case LOWER: // Lowered layer
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _BOTH);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _BOTH);
      }
      return false;

    case FUNCTION:
      if (record->event.pressed) {
        layer_on(_FUNCTION);
      } else {
        layer_off(_FUNCTION);
      }
      return false;
  }

  return true;
}
