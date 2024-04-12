/* Copyright 2024 set_st
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
#include "keymap.c"

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    // Set cursor position
    oled_set_cursor(0, 0);
    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case BASE :
            oled_write_ln_P("1:Base", false);
            break;
        case FN :
            oled_write_ln_P("2:Functions", false);
            break;
        case MEDIA : 
            oled_write_ln_P("3:Media", false);
            break;
        case LIGHT :
            oled_write_ln_P("4:Lights controll", false);
            break;
    }
    

    oled_set_cursor(0, 1);
    oled_write(PSTR("Keys: "), false);

    os_variant_t os = detected_host_os();
    switch (os){
      case OS_MACOS:
        oled_write("MAC", false);
        break;
      case OS_LINUX:
        oled_write("LIN", false);
        break;
      case OS_WINDOWS:
        oled_write("WIN", false);
        break;
      default:
        break;
    }
    oled_write_ln("", false);

    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            uint16_t keycode = keymaps[get_highest_layer(layer_state)][i][j];
            if(keycode == KC_NO || keycode == KC_TRANSPARENT){
              oled_write("    ", false);
            }
            else{
              oled_write("(", false);
              if (KEYCODE2CONSUMER(keycode)) {
                    oled_write("M", false);
              }
              else if (IS_ANY(keycode))
              {
                oled_write("A", false);
              }
              else{
                  oled_write("D", false);
              }
              oled_write(") ", false);
            }
        }
        oled_write_ln("", false);
    }
  
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CYCLE_LAYERS:
      if (!record->event.pressed) { 
        return false;
      }

      uint8_t current_layer = get_highest_layer(layer_state);
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer >= LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
      return false;
    default:
      oled_clear();
      oled_set_cursor(0, 6);
      oled_write("Keycode: ", false);
      char keycode_str[6];
      itoa(keycode, keycode_str, 10);
      oled_write(keycode_str, false);
      oled_write_ln("", false);
      return true;
  }
}

#endif
