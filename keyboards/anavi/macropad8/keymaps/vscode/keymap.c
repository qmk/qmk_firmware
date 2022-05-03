 /* Copyright 2022 Efthimis Iosifidis <iosifidise@gmail.com>
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

#include QMK_KEYBOARD_H

enum layers {
    _BASIC,
    _FN,
};


#define KC_X0 LT(_FN, KC_ESC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _BASIC Layer
 * ,-------------------------------------.
 * | Toggle  | Toggle  |        |         |
 * | Block   | Line    |  Undo  |   Redo  |
 * | Comment | Comment |        |         |
 * |---------+---------+--------+---------+
 * |         |         |        |   TO    |
 * |  Cut    |   Copy  |  Paste |   _FN   |   
 * |         |         |        |         |
 *  `-------------------------------------' 
 */ 
  [_BASIC] = LAYOUT_ortho_2x4(
     RCS(KC_A), C(KC_SLASH), C(KC_Z),  C(KC_Y),
     C(KC_X),   C(KC_C),     C(KC_V),  TO(_FN)
  ),
/* _FN Layer
 * ,--------------------------------------------.
 * | RGB       |  RGB      |  RGB      | RGB     |
 * | Toggle    |  Mode     |  Mode     | Snake   |
 * |           |  Forward  | Reverse   | Mode    |         
 * |-----------+-----------+-----------+---------+
 * |           |  Cycle    |  Toggle   |  TO     |
 * | BackLight | BackLight | BackLight |  _BASIC |  
 * |  Toggle   |   Levels  |           |         |
 *  `--------------------------------------------' 
 */ 
  [_FN] = LAYOUT_ortho_2x4(
     RGB_TOG, RGB_MOD, RGB_M_R, RGB_M_SN,
     BL_TOGG, BL_STEP, BL_BRTG, TO(_BASIC)
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}


bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("ANAVI Macro Pad 8"), false);
  oled_write_P(PSTR("Active layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _BASIC:
      oled_write_ln_P(PSTR("Basic"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("FN"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("N/A"), false);
  }


  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("Num Lock: "), false);
  oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Caps Lock: "), false);
  oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Backlit: "), false);
  oled_write_ln_P(is_backlight_enabled() ? PSTR("On") : PSTR("Off"), false);
#ifdef RGBLIGHT_ENABLE
  static char rgbStatusLine1[26] = {0};
  snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
  oled_write_ln(rgbStatusLine1, false);
  static char rgbStatusLine2[26] = {0};
  snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
  oled_write_ln(rgbStatusLine2, false);
#endif
    return false;
}
#endif
