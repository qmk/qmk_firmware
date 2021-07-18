/* Copyright 2020 Brandon Schlack
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
#pragma once
#include "brandonschlack.h"
#ifdef TAP_DANCE_ENABLE
#   include "process_keycode/process_tap_dance.h"
#endif

enum tap_dance_states {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5,
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};

int cur_dance (qk_tap_dance_state_t *state);
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer);

/* Tap Dance: Trigger Layer
 *
 * Toggles Layer based on given trigger (Single Hold, Double Tap, Double Hold, etc).
 * Uses process_tap_dance_keycode() to allow keycode defines based on layer
 */
typedef struct {
    uint8_t  trigger;
    uint8_t  layer;
    uint8_t  state;
} qk_tap_dance_trigger_layer_t;

#define ACTION_TAP_DANCE_TRIGGER_LAYER(trigger, layer) { \
    .fn = { NULL, td_trigger_layer_finished, td_trigger_layer_reset }, \
    .user_data = (void *)&((qk_tap_dance_trigger_layer_t) { trigger, layer, 0 }), \
}

void td_trigger_layer_finished (qk_tap_dance_state_t *state, void *user_data);
void td_trigger_layer_reset (qk_tap_dance_state_t *state, void *user_data);
