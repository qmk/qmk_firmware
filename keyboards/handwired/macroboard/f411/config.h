/*
Copyright 2021 Michał Szczepaniak

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

#define AUDIO_INIT_DELAY
#define AUDIO_PIN B10
#define AUDIO_PWM_DRIVER PWMD2
#define AUDIO_PWM_CHANNEL 3
#define AUDIO_PWM_PAL_MODE 1

#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.5f

#ifdef USER_SONG_LIST
#define STARTUP_SONG SONG(RICK_ROLL)
#else
#define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
