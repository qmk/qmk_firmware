/*
Copyright 2021 Takeshi Nishio

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

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN C6
  #define AUDIO_CLICKY
  #define MUSIC_MAP
#endif

/* RGBLIGHT */
  /*== Lighting Layers ==*/
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status

/* External EEPROM */
// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64
