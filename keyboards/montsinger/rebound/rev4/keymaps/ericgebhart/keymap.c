/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include "layouts.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Qwerty based Base layers
  [_DVORAK]  = Rebound_base(___DVORAK___),
  [_BEAKL]   = Rebound_base(___BEAKL15___),
  [_COLEMAK] = Rebound_base(___COLEMAK_DH___),
  [_QWERTY]  = Rebound_base(___QWERTY___),

  // Bepo base layers
  [_BEAKL_BP]  = Rebound_base_bepo(___BEAKL15_FR___),
  [_DVORAK_BP] = Rebound_base_bepo(___DVORAK_FR___),
  [_BEPO]      = Rebound_base_bepo6(___BEPO6___),

  // Transient layers.
  [_SYMB]    = Rebound_transient(___SYMB_BEAKLA_3x12___),
  [_SYMB_BP] = Rebound_transient(___SYMB_BEAKLA_BP_3x12___),

  [_KEYPAD]    = Rebound_transient(___KP_C_3x12___),
  [_KEYPAD_BP] = Rebound_transient(___KP_C_BP_3x12___),

  [_TOPROWS]    = Rebound_transient(___TOPROWS_3x12___),
  [_TOPROWS_BP] = Rebound_transient(___TOPROWS_BP_3x12___),
  [_NAV]    = Rebound_transient(___NAV_3x12___),
  [_LAYERS] = Rebound_transient(___LAYERS_3x12___),
};


bool encoder_update_user(uint8_t index, bool clockwise) {
  switch(get_highest_layer(layer_state)){
  case _DVORAK:
    if (clockwise) {
      tap_code16(KC_VOLD);
    } else {
      tap_code16(KC_VOLU);
    }
    break;

  case _NAV:
    if (clockwise) {
      tap_code16(S(KC_TAB));
    } else {
      tap_code16(KC_TAB);
    }
    break;
  }
  return true;
}

#ifdef OLED_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR(""), false);

  switch (get_highest_layer(layer_state)) {
  case _BASE:
    oled_write_P(PSTR("Rebound\n"), false);
    oled_write_P(PSTR("Rev4\n"), false);
    break;
  case _NAV:
    oled_write_P(PSTR("Nav\n"), false);
    break;
  case _SYMB_BEAKL:
  case _SYMB:
    oled_write_P(PSTR("Symbols\n"), false);
    break;
  case _KEYPAD:
    oled_write_P(PSTR("Top Rows\n"), false);
    break;
  default:
    // Or use the write_ln shortcut over adding '\n' to the end of your string
    oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

}

#endif
