/*
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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define FORCE_NKRO //No boot-magic, so we'll force it on here.
#define QMK_KEYS_PER_SCAN 4 //if we press four keys simultaneously, lets process them simultaneously...
#ifdef AUDIO_ENABLE
#define C6_AUDIO
#define STARTUP_SONG SONG(STARTUP_SOUND)
#define NO_MUSIC_MODE
#endif

#endif
