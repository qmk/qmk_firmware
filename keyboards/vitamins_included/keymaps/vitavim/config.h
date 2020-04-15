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

/* Use I2C or Serial. Default is Serial */
// #define USE_I2C

/* Select hand configuration */
// Defaults:
// Rev1: EE_HANDS
// Rev2: SPLIT_HAND_PIN B4

// You can override the defaults (rev1 doesn't support SPLIT_HAND_PIN)
//#define EE_HANDS
//#define MASTER_LEFT
//#define MASTER_RIGHT

#define RGBLIGHT_SPLIT

#ifdef AUDIO_ENABLE
  #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                SONG(DVORAK_SOUND), \
                                SONG(COLEMAK_SOUND) \
                              }
#endif
