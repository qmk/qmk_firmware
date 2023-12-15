/* Copyright 2018 Jack Humbert
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

#define BASE 0
#define FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
		KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6,
		KC_1, KC_2, KC_3,
		MO(1), KC_0, KC_DOT
	),

	[FN] = LAYOUT(
		KC_TRNS, KC_HOME, KC_PGUP,
		KC_TRNS, KC_END, KC_PGDN,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_ENT
	)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Let's\nbuild\nsome-\nthing\nto-\nget-\nher!"), false);
  switch (get_highest_layer(layer_state)) {
    case BASE:
      oled_write_ln_P(PSTR(""), false);
      break;
    case FN:
      oled_write_ln_P(PSTR("FN"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undef"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NLCK ") : PSTR("     "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("       "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCRLK") : PSTR("       "), false);

    return false;
}
#endif
