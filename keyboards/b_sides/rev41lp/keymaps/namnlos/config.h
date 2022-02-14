/* Copyright 2022 Jan Lindblom (@janlindblom)
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

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 11
#undef BACKLIGHT_LIMIT_VAL
#define BACKLIGHT_LIMIT_VAL 255
#define BACKLIGHT_DEFAULT_LEVEL 3

#define COMBO_COUNT 3
#define IGNORE_MOD_TAP_INTERRUPT

#define UNICODE_SELECTED_MODES UC_WINC, UC_WIN, UC_MAC, UC_LNX

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define LAYER_STATE_8BIT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* key combination for command */
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
