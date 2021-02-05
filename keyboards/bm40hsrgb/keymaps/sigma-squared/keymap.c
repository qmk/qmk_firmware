// qmk flash -kb bm40hsrgb -km sigma-squared

/* Copyright 2021 Vincenzo Mitchell Barroso
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

#include "sigma-squared.h"

//cmd tab

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LCTL);
        }
        cmd_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 500) {
      unregister_code(KC_LCTL);
      is_cmd_tab_active = false;
    }
  }
}

//layer led colors

void rgb_matrix_indicators_user(void) {

//game indicators

if(IS_LAYER_ON(GAME)) {
  rgb_matrix_set_color(11, 0, 4, 5);
}

if(IS_LAYER_ON(SECGAME)) {
  rgb_matrix_set_color(11, 5, 0, 0);
}

//layer indicators

if(IS_LAYER_ON(NAVR)) {
  rgb_matrix_set_color(40, 0, 4, 5);

  rgb_matrix_set_color(19, 0, 4, 5);
  rgb_matrix_set_color(20, 0, 4, 5);
  rgb_matrix_set_color(21, 0, 4, 5);
  rgb_matrix_set_color(22, 0, 4, 5);
}

if(IS_LAYER_ON(MEDR)) {
  rgb_matrix_set_color(39, 5, 1, 2);

  rgb_matrix_set_color(19, 5, 1, 2);

  rgb_matrix_set_color(22, 5, 1, 2);

  rgb_matrix_set_color(42, 5, 1, 2);
}

if(IS_LAYER_ON(FUNL)) {
  rgb_matrix_set_color(43, 5, 0, 0);

  rgb_matrix_set_color(1, 5, 0, 0);
  rgb_matrix_set_color(2, 5, 0, 0);
  rgb_matrix_set_color(3, 5, 0, 0);
  rgb_matrix_set_color(4, 5, 0, 0);

  rgb_matrix_set_color(13, 5, 0, 0);
  rgb_matrix_set_color(14, 5, 0, 0);
  rgb_matrix_set_color(15, 5, 0, 0);
  rgb_matrix_set_color(16, 5, 0, 0);

  rgb_matrix_set_color(25, 5, 0, 0);
  rgb_matrix_set_color(26, 5, 0, 0);
  rgb_matrix_set_color(27, 5, 0, 0);
  rgb_matrix_set_color(28, 5, 0, 0);
}

if(IS_LAYER_ON(NSL)) {
  rgb_matrix_set_color(42, 1, 0, 5);

  rgb_matrix_set_color(2, 1, 0, 5);
  rgb_matrix_set_color(3, 1, 0, 5);
  rgb_matrix_set_color(4, 1, 0, 5);

  rgb_matrix_set_color(14, 1, 0, 5);
  rgb_matrix_set_color(15, 1, 0, 5);
  rgb_matrix_set_color(16, 1, 0, 5);

  rgb_matrix_set_color(26, 1, 0, 5);
  rgb_matrix_set_color(27, 1, 0, 5);
  rgb_matrix_set_color(28, 1, 0, 5);

  rgb_matrix_set_color(38, 1, 0, 5);
  rgb_matrix_set_color(39, 1, 0, 5);
  rgb_matrix_set_color(40, 1, 0, 5);
}

if(IS_LAYER_ON(NSSL)) {
  rgb_matrix_set_color(41, 0, 5, 0.19);

  rgb_matrix_set_color(1, 0, 5, 0.19);
  rgb_matrix_set_color(2, 0, 5, 0.19);
  rgb_matrix_set_color(3, 0, 5, 0.19);
  rgb_matrix_set_color(4, 0, 5, 0.19);
  rgb_matrix_set_color(5, 0, 5, 0.19);

  rgb_matrix_set_color(13, 0, 5, 0.19);
  rgb_matrix_set_color(14, 0, 5, 0.19);
  rgb_matrix_set_color(15, 0, 5, 0.19);
  rgb_matrix_set_color(16, 0, 5, 0.19);
  rgb_matrix_set_color(17, 0, 5, 0.19);

  rgb_matrix_set_color(25, 0, 5, 0.19);
  rgb_matrix_set_color(26, 0, 5, 0.19);
  rgb_matrix_set_color(27, 0, 5, 0.19);
  rgb_matrix_set_color(28, 0, 5, 0.19);
  rgb_matrix_set_color(29, 0, 5, 0.19);

}

//capslock leds

if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    rgb_matrix_set_color_all(5, 1.56, 0);
  }

}
