/* Copyright 2021 Leon Anavi <leon@anavi.org>
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

#define _MAIN 0
#define _FN 1

/*
 * This keymap contains the following shortcuts for Git. On the
 * first row from left to right:
 *
 * git status
 * git log
 * git pull
 * git push
 *
 * On the second row from left to right:
 *
 * git diff
 * git add
 * git commit
 * FN key to switch to the 2nd layout and control lights
 *
 */

enum custom_keycodes {
	GITCOMMIT = SAFE_RANGE,
	GITPUSH,
	GITPULL,
	GITSTATUS,
	GITDIFF,
	GITLOG,
	GITADD
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case GITCOMMIT:
		if (record->event.pressed) {
			SEND_STRING("git commit -s\n");
		}
	break;
	case GITPUSH:
		if (record->event.pressed) {
			SEND_STRING("git push\n");
		}
	break;
	case GITPULL:
		if (record->event.pressed) {
			SEND_STRING("git pull\n");
		}
	break;
	case GITSTATUS:
		if (record->event.pressed) {
			SEND_STRING("git status\n");
		}
	break;
	case GITDIFF:
		if (record->event.pressed) {
			SEND_STRING("git diff ");
		}
	break;
	case GITLOG:
		if (record->event.pressed) {
			SEND_STRING("git log\n");
		}
	break;
	case GITADD:
		if (record->event.pressed) {
			SEND_STRING("git add ");
		}
	break;
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_2x4(
     GITSTATUS, GITLOG, GITPULL, GITPUSH,
     GITDIFF, GITADD, GITCOMMIT, MO(_FN)
  ),

  [_FN] = LAYOUT_ortho_2x4(
     RGB_TOG, RGB_MOD, RGB_M_R, RGB_M_SN,
     BL_TOGG, BL_STEP, BL_BRTG, _______
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
    case _MAIN:
      oled_write_ln_P(PSTR("Git"), false);
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
  oled_write_P(PSTR("Scroll Lock: "), false);
  oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);
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
