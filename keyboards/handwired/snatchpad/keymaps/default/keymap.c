// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
  TOGGLE_RESET = SAFE_RANGE,
  TOGGLE_M1,
  TOGGLE_M2,
  TOGGLE_M3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MPRV, KC_MNXT, LT(5, KC_MPLY),
    KC_MRWD, KC_MFFD, KC_CALC,
    KC_MUTE,          KC_RSFT
  ),
  [1] = LAYOUT(
    KC_HOME, KC_UP  , LT(5, KC_END),
    KC_LEFT, KC_DOWN, KC_RGHT,
    KC_MUTE,          KC_MPLY
  ),
  [2] = LAYOUT(
    KC_INS , KC_HOME, LT(5, KC_PGUP),
    KC_DEL , KC_END , KC_PGDN,
    KC_MUTE,          KC_MPLY
  ),
  [3] = LAYOUT(
    KC_HOME, KC_UP  , LT(5, KC_END),
    KC_LEFT, KC_DOWN, KC_RGHT,
    KC_BTN1,          KC_BTN2
  ),
  [4] = LAYOUT(
    TOGGLE_RESET, KC_LOCK, LT(5, KC_ESC),
    TOGGLE_M1, TOGGLE_M3, TOGGLE_M2,
    KC_BTN1,          KC_BTN2
  ),
  [5] = LAYOUT(
    TO(0)  , TO(1)  , KC_NO  ,
    TO(2)  , TO(3)  , TO(4)  ,
    KC_BTN1,          KC_BTN2
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t layer = biton32(layer_state);

  /* Default behaviour for encoders is to move mouse cursor */
  if (index == 0) { /* First encoder */
    switch(layer) {
      case 3:
      case 4:
        if (clockwise) {
          tap_code(KC_MS_L);
        } else {
          tap_code(KC_MS_R);
        }
        return false;

      default:
        if (clockwise) {
          tap_code_delay(KC_VOLU, 10);
        } else {
          tap_code_delay(KC_VOLD, 10);
        }
        return false;
    }

  } else if (index == 1) { /* Second encoder */
      switch(layer) {
        case 3:
        case 4:
          if (clockwise) {
            tap_code(KC_MS_D);
          } else {
            tap_code(KC_MS_U);
          }
          return false;

        default:
          if (clockwise) {
            tap_code(KC_WH_D);
          } else {
            tap_code(KC_WH_U);
          }
          return false;

    }
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case TOGGLE_RESET:
      if (record->event.pressed) {
        unregister_code(KC_BTN1);
        unregister_code(KC_BTN2);
        unregister_code(KC_BTN3);
      }
      return false;

    case TOGGLE_M1:
      if (record->event.pressed) {
        static bool toggled_m1;
        toggled_m1 ^= 1;
        if (toggled_m1) {
          register_code(KC_BTN1);
        } else {
          unregister_code(KC_BTN1);
        }
      }
      return false;

    case TOGGLE_M2:
      if (record->event.pressed) {
        static bool toggled_m2;
        toggled_m2 ^= 1;
        if (toggled_m2) {
          register_code(KC_BTN2);
        } else {
          unregister_code(KC_BTN2);
        }
      }
      return false;

    case TOGGLE_M3:
      if (record->event.pressed) {
        static bool toggled_m3;
        toggled_m3 ^= 1;
        if (toggled_m3) {
          register_code(KC_BTN3);
        } else {
          unregister_code(KC_BTN3);
        }
      }
      return false;

    default:
      return true; // Process all other keycodes normally
  }
}
