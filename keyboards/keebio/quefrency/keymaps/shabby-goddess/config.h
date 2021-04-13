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

#define ENCODER_RESOLUTION 2


// set rbg to a slow breathe effect and a soft purple color. see https://docs.qmk.fm/#/feature_rgblight
#define RGBLIGHT_SLEEP 1
#define RGBLIGHT_SPLIT 1

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
#define RGBLIGHT_EFFECT_BREATHE_MAX 170

#define RGBLIGHT_DEFAULT_SPD 85

#define RGBLIGHT_DEFAULT_HUE 188
#define RGBLIGHT_DEFAULT_SAT 89
#define RGBLIGHT_DEFAULT_VAL 78

