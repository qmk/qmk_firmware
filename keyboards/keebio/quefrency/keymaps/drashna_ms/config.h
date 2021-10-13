/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 Danny Nguyen <danny@keeb.io>

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

// #define USE_I2C
#define EE_HANDS


#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_SPLIT
    #undef  RGBLED_NUM
    #define RGBLED_NUM 17
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT { 9, 8 }
    #define RGBLIGHT_SLEEP
#endif

#ifdef AUDIO_ENABLE
    #define AUDIO_PIN B7
    #define AUDIO_CLICKY
#endif
