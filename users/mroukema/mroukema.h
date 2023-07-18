/*
Copyright 2023 @mroukema

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
#define LAYER_ENTRY KC_TRANSPARENT

#include "keyrecords/layer_names.h"

// C Macro Magic to define custom keycode and accompanying switch statement for custom shift behaviour
#include "lib/custom_keycodes.h"

#ifdef TAP_DANCE_ENABLE
#include "keyrecords/tap_dances.h"
#endif

#ifdef COMBO_ENABLE
/*
 * https://docs.qmk.fm/#/feature_combo?id=dictionary-management
 */
#include "lib/keymap_combos.h"
#endif
