/* Copyright 2023 Brian Low
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
#include <stdio.h>
#include "rgb_matrix_user.h"

char rgb_str[10];

enum layer_names {
    _MAC_DEFAULT,
    _MAC_SYMBOLS,
    _MAC_UTIL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAC_DEFAULT] = 
        LAYOUT( 
    KC_GRV,     KC_1,   KC_2, KC_3, KC_4,           KC_5,                   KC_6,   KC_7,           KC_8, KC_9, KC_0,       KC_MINUS, 
    KC_TAB,     KC_Q,   KC_W, KC_E, KC_R,           KC_T,                   KC_Y,   KC_U,           KC_I, KC_O, KC_P,       KC_EQUAL, 
    KC_RCTL,    KC_A,   KC_S, KC_D, KC_F,   KC_G,                   KC_H,   KC_J,   KC_K, KC_L, KC_SCLN,    KC_QUOT, 
    LSFT_T(KC_LBRC),    KC_B,   KC_Z, KC_X, KC_C,   KC_V,  KC_MUTE,     KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_RBRC), 
                RGB_MOD, LSA_T(KC_TAB), LCA_T(KC_ESC), MO(1), LCMD_T(KC_SPC),     KC_SPC, KC_ENT, SCMD_T(KC_TAB), MO(2), MOD_MEH  
            ),
            
    [_MAC_SYMBOLS] = 
        LAYOUT( 
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_PAGE_DOWN, KC_PAGE_UP, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSLS, 
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            ),
                                                              
    [_MAC_UTIL] = 
        LAYOUT(
    RGB_TOG,    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, QK_BOOT,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    RGB_MOD,    RGB_HUI, RGB_SAI,   RGB_VAI, RGB_SPI, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR, 
    RGB_RMOD,   RGB_HUD, RGB_SAD,   RGB_VAD, RGB_SPD, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,        KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_DOWN, KC_PAGE_UP)},
    {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
};
#endif

// OLED
#ifdef OLED_ENABLE
 
// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270; 
}

// Draw to OLED
bool oled_task_user() {

       // WPM text
    oled_set_cursor(0, 0);
    sprintf(rgb_str, "%03d", get_current_wpm()); // %03d defines digits to display
    oled_write(rgb_str, false);

    // Set cursor position
    oled_set_cursor(0, 1);

    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case _MAC_DEFAULT :
            oled_write("Main   ", false);
            break;
        case _MAC_SYMBOLS : 
            oled_write("Symbols", false);
            break;
        case _MAC_UTIL :
            oled_write("Util", false);
            break;
    }


    // Set cursor position
    oled_set_cursor(0, 2);
      oled_write_P(PSTR("RGB: "), false);
        if (!(rgb_matrix_is_enabled())) {
            oled_write_P(PSTR("Off\n"), false);
        } else {
            switch (rgb_matrix_get_mode()) {
                // case MY_RGB_MATRIX_SOLID_COLOR:
                //     oled_write_P(PSTR("Solid Color\n"), false);
                //     break;
                // case MY_RGB_MATRIX_ALPHAS_MODS:
                //     oled_write_P(PSTR("Alphas Mods\n"), false);
                //     break;
                // case MY_RGB_MATRIX_GRADIENT_UP_DOWN:
                //     oled_write_P(PSTR("Gradient Up Down\n"), false);
                //     break;
                // case MY_RGB_MATRIX_GRADIENT_LEFT_RIGHT:
                //     oled_write_P(PSTR("Gradient Left Right\n"), false);
                //     break;
                // case MY_RGB_MATRIX_BREATHING:
                //     oled_write_P(PSTR("Breathing\n"), false);
                //     break;
                default:
                    sprintf(rgb_str, "m:%02d\n", rgb_matrix_get_mode()); // %03d defines digits to display
                    oled_write(rgb_str, false);
                    // write the current rgb speed using rgb_matrix_get_speed() to the oled display
                    sprintf(rgb_str, "s:%03d\n", rgb_matrix_get_speed()); 
                    oled_write(rgb_str, false);

            }
        }

    return false;
}

#endif
