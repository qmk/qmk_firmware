/*
  Copyright 2018 Ewan Taylor <ewan.taylor@gmail.com> @bit-shifter

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

#define USERSPACE

#include "quantum.h"

// modifier masks used for determining modifier actuation within macros
#define MODS_SHIFT_MASK   (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_META_MASK    (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))
#define MODS_CTRL_MASK    (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))
#define MODS_ALT_MASK     (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_HYPR_MASK     MOD_BIT(KC_HYPR)
#define MODS_SUPER_MASK    MOD_BIT(KC_SUPER)

// Clear mods, perform action, restore mods
#define CLEAN_MODS(action) {       \
        uint8_t mods = get_mods(); \
        clear_mods();              \
        action;                    \
        set_mods(mods);            \
    }
