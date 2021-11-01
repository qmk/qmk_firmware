 /* Copyright 2020 Imam Rafii
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

enum layers {
    _BL,
    _FL
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        KC_F1,
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_DEL,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,   KC_BSPC,
        KC_LCTL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,    KC_ENT,
        KC_LSFT,   KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT, MO(_FL),
        MO(_FL),  KC_LGUI,  KC_LALT,               KC_SPC,                KC_RALT, KC_RGUI, MO(_FL), KC_RCTL
    ),
    [_FL] = LAYOUT(
        KC_TRNS,
        KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_PSCR, KC_INS,
        KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_CAPS,  KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT,    KC_TRNS,
        KC_TRNS,  KC_HOME, XXXXXXX, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, XXXXXXX, KC_END,    KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

#ifdef OLED_ENABLE

static void render_oled(void) {
    oled_write_P(PSTR("Pill60"), false);
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
    oled_write_P(PSTR("   "), false);
    switch (get_highest_layer(layer_state)) {
        case _BL:
            oled_write_P(PSTR("Base"), false);
            break;
        case _FL:
            oled_write_P(PSTR("Function"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Base"), false);
    }
    oled_write_P(PSTR("       "), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

bool oled_task_user(void) {
    render_oled();
    return false;
}

#endif

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
    }
    return true;
}

#endif
