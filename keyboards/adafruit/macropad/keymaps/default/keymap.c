/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                    LT(1,KC_MUTE),
      KC_ENT, KC_0, KC_BSPC,
      KC_7,   KC_8, KC_9,
      KC_4,   KC_5, KC_6,
      KC_1,   KC_2, KC_3
  ),
  [1] = LAYOUT(
                        _______,
      CK_TOGG, AU_TOGG, _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [1] = { ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef QUANTUM_PAINTER_ENABLE

#include "gfx/qmk_logo.qgf.h"

extern painter_device_t oled_display;
static painter_image_handle_t qmk_logo_handle;
static deferred_token qmk_logo_anim;

void keyboard_post_init_user() {
  qmk_logo_handle = qp_load_image_mem(qmk_logo);
  qmk_logo_anim = qp_animate(oled_display, 0, 0, qmk_logo_handle);
}

void housekeeping_task_user(void) {
  static uint32_t anim_timeout = 0;
  static bool stopped = false;
  if (!stopped && timer_elapsed32(anim_timeout) > 2000) {   //Stop animation after 2 seconds.
    stopped = true;
    qp_stop_animation(qmk_logo_anim);
  }
}
#endif
