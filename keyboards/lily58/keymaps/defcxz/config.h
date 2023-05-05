/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2 
#define SPLIT_WPM_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE     // para que los modificadores funcionen en ambos lados

#define TAPPING_FORCE_HOLD    // para que no se repita la tecla al mantenerla
#define TAPPING_TERM 180      // cantidad en ms para considerar tap dance
#define TAPPING_TERM_PER_KEY  // para que cada tecla tenga su propio tapping term

#define OLED_BRIGHTNESS 255
#define OLED_TIMEOUT 0
#define RGBLIGHT_ANIMATIONS
