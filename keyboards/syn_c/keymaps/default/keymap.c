/* Copyright 2019 kratsyn
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

bool at_enable = false;
uint32_t at_clock = 0;

enum custom_keycodes {
    ALT_TAB_TICK,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB_TICK:
            at_enable = record->event.pressed;
            if (at_enable) {
                at_clock = timer_read();
                register_code(KC_LALT);
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LALT);
            }
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        BL_STEP, OSL(1),  KC_MUTE,
        LCTL(LSFT(KC_ESC)), KC_UP,ALT_TAB_TICK,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_ESC,  RESET,
        LGUI(KC_P), KC_PGUP, LCA(KC_DELETE),
        BL_BRTG, KC_PGDOWN, KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

void matrix_scan_user(void) {
    // [ALT-TAB] (send tab every 500ms until the key is released
    if (at_enable && (timer_elapsed(at_clock) > 500 )) {
        tap_code(KC_TAB);
        at_clock = timer_read();
    }
}
