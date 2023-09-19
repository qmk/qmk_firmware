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

#include "replicazeron.h"

controller_state_t controller_state;

#ifdef JOYSTICK_ENABLE
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(ANALOG_AXIS_PIN_X , 0, 512, 1023),
    JOYSTICK_AXIS_IN(ANALOG_AXIS_PIN_Y , 0, 512, 1023)
};
#endif

#ifdef THUMBSTICK_ENABLE
void housekeeping_task_kb(void) {
    if (controller_state.wasdMode) {
        thumbstick(controller_state);
    }
}
#endif

void keyboard_post_init_kb(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;

#ifdef LEDS_ENABLE
    init_leds();
#endif // LEDS_ENABLE

#ifdef THUMBSTICK_ENABLE
    init_wasd_state();
#endif // THUMBSTICK_ENABLE

    controller_state = init_state();

    keyboard_post_init_user();
}

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    draw_oled(controller_state);
    return false;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }


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

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    controller_state.highestActiveLayer = get_highest_layer(state) ;

#ifdef LEDS_ENABLE
    set_leds(controller_state.highestActiveLayer) ;
#endif // LEDS_ENABLE

    return state;
}
