/* Copyright 2020 tominabox1
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  KC_MPLY,  KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,            KC_H,   KC_J,    KC_K,   KC_L,  KC_SCLN,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,
                         KC_LCTL, KC_ENT,            KC_SPC, KC_RALT
  ),

  [1] = LAYOUT(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                 KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_TRNS
  ),

  [2] = LAYOUT(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                 KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_TRNS
  ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // rotates for dank proper orientation
}

void render_lechiffre_logo(void) {
    static const char PROGMEM lechiffre_logo[] = {
	// 'lechiffre_logo', 32x20px
   0x00, 0x3e, 0x20, 0x20, 0x00, 0x18, 0x2c, 0xa8, 0x80, 0x00, 0x1c, 0x22, 0x22, 0x00, 0x3e, 0x08,
0x30, 0x00, 0x34, 0x00, 0x3c, 0x0a, 0x00, 0xbc, 0x8a, 0x00, 0x38, 0x08, 0x00, 0x18, 0x2c, 0x28,
0x00, 0xb6, 0xb6, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00,
0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xb6, 0xb6, 0x00,
0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00
};

  oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
}

static void render_status(void) {

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _NUM_SYM:
            oled_write_ln_P(PSTR(" NUM"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR(" NAV"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("Lock\n"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR(" N") : PSTR(" *"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("C") : PSTR("*"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("S\n") : PSTR("*\n"), false);
}

void oled_task_user(void) {
    render_lechiffre_logo();
    oled_set_cursor(0,3);
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
}
#endif
