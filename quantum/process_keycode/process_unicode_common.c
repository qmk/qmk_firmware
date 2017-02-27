/* Copyright 2017 Jack Humbert
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

#include "process_unicode_common.h"

uint8_t mods;

void set_unicode_input_mode(uint8_t os_target)
{
  input_mode = os_target;
}

uint8_t get_unicode_input_mode(void) {
  return input_mode;
}

__attribute__((weak))
void unicode_input_start (void) {
  // save current mods
  mods = keyboard_report->mods;

  // unregister all mods to start from clean state
  if (mods & MOD_BIT(KC_LSFT)) unregister_code(KC_LSFT);
  if (mods & MOD_BIT(KC_RSFT)) unregister_code(KC_RSFT);
  if (mods & MOD_BIT(KC_LCTL)) unregister_code(KC_LCTL);
  if (mods & MOD_BIT(KC_RCTL)) unregister_code(KC_RCTL);
  if (mods & MOD_BIT(KC_LALT)) unregister_code(KC_LALT);
  if (mods & MOD_BIT(KC_RALT)) unregister_code(KC_RALT);
  if (mods & MOD_BIT(KC_LGUI)) unregister_code(KC_LGUI);
  if (mods & MOD_BIT(KC_RGUI)) unregister_code(KC_RGUI);

  switch(input_mode) {
  case UC_OSX:
    register_code(KC_LALT);
    break;
  case UC_LNX:
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_U);
    unregister_code(KC_U);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    break;
  case UC_WIN:
    register_code(KC_LALT);
    register_code(KC_PPLS);
    unregister_code(KC_PPLS);
    break;
  case UC_WINC:
    register_code(KC_RALT);
    unregister_code(KC_RALT);
    register_code(KC_U);
    unregister_code(KC_U);
  }
  wait_ms(UNICODE_TYPE_DELAY);
}

__attribute__((weak))
void unicode_input_finish (void) {
  switch(input_mode) {
    case UC_OSX:
    case UC_WIN:
      unregister_code(KC_LALT);
      break;
    case UC_LNX:
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      break;
  }

  // reregister previously set mods
  if (mods & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
  if (mods & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
  if (mods & MOD_BIT(KC_LCTL)) register_code(KC_LCTL);
  if (mods & MOD_BIT(KC_RCTL)) register_code(KC_RCTL);
  if (mods & MOD_BIT(KC_LALT)) register_code(KC_LALT);
  if (mods & MOD_BIT(KC_RALT)) register_code(KC_RALT);
  if (mods & MOD_BIT(KC_LGUI)) register_code(KC_LGUI);
  if (mods & MOD_BIT(KC_RGUI)) register_code(KC_RGUI);
}

void register_hex(uint16_t hex) {
  for(int i = 3; i >= 0; i--) {
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    register_code(hex_to_keycode(digit));
    unregister_code(hex_to_keycode(digit));
  }
}
