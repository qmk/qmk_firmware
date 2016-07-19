/*
 * Keyboard: Atreus
 * Keymap:   replicaJunction
 * Version:  0.1
 *
 * This keymap is designed to complement my Ergodox keyboard layout, found in keyboards/ergodox_ez.
 * The Atreus keyboard is a 40% board whose design was heavily influenced by the Ergodox, and I now
 * have both keyboards, so I've designed these layouts in an effort to make switching between the
 * two as easy as possible.
 *
 * Clearly, the Atreus is the limiting factor in this equation, so I've taken heavy advantage of
 * function and dual-role keys.
 *
 * The default key layout in this keymap is Colemak-ModDH. Information on that layout can be found
 * here: https://colemakmods.github.io/mod-dh/
 */

#include "atreus.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Note that whatever is set as layer 0 will be the default layer of the keyboard.

#define _CO 0 // Colemak
#define _QW 1 // QWERTY
#define _GA 2 // Gaming
#define _NU 3 // Numpad
#define _FN 4 // Function

// Quick alias for visual sake
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_CO] = KEYMAP(
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                    KC_J,            KC_L,    KC_U,    KC_Y,    KC_SCLN,
  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                                    KC_M,            KC_N,    KC_E,    KC_I,    KC_O,
  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                                    KC_K,            KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
  KC_ESC,  KC_TAB,  KC_LGUI, KC_LSFT, KC_LSFT, CTL_T(KC_BSPC), ALT_T(KC_ENT),  LT(_NU, KC_SPC), MO(_NU), KC_MINS, KC_QUOT, KC_EQL
),

[_QW] = KEYMAP( /* Qwerty */
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                    KC_Y,            KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                    KC_H,            KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                    KC_N,            KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
  KC_ESC,  KC_TAB,  KC_LGUI, KC_LSFT, KC_BSPC, CTL_T(KC_BSPC), ALT_T(KC_ENT),  LT(_NU, KC_SPC), MO(_NU), TG(_GA), KC_QUOT, KC_EQL
),

[_NU] = KEYMAP( /* Numbers and symbols */
  KC_GRV,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                          KC_PGUP, KC_7,    KC_8,   KC_9, KC_ASTR,
  KC_HASH, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                          KC_PGDN, KC_4,    KC_5,   KC_6, KC_PLUS,
  KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                          KC_TILD, KC_1,    KC_2,   KC_3, KC_BSLS,
  MO(_FN), KC_INS,  KC_LGUI, KC_LSFT, _______, CTL_T(KC_BSPC), _______, KC_SPC,  _______, KC_DOT, KC_0, _______
),

[_FN] = KEYMAP( /* Functions */
  KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_DELT, KC_LEFT, KC_DOWN, KC_RGHT, KC_DOWN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11,
  _______, _______, _______, _______, _______,                   _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,
  _______, _______, KC_LGUI, KC_LSFT, _______, _______, _______, _______,  _______, DF(_CO), DF(_QW), RESET
),

[_GA] = KEYMAP( /* Gaming */
  _______, _______, _______, _______, _______,                   _______, KC_WH_U, KC_MS_U, KC_WH_D, _______,
  _______, _______, _______, _______, _______,                   _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
  _______, _______, _______, _______, _______,                   KC_BTN3, _______, KC_MS_D, _______, _______,
  _______, _______, _______, _______, KC_SPC,  KC_BSPC, KC_BTN2, KC_BTN1, _______, _______, _______, _______
)};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
