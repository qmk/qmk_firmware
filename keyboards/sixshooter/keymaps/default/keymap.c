/* Copyright 2018 Nicholas Shaff
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

#define _BL 0
#define _FN 1

enum custom_keycode {
  SS_LON = SAFE_RANGE,
  SS_LOFF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Media Keys
     * ,-----------.
     * |Mut| V-| V+|
     * |---+---+---|
     * |Prv|Ply|Nxt|
     * `-----------'
     */
  [_BL] = LAYOUT( /* Base */
    MO(_FN), KC_VOLD, KC_VOLU, \
    KC_MPRV, KC_MPLY, KC_MNXT  \
  ),
  [_FN] = LAYOUT(
    KC_TRNS, SS_LON, SS_LOFF, \
    KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

void matrix_init_user(void) {
  sixshooter_led_all_on();
}

void matrix_scan_user(void) {

}

bool process_record_user( uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
        switch(keycode) {
            case SS_LON:
                sixshooter_led_all_on();
                return false;
            case SS_LOFF:
                sixshooter_led_all_off();
                return false;
        }
    }
    return true;
}
