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
#include "ericgebhart.h"
#include "locales.h"

bool process_locales(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
  case KC_SET_BASE:
    // set the current default base to eeprom.
    if (record->event.pressed) {
      set_single_persistent_default_layer(get_highest_layer(default_layer_state));
    }
    break;

    // choose a different set of default layers based on locales.
  case KC_NEXT_LOCALE:
    // choose another locale and set the default base to the first layer.
    if (!record->event.pressed) {
      if (current_locale + 1 < LOCALES_END){
        current_locale++;
      }else{
        current_locale = 0;
      }
      default_layer_set(1UL << LOCALE_LAYER_RANGE[0]);
    }
    return false;
    break;

    // choose a different base layer based on locales.
    // simply iterates over the list and sets the default layer.
  case KC_NEXT_BASE_LAYER:
    if (!record->event.pressed) {
      uint8_t current = get_highest_layer(default_layer_state);
      if (current < LOCALE_LAYER_RANGE[1]){
        current++;
      }else{
        current = LOCALE_LAYER_RANGE[0];
      }
      default_layer_set(1UL << current);
    }
    return false;
    break;
  }
  return true;
}
