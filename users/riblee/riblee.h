/* Copyright 2020 Janos Daniel Reibl <janos.daniel.reibl@protonmail.com> @riblee
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

#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _HUNGARIAN,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    HUNGARIAN,
    COLEMAK,
    DVORAK,
    WORKMAN,
    BACKLIT
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Tap Dance declarations
enum {
    TD_A,
    TD_E,
    TD_I,
    TD_O,
    TD_U,
};

void dance_key_a (qk_tap_dance_state_t *, void *);
void dance_key_e (qk_tap_dance_state_t *, void *);
void dance_key_i (qk_tap_dance_state_t *, void *);
void dance_key_o (qk_tap_dance_state_t *, void *);
void dance_key_u (qk_tap_dance_state_t *, void *);

layer_state_t layer_state_set_user(layer_state_t);
bool process_record_user(uint16_t keycode, keyrecord_t *record);