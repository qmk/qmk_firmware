/*
Copyright 2020 LFKeyboards
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


// RevA
// #define DIODE_DIRECTION COL2ROW
// #define MATRIX_ROW_PINS {B7, F7, F6, F5, F4}
// #define MATRIX_COL_PINS {F0, F1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C7, B3, B2, B1, B0}

// RevB
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS {D6, D7, E0, C3, C4}
#define MATRIX_COL_PINS {F2, C5, E5, E4, B7, B6, B5, B4, B3, B2, B1, B0, E1, C0, C1, C2}

//RevB only:

#define AUDIO_VOICES
#define AUDIO_PIN C6

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
