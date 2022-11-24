/* Copyright 2022 @toinux
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
#include "keycodes.h"
#include "oled.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


void oled_render_mod_status(void) {

    const uint8_t modifiers = get_mods() | get_oneshot_mods();

    for (uint8_t i = 0; i < 2; i++) {
        oled_set_cursor(9,i);
        oled_write_P(gui_icon[(modifiers & MOD_MASK_GUI) ? 1 : 0][i], false);
        oled_write_P(ctrl_icon[(modifiers & MOD_MASK_CTRL) ? 1 : 0][i], false);
        oled_set_cursor(9,i+2);
        oled_write_P(alt_icon[(modifiers & MOD_MASK_ALT) ? 1 : 0][i], false);
        oled_write_P(shift_icon[(modifiers & MOD_MASK_SHIFT) ? 1 : 0][i], false);
    }

}

void oled_render_layer_state(void) {

    char c = 0x9F - get_highest_layer(layer_state|default_layer_state);

    oled_set_cursor(20,0);
    oled_write_char(0X00, false);

    oled_set_cursor(20,1);
    oled_write_char(c, false);
    c += 32;
    oled_set_cursor(20,2);
    oled_write_char(c, false);
    c += 32;
    oled_set_cursor(20,3);
    oled_write_char(c, false);

}

void oled_render_led_state(void) {
    // oled_advance_page(false) instead of oled_write_ln_P to not break OLED_TIMEOUT
    oled_write_P(PSTR("NUM"), host_keyboard_led_state().num_lock);
    oled_advance_page(false);
    oled_write_P(PSTR("CAP"), host_keyboard_led_state().caps_lock);
    oled_advance_page(false);
    oled_write_P(PSTR("SCL"), host_keyboard_led_state().scroll_lock);
    oled_advance_page(false);
}

uint8_t last_row = 0;
uint8_t last_col = 0;

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  last_row = record->event.key.row;
  last_col = record->event.key.col;
}

void oled_render_keylog(void) {
    oled_write_char(last_row + '0', false);
    oled_write_char('x', false);
    oled_write_char(last_col + '0', false);
}

void oled_render_logo(void) {
    static const char PROGMEM kpu_logo[][3] = {
        {0x82, 0x83, 0},
        {0x80, 0x81, 0},
        {0xa0, 0xa1, 0},
        {0xc0, 0xc1, 0}
    };
    for (uint8_t i = 0; i < 4; i++) {
        oled_write_ln_P(kpu_logo[i], false);
    }

}

bool oled_task_user(void) {
    if (is_keyboard_master ()) {
        oled_render_led_state();
        oled_render_keylog();
        oled_render_mod_status();
        oled_render_layer_state();
    } else {
        oled_render_logo();
        oled_scroll_right();
        oled_scroll_set_speed(4);
    }
    return false;
}
