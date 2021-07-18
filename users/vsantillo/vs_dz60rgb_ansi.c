/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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

#include "vs_dz60rgb_ansi.h"
#include "tap_dances/tap_dance.h"
#include "tap_dances/tap_dance_controller.h"
#include "tap_dances/dances/quick_mute.h"
#include "tap_dances/dances/quick_redo.h"
#include "tap_dances/dances/quick_undo.h"
#include "tap_dances/dances/space_cadet_pro.h"

void matrix_init_user(void) {
    rgblight_mode(RGB_MATRIX_CUSTOM_berryLerp);
    autoshift_enable();
}

layer_state_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case GAME:
      autoshift_disable();
      break;
    default:
      break;
  }
  return state;
}

// Tap dances
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSCP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_space_cadet_pro_on_finish, left_space_cadet_pro_on_reset),
    [TD_RSCP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_space_cadet_pro_on_finish, right_space_cadet_pro_on_reset),
    [TD_QUICK_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quick_undo_on_finish, quick_undo_on_reset),
    [TD_QUICK_REDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quick_redo_on_finish, quick_redo_on_reset),
    [TD_QUICK_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, quick_mute, NULL, 115),
};

__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    // Operating System
    rgb_matrix_set_color(27, RGB_WHITE); // Set Tab to White
    if (layer_state_is(WINDOWS)) {
        rgb_matrix_set_color(27, RGB_CYAN);  // Set Tab to Cyan
    }

    // Autoshift enabled
    if (get_autoshift_state()) {
        rgb_matrix_set_color(40, RGB_CYAN); // Set Caps Lock To Cyan
    }

    // Game Layer toggled
    if (layer_state_is(GAME)) {
        rgb_matrix_set_color(40, RGB_GREEN); // Set Caps Lock to Green
        rgb_matrix_set_color(55, RGB_OFF);  // Disable Right Windows Key LED
        rgb_matrix_set_color(59, RGB_OFF);  // Disable Left Windows Key LED
    }

    // Function Layers
    if (layer_state_is(SPACEFN)) {
        rgb_matrix_set_color(40, RGB_SPRINGGREEN);  // Set Caps Lock to Springgreen
    } else if (layer_state_is(FN1)) {
        rgb_matrix_set_color(40, RGB_GOLD);  // Set Caps Lock to Gold
        rgb_matrix_set_color(60, RGB_RED);  // Set Ctrl to Red for RESET
    }

    // Caps Lock
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(40, RGB_MAGENTA); // Set Caps Lock to Magenta
    }
}
