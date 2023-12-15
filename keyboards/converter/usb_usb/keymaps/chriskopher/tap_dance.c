/* Copyright 2020 Christopher Ko <chriskopher@gmail.com>
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

#include "shared_enum.h"

#include "quantum.h"

enum tap_dance_state {
    SINGLE_HOLD = 1,
    SINGLE_TAP,
    DOUBLE_TAP,
    TRIPLE_TAP,
};

// Record current state of a tap dance
static int espc_l_tap_state   = 0;
static int espc_r_tap_state   = 0;
static int scln_cln_tap_state = 0;

// Watch the state of the tap dance
int cur_dance(tap_dance_state_t *state) {
    if (state->pressed) {
        return SINGLE_HOLD;
    }
    if (state->count == 1) {
        return SINGLE_TAP;
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    }
    if (state->count == 3) {
        return TRIPLE_TAP;
    }

    return -1;
}

// Extended Space Cadet Shift - Left ==================================
void espc_l_finished(tap_dance_state_t *state, void *user_data) {
    espc_l_tap_state = cur_dance(state);
    switch (espc_l_tap_state) {
        case SINGLE_TAP:  // (
            register_code16(LSFT(KC_9));
            break;
        case DOUBLE_TAP:  // {
            unregister_code16(LSFT(KC_9));
            register_code16(LSFT(KC_LBRC));
            break;
        case TRIPLE_TAP:  // [
            unregister_code16(LSFT(KC_LBRC));
            register_code16(KC_LBRC);
            break;
        case SINGLE_HOLD:  // LShift
            register_code16(KC_LSFT);
            break;
    }
}

void espc_l_reset(tap_dance_state_t *state, void *user_data) {
    switch (espc_l_tap_state) {
        case SINGLE_TAP:  // (
            unregister_code16(LSFT(KC_9));
            break;
        case DOUBLE_TAP:  // {
            unregister_code16(LSFT(KC_LBRC));
            break;
        case TRIPLE_TAP:  // [
            unregister_code16(KC_LBRC);
            break;
        case SINGLE_HOLD:  // LShift
            unregister_code16(KC_LSFT);
            break;
    }
    espc_l_tap_state = 0;
}
// ====================================================================//

// Extended Space Cadet Shift - Right ==================================
void espc_r_finished(tap_dance_state_t *state, void *user_data) {
    espc_r_tap_state = cur_dance(state);
    switch (espc_r_tap_state) {
        case SINGLE_TAP:  // )
            register_code16(LSFT(KC_0));
            break;
        case DOUBLE_TAP:  // }
            unregister_code16(LSFT(KC_0));
            register_code16(LSFT(KC_RBRC));
            break;
        case TRIPLE_TAP:  // ]
            unregister_code16(LSFT(KC_RBRC));
            register_code16(KC_RBRC);
            break;
        case SINGLE_HOLD:  // RShift
            register_code16(KC_RSFT);
            break;
    }
}

void espc_r_reset(tap_dance_state_t *state, void *user_data) {
    switch (espc_r_tap_state) {
        case SINGLE_TAP:  // )
            unregister_code16(LSFT(KC_0));
            break;
        case DOUBLE_TAP:  // }
            unregister_code16(LSFT(KC_RBRC));
            break;
        case TRIPLE_TAP:  // ]
            unregister_code16(KC_RBRC);
            break;
        case SINGLE_HOLD:  // RShift
            unregister_code16(KC_RSFT);
            break;
    }
    espc_r_tap_state = 0;
}
// ====================================================================//

// Semicolon - Colon ==================================================
void scln_cln_finished(tap_dance_state_t *state, void *user_data) {
    scln_cln_tap_state = cur_dance(state);
    switch (scln_cln_tap_state) {
        case SINGLE_TAP:  // ;
            register_code16(KC_SCLN);
            break;
        default:  // :
            register_code16(LSFT(KC_SCLN));
            break;
    }
}

void scln_cln_reset(tap_dance_state_t *state, void *user_data) {
    switch (scln_cln_tap_state) {
        case SINGLE_TAP:  // ;
            unregister_code16(KC_SCLN);
            break;
        default:  // :
            unregister_code16(LSFT(KC_SCLN));
            break;
    }
}
// ====================================================================//

// Associate tap dance with defined functionality
tap_dance_action_t tap_dance_actions[] = {
    // Extended space cadet shift left: Hold - Shift, One - (, Two - {, Three - [
    [ESPC_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, espc_l_finished, espc_l_reset),
    // Extended space cadet shift right: Hold - Shift, One - ), Two - }, Three - ]
    [ESPC_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, espc_r_finished, espc_r_reset),
    // Semicolon - Colon: One - ;, Two - :
    [SCLN_CLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_cln_finished, scln_cln_reset),
};
