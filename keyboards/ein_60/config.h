/*
Copyright 2021 klackygears

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

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 450000
#    define OLED_FONT_H  "keyboards/ein_60/glcdfont.c"
#endif

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN C6
#    define AUDIO_CLICKY
#    define AUDIO_DAC_SAMPLE_MAX 4095U
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT              38
#    define RGB_MATRIX_LED_FLUSH_LIMIT    16
#    define RGB_MATRIX_DEFAULT_VAL        150
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
