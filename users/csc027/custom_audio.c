/*
Copyright 2020 Constantine Chen @csc027

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

#include "csc027.h"
#include "custom_audio.h"

#if defined(AUDIO_ENABLE)

float tone_on[][2] = SONG(E__NOTE(_G6));
float tone_off[][2] = SONG(E__NOTE(_D5));

void on_usb_led_off(void) {
    PLAY_SONG(tone_off);
}

void on_usb_led_on(void) {
    PLAY_SONG(tone_on);
}

#endif
