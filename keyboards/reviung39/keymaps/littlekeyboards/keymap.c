/* Copyright 2019 gtips
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

enum layer_names {
    _BASE,
    _NUMBERS,
    _CODE,
    _NAVIGATION,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COMMAND_ESCAPE,
    TAB_LGUI,
    NAVIGATION_SPACE,
    ALT_BACKSPACE
};

#define NUMBERS  MO(_NUMBERS)
#define CODE  MO(_CODE)
#define ADJUST MO(_ADJUST)

#define KC_CMES COMMAND_ESCAPE
#define KC_TBGU TAB_LGUI
#define KC_NVSP NAVIGATION_SPACE
#define KC_ALQU ALT_QUOTE
#define KC_ALBS ALT_BACKSPACE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
    KC_TBGU,  KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_ALBS,
    KC_CMES,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_ENT),
                                                       NUMBERS,  KC_NVSP,  CODE
  ),

  [_NUMBERS] = LAYOUT_reviung39(
    KC_TILD,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN, _______,
    KC_F1,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   _______,
                                                       _______,  KC_ENT,   _______
  ),

  [_CODE] = LAYOUT_reviung39(
    KC_GRV,   _______, _______, KC_LCBR, KC_RCBR,  _______,           _______, KC_AMPR, KC_PIPE, _______, _______, _______,
    _______,  _______, _______, KC_LPRN, KC_RPRN,  _______,           _______, KC_UNDS, KC_MINS, _______, _______, _______,
    _______,  _______, _______, KC_LBRC, KC_RBRC,  _______,           _______, KC_PLUS, KC_EQL,  _______, KC_BSLS, _______,
                                                   _______,  _______, _______
  ),

  [_NAVIGATION] = LAYOUT_reviung39(
    _______,  _______, _______, KC_UP,   _______,  _______,           _______, _______, KC_UP,   _______, _______, _______,
    _______,  _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,           _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,
    _______,  _______, _______, _______, _______,  _______,           _______, _______, _______, _______, _______, _______,
                                                   _______,  _______, _______
  ),

//   [_BLANK] = LAYOUT_reviung39(
//     _______,  _______, _______, _______, _______,  _______,           _______, _______, _______, _______, _______, _______,
//     _______,  _______, _______, _______, _______,  _______,           _______, _______, _______, _______, _______, _______,
//     _______,  _______, _______, _______, _______,  _______,           _______, _______, _______, _______, _______, _______,
//                                                    _______,  _______, _______
//   ),
};
uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _NUMBERS, _CODE, _ADJUST);
}

uint16_t custom_lt_timer;
keypos_t prv_key_pressed;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    inline void tap(uint16_t keycode) {
        register_code(keycode);
        unregister_code(keycode);
    };

    if (record->event.pressed) {
        #ifdef SSD1306OLED
            set_keylog(keycode, record);
        #endif
        prv_key_pressed = record->event.key;
    }

#define IS_KEYPOS_SAME(keyone, keytwo) ((keyone.col == keytwo.col) && (keyone.row == keytwo.row))
#define ANOTHER_KEY_PRESSED (!IS_KEYPOS_SAME(prv_key_pressed, record->event.key))

    switch (keycode) {
        case COMMAND_ESCAPE:
            if (record->event.pressed) {
                custom_lt_timer = timer_read();
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
                if (timer_elapsed(custom_lt_timer) < 150 && (!ANOTHER_KEY_PRESSED)) {
                    tap(KC_ESC);
                }
            }
            return false;
            break;
        case TAB_LGUI:
            if (record->event.pressed) {
                custom_lt_timer = timer_read();
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
                if (timer_elapsed(custom_lt_timer) < 150 && (!ANOTHER_KEY_PRESSED)) {
                    tap(KC_TAB);
                }
            }
            return false;
            break;
        case NAVIGATION_SPACE:
            if (record->event.pressed) {
                custom_lt_timer = timer_read();
                layer_on(_NAVIGATION);
            } else {
                layer_off(_NAVIGATION);
                if (timer_elapsed(custom_lt_timer) < 150 && (!ANOTHER_KEY_PRESSED)) {
                    tap(KC_SPC);
                }
            }
            return false;
            break;
        case ALT_BACKSPACE:
            if (record->event.pressed) {
                custom_lt_timer = timer_read();
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (timer_elapsed(custom_lt_timer) < 150 && (!ANOTHER_KEY_PRESSED)) {
                    tap(KC_BSPC);
                }
            }
            return false;
            break;
    }
    return true;
}
