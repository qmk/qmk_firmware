/* Copyright 2020 Kyrre Havik Eriksen
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
#include "quantum.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }

  return OLED_ROTATION_270;
}

static void render_named_logo(void) {
  static const char PROGMEM raw_logo[] = {
    12, 60,252,252,252,236,236,140, 12, 28,248,192,  0,192,248,252,252,252,108, 12, 12,140,236, 60, 12,  0,  0,  0,248,252,252,252,236,204,204,204,204,204,204,204,204,204,204,204,204,140, 12,252,248,  0,  0,  0,252,252,252,252,236,236,236,204, 12, 60,240,192,  0,  0,  0,252,252,252,236,236, 12, 12, 12,252,248,  0,  0,192,224, 96, 48, 24, 24,140,140,132,196,196,196,196,132,140,140, 12, 24, 48, 48, 96,192,128,  0,  0,252,252,252,236,236,236,236,140, 28,120,224,128,  0,  0,252,252,252,252,236,236, 12, 12, 12,252,
    0,  0,  0,  3, 15,255,255,255,254,248,192,195,223,255,255, 63, 15,  1,224,248, 30,  7,  1,  0,  0,  0,  0,  0,255,255,255,255,255,255,  0,  0,  1, 63, 63, 51, 51, 51, 51, 51, 51, 51,243,  3,  1,  0,  0,  0,255,255,255,255,255,  1, 15,127,255,252,240,195, 15, 60,240,255,255,255,255,255,  0,  0,  0,255,255,254,255,255,255,127, 14,  2,195,247, 63, 31, 15, 15, 15, 15, 31, 63,255,255,254,252,248,224,  1,  3, 30,252,255,255,255,255,255,  3, 31,255,254,248,225,135, 30,120,255,255,255,255,255,255,  0,  0,  0,255, 
    0,  0,128,240,252,255,255,255, 63,  7,  1,227,127,255,255,255,248,224,  1,  7, 62,240,192,  0,  0,  0,  0,  0,255,255,255,255,255,255,  1,  3,  7,255,255,207,207,207,207,207,206,204,207,192,128,  0,  0,  0,255,255,255,255,255,  0,  0,  0,255,255, 15,127,255,252,240,227,143,127,255,255,  0,  0,  0,255,255, 63,255,255,255,254,240,192,131,135, 12, 24, 48, 48, 48, 48, 24, 28, 15,159,255, 63, 31,  7,128,192,120, 31,255,255,255,255,255,  0,  0,  0,255,255, 31,127,255,252,241,199, 31,127,255,255,  0,  0,  0,255,
    48, 62, 63, 63, 63, 63, 63, 56, 48, 60, 31,  3,  0,  3, 31, 63, 63, 63, 63, 60, 60, 56, 59, 63, 56,  0,  0,  0, 31, 63, 63, 63, 63, 63, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 56, 63, 31,  0,  0,  0, 63, 63, 63, 63, 63, 60, 56, 48, 63, 63,  0,  0,  0,  3, 31, 63, 63, 62, 61, 63, 60, 56, 48, 63, 31,  0,  0,  1,  7,  7, 15, 31, 31, 63, 63, 63, 62, 62, 62, 62, 63, 63, 63, 31, 31, 15, 14,  6,  3,  1,  0,  0, 63, 63, 63, 63, 63, 60, 56, 56, 63, 31,  0,  0,  1,  7, 31, 63, 63, 60, 63, 63, 60, 56, 48, 63
  };
  oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_status(void) {
  oled_write_P(PSTR("\n\n\n-----\nXENON\n-----\n\n"), false);

  // Host Keyboard Layer Status
  switch (get_highest_layer(layer_state)) {
  case 0:
    oled_write_P(PSTR("Base \n"), false);
    break;
  case 1:
    oled_write_P(PSTR("Lower\n"), false);
    break;
  case 2:
    oled_write_P(PSTR("Raise\n"), false);
    break;
  default:
    oled_write_P(PSTR("Undef\n"), false);
  }
  oled_write_P(PSTR("Layer\n"), false);
}

bool oled_task_kb(void) {
	if (!oled_task_user()) {
		return false;
	}

  if (is_keyboard_master()) {
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_named_logo();
  }

  return true;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
	if (!encoder_update_user(index, clockwise)) {
		return false;
	}

	if (index == 0) {
		// Volume control
		if (clockwise) {
			tap_code(KC_VOLD);
		} else {
			tap_code(KC_VOLU);
		}
	}
	else if (index == 1) {
		// Page up/Page down
		if (clockwise) {
			tap_code(KC_PGDN);
		} else {
			tap_code(KC_PGUP);
		}
	}
	
  return true;
}
#endif
