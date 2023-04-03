/*
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

#define USE_I2C
#define SCL_CLOCK  800000UL

/* Select hand configuration */
#define MASTER_LEFT

//#define DEBUG_MATRIX_SCAN_RATE //Use this to determine scan-rate.
#define FORCE_NKRO

#ifdef AUDIO_ENABLE
  #define AUDIO_PIN C6
  #define STARTUP_SONG SONG(STARTUP_SOUND)
  #define NO_MUSIC_MODE
  #define TONE_QWERTY SONG(Q__NOTE(_E4));
  #define TONE_NUMPAD SONG(Q__NOTE(_D4));
#endif
