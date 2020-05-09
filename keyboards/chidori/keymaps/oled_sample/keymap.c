/* Copyright 2019 ENDO Katsuhiro <ka2hiro@kagizaraya.jp>
 * Copyright 2020 Masaya Uno
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

#include "board.h"

enum layer_number {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |ADJUST| Esc  | Alt  | GUI  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_QWERTY] = LAYOUT(
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,            KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
  /* Colemak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   K  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |ADJUST| Esc  | Alt  | GUI  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_COLEMAK] = LAYOUT(
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,              KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
      KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,              KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,            KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |             |   B  |   M  |   W  |   V  |   Z  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |ADJUST| Esc  | Alt  | GUI  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_DVORAK] = LAYOUT(
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,              KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,              KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,              KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,            KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   -  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      | Home | End  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_LOWER] = LAYOUT(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, _______, _______, _______, _______, _______,           KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
      _______, _______, _______, _______, _______, _______,           _______, _______, _______, KC_HOME, KC_END,  _______,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_RAISE] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,            KC_F12,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Caps |      |      |      |      | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             | KANA |      | Home |PageDn|PageUp| End  |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] = LAYOUT(
      _______, RESET,   _______, _______, _______, _______,           _______, QWERTY,  COLEMAK, DVORAK,  _______, KC_INS,
      KC_CAPS, _______, _______, _______, _______, AG_NORM,           AG_SWAP, KC_MINS, KC_EQL,  KC_PSCR, KC_SLCK, KC_PAUS,
      _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
    }
    return true;
}

bool led_update_user(led_t led_state) {
    board_set_led_by_index(0, LED_YELLOW, led_state.caps_lock);
    board_set_led_by_index(1, LED_YELLOW, led_state.scroll_lock);

    return false;
}

#ifdef OLED_DRIVER_ENABLE

void oled_write_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwerty"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case _DVORAK:
            oled_write_ln_P(PSTR("Dvorak"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

void oled_task_user(void) {
    // If you want to change the display of OLED, you need to change here
    oled_write_layer_state();
}
#endif
