/* Copyright 2020 noclew
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE,
    LOWER,
    RAISE,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE
     * -------------------------------------------               -------------------------------------------
     * |   `  |   1  |   2  |   3  |   4  |   5  |               |   6  |   7  |   8  |   9  |   0  | Bksp |
     * -------------------------------------------               -------------------------------------------
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |               |   Y  |   U  |   I  |   O  |   P  |   \  |
     * -------------------------------------------   ---------  --------------------------------------------
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   | Bksp  |   |   H  |   J  |   K  |   L  |   ;  |Enter |
     * -------------------------------------------   ---------   -------------------------------------------
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   | Del   |   |   N  |   M  |   ,  |   .  |   /  | "    |
     * -------------------------------------------   ---------   -------------------------------------------
     *        | Ctrl | GUI  |  Alt |Lower |Space |               |Space |Raise |Alt   | DOWN | UP   |
     *        ------------------------------------               ------------------------------------
     */

    [_BASE] = LAYOUT(
    KC_GRV,     KC_1   ,    KC_2   ,    KC_3   ,    KC_4   ,    KC_5,                       KC_6   ,    KC_7   ,    KC_8   ,    KC_9   ,    KC_0   ,    KC_BSPC,
    KC_TAB,     KC_Q   ,    KC_W   ,    KC_E   ,    KC_R   ,    KC_T,                       KC_Y   ,    KC_U   ,    KC_I   ,    KC_O   ,    KC_P   ,    KC_BSLS,
    KC_ESC,     KC_A   ,    KC_S   ,    KC_D   ,    KC_F   ,    KC_G,       KC_BSPC,        KC_H   ,    KC_J   ,    KC_K   ,    KC_L   ,    KC_SCLN,    KC_ENT ,
    KC_LSFT,    KC_Z   ,    KC_X   ,    KC_C   ,    KC_V   ,    KC_B,       KC_DEL ,        KC_N   ,    KC_M   ,    KC_COMM,    KC_DOT ,    KC_SLSH,    RSFT_T(KC_QUOT),
                KC_LCTL,    KC_LALT,    KC_LGUI,    LOWER  ,    KC_SPC,                     KC_SPC ,    RAISE  ,    KC_RALT,    KC_DOWN,    KC_UP
    ),
    [_LOWER] = LAYOUT(
    KC_F1  ,    KC_F2  ,    KC_F3  ,    KC_F4  ,    KC_F5  ,    KC_F6  ,                    KC_F7  ,    KC_F8  ,    KC_F9  ,    KC_F10 ,    KC_F11 ,    KC_F12 ,
    KC_BSPC,    KC_EQL ,    KC_7   ,    KC_8   ,    KC_9   ,    KC_SLSH,                    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_AT  ,    KC_EXLM,    KC_BSLS,
    KC_ENT ,    KC_0   ,    KC_4   ,    KC_5   ,    KC_6   ,    KC_MINS,     KC_LEFT,       KC_UNDS,    KC_LPRN,    KC_RPRN,    KC_HASH,    KC_DQUO,    _______,
    KC_DLR ,    KC_PAST,    KC_1   ,    KC_2   ,    KC_3   ,    KC_PPLS,     KC_RGHT,       KC_PIPE,    KC_LCBR,    KC_RCBR,    KC_PERC,    KC_AMPR,    _______,
                _______,    _______,    _______,    _______,    _______,                    _______,    _______,    _______,    _______,    _______
    ),

    [_RAISE] = LAYOUT(
    _______,    _______,    _______,    _______,    _______,    _______,                    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,                    _______,    KC_HOME,    KC_BSPC,    KC_DEL ,    KC_END ,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    KC_UP  ,        KC_LEFT,    KC_DOWN,    KC_UP  ,    KC_RGHT,    KC_QUOT,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    KC_DOWN,        _______,    KC_PGUP,    _______,    KC_PGDN,    _______,    _______,
                _______,    _______,    _______,    _______,    _______,                    _______,    _______,    _______,    _______,    _______
    ),
    [_ADJUST] = LAYOUT(
    RESET  ,    _______,    _______,    _______,    _______,    _______,                    _______,    _______,    _______,    _______,    _______,    DEBUG  ,
    _______,    RGB_TOG,    RGB_RMOD,   RGB_MOD,    RGB_VAD,    RGB_VAI,                    _______,    _______,    _______,    _______,    _______,    _______,
    KC_CAPS,    _______,    RGB_HUD,    RGB_HUI,    RGB_SAD,    RGB_SAI,    KC_VOLU,        _______,    _______,    _______,    _______,    _______,    _______,
    _______,    AU_ON  ,    AU_OFF ,    _______,    _______,    _______,    KC_VOLD,        _______,    _______,    _______,    _______,    _______,    _______,
                _______,    _______,    _______,    _______,    _______,                    _______,    _______,    _______,    _______,    _______
    )
};
