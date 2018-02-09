/*
Copyright 2018 Mitchell van Manen <ma.van.manen@live.nl>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "../../../quantum/config_common.h"
#include "songs.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1337
#define DEVICE_VER      0x0001
#define MANUFACTURER    Mavanmanen
#define PRODUCT         Core
#define DESCRIPTION     Handwired Vortex Core

#define MATRIX_ROWS 4
#define MATRIX_COLS 13
#define MATRIX_ROW_PINS {F4, F5, F6, F7}
#define MATRIX_COL_PINS {B3, B2, B6, B1, B4, E6, D7, C6, D4, D0, D1, D2, D3}
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define B5_AUDIO // enables audio on pin B5
// #define STARTUP_SONG SONG(IMPERIAL_MARCH)

#define DEBOUNCING_DELAY 0
#define TAPPING_TOGGLE 2
#define TAPPING_TERM 300 // how long before a tap becomes a hold
// #define RETRO_TAPPING // tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
#define IS_COMMAND() ( keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define FORCE_NKRO

#define NO_MUSIC_MODE

#endif
