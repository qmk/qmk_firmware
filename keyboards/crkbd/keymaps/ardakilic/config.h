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

#define SPLIT_WPM_ENABLE

// #define MASTER_RIGHT
// #define EE_HANDS


#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define RETRO_TAPPING



#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

// size optimisations
// #define NO_DEBUG
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* CONSOLE_ENABLE = no achieves this
// Size optimisations
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define NO_ACTION_ONESHOT
// Size optimisations END
*/
