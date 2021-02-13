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

#define EE_HANDS
#define USE_SERIAL_PD2

#define OLED_TIMEOUT 300000

#define NO_MUSIC_MODE

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 120

#ifdef COMBO_COUNT
#undef COMBO_COUNT
#endif
#define COMBO_COUNT 2
#define COMBO_TERM 20
