/* Copyright 2022 Even A. Nilsen (@eanilsen)
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

// Taken from here: https://github.com/callum-oakley/qmk_firmware/tree/d63988caaf86217cfddf903c2c32dc042a8ef4da/users/callum

#include "swapper.h"

#include QMK_KEYBOARD_H
#include "customkeys.h"

bool is_swapper_ignored_key(uint16_t keycode, uint16_t tabish)
{
  if (tabish == KC_GRV) {
    return keycode == KC_LSFT;
  }

  switch (keycode) {
  case KC_LSFT:
  case KC_UP:
  case KC_LEFT:
  case KC_DOWN:
  case KC_RGHT:
    return true;
  default:
    return false;
  }
}

void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record)
{
  if (keycode == trigger) {
    if (record->event.pressed) {
      if (!*active) {
	*active = true;
	register_code16(cmdish);
      }
      register_code16(tabish);
    } else {
      unregister_code16(tabish);
    }
  } else if (*active && !is_swapper_ignored_key(keycode, tabish)) {
    unregister_code16(cmdish);
    *active = false;
  }
}
