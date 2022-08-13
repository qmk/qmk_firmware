/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#define TRANS_LAYER_NO {{trans_layer_no}}

#define TRANS_KEYCODES_ENUM {{trans_keycodes_enum}}

#define TRANS_CUSTOM_KEYCODES {{trans_custom_keycodes}}

#define TRANS_LAYER_STRINGS {{trans_layer_string}}

#define TRANS_KEYMAP_STRINGS {{trans_keymap_string}}

#define TRANS_INDICATORS {{trans_indicators}}

#define TRANS_KEYMAP {{trans_keymap}}

#define TOTP_LAYER {{totp_layer}}

#if (__has_include("keys.h"))
    #include "keys.h"
#else
    #define DISABLE_SECRETS
#endif
