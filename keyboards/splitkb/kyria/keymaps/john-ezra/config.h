/* Copyright 2021 John Ezra
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

#define OLED_FONT_H "keyboards/splitkb/kyria/keymaps/john-ezra/glcdfont.c"
#define OLED_FONT_END 255
#define OLED_TIMEOUT 30000
#define OLED_DISPLAY_128X64

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_HUE_STEP 5
  #define RGBLIGHT_SAT_STEP 5
  #define RGBLIGHT_VAL_STEP 5
  #define RGBLIGHT_LIMIT_VAL 150
#endif

#undef DEBOUNCE
#define DEBOUNCE 1

#define TAPPING_TERM 125

#define SPLIT_WPM_ENABLE

#define USB_POLLING_INTERVAL_MS 1

#define DEBUG_MATRIX_SCAN_RATE
