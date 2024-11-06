/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"
#include "analog_matrix.h"
#include "profile.h"
#include "action_socd.h"

enum {
    KEY_1_ACTIVE     = 0x01,
    KEY_2_ACTIVE     = 0x02,
    BOTH_KEYS_ACTIVE = 0x03,
};

extern matrix_row_t analog_raw_matrix[MATRIX_ROWS];
extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t changed_matrix[MATRIX_ROWS];

void socd_action(void) {
    matrix_row_t socd_mask[MATRIX_ROWS] = {0};
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        socd_mask[row] = ~socd_mask[row];
    }

    socd_config_t *socd = profile_get_current()->socd;
    static uint8_t state[SOCD_COUNT];
    bool           keep_last_state;
    uint8_t        row1, row2, col1, col2;
    for (uint8_t i = 0; i < SOCD_COUNT; i++) {
        if (socd[i].type) {
            keep_last_state = false;
            row1 = socd[i].key_1_row;
            col1 = socd[i].key_1_col;
            row2 = socd[i].key_2_row;
            col2 = socd[i].key_2_col;

            if ((analog_raw_matrix[row1] & (0x01 << col1)) && (analog_raw_matrix[row2] & (0x01 << col2))) {
                switch (socd[i].type) {
                    case SOCD_PRI_DEEPER_TRAVEL:
                    case SOCD_PRI_DEEPER_TRAVEL_SINGLE:
                        if (analog_matrix_get_travel(row1, col1) > 230 && analog_matrix_get_travel(row2, col2) > 230) {
                            if (socd[i].type == SOCD_PRI_DEEPER_TRAVEL_SINGLE) {
                                keep_last_state = true;
                            }
                        } else if (state[i] == KEY_2_ACTIVE && analog_matrix_get_travel(row1, col1) > analog_matrix_get_travel(row2, col2)) {
                            socd_mask[row2] &= ~(0x01 << col2);
                        } else if (state[i] == KEY_1_ACTIVE && analog_matrix_get_travel(row1, col1)  < analog_matrix_get_travel(row2, col2)) {
                            socd_mask[row1] &= ~(0x01 << col1);
                        } else
                            keep_last_state = true;
                        break;

                    case SOCD_PRI_LAST_KEYSTROKE:
                        if ((raw_matrix[row1] & (0x01 << col1)) && (analog_raw_matrix[row2] & (0x01 << col2)) && (changed_matrix[row2] & (0x01 << col2))) {
                            socd_mask[row1] &= ~(0x01 << col1);
                            state[i] = KEY_2_ACTIVE;

                        } else if ((raw_matrix[row2] & (0x01 << col2)) && (analog_raw_matrix[row1] & (0x01 << col1)) && (changed_matrix[row1] & (0x01 << col1))) {
                            socd_mask[row2] &= ~(0x01 << col2);
                            state[i] = KEY_1_ACTIVE;

                        } else
                            keep_last_state = true;
                        break;

                    case SOCD_PRI_KEY_1:
                        socd_mask[row2] &= ~(0x01 << col2);
                        state[i] = KEY_1_ACTIVE;
                        break;

                    case SOCD_PRI_KEY_2:
                        socd_mask[row1] &= ~(0x01 << col1);
                        state[i] = KEY_2_ACTIVE;
                        break;

                    case SOCD_PRI_NEUTRAL:
                        socd_mask[row1] &= ~(0x01 << col1);
                        socd_mask[row2] &= ~(0x01 << col2);
                        state[i] = 0;
                        break;

                    default:
                        break;
                }
            } else if (analog_raw_matrix[row1] & (0x01 << col1)) {
                state[i] = KEY_1_ACTIVE;
            } else if (analog_raw_matrix[row2] & (0x01 << col2)) {
                state[i] = KEY_2_ACTIVE;
            }

            if (keep_last_state) {
                if (state[i] == KEY_1_ACTIVE)
                    socd_mask[row2] &= ~(0x01 << col2);
                else if (state[i] == KEY_2_ACTIVE)
                    socd_mask[row1] &= ~(0x01 << col1);
            }
        }
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        raw_matrix[row] = analog_raw_matrix[row] & socd_mask[row];
    }
}
