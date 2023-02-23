/*
Copyright 2017 Zach White <skullydazed@clueboard.co>

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

/* audio support */
#define AUDIO_PIN_ALT B7
#define AUDIO_PIN C4
#define AUDIO_CLICKY

/*
 * Drawing mode
 */
#define DRAWING_ENABLE
//#define UNDO_KEY LGUI(KC_Z)  // What key to send for undo
//#define UNDO_KEY LCTL(KC_Z)
#define UNDO_KEY LGUI(KC_SLSH)

/*
 * Shake to undo configuration
 */
#define SHAKE_ENABLE
#define SHAKE_PIN_A E4
#define SHAKE_PIN_B E5
#define SHAKE_TIMEOUT 500     // How long after shaking stops before we register it
#define SHAKE_COUNT 8         // How many shakes it takes to activate
#define SHAKE_KEY UNDO_KEY    // What key to send after a shake
