/* Copyright 2021 Stanrc85
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
#include "stanrc85.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_alice(
    KC_ESC, KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CTLE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2_60),
             KC_LCTL,          KC_LALT, LT_BPCF, KC_LGUI,                           LT_SPCF,          TD_TWIN,          TD_TCTL
  ),

  [_DEFAULT] = LAYOUT_alice(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2_60),
             KC_LCTL,          KC_LALT, KC_SPC,  MO(_FN1_60),                       KC_SPC,           KC_RALT,          KC_RCTL
  ),

  [_FN1_60] = LAYOUT_alice(
    _______, KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______,  _______, CA_QUOT, _______, CA_SCLN, KC_VOLU,          KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PSCR, _______, _______, KC_INS,
    _______, KC_CAPS,  _______, _______, KC_LCTL, KC_LSFT, KC_VOLD,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
    _______, _______,  KC_RDP,  _______, _______, _______, _______,          _______, _______, KC_WBAK, KC_WFWD, _______, _______, _______, _______,
             _______,           _______, _______, _______,                            _______,          _______,          _______
  ),

  [_FN2_60] = LAYOUT_alice(
    BL_TOGG,  RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, RGB_SAI, RGB_HUD,  RGB_HUI, _______, _______, _______, _______, _______, _______, _______,
    BL_INC,   VLK_TOG, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, RESET,
    BL_DEC,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,          KC_MAKE,
    _______,  _______, _______, _______, _______, _______, _______,           _______, NK_TOGG, _______, _______, _______, _______, _______, _______,
              _______,          _______, _______, _______,                             _______,          _______,          TG(_DEFAULT)
  )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
  };

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(qmk_logo, false);
            break;
        case _DEFAULT:
            oled_write_ln_P(PSTR("     Layer: Game\n\n"), false);
            break;
        case _FN1_60:
            oled_write_ln_P(PSTR("     Layer: FN\n\n"), false);
            break;
        case _FN2_60:
            oled_write_ln_P(PSTR("     Layer: RGB\n\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
