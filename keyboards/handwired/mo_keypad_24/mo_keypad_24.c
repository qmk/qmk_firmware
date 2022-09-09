/* Copyright 2021 mo
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

#include "mo_keypad_24.h"

#define MO_BUTTON_MAPS_MAX 1
typedef struct _mo_pad_t {
    int            current;
    const uint16_t codes[MO_BUTTON_MAPS_MAX][2];
} mo_pad_t;

mo_pad_t button_layers[2] = {
    {
        0,
        {
            {KC_MS_WH_DOWN, KC_MS_WH_UP},
        },
    },
    {
        0,
        {
            {KC_MS_WH_RIGHT, KC_MS_WH_LEFT},
        },
    },
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    if (0 <= index && index <= 1) {
        mo_pad_t *ptr        = &(button_layers[index]);
        uint8_t   turn_index = (clockwise ? 0 : 1);
        tap_code(ptr->codes[ptr->current][turn_index]);
    }

    return false;
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }

    if (!active) {
        return true;
    }

    switch (index) {
        case 0: // left encoder
            tap_code(KC_CAPSLOCK);
            break;
        case 1: {
            tap_code(KC_NUMLOCK);
            break;
        }
    }

    return true;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (res) {
        writePin(B0, !led_state.num_lock);
        writePin(D5, !led_state.caps_lock);
    }

    return res;
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->interrupted) {
            return TD_DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            return TD_TRIPLE_TAP;
        } else {
            return TD_TRIPLE_HOLD;
        }
    } else if (state->count == 4) {
        return TD_QUAD_TAP;
    } else {
        return TD_UNKNOWN;
    }
}
