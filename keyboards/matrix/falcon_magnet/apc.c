/**
 * Copyright 2023 astro
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

#include "apc.h"

#define APC_KEY_STATE_DEFAULT   APC_KEY_OFF
#define APC_KEY_MIN_DEFAULT     APC_KEY_MAX
#define APC_KEY_MAX_DEFAULT     APC_KEY_MIN
#define APC_KEY_LAST_DEFAULT    0
#define APC_KEY_TRIGGER_DEFAULT 0
#define APC_KEY_DOWN_DEFAULT    1024
#define APC_KEY_UP_DEFAULT      0

enum apc_key_state
{
    APC_KEY_OFF,
    APC_KEY_PRESSING,
    APC_KEY_ON,
    APC_KEY_RELEASING,
};

struct apc_key
{
    uint32_t state;
    uint32_t min;
    uint32_t max;
    uint32_t last;
    uint32_t trigger;
    uint32_t down;
    uint32_t up;
    bool on;
};

static struct apc_key apc_matrix[MATRIX_ROWS][MATRIX_COLS];


//
// TODO:
// actually the relationship between the interval and the magnetic value
// was non-linear. Currently implementation was not accurate but can work.
//
static uint32_t apc_compute_interval(uint32_t row, uint32_t col, uint32_t index)
{
    struct apc_key *key = &apc_matrix[row][col];
    uint32_t interval = APC_INTERVAL_INVALID;

    if ((key->min == APC_KEY_MIN_DEFAULT) || (key->max < APC_KEY_MAX)) {
        interval = APC_INTERVAL_MIN + ((APC_INTERVAL_MAX-APC_INTERVAL_MIN)/APC_INTERVAL_COUNT)*(index);
    } else {
        interval = APC_INTERVAL_MIN + ((key->max-key->min)/APC_INTERVAL_COUNT)*(index);
    }

    return interval;
}

// currently two keymap was use for set the down&up actuation point. the up actuation also
// enabled the rapid trigger feature
static uint32_t apc_get_key_interval(uint32_t row, uint32_t col, uint32_t layer)
{
    uint16_t keycode = keycode_at_keymap_location(layer, row, col);
    uint16_t index = 0;
    if (keycode>=KC_F1 && keycode <= KC_F12) {
        index = keycode - KC_F1 + 1;
    } else if (keycode>=KC_F13 && keycode <= KC_F24) {
        index = keycode - KC_F13 + (KC_F12 - KC_F1) + 1;
    } else {
        if (layer == APC_KEYMAP_UP_LAYER) {
            return APC_INTERVAL_INVALID;
        }
        index = APC_INTERVAL_INDEX;
    }

    return apc_compute_interval(row, col, index);
}

static void apc_update_key_interval(uint32_t row, uint32_t col)
{
    apc_matrix[row][col].down = apc_get_key_interval(row, col, APC_KEYMAP_DOWN_LAYER);
    apc_matrix[row][col].up = apc_get_key_interval(row, col, APC_KEYMAP_UP_LAYER);
}

void apc_matrix_init(void)
{
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            apc_matrix[i][j].state = APC_KEY_STATE_DEFAULT;
            apc_matrix[i][j].min = APC_KEY_MIN_DEFAULT;
            apc_matrix[i][j].max = APC_KEY_MAX_DEFAULT;
            apc_matrix[i][j].last = APC_KEY_LAST_DEFAULT;
            apc_matrix[i][j].trigger = APC_KEY_TRIGGER_DEFAULT;
            apc_matrix[i][j].down = APC_KEY_DOWN_DEFAULT;
            apc_matrix[i][j].up = APC_KEY_UP_DEFAULT;
            apc_matrix[i][j].on = false;
        }
    }
}

static bool is_adc_value_valid(uint32_t value)
{
    if (value < APC_KEY_MIN|| value > APC_KEY_MAX) return false;
    return true;
}

static int apc_update_dir(struct apc_key* key, uint32_t value)
{
    if (value > (key->last + APC_THRESHOLD)) {
        key->last = value;
        return 1; // down
    } 

    if ((value + APC_THRESHOLD) < key->last) {
        key->last = value;
        return -1; // up
    }

    return 0;
}

bool apc_matrix_update(uint32_t row, uint32_t col, uint32_t value)
{
    struct apc_key* key = &apc_matrix[row][col];
    if (is_adc_value_valid(value)) {
        if (key->min > value) key->min = value;
        if (key->max < value) key->max = value;
        if (key->last == APC_KEY_LAST_DEFAULT) key->last = value;
        apc_update_key_interval(row, col);
        int dir = apc_update_dir(key, value);

        switch(key->state) {
        case APC_KEY_OFF:
            if (dir > 0) {
                // key down
                key->state = APC_KEY_PRESSING;
                key->trigger = value;
            }
            break;
        case APC_KEY_ON:
            if (dir < 0) {
                // key up
                key->state = APC_KEY_RELEASING;
                key->trigger = value;
            }
            break;
        case APC_KEY_PRESSING: 
            {
                if (dir < 0) {
                    // switch to releasing
                    key->state = APC_KEY_RELEASING;
                    key->trigger = value;
                } else {
                    if (!key->on) {
                        if (value > key->min + key->down) {
                            key->trigger = value;
                            key->state = APC_KEY_ON;
                            key->on = true;
                        }
                    }
                }
            }
            break;
        case APC_KEY_RELEASING:
            {
                if (dir > 0) {
                    // switch to pressing
                    key->state = APC_KEY_PRESSING;
                    key->trigger = value;
                } else {
                    if (key->on) {
                        if (key->up != APC_INTERVAL_INVALID) {
                            if (((value + key->up) < key->trigger)) {
                                // rapid trigger
                                key->state = APC_KEY_OFF;
                                key->on = false;
                                key->trigger = value;
                            }
                        } else {
                            if ((value + APC_THRESHOLD) < key->min + key->down) {
                                key->state = APC_KEY_OFF;
                                key->on = false;
                                key->trigger = value;
                            }
                        }
                    } else {
                        if (value < (key->min + APC_THRESHOLD)) {
                            key->state = APC_KEY_OFF;
                            key->trigger = value;
                        }
                    }
                }
            }
            break;
        default:
            // never here
            break;
        }
    }

    return key->on;
}
