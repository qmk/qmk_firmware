/* Copyright 2020 Terence Rudkin 
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

#define MAX_LMT 8

#define USE_ZSA

#define RGB_DI_PIN A1
#define RGBLED_NUM 9
#define RGBLIGHT_LIMIT_VAL 255


#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#undef TAPPING_TERM
#define TAPPING_TERM 390

#define ONESHOT_TAP_TOGGLE 2


#define FIRMWARE_VERSION u8"YnNGZ/oLM3Q"
#define RGB_MATRIX_STARTUP_SPD 60



#ifndef PLANCK_EZ_LED_LOWER
#    define PLANCK_EZ_LED_LOWER 2
#endif
#ifndef PLANCK_EZ_LED_RAISE
#    define PLANCK_EZ_LED_RAISE 3
#endif
#ifndef PLANCK_EZ_LED_ADJUST
#    define PLANCK_EZ_LED_ADJUST 4
#endif
