#include QMK_KEYBOARD_H

#include "nicola.h"

#define _QWERTY 0
#define _NICOLA 1
#define _FN 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NICOLA,
  FN
};

static uint16_t mkeys[] = {FN};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_UP, KC_RSFT,
        FN, KC_ZKHK, KC_LGUI, KC_LALT, KC_MHEN, KC_SPC, KC_HENK, KC_KANA, KC_RALT, FN, KC_LEFT, KC_DOWN, KC_RGHT),

    [_NICOLA] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_UP, KC_RSFT,
        FN, KC_ZKHK, KC_LGUI, KC_LALT, KC_MHEN, KC_SPC, KC_HENK, KC_KANA, KC_RALT, FN, KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN] = LAYOUT_JP(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______, _______, _______, NICOLA, _______, _______, _______, _______, _______, _______, _______)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macro_id, uint8_t opt)
{
    return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case NICOLA:
      if (record->event.pressed) {
        if (!layer_state_is(_NICOLA)) {
          // 親指シフト
          layer_on(_NICOLA);
          // 親指シフト
          register_code(KC_LANG1); // Mac
          register_code(KC_HENK); // Win
          unregister_code(KC_LANG1); // Mac
          unregister_code(KC_HENK); // Win
        } else {
          // 親指シフト
          layer_off(_NICOLA);
          // 親指シフト
          register_code(KC_LANG2); // Mac
          register_code(KC_MHEN); // Win
          unregister_code(KC_LANG2); // Mac
          unregister_code(KC_MHEN); // Win
        }
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
      break;
  }

  // 親指シフト
  return process_nicola(keycode, record, _NICOLA, KC_SPC, KC_HENK, mkeys);
  // 親指シフト
}
