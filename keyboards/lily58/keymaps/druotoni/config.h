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
GNU General Pllllllljublic License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MASTER_LEFT
#define OLED_DRIVER_ENABLE

// tapping toggle for my layers
#define TAPPING_TOGGLE 2

// choose IS_LEFT or IS_RIGHT for compilation and flash firmware
#define IS_LEFT 1
//#define IS_RIGHT 1

// logo glitch
#define WITH_GLITCH

// custom transport for displaying on both side
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A

// custom font
#ifdef OLED_FONT_H
#    undef OLED_FONT_H
#endif
#define OLED_FONT_H "navi_font.c"
#undef OLED_FONT_END
#define OLED_FONT_END 125

// more space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
#define DISABLE_LEADER

// ???
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// small layer state
#define LAYER_STATE_8BIT

// no debug or trace
#ifndef NO_DEBUG
#    define NO_DEBUG
#endif
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#    define NO_PRINT
#endif 


