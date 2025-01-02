/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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
// #include <stdio.h>
#include <stdbool.h>
// #include <time.h>

bool onStartup = true;
// clock_t  start_t;
// clock_t now_t;

enum layer_names {
    _LAYER0,
    _LAYER1,
    _LAYER2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                        TO(1),
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3,
        KC_ENT, KC_0,   KC_BSPC
  ),
  [1] = LAYOUT(
                       TO(2),
        KC_ESC, KC_MS_U, KC_NO,
        KC_MS_L, KC_MS_D, KC_MS_R,
        KC_NO, KC_WH_U, KC_NO,
        KC_WH_L, KC_WH_D, KC_WH_R
  ),
  [2] = LAYOUT(
                       TO(0),
        KC_NO, KC_NO, KC_NO,
        RGB_MOD, RGB_RMOD, KC_NO,
        RGB_M_B, RGB_M_R, RGB_M_SW,
        RGB_TOG, RGB_M_P, KC_NO
  ),
};

#ifdef ENCODER_MAP_ENABLE
/*  This sets what the encoder turns do at each layer.
    There has to be a setting for each defined layer. Otherwise,
    there will be a compile error.

    Keep in mind the transparency encoding applies.
*/
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [1] = { ENCODER_CCW_CW(_______, _______) },
  [2] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif


#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // render_logo();
    // onStartup = false;
    if (onStartup) {
        // short t;
        render_logo();
        // while( t <= 500000) {
        //     ++t;
        // }
        onStartup = false;
        return false;
    }

    oled_write_P(PSTR("    MLS Macropad    \n"), true);

    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _LAYER0:
            oled_write_P(PSTR("Base (0)\n"), false);
            break;
        case _LAYER1:
            oled_write_P(PSTR("(1)\n"), false);
            break;
        case _LAYER2:
            oled_write_P(PSTR("(2) NO ACTION\n"), false);
            oled_write_P(PSTR("Tap encoder to re-engage.\n"), false);
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

    return false;
}
#endif




#endif
