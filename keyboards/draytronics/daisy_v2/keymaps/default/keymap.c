/*Copyright 2024 Blake Drayson / Draytronics

Contact info@draytronics.co.uk

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

enum layers {
    _BASE,
    _CODE
};

enum my_keycodes {
  ENCODER_PRESS = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * ┌────────────┐
     * │ Vol / Anim │
     * ├────────────┼────────────┬────────────┬─────────────┐
     * │ Code Layer │ Media Next │ Media Prev │ Media Pause │
     * ├────────────┼────────────┼────────────┼─────────────┤
     * │ Prev Desk  │ Miss Ctrl  │ App Window │  Next Desk  │
     * └────────────┴────────────┴────────────┴─────────────┘
     */
    [_BASE] = LAYOUT(
        ENCODER_PRESS,
        MO(_CODE), KC_MPRV, KC_MNXT, KC_MPLY,
        C(KC_LEFT), C(KC_UP), C(KC_DOWN), C(KC_RIGHT)
    ),
    /*
     * ┌────────────┐
     * │ Vol / Anim │
     * ├────────────┼────────────┬────────────┬─────────────┐
     * │            │  RGB Mode  │   RBG Hue  │  RGB Toggle │
     * ├────────────┼────────────┼────────────┼─────────────┤
     * │ Scrn Shot  │ Force Quit │   GUI + F  │   DFU Mode  │
     * └────────────┴────────────┴────────────┴─────────────┘
     */
    [_CODE] = LAYOUT(
        ENCODER_PRESS,
        _______, RGB_MOD, RGB_HUI, RGB_TOG,
        G(S(KC_5)), G(A(KC_ESC)), G(KC_F), QK_BOOT
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return false;
}
