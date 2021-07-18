/* Copyright 2021 Joshua T.
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
#include "rj_keycodes.h"
#include "rj_layers.h"
#include "keycode_aliases.h"
#include "version.h"

#ifdef USER_CAPS_WORD_ENABLE
#    include "features/caps_word.h"
#endif

#ifdef USER_MOUSE_JIGGLE_ENABLE
#    include "features/mouse_jiggle.h"
#endif

#ifdef USER_NUM_WORD_ENABLE
#    include "features/num_word.h"
#endif

#ifdef USER_SECRETS_ENABLE
#    include "features/secrets.h"
#endif

#ifdef USER_SUPER_ALT_TAB_ENABLE
#    include "features/super_alt_tab.h"
#endif
