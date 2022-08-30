/*
Copyright 2022 Dalius Dobravolskas <dalius.dobravolskas@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include "minunit.h"

// Stubs
#define QMK_KEYBOARD_H "tests/qmk.h"

// Keycodes necessary for testing
typedef enum {
    KC_NO,
    KC_A,
    KC_S,
    KC_D,
    KC_K,
    KC_L,
    KC_SCLN,
    KC_TAB,
    KC_LCTL,
    KC_LGUI,
    KC_LALT,
    KC_LSFT,
    KC_RCTL,
    KC_RGUI,
    KC_RALT,
    KC_RSFT,

    L_NAV,
    L_SYM,

    OS_NAV,
    OS_TMUX,

    SAFE_RANGE
} keycodes;

enum layers {
    _BASE,
    _NAV,
    _TMUX,
    _LAYER_COUNT,
};

#define FLOW_COUNT 7
const uint16_t flow_config[FLOW_COUNT][2] = {
    {L_NAV, KC_LALT},
    {L_NAV, KC_LGUI},
    {L_NAV, KC_LCTL},
    {L_SYM, KC_LCTL},
    {L_SYM, KC_LGUI},
    {L_SYM, KC_LALT},
    {OS_NAV, KC_LALT},
};

#define FLOW_LAYERS_COUNT 2
const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_NAV, _NAV},
    {OS_TMUX, _TMUX},
};

keycodes last_registered_code = KC_NO;
uint16_t registered_codes_count = 0;
keycodes last_unregistered_code = KC_NO;
uint16_t unregistered_codes_count = 0;

void register_code(uint16_t keycode) {
    last_registered_code = keycode;
    registered_codes_count++;
}

void unregister_code(uint16_t keycode) {
    last_unregistered_code = keycode;
    unregistered_codes_count++;
}

uint16_t timer = 0;

uint16_t timer_read(void) {
    return timer;
}

uint16_t timer_elapsed(uint16_t from) {
    return timer - from;
}

typedef struct {
    uint8_t col;
    uint8_t row;
} keypos_t;

keypos_t kp = {0, 0};

uint8_t active_layer = 0;
uint8_t key_layer = 0;

bool active_layers_array[_LAYER_COUNT] = { false, false, false };

void layer_off(uint8_t layer) {
    active_layers_array[layer] = false;

    active_layer = _LAYER_COUNT - 1;
    while (active_layers_array[active_layer] == false && active_layer > 0) {
        active_layer--;
    }

    key_layer = active_layer;
}

void layer_on(uint8_t layer) {
    active_layers_array[layer] = true;

    active_layer = _LAYER_COUNT - 1;
    while (active_layers_array[active_layer] == false && active_layer > 0) {
        active_layer--;
    }

    key_layer = active_layer;
}

void set_key_layer(uint8_t layer) {
    key_layer = layer;
}

uint8_t read_source_layers_cache(keypos_t keypos) {
    return key_layer;
}

#include "../flow.c"

void advance_timer_and_scan(uint16_t byUnits) {
    timer += byUnits;
    flow_matrix_scan();
}

void reset() {
    last_registered_code = KC_NO;
    registered_codes_count = 0;
    last_unregistered_code = KC_NO;
    unregistered_codes_count = 0;
    timer = 0;

    for (int i = 0; i < FLOW_COUNT; i++) {
        flow_state[i] = flow_up_unqueued;
        flow_pressed[i][0] = false;
        flow_pressed[i][1] = false;
        flow_timeout_timers_active[i] = false;
    }

    for (int i = 0; i < FLOW_LAYERS_COUNT; i++) {
        flow_layers_state[i] = flow_up_unqueued;
    }
}

MAIN

TEST("navD + altD = alt")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
    ASSERT_EQ(UINT, pass, false);
END_TEST

TEST("navD + altD + altU + navU + aD + aU + aD + aU = alt+a a")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + altD + navU + altU + aD + aU + aD + aU  = alt+a a")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + altD + navU + sD + sU + altU + sD + sU = alt+s s")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("altD + navD + altU + navU + sD + sU + sD + sU = s s")
    reset();

    bool pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(L_NAV, true, kp);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 0);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);
END_TEST

TEST("navD + altD + navU + sD + sU + sD + sU + altU + sD + sU = alt+s alt+s s")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + altD + tabD + tabU + navU + altU + sD + sU = alt+tab s")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + altD + ctrlD + ctrlU + altU + navU + sD + sU + sD + sU = alt+ctrl+s s")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(KC_LCTL, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_LCTL);

    pass = update_flow(KC_LCTL, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 2);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 2);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LCTL);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 2);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 2);
END_TEST

TEST("navD + altD + navU + navD + tabD + tabU + navU + altU + sD + sU = alt+tab s")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

// One shot works properly when subsequent keys are pressed almost at once
// but released one by one.
TEST("navD + altD + navU + altU + sD + kD + sU + kU = alt+s k")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_K, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);

    pass = update_flow(KC_K, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

// One shot should not happen if key is pressed for longer than 500ms
TEST("navD + altD + 501ms + altU + navU + aD + aU = a")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    advance_timer_and_scan(501);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("navD + altD + altU + navU + 400ms + aD + aU + navD + altD + altU + navU + 101ms + aD + aU = alt+a alt+a")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    advance_timer_and_scan(400);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    // Second action with 101ms iteration
    pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, registered_codes_count, 2);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);

    // NOTE: timer from previous click should not be called here
    advance_timer_and_scan(101);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 2);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST


TEST("navD + altD + altU + navU + 501ms + aD + aU + aD + aU = a a")
    reset();

    bool pass = update_flow(L_NAV, true, kp);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);

    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    pass = update_flow(L_NAV, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    advance_timer_and_scan(501);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);

    pass = update_flow(KC_A, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    pass = update_flow(KC_A, false, kp);
    ASSERT_EQ(UINT, pass, true);

    ASSERT_EQ(UINT, unregistered_codes_count, 1);
END_TEST

TEST("tmuxD + tmuxU + tabD + tabU = tmux tab")
    reset();

    bool pass = update_flow(OS_TMUX, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);
    pass = update_flow(OS_TMUX, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
END_TEST

TEST("tmuxD + tabD + tabU + tmuxU = tmux tab")
    reset();

    bool pass = update_flow(OS_TMUX, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    pass = update_flow(OS_TMUX, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);
END_TEST

TEST("tmuxD + tmuxU + 501ms + tabD + tabU = tab")
    reset();

    bool pass = update_flow(OS_TMUX, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);
    pass = update_flow(OS_TMUX, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    advance_timer_and_scan(501);
    ASSERT_EQ(UINT, active_layer, _BASE);

    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
END_TEST

TEST("tmuxD + 501ms + tmuxU + tabD + tabU = tab")
    reset();

    bool pass = update_flow(OS_TMUX, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    advance_timer_and_scan(501);

    pass = update_flow(OS_TMUX, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);

    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
END_TEST

TEST("navD + navU + tmuxD + tmuxU + tabD + tabU = tmux tab")
    reset();

    bool pass = update_flow(OS_NAV, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);
    pass = update_flow(OS_NAV, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);

    set_key_layer(_NAV);
    pass = update_flow(OS_TMUX, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);
    set_key_layer(_NAV);
    pass = update_flow(OS_TMUX, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    set_key_layer(_TMUX);
    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    set_key_layer(_TMUX);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
END_TEST

TEST("navD + tmuxD + tabD + navU + tmuxU + tabU = tmux tab")
    reset();

    set_key_layer(_BASE);
    bool pass = update_flow(OS_NAV, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);

    set_key_layer(_NAV);
    pass = update_flow(OS_TMUX, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    set_key_layer(_TMUX);
    pass = update_flow(KC_TAB, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    set_key_layer(_BASE);
    pass = update_flow(OS_NAV, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _TMUX);

    set_key_layer(_NAV);
    pass = update_flow(OS_TMUX, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);

    set_key_layer(_TMUX);
    pass = update_flow(KC_TAB, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
END_TEST

TEST("navD + altD + altU + navU + sD + sU = alt+s")
    reset();

    bool pass = update_flow(OS_NAV, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);

    set_key_layer(_NAV);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);

    set_key_layer(_NAV);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    set_key_layer(_BASE);
    pass = update_flow(OS_NAV, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);

    set_key_layer(_BASE);
    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    set_key_layer(_BASE);
    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST

TEST("navD + altD + navU + altU + sD + sU = alt+s")
    reset();

    bool pass = update_flow(OS_NAV, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);

    set_key_layer(_NAV);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);

    set_key_layer(_BASE);
    pass = update_flow(OS_NAV, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);

    set_key_layer(_NAV);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    set_key_layer(_BASE);
    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    set_key_layer(_BASE);
    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST

TEST("navD + navU + altD + altU + sD + sU = alt+s")
    reset();

    bool pass = update_flow(OS_NAV, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);
    ASSERT_EQ(UINT, flow_pressed[6][0], true);
    pass = update_flow(OS_NAV, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);
    ASSERT_EQ(UINT, flow_pressed[6][0], true);

    set_key_layer(_NAV);
    pass = update_flow(KC_LALT, true, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _NAV);
    set_key_layer(_NAV);
    pass = update_flow(KC_LALT, false, kp);
    ASSERT_EQ(UINT, pass, false);
    ASSERT_EQ(UINT, active_layer, _BASE);
    ASSERT_EQ(UINT, registered_codes_count, 1);
    ASSERT_EQ(UINT, last_registered_code, KC_LALT);
    ASSERT_EQ(UINT, unregistered_codes_count, 0);

    set_key_layer(_BASE);
    pass = update_flow(KC_S, true, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, registered_codes_count, 1);

    set_key_layer(_BASE);
    pass = update_flow(KC_S, false, kp);
    ASSERT_EQ(UINT, pass, true);
    ASSERT_EQ(UINT, active_layer, _BASE);
    ASSERT_EQ(UINT, unregistered_codes_count, 1);
    ASSERT_EQ(UINT, last_unregistered_code, KC_LALT);
END_TEST

END
