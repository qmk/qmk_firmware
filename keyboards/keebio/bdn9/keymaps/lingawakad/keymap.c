/*
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

/*
 * rotary encoder functionality heavily cribbed from /u/hansolo71
 * https://www.reddit.com/r/MechanicalKeyboards/comments/s52e51/added_alttab_to_my_rotary_encoder_on_my_qmk_board/
 */

#include QMK_KEYBOARD_H

bool is_gui_tab_active = false;
bool is_gui_shift_tab_active = false;
uint16_t gui_tab_timer = 0;
/* ALT↯TAB gudniss */
void matrix_scan_user(void) {
  if (is_gui_tab_active) {
    if (timer_elapsed(gui_tab_timer) > 1250) {
      unregister_code(KC_LGUI);
			unregister_code(KC_LSFT);
      is_gui_tab_active = false;
    }
  }
};

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ENT , KC_ENT, KC_MUTE,
        KC_V   , KC_C  , KC_RGUI,
        KC_BTN1, MO(1) , KC_BTN2
    ),

    [1] = LAYOUT(
        KC_ENT , KC_ENT , KC_MUTE,
		KC_WH_U, KC_TAB , KC_RSFT,
        KC_WH_D, _______, KC_TAB
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code16(C(KC_TAB));
        } else {
            tap_code16(C(S(KC_TAB)));
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
					if (!is_gui_tab_active) {
						is_gui_tab_active = true;
					unregister_code(KC_LSFT);
					register_code(KC_LGUI);
					}
					gui_tab_timer = timer_read();
					tap_code16(KC_TAB);
				} else {
					if (!is_gui_shift_tab_active) {
						is_gui_shift_tab_active = true;
					register_code(KC_LGUI);
					register_code(KC_LSFT);
					}
					gui_tab_timer = timer_read();
					tap_code16(KC_TAB);
				}
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code16(KC_VOLU);
        } else {
            tap_code16(KC_VOLD);
        }
    }
    return false;
}
