/* Copyright 2020 boardsource
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_ortho_2x3(
        RGB_TOG, KC_VOLU, KC_F2,
        RGB_MOD, KC_VOLD, KC_F1
    ),
};
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_RIP(void) {
  static const char PROGMEM my_logo[] = {
0xff, 0xff, 0x07, 0x1e, 0x70, 0xc0, 0x00, 0x00, 0xe0, 0x78, 0x1e, 0x07, 0xff, 0xfe, 0x00, 0x00,
0x00, 0x00, 0x03, 0x06, 0x1c, 0xb8, 0xf0, 0xe0, 0xb8, 0x1c, 0x0e, 0x07, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x66, 0x63, 0x63, 0x43, 0x43, 0xc3, 0xc2, 0x82,
0x00, 0x00, 0x00, 0x30, 0xf0, 0xc0, 0x00, 0x00, 0xc0, 0xf0, 0x30, 0xf0, 0x80, 0x00, 0x00, 0xc0,
0xf0, 0x10, 0x00, 0x00, 0x00, 0xf3, 0xf3, 0x00, 0x00, 0x10, 0x18, 0xfe, 0x18, 0x10, 0x10, 0x10,
0x00, 0x00, 0xc0, 0xe0, 0x30, 0x10, 0x18, 0x18, 0x18, 0x10, 0x10, 0x00, 0x00, 0x00, 0xff, 0xff,
0x30, 0x10, 0x18, 0x18, 0x18, 0x30, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x90, 0x90, 0x98,
0x98, 0x98, 0xb0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0xf0, 0x90, 0x98, 0x98, 0x18, 0x18, 0x10, 0x00,
0x1f, 0x1f, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00,
0x00, 0x10, 0x1c, 0x0e, 0x07, 0x01, 0x00, 0x00, 0x01, 0x07, 0x0e, 0x1c, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x18, 0x18, 0x10, 0x10, 0x18, 0x18, 0x0d, 0x0f,
0x03, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x1e, 0x1e, 0x07, 0x00, 0x00, 0x01, 0x0f, 0x1c, 0x1e, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0c, 0x18, 0x18, 0x18,
0x00, 0x00, 0x03, 0x0f, 0x0c, 0x18, 0x10, 0x10, 0x10, 0x18, 0x08, 0x00, 0x00, 0x00, 0x1f, 0x1f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x18, 0x10,
0x10, 0x10, 0x18, 0x18, 0x08, 0x00, 0x00, 0x08, 0x18, 0x10, 0x11, 0x11, 0x11, 0x19, 0x0f, 0x0e,
0x00, 0x30, 0x30, 0x10, 0x10, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0,
0x30, 0x10, 0x18, 0x18, 0x10, 0x70, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x40, 0xf0, 0xb0, 0x10, 0x18,
0x18, 0x10, 0x30, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x70, 0x10, 0x18, 0x18, 0x10, 0x30,
0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x10, 0x18, 0x18, 0x18,
0x10, 0x30, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0x30, 0x10, 0x18, 0x10, 0x30, 0xf0,
0xe0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x10, 0x18, 0x18, 0x10, 0x30, 0xf0, 0xe0, 0x00, 0x00,
0x00, 0x00, 0xc0, 0xe0, 0x30, 0x10, 0x18, 0x18, 0x10, 0x30, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc7,
0xc4, 0x8c, 0x8c, 0xcc, 0xc4, 0x77, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x38, 0x7d, 0xc7, 0xc3, 0x82,
0x82, 0xc3, 0xc7, 0x7d, 0x7c, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x70, 0xc0, 0x80, 0x80, 0xc0, 0xc0,
0x7f, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08,
0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xd8, 0xcc,
0xc6, 0xc3, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x70, 0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0x70,
0x3f, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xd8, 0xcc, 0xcc, 0xc7, 0xc3, 0xc1, 0x00, 0x00,
0x00, 0x00, 0x3f, 0x7f, 0xe0, 0xc0, 0x80, 0x80, 0xc0, 0x60, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00
 };

  oled_write_raw_P(my_logo, sizeof(my_logo));
}

void oled_task_user(void) {
  render_RIP();
  }

#endif
