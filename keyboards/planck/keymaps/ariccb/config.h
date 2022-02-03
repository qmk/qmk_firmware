/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(PLANCK_SOUND)
// #define STARTUP_SONG SONG(NO_SOUND)

#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND) }
#endif
/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
#define MIDI_BASIC
/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

#define TAPPING_TERM 150
#define IGNORE_MOD_TAP_INTERRUPT
// #define IGNORE_MOD_TAP_INTERRUPT
// #define HOLD_ON_OTHER_KEY_PRESS

#define COMBO_TERM 20



#define MOUSEKEY_INTERVAL 16        //Time between cursor movements in milliseconds.
                                    //If the refresh rate of your display is 60Hz, you could set it to 16 (1/60). As this raises the cursor speed significantly, you may want to lower MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 8        //Maximum cursor speed at which acceleration stops
#define MOUSEKEY_TIME_TO_MAX 50     //Time until maximum scroll speed is reached
#define MOUSEKEY_DELAY 100          //Delay between pressing a movement key and cursor movement
#define MOUSEKEY_MOVE_DELTA 8       //Step size
