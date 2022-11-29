/* Copyright 2022 splitkb.com <support@splitkb.com>
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

#define SYMB OSL(_SYMBOL)
#define FUNC OSL(_FUNCTION)
#define NAV TO(_NAV)
#define BASE TO(_ISRT)
#define NUM TO(_NUM)
#define MDIA TO(_MEDIA)
/* #define MOD_SPC GUI_T(KC_SPC) // For DWM */
#define MOD_SPC MEH_T(KC_SPC)
#define MOD_BSP LT(0,KC_BSPC)
#define LT_UP LT(0,KC_UP)
#define LT_LEFT LT(0,KC_LEFT)
/* Home row mods */
#define HOME_S LGUI_T(KC_S)
#define HOME_R LALT_T(KC_R)
#define HOME_T LCTL_T(KC_T)
#define HOME_N RCTL_T(KC_N)
#define HOME_E RALT_T(KC_E)
#define HOME_A RGUI_T(KC_A)
#define HOME_P LT(_NUM,KC_P)


enum layers {
    _ISRT = 0,
    _SYMBOL,
    _FUNCTION,
    _NAV,
    _NUM,
    _MEDIA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ISRT] = LAYOUT(
        KC_Y, KC_C,   KC_L,   KC_M,    KC_K,     KC_Z,   KC_F,   KC_U,    KC_COMM, KC_QUOT,
        KC_I, HOME_S, HOME_R, HOME_T,  KC_G,     HOME_P, HOME_N, HOME_E,  HOME_A,  KC_O,
        KC_Q, KC_V,   KC_W,   KC_D,    KC_J,     KC_B,   KC_H,   KC_SLSH, KC_DOT,  KC_X,
                              MOD_SPC, SYMB,     FUNC,   MOD_BSP
    ),
    [_SYMBOL] = LAYOUT(
        KC_Y, KC_C,   KC_L,   KC_M,    KC_K,     KC_Z,   KC_F,   KC_U,    KC_COMM, KC_QUOT,
        KC_I, HOME_S, HOME_R, HOME_T,  KC_G,     HOME_P, HOME_N, HOME_E,  HOME_A,  S(KC_F),
        KC_Q, KC_V,   KC_W,   KC_D,    KC_J,     KC_B,   KC_H,   KC_SLSH, KC_DOT,  KC_X,
                              MOD_SPC, SYMB,     FUNC,   MOD_BSP
    ),
    [_FUNCTION] = LAYOUT(
        KC_Y, KC_C,   KC_L,   KC_M,    KC_K,     KC_Z,   KC_F,   KC_U,    KC_COMM, KC_QUOT,
        KC_I, HOME_S, HOME_R, HOME_T,  KC_G,     HOME_P, HOME_N, HOME_E,  HOME_A,  S(KC_F),
        KC_Q, KC_V,   KC_W,   KC_D,    KC_D,     KC_B,   KC_H,   KC_SLSH, KC_DOT,  QK_BOOT,
                              MOD_SPC, SYMB,     FUNC,   MOD_BSP
    ),
    [_NUM] = LAYOUT(
        KC_Y, KC_C,   KC_L,   KC_M,    KC_K,     KC_Z,   KC_F,   KC_U,    KC_COMM, KC_QUOT,
        KC_I, HOME_S, HOME_R, HOME_T,  KC_G,     HOME_P, HOME_N, HOME_E,  HOME_A,  S(KC_F),
        KC_Q, KC_V,   KC_W,   KC_D,    KC_D,     KC_B,   KC_H,   KC_SLSH, KC_DOT,  KC_X,
                              MOD_SPC, SYMB,     FUNC,   MOD_BSP
    ),
    [_NAV] = LAYOUT(
        KC_Y, KC_C,   KC_L,   KC_M,    KC_K,     KC_Z,   KC_F,   KC_U,    KC_COMM, KC_QUOT,
        KC_I, HOME_S, HOME_R, HOME_T,  KC_G,     HOME_P, HOME_N, HOME_E,  HOME_A,  S(KC_F),
        KC_Q, KC_V,   KC_W,   KC_D,    KC_D,     KC_B,   KC_H,   KC_SLSH, KC_DOT,  KC_X,
                              MOD_SPC, SYMB,     FUNC,   MOD_BSP
    )
};

bool is_mac_the_default(void) { return keymap_config.swap_lctl_lgui; }

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  bool isPressed = record->event.pressed;
  bool isHeld = !record->tap.count && isPressed;
  /* const uint8_t mods = get_mods(); */

  switch (keycode) {
  case MOD_BSP:
    if (isHeld) {
      uint16_t code = is_mac_the_default() ? A(KC_BSPC) : C(KC_BSPC);
      tap_code16(code);
      return false;
    }
  }
  return true;
}

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
  case HOME_R:
    return TAPPING_TERM + 200;
  case HOME_T:
    return TAPPING_TERM + 200;
  case HOME_N:
    return TAPPING_TERM + 200;
  case HOME_P:
    return TAPPING_TERM + 200;
  case HOME_E:
    return TAPPING_TERM + 200;
  case HOME_S:
    return TAPPING_TERM + 200;
  case HOME_A:
    return TAPPING_TERM + 200;
  case LT_UP:
    return TAPPING_TERM + 200;
  case MOD_SPC:
    return TAPPING_TERM + 60;
  case MOD_BSP:
    return TAPPING_TERM + 60;
  default:
    return TAPPING_TERM;
  }
}
#endif
