/* Copyright 2023 9R
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

#ifdef LEDS_ENABLE
#  include "../common/leds.h"
#endif

#ifdef OLED_ENABLE
#  include "../common/oled.h"
#endif

#ifdef THUMBSTICK_ENABLE
#  include "../common/thumbstick.h"
#endif

#include "../common/state.h"

controller_state_t controller_state ;

#ifndef OLED_ENABLE
enum keymap_layers {
  LAYER_BASE = 0,
  LAYER_SHOOTER,
  LAYER_MISC,
  LAYER_SETTINGS,
};
#endif

enum custom_keycodes {
  JOYMODE = SAFE_RANGE,
  AUTORUN,
  M_UP,
  M_DWN,
  M_L,
  M_R,
  M_SEL
};

//////////// Status LEDs //////////////
#ifdef LEDS_ENABLE
void keyboard_pre_init_user(void) {
  init_leds() ;
}
#endif

//////////// WASD THUMBSTICK //////////////
#ifdef THUMBSTICK_ENABLE
void matrix_init_user(void) {
  init_wasd_state() ;
  controller_state = init_state();
}

void matrix_scan_user(void) {
  if (controller_state.wasdMode) {
    thumbstick (controller_state);
  }
}
#endif

#ifdef JOYSTICK_ENABLE
//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
  JOYSTICK_AXIS_IN(B0, 0, 512, 1023),
  JOYSTICK_AXIS_IN(B1, 0, 512, 1023)
};
#endif

//////////// KEYMAPS //////////////
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
  // | little | ring   | middle | index   | 5way-dpad | -finger
      KC_GRV,  KC_ESC,  KC_J,    KC_M,     KC_RIGHT,  // up
      KC_T,    KC_3,    KC_4,    KC_R,     KC_ENT,    // forward
      KC_X,    KC_LCTL, KC_LCTL, KC_LALT,  KC_DOWN,   // down
      KC_LSFT, KC_SPC,  KC_C,    KC_F,     KC_LEFT,   // back 2
      KC_LSFT, KC_6,    KC_Z,    KC_V,     KC_UP,     // back 1
      KC_TAB,  TG(1),   KC_I,    KC_B,     KC_P       // special
  //  ^side_l | ^case  | ^thumb | ^side_r | ^analog click <= special row mapping
      ),

  [LAYER_SHOOTER] = LAYOUT(
  // | little | ring   | middle | index   | 5way-dpad | -finger
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_RIGHT,  // up
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_ENT,    // forward
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_DOWN,   // down
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_LEFT,   // back 2
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_UP,     // back 1
      KC_NO,   TG(2),   KC_NO,   KC_NO,    KC_P       // special
  //  ^side_l | ^case  | ^thumb | ^side_r | ^analog click <= special row mapping
      ),
  [LAYER_MISC] = LAYOUT(
  // | little | ring   | middle | index   | 5way-dpad | -finger
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_RIGHT,  // up
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_ENT,    // forward
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_DOWN,   // down
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_LEFT,   // back 2
      KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_UP,     // back 1
      KC_NO,   TG(3),   KC_NO,   KC_NO,    KC_P       // special
  //  ^side_l | ^case  | ^thumb | ^side_r | ^analog click <= special row mapping
      ),
  [LAYER_SETTINGS] = LAYOUT(
  // | little | ring   | middle | index   | 5way-dpad | -finger
      RGB_M_P, RGB_M_B, RGB_M_K, RGB_M_T,  KC_RIGHT,  // up
      KC_NO,   RGB_SAI, RGB_VAI, RGB_HUI,  KC_ENT,    // forward
      RGB_TOG, KC_NO,   KC_NO,   KC_NO  ,  KC_DOWN,   // down
      EE_CLR,  RGB_SAD, RGB_VAD, RGB_HUD,  KC_LEFT,   // back 2
      QK_BOOT, AUTORUN, JOYMODE, KC_V,     KC_UP,     // back 1
      RGB_MOD, TO(0),   KC_NO,   RGB_RMOD, KC_P       // special
  //  ^side_l | ^case  | ^thumb | ^side_r | ^analog click <= special row mapping
      )
};

//////////// Change modes on keypress //////////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == JOYMODE && record->event.pressed) {
    if (!controller_state.wasdMode) {
      controller_state.wasdMode = true;
    } else if (controller_state.wasdMode && !controller_state.wasdShiftMode) {
      controller_state.wasdShiftMode = true;
    } else {
      controller_state.wasdMode = false;
      controller_state.wasdShiftMode = false;
    }
  } else if (keycode == AUTORUN && record->event.pressed) {
    if (!controller_state.autoRun) {
      controller_state.autoRun = true;
      register_code(KC_W);
    } else {
      controller_state.autoRun = false;
      unregister_code(KC_W);
    }
  }
  return true;
};

//////////// Draw OLED menu //////////////
#ifdef OLED_ENABLE
bool oled_task_user(void) {
  draw_oled(controller_state);

  return false;
}
#endif

//////////// Handle layer changes //////////////
layer_state_t layer_state_set_user(layer_state_t state) {
  controller_state.activeLayer = get_highest_layer(state) ;

  #ifdef LEDS_ENABLE
  set_leds(controller_state.activeLayer) ;
  #endif

  return state ;
}
