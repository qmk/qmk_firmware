 /* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
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

#include "wrappers.h"

enum layers {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum userspace_keycodes {
    KC_VRSN = SAFE_RANGE,
    KC_QWER,
    KC_COLE,
    KC_DVOR,
    NEW_SAFE_RANGE
};

#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)

#ifdef TAP_DANCE_ENABLE
#   include "tap_dance.h"
#endif

#ifdef RGBLIGHT_ENABLE
#   include "rgb_light.h"
#endif

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
layer_state_t layer_state_set_keymap (layer_state_t state);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
