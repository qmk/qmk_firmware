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
#    define STARTUP_SONG SONG(PREONIC_SOUND)
#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND) }
#endif

#define MUSIC_MASK (keycode != KC_NO)

#define PERMISSVE_HOLD

#define LEADER_PER_KEY_TIMING

#define LEADER_TIMEOUT 250

#define LEADER_NO_TIMEOUT

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

#define COMBO_NO_TIMER
