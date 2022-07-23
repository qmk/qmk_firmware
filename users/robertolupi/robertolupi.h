/*
Copyright 2022 Roberto Lupi <Roberto.Lupi@gmail.com> @robertolupi

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
#pragma once

#include QMK_KEYBOARD_H

enum rl_custom_keycodes {
    // clang-format off
    KC_MISSION_CONTROL = SAFE_RANGE + 100,
    KC_LAUNCHPAD,
    KC_PREVIOUS_APP, // C-S-Tab, holding down CMD temporarily
    KC_NEXT_APP,     // C-Tab, holding CMD temporarily
    // clang-format on
    KEYMAP_SAFE_RANGE
};

#define RL_MCTL KC_MISSION_CONTROL
#define RL_LPAD KC_LAUNCHPAD
#define RL_APPP KC_PREVIOUS_APP
#define RL_APPN KC_NEXT_APP

/* HOLDING_DOWN: Temporarily hold down a modifier.
 *
 * If called repeatedly, extends the time the mod is hold down.
 * If the mod is already down, does nothing.

Example:

void some_function() {
    HOLDING_DOWN(KC_LCMD, 1000);
    // do something
}

*/

struct PACKED temporary_mod_t {
    uint16_t       keycode;
    deferred_token token;
};

bool send_temporary_mod(struct temporary_mod_t* mod, uint32_t duration);

#define HOLDING_DOWN_(k, d, t)                                                             \
    do {                                                                                   \
        static struct temporary_mod_t t = {.keycode = k, .token = INVALID_DEFERRED_TOKEN}; \
        send_temporary_mod(&t, d);                                                         \
    } while (0)
#define HOLDING_DOWN(k, c) HOLDING_DOWN_(k, c, temporary_mod_##k)

/*
 * Utility functions for rotary encoders.
 */

void knob_switch_apps(bool clockwise, uint32_t duration);

void knob_volume(bool clockwise);

void knob_scroll(bool clockwise);
