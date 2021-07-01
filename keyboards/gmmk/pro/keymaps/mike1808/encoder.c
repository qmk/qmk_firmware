/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
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
#include "encoder.h"
#include "mike1808.h"
#include "print.h"
#include "utils.h"
#include "rgb_matrix_ledmaps.h"

typedef void (*encoder_callback)(void);

static uint8_t state = ENCODER_DEFAULT;

// clang-format off
const encoder_callback encoder_mapping[][2] = {
    [ENCODER_VOLUME] = {&volume_up, &volume_down},
#ifdef RGB_MATRIX_ENABLE
    [ENCODER_RGB_HUE] = {&rgb_matrix_increase_hue_noeeprom, &rgb_matrix_decrease_hue_noeeprom},
    [ENCODER_RGB_SAT] = {&rgb_matrix_increase_sat_noeeprom, &rgb_matrix_decrease_sat_noeeprom},
    [ENCODER_RGB_VAL] = {&rgb_matrix_increase_val_noeeprom, &rgb_matrix_decrease_val_noeeprom},
    [ENCODER_RGB_EFFECT] = {&rgb_matrix_step_noeeprom, &rgb_matrix_step_reverse_noeeprom},
    [ENCODER_RGB_EFFECT_SPEED] = {&rgb_matrix_increase_speed_noeeprom, &rgb_matrix_decrease_speed_noeeprom},
#endif // RGB_MATRIX_ENABLE
};

// clang-format on

void volume_up() {
    tap_code(KC_VOLU);
}

void volume_down() {
    tap_code(KC_VOLD);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    dprintf("current encoder state is: %d\n", state);

#ifdef RGB_MATRIX_LEDMAPS_ENABLED
// disable layers so we can adjust RGB effects
rgb_matrix_layers_disable();
#endif // RGB_MATRIX_LEDMAPS_ENABLED

    if (clockwise) {
        (*encoder_mapping[state][0])();
    } else {
        (*encoder_mapping[state][1])();
    }

#ifdef RGB_MATRIX_LEDMAPS_ENABLED
// disable layers so we can adjust RGB effects
rgb_matrix_layers_enable();
#endif // RGB_MATRIX_LEDMAPS_ENABLED

    return true;
}

bool process_record_encoder(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_MATRIX_ENABLE
    switch (keycode) {
        case KC_RGB_ENC_HUE ... KC_RGB_ENC_EFFECT:
            if (record->event.pressed) {
#ifdef RGB_MATRIX_LEDMAPS_ENABLED
                // disable layers so we can adjust RGB effects
                rgb_matrix_layers_disable();
#endif // RGB_MATRIX_LEDMAPS_ENABLED

                switch (keycode) {
                    case KC_RGB_ENC_HUE:
                        state = ENCODER_RGB_HUE;
                        break;
                    case KC_RGB_ENC_SAT:
                        state = ENCODER_RGB_SAT;
                        break;
                    case KC_RGB_ENC_VAL:
                        state = ENCODER_RGB_VAL;
                        break;
                    case KC_RGB_ENC_EFFECT_SPEED:
                        state = ENCODER_RGB_EFFECT_SPEED;
                        break;
                    case KC_RGB_ENC_EFFECT:
                        state = ENCODER_RGB_EFFECT;
                        break;
                }
            } else {
#ifdef RGB_MATRIX_LEDMAPS_ENABLED
// disable layers so we can adjust RGB effects
                rgb_matrix_layers_enable();
#endif // RGB_MATRIX_LEDMAPS_ENABLED
                state = ENCODER_DEFAULT;
                store_rgb_state_to_eeprom();
            }

            return false;
    }
#endif // RGB_MATRIX_ENABLE

    return true;
}
