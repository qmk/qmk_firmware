/* Copyright 2022 Christoph Jabs (BifbofII)
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

// ====== LED Colors ======
#define QWERTY_HSV HSV_WHITE
#define COLEMAK_HSV HSV_CYAN
#define DVORAK_HSV HSV_YELLOW
#ifdef GAMING_ENABLE
#    define GAMING_HSV HSV_GREEN
#endif
#define FUNC_HSV HSV_ORANGE
#ifdef RAISE_LOWER
#    define RAISE_HSV HSV_ORANGE
#    define LOWER_HSV HSV_PURPLE
#else
#    define FUNC2_HSV HSV_PURPLE
#endif
#define UNICODE_HSV HSV_BLUE
#define ADJUST_HSV HSV_RED
#define CAPS_HSV HSV_RED

void          keyboard_post_init_rgb_light(void);
layer_state_t layer_state_set_rgb_light(layer_state_t state);
bool          led_update_rgb_light(led_t led_state);
