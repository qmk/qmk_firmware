/*
Copyright 2022 an_achronism (@an-achronism)

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
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Del│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab| Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │UK#│Rtn|
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Sft│ ↑ │App|
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│Ctl│Alt│GUI│L_1│Spc│L_2|GUI│Alt│Ctl|UK\│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x14(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP, RSFT_T(KC_APP),
        KC_ESC,  KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,  MO(2),   KC_RGUI, KC_RALT, KC_RCTL, KC_NUBS, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_ortho_5x14(
        KC_BRID, KC_BRIU, _______, _______, _______, _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PEQL, _______, _______, _______, KC_PWR,
        _______, _______, KC_UP,   _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_PAUS, KC_ESC,  _______, KC_SLEP,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______, _______, KC_CALC,
        KC_CAPS, _______, _______, _______, _______, KC_PAUS, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, KC_CAPS, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT_ortho_5x14(
        _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP,
        _______, KC_F4,   KC_F3,   KC_F2,   KC_F1,   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, C(KC_BRK), KC_ESC, _______, _______,
        _______, KC_F8,   KC_F7,   KC_F6,   KC_F5,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_MPRV, KC_MNXT, KC_MPLY,
        KC_CAPS, KC_F12,  KC_F11,  KC_F10,  KC_F9,  C(KC_BRK),_______, _______, _______, _______, _______, KC_CAPS, _______, KC_PSCR,
        _______, _______, _______, _______, MO(3),   _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_ortho_5x14(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

// Initialise RBG matrix with all LEDs set to solid colour and zero HSV (i.e. off):
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
};

// Custom RGB indicator behaviour:
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t led_processed_count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (led_processed_count == RGB_MATRIX_LED_PROCESS_LIMIT){
                return;
            }
            uint8_t led_index = g_led_config.matrix_co[row][col];
            uint16_t keycode = keymap_key_to_keycode(0, (keypos_t){col,row});
            if (led_index >= led_min && led_index <= led_max && led_index != NO_LED) {
                // Light base layer arrow keys orange if Scroll Lock is on, otherwise light them magenta:
                led_processed_count++;
                if (keycode >= KC_RIGHT && keycode <= KC_UP) {
                    if (host_keyboard_led_state().scroll_lock) {
                        rgb_matrix_set_color(led_index, RGB_ORANGE);
                    } else {
                        rgb_matrix_set_color(led_index, RGB_MAGENTA);
                    }
                }
                // Light alpha keys (A-Z only) red if Caps Lock is on:
                if (host_keyboard_led_state().caps_lock && keycode >= KC_A && keycode <= KC_Z) {
                    rgb_matrix_set_color(led_index, RGB_RED);
                }
                // Whenever a layer above base is active, recolour only the keys that are different on that layer:
                if (get_highest_layer(layer_state) > 0) {
                    uint8_t layer = get_highest_layer(layer_state);
                    uint16_t momentary_keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (momentary_keycode > KC_TRNS) {
                        switch(layer) {
                            case 2:
                                // The uppermost layer is blue:
                                rgb_matrix_set_color(led_index, RGB_BLUE);
                                break;
                            case 1:
                                // The middle layer is green, except that the numpad section turns
                                // orange when Num Lock is on:
                                if (host_keyboard_led_state().num_lock &&
                                (momentary_keycode == KC_KP_EQUAL ||
                                (momentary_keycode >= KC_NUM_LOCK && momentary_keycode <= KC_KP_DOT)
                                )) {
                                    rgb_matrix_set_color(led_index, RGB_ORANGE);
                                } else {
                                    rgb_matrix_set_color(led_index, RGB_GREEN);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
    return false;
}
