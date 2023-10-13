/**
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jjerrell.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_WORKMAN] = LAYOUT_ergodox_mods(
        __________________WORKMN_L1__________________, __________________WORKMN_R1__________________,
        __________________WORKMN_L2__________________, __________________WORKMN_R2__________________,
        __________________WORKMN_L3__________________, __________________WORKMN_R3__________________,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                       KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    /* Lower - Nav/Select/Nums */
    [_LOWER] = LAYOUT_ergodox_mods(
        __________________LOWER_L1___________________, __________________LOWER_R1___________________,
        __________________LOWER_L2___________________, __________________LOWER_R2___________________,
        __________________LOWER_L3___________________, __________________LOWER_R3___________________,
          XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                         KC_0, KC_DOT, KC_COMM, KC_PLUS
    ),
    /* Raise - Symbols */
    [_RAISE] = LAYOUT_ergodox_common(
        __________________RAISE_L1___________________, __________________RAISE_R1___________________,
        __________________RAISE_L2___________________, __________________RAISE_R2___________________,
        __________________RAISE_L3___________________, __________________RAISE_R3___________________,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                       KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    /* Adjust (Lower + Raise) */
    [_ADJUST] = LAYOUT_ergodox_common(
         __________________ADJUST_L1__________________, __________________ADJUST_R1__________________,
         __________________ADJUST_L2__________________, __________________ADJUST_R2__________________,
         __________________ADJUST_L3__________________, __________________ADJUST_R3__________________,
         XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,                       KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_SPECIAL] = LAYOUT_ergodox_common(
        XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_R, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,                       KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX
    )
// clang-format on
};

#ifdef KEYBOARD_ergodox_ez
// Runs whenever there is a layer state change.
layer_state_t layer_state_set_keymap(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _LOWER:
            ergodox_right_led_3_on();
            break;
        case _RAISE:
            ergodox_right_led_1_on();
            break;
        case _ADJUST:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case _SPECIAL:
            ergodox_right_led_2_on();
            break;
        default:
            break;
    }

    ergodox_right_led_1_set(25);
    ergodox_right_led_2_set(25);
    ergodox_right_led_3_set(25);

    return state;
};

void matrix_scan_keymap(void) {
    uint8_t modifiers = get_mods();
    led_t   led_state = host_keyboard_led_state();
    uint8_t one_shot = get_oneshot_mods();
    uint8_t layer_is_workman = layer_state_is(_WORKMAN);

    if ((modifiers) && (layer_is_workman)) {
        if (modifiers & MOD_MASK_SHIFT || led_state.caps_lock || one_shot & MOD_MASK_SHIFT) {
            ergodox_right_led_1_on();
            ergodox_right_led_1_set( 25 );
        } else {
            ergodox_right_led_1_off();
        }
        if ((modifiers & MOD_MASK_CTRL || one_shot & MOD_MASK_CTRL) && (modifiers & MOD_MASK_GUI || one_shot & MOD_MASK_GUI)) {
            ergodox_right_led_2_on();
            ergodox_right_led_2_set( 50 );
        } else if ((modifiers & MOD_MASK_CTRL || one_shot & MOD_MASK_CTRL) || (modifiers & MOD_MASK_GUI || one_shot & MOD_MASK_GUI)) {
            ergodox_right_led_2_on();
            ergodox_right_led_2_set( 10 );
        } else {
            ergodox_right_led_2_off();
        }
        if (modifiers & MOD_MASK_ALT || one_shot & MOD_MASK_ALT) {
            ergodox_right_led_3_on();
            ergodox_right_led_3_set( 10 );
        } else {
            ergodox_right_led_3_off();
        }
    } else if (layer_is_workman) {
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
    }
};
#endif
