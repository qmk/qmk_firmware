/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
 * Copyright 2022 Ryan Anderson <ryan@michonline.com>
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

// OLED animation
#include "lib/layer_status/layer_status.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE = 0,
    _FN,
    _FN1,
    _FN2,
};

// enum layer_keycodes { };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
           ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
           │C-D│C-E│M-D│M-E│   │Ply│ │TO1│
           ├───┼───┼───┼───┤   └───┘ └───┘
           │ 5 │ 6 │ 7 │ 8 │
           ├───┼───┼───┼───┤
           │ 9 │ 0 │ ↑ │Ent│      ┌───┐
           ├───┼───┼───┼───┤      │Mut│
           │Fn2│ ← │ ↓ │ → │      └───┘
           └───┴───┴───┴───┘
           ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
           │ ! │ @ │ # │ $ │   │   │ │   │
           ├───┼───┼───┼───┤   └───┘ └───┘
           │ % │ ^ │ & │ * │
           ├───┼───┼───┼───┤
           │ ( │ ) │   │   │      ┌───┐
           ├───┼───┼───┼───┤      │   │
           │   │   │   │   │      └───┘
           └───┴───┴───┴───┘
    */
    /*  Row:    0         1        2        3         4        5        6      */
    [_BASE] = LAYOUT(C(KC_D), C(KC_E), LCMD(KC_D), LCMD(KC_E), KC_MPLY,
                     KC_5, KC_6, LCTL(LCMD(KC_H)), KC_8, TO(_FN),
                     KC_9, KC_0, KC_UP, KC_ENT, KC_MUTE,
                     MO(_FN2), KC_LEFT, KC_DOWN, KC_RIGHT),

    /*
           ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
           │   │   │   │   │   │   │ │   │
           ├───┼───┼───┼───┤   └───┘ └───┘
           │   │   │   │   │
           ├───┼───┼───┼───┤
           │   │   │   │   │      ┌───┐
           ├───┼───┼───┼───┤      │   │
           │   │   │   │   │      └───┘
           └───┴───┴───┴───┘
    */
    /*  Row:    0        1        2        3        4        5         6      */
    [_FN] = LAYOUT(_______, _______, _______, _______, _______,
                   _______, _______, _______, _______, TO(_FN1),
                   _______, _______, _______, _______, _______,
                   _______, _______, _______, _______),

    /*
           ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
           │   │   │   │   │   │   │ │   │
           ├───┼───┼───┼───┤   └───┘ └───┘
           │   │   │   │   │
           ├───┼───┼───┼───┤
           │   │   │   │   │      ┌───┐
           ├───┼───┼───┼───┤      │   │
           │   │   │   │   │      └───┘
           └───┴───┴───┴───┘
    */
    /*  Row:    0        1        2        3        4        5         6      */
    [_FN1] = LAYOUT(_______, _______, _______, _______, _______,
                    _______, _______, _______, _______, TO(_FN2),
                    _______, _______, _______, _______, _______,
                    _______, _______, _______, _______),

    /*
           ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
           │Spi│Spd│   │   │   │   │ │TO0│
           ├───┼───┼───┼───┤   └───┘ └───┘
           │Sai│Sad│   │   │
           ├───┼───┼───┼───┤
           │Tog│Mod│Hui│   │      ┌───┐
           ├───┼───┼───┼───┤      │   │
           │   │Vai│Hud│Vad│      └───┘
           └───┴───┴───┴───┘
    */
    /*  Row:    0        1        2        3        4        5          6      */
    [_FN2] = LAYOUT(RGB_SPI, RGB_SPD, _______, QK_BOOT, _______,
                    RGB_SAI, RGB_SAD, _______, _______, TO(_BASE),
                    RGB_TOG, RGB_MOD, RGB_HUI, _______, _______,
                    _______, RGB_VAI, RGB_HUD, RGB_VAD),
};
// clang-format on

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    render_layer_status();

    return true;
}
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN]   = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN2]  = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_BASE] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif
