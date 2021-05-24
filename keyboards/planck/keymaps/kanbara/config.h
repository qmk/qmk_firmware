/* Copyright 2021 Jay Morrow
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
    #ifdef TEMPO_DEFAULT
        #undef TEMPO_DEFAULT
        #define TEMPO_DEFAULT 80
    #endif

    #define STARTUP_SONG SONG(MAJOR_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND), \
                                  SONG(WORKMAN_SOUND) \
                                }
#endif
