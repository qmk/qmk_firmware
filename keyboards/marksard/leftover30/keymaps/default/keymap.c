/* Copyright 2020 marksard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_number {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    RGBRST = SAFE_RANGE,
    LOWER,
    RAISE,
    KANJI,
};

// #define KC_ESAD  LT(_ADJUST, KC_ESC)
// #define KC_BSLO  LT(_LOWER, KC_BSPC)
#define KC_LOWR  MO(_LOWER)
#define KC_SPRA  LT(_RAISE, KC_SPC)
#define KC_AJST  MO(_ADJUST)

#define KC_Q_AL  LALT_T(KC_Q)
#define KC_A_CT  LCTL_T(KC_A)
#define KC_Z_SF  LSFT_T(KC_Z)
#define KC_X_AL  LALT_T(KC_X)
#define KC_ENSF  RSFT_T(KC_ENT)
#define KC_SLSF  RSFT_T(KC_SLSH)

#define KC_F1AL  LALT_T(KC_F1)
#define KC_F6CT  LCTL_T(KC_F6)
#define KC_11SF  LSFT_T(KC_F11)
#define KC_12AL  LALT_T(KC_F12)
#define KC_QUSF  RCTL_T(KC_QUOT)
#define KC_ROSF  RSFT_T(KC_INT1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all(
  //,-----------------------------------------------------------------------------------------------------------.
               KC_Q_AL,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_A_CT,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_ENSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_Z_SF, KC_X_AL,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,     KC_SLSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LGUI,                                KC_SPRA,                                 KC_LOWR, KC_RCTL
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_all(
  //,-----------------------------------------------------------------------------------------------------------.
               KC_F1AL,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_MINS,  KC_EQL, KC_INT3, KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_F6CT,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN,     KC_QUSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_11SF, KC_12AL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_GRV, KC_INT1, KC_SLSH,     KC_ROSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,                                KC_AJST,                                 _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_all(
  //,-----------------------------------------------------------------------------------------------------------.
                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,     _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_LSFT, XXXXXXX,  KC_ESC,  KC_TAB,   KANJI,  KC_DEL, KC_COMM,  KC_DOT, KC_BSLS,     KC_ROSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,                                _______,                                 KC_AJST, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT_all(
  //,-----------------------------------------------------------------------------------------------------------.
               QK_BOOT,  RGBRST, AG_NORM, AG_SWAP, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT,     KC_NUM,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               UG_NEXT, UG_HUED, UG_SATD, UG_VALD, XXXXXXX, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX,     KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,                                _______,                                 _______, KC_CAPS
  //`-----------------------------------------------------------------------------------------------------------'
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SPRA:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case KANJI:
      if (record->event.pressed) {
          register_code16(keymap_config.swap_lalt_lgui ? A(KC_GRV) : KC_LNG2);
      } else {
          unregister_code16(keymap_config.swap_lalt_lgui ? A(KC_GRV) : KC_LNG2);
      }
    break;
#ifdef RGBLIGHT_ENABLE
    case RGBRST:
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
    break;
#endif
    default:
      result = true;
      break;
  }

  return result;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_ADJUST)) {
          if (clockwise) {
              rgblight_increase_hue_noeeprom();
          } else {
              rgblight_decrease_hue_noeeprom();
          }
        } else if (IS_LAYER_ON(_LOWER)) {
          tap_code16((clockwise == true) ? LCTL(KC_Y) : LCTL(KC_Z));
        } else if (IS_LAYER_ON(_RAISE)) {
          tap_code16((clockwise == true) ? S(KC_DOWN) : S(KC_UP));
        } else {
          tap_code((clockwise == true) ? MS_WHLD : MS_WHLU);
        }
    }
    return true;
}

// for exsample customize of LED inducator
// bool led_update_user(led_t led_state) {
//     gpio_write_pin(D2, IS_LAYER_ON(_LOWER));
//     gpio_write_pin(D1, IS_LAYER_ON(_RAISE));
//     return false;
// }
