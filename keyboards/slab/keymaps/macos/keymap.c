/* Copyright 2022 tjcampie
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
#include "analog.h"

int16_t max_pot_val = 1600;
int16_t max_ticks   = 28;   // MacOS - allows for full control from Mute to 100% volume on MacOS systems when used as Vol Up/Down slider.
int16_t pot_oldVal = 0;
int16_t ticks      = 0;
int16_t pot_val    = 0;
bool    moving     = false;
#define POT_TOLERANCE 20
#define SLIDER_PIN F0
#include "print.h"

void matrix_init_user(void) {
    analogReference(ADC_REF_POWER);
    for (int i = 0; i < max_ticks; ++i) {
        tap_code(KC_VOLD);
    }
    ticks = 0;
}

void matrix_scan_user(void) {
    // slider();

    pot_val = (analogReadPin(SLIDER_PIN));
    // If there is a big enough change, then we need to do something
    if (abs(pot_val - pot_oldVal) > POT_TOLERANCE) {
        // uprintf("Pot Val: %d",pot_val);
        int num_ticks   = ((float)pot_val / max_pot_val) * max_ticks;
        int delta_ticks = num_ticks - ticks;
        if (delta_ticks < 0) {
            for (int i = 0; i < abs(delta_ticks); ++i) {
                tap_code(KC_VOLD);
            }
        } else {
            for (int i = 0; i < abs(delta_ticks); ++i) {
                tap_code(KC_VOLU);
            }
        }
        ticks      = num_ticks;
        pot_oldVal = pot_val;
    }
}

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8)};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code_delay(KC_UP, 10);
    } else {
        tap_code_delay(KC_DOWN, 10);
    }
    return true;
};
