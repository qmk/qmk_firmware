/*
Copyright 2021 Jeremy Herve <jeremy@jeremy.hu>

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

/* Change the default tapping toggle value (normally 5) */
#define TAPPING_TOGGLE 2

#ifdef UNICODE_ENABLE
/* Set Unicode mode by default */
#    define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
#endif

/* Custom startup sound */
#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(ZELDA_PUZZLE)
#endif
