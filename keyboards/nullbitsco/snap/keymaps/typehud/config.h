/* Copyright 2022 Chris Tanaka <https://github.com/christanaka>
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

/* space savers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define TAPPING_FORCE_HOLD

// Old configuration
#define OLED_BRIGHTNESS 128
#define OLED_TIMEOUT 30000
#define OLED_UPDATE_INTERVAL 200

// Selectively undefine to save space
// VIA support won't fit otherwise
#ifdef RGBLIGHT_ENABLE
#undef RGBLIGHT_EFFECT_TWINKLE
#endif //RGB LIGHT_ENABLE

// Split configuration
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_WPM_ENABLE

// Typehud configuration
#define TYPEHUD_FILLGRAPH
#define TYPEHUD_MATRIX_COLS 16
// #define TYPEHUD_MASTER
// #define TYPEHUD_MATRIX_ROTATE_90
// #define TYPEHUD_MATRIX_ROTATE_180
// #define TYPEHUD_MATRIX_ROTATE_270
