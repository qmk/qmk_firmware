/*
Copyright 2020 Alabahuy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
        QK_GESC, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_DEL,
        KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
                 KC_LCTL,          KC_LALT,          KC_SPC,  MO(1),            KC_SPC,           KC_RALT,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
  [1] = LAYOUT(
        KC_NUM,  RGB_TOG, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT, _______,
        KC_SCRL, _______, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   _______, _______, _______, _______,
        _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______,
                 _______, _______,  _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______,          _______,
                 _______,           _______,          _______, _______,          _______,          _______,          _______, _______, _______
    ),
  [2] = LAYOUT(
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                 _______,           _______,          _______, _______,          _______,          _______,          _______, _______, _______
    ),
  [3] = LAYOUT(
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                 _______,           _______,          _______, _______,          _______,          _______,          _______, _______, _______
    ),

};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("* R A R T L I C E *\n  Powered by QMK\nLayer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Fn\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Layer 3\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Layer 4\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undifined\n"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return false;
}
#endif
