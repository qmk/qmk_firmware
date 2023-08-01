#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

#ifdef OLED_CUSTOM_ENABLE

#include "quantum.h"
//#include "oled_driver.h"

void oled_render_mod_lock_status(void);
void oled_driver_render_logo(void);
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
void oled_render_layer_map(void);
void oled_render_default_layer_state(void);
void oled_render_layer_state(void);

#define WRITE_STR_CASE(CASE, STRING)            \
  case CASE:                                    \
  oled_write_P(PSTR(STRING), false);            \
  break;                                        \

// kinda hacky for the moment.
// assume bepo is enabled.
#define WRITE_STR_LAYER(CASE, STRING)           \
  LCASE(CASE)                                   \
    oled_write_P(PSTR(STRING), false);          \
  break;

// make maps for the oled. code doc.
#define carte_de_map(ROW1, ROW2, ROW3)          \
  oled_write_ln_P(PSTR(ROW1), false);           \
  oled_write_ln_P(PSTR(ROW2), false);           \
  oled_write_ln_P(PSTR(ROW3), false);

// generate Case for all locales for this map.
#define SHOW_MAP(LAYER)                         \
  LCASE(LAYER)                                  \
    CAT(CARTE, LAYER)                           \
    break;

// a single case, for single locale layers.
#define SHOW_MAP_S(LAYER)                       \
  case LAYER:                                   \
  CAT(CARTE, LAYER)                             \
  break;

#endif
