/* Copyright 2022 NaCly
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
#define _BASE 0
#define _L1 1
#define _L2 2
#define _L3 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,       KC_5,                      KC_6,    KC_7,       KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,                      KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LGUI, KC_A,    KC_S,    KC_D,    LT(1,KC_F), KC_G,                      KC_H,    LT(2,KC_J), KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,                      KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_GRV,  KC_EQL,     KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  KC_LBRC,    KC_RBRC, KC_HOME, KC_END,  KC_ESC
    ),
    //Holding F
    [1] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LGUI, KC_NO,   KC_NO,   KC_NO,   _______, KC_NO,                     KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_END,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
    //Holding J
    [2] = LAYOUT(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO,   KC_NO,   KC_F14,   KC_F15,   KC_ENT,  KC_SPC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   TG(3)
    ),
    //game layer
    [3] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,       KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    LT(2,KC_J), KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_NO,   KC_M, KC_GRV,  KC_SPC,  KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  KC_LBRC,    KC_RBRC, KC_HOME, KC_END,  TO(0)
    )
};
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _L1:
            oled_write_P(PSTR("ONE\n"), false);
            break;
        case _L2:
            oled_write_P(PSTR("TWO\n"), false);
            break;
        case _L3:
            oled_write_P(PSTR("Three\n"), false);
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
