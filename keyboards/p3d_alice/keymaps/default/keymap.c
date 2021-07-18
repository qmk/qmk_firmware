/* Copyright 2021 Matthew Dias
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

//This is the ANSI version of the PCB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_all( \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL, KC_MUTE, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,      KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,      KC_ENT, KC_PGDN, \
    KC_LSFT,      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END, \
    KC_LCTL, KC_LGUI,      KC_LALT,      KC_SPC,      KC_SPC,      KC_RALT,      KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  \
)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        // tap_code(RGB_MOD);
         rgblight_step();
    } else {
        // tap_code(RGB_RMOD);
        rgblight_step_reverse();
    }
    return true;
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
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
}