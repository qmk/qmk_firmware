/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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

enum layer_names {
    _BASE,
    _FUNC1,
    _FUNC2,
    _FUNC3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer
     *
     * ,-----------------------------------------------------------. .-------------------.
     * | ~ | 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |NumL| /  | *  | -  |
     * |-----------------------------------------------------------| |-------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | | 7  | 8  | 9  |    |
     * |-----------------------------------------------------------| |--------------| +  |
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return | | 4  | 5  | 6  |    |
     * |-----------------------------------------------------------| |-------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     | | 1  | 2  | 3  | Ent|
     * |-----------------------------------------------------------| |--------------|    |
     * |Ctrl|Gui |Alt |      Space           | Alt | Win |FN  |Ctr | |   0     | .  |    |
     * `-----------------------------------------------------------' '-------------------'
     */
    [_BASE] = LAYOUT_all(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_BSPC, XXXXXXX,     KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_BSLS,              KC_P7,   KC_P8,   KC_P9,   XXXXXXX,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX,    KC_ENT,               KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,    XXXXXXX,              KC_P1,   KC_P2,   KC_P3,   XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RWIN, MO(_FUNC1), KC_RCTL,              KC_P0,   XXXXXXX, KC_PDOT, KC_PENT
    ),

    /* Function Layer
     *
     * ,-----------------------------------------------------------. .-------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   | QK_BOOT | |    |    |    |    |
     * |-----------------------------------------------------------| |-------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |    |    |    |    |
     * |-----------------------------------------------------------| |-------------------|
     * |       |   |   |   |   |   |   |   |   |   |   |   |       | |    |    |    |    |
     * |-----------------------------------------------------------| |-------------------|
     * |        |Tog|Mod|Hu+|Hu-|Sa+|Sa-|Va+|Va-|Stp|   |          | |    |    |    |    |
     * |-----------------------------------------------------------| |--------------|    |
     * |    |    |    |                      |     |     |    |    | |         |    |    |
     * `-----------------------------------------------------------' '-------------------'
     */
    [_FUNC1] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,   XXXXXXX,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______,              _______, _______, _______, _______,
        _______, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_STEP, _______, _______, XXXXXXX,              _______, _______, _______, XXXXXXX,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,              _______, XXXXXXX, _______, _______
    ),

    [_FUNC2] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,   XXXXXXX,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______,              _______, _______, _______, _______,
        _______, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_STEP, _______, _______, XXXXXXX,              _______, _______, _______, XXXXXXX,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,              _______, XXXXXXX, _______, _______
    ),

    [_FUNC3] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,   XXXXXXX,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______,              _______, _______, _______, _______,
        _______, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_STEP, _______, _______, XXXXXXX,              _______, _______, _______, XXXXXXX,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,              _______, XXXXXXX, _______, _______
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("M0lly\n"),false);

    // Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _FUNC1:
            oled_write_P(PSTR("Func 1\n"), false);
            break;
        case _FUNC2:
            oled_write_P(PSTR("Func 2\n"), false);
            break;
        case _FUNC3:
            oled_write_P(PSTR("Func 3\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Indicators
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
