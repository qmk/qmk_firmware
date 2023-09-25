/*
Copyright 2021 0xCB - Conor Burns

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

// clang-format off

  /* default setup after eeprom reset */
  #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_EFFECT_BREATHING + 2
  #define RGBLIGHT_DEFAULT_HUE 152
  #define RGBLIGHT_DEFAULT_SAT 232
  #define RGBLIGHT_DEFAULT_VAR 255
  #define RGBLIGHT_DEFAULT_SPD 2
// clang-format on

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
/* Oled Size */
#define OLED_DISPLAY_128X64
#define OLED_FONT_END 255
#define OLED_FONT_H "gfxfont.c"
