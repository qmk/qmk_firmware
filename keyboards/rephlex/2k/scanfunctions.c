// Copyright 2023 RephlexZero (@RephlexZero)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "2k.h"
#include "analog.h"


void calibrate(uint16_t rest_adc_value) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for (uint8_t j = 0; j < MATRIX_COLS; j++) {
            keys[i][j].offset = rest_adc_value - analogReadPin(matrix_pins[i][j]);
        }
    }
}

void update_extremum(key_t *key) {
    key->extremum = key->value;
}

void register_key(matrix_row_t *current_row, uint8_t current_col) {
    *current_row |= (1 << current_col);
}

void deregister_key(matrix_row_t *current_row, uint8_t current_col) {
    *current_row &= ~(1 << current_col);
}

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key) {
    if (*current_row & (1 << current_col)) {
        if (key->value < g_config.actuation_point - g_config.release_hysteresis) {
            deregister_key(current_row, current_col);
        }
    } else {
        if (key->value > g_config.actuation_point + g_config.press_hysteresis) {
            register_key(current_row, current_col);
        }
    }
}
// Extremum is the highest or lowest value of the key reached
// this functionality changes based on whether the key is pressed or not,
// assuming your sensor value decreases when the key is pressed,
// if the key is pressed, the extremum is the lowest value reached,
// if the key is not pressed, the extremum is the highest value reached.

void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key) {

    if (key->value > g_config.actuation_point) {
        // In DA zone?
        if (*current_row & (1 << current_col)) {
            // Key is pressed
            // Is key still moving down?
            if (key->value > key->extremum) {
                update_extremum(key);
            } else if (key->value < key->extremum - g_config.release_sensitivity) {
                // Has key moved up enough to be released?
                deregister_key(current_row, current_col);
                update_extremum(key);
            }
        } else {
            // Key is not pressed
            // Is the key still moving up?
            if (key->value < key->extremum) {
                update_extremum(key);
            } else if (key->value > key->extremum + g_config.press_sensitivity) {
                // Has key moved down enough to be pressed?
                register_key(current_row, current_col);
                update_extremum(key);
            }
        }
    } else {
        // Out of DA zone
        // Always deregister key
        deregister_key(current_row, current_col);
        if (key->value > key->extremum) {
            update_extremum(key);
        }
    }
}

void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key) {
    if (key->continuous_rapid_trigger) {
        if (*current_row & (1 << current_col)) {
            // Key is pressed
            // Is key still moving down?
            if (key->value > key->extremum) {
                update_extremum(key);

            } else if (key->value < key->extremum - g_config.release_sensitivity) {
                // Has key moved up enough to be released?
                deregister_key(current_row, current_col);
                update_extremum(key);
            }
        } else {
            // Key is not pressed
            // Is the key still moving up?
            if (key->value < key->extremum) {
                update_extremum(key);
            } else if (key->value > key->extremum + g_config.press_sensitivity) {
                // Has key moved down enough to be pressed?
                register_key(current_row, current_col);
                update_extremum(key);
            }
        }
        if (key->value == 0) {
            deregister_key(current_row, current_col);
            update_extremum(key);
            key->continuous_rapid_trigger = false;
        }
    } else if (key->value > g_config.actuation_point) {
        register_key(current_row, current_col);
        update_extremum(key);
        key->continuous_rapid_trigger = true;
    }
}