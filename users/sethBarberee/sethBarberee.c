 /* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
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
#include "sethBarberee.h"
#include "version.h"

__attribute__ ((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void){
#if defined(BOOTLOADER_CATERINA)
    // Make sure the red LEDs don't light
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
    keyboard_pre_init_keymap();
}

__attribute__ ((weak)) layer_state_t layer_state_set_keymap (layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state){

    if (!is_keyboard_master()) {
        return state;
    }

    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#if defined(RGBLIGHT_ENABLE)
    state = layer_state_set_rgb_light(state);
#endif
    return layer_state_set_keymap(state);
}

__attribute__ ((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void)
{
#if defined(RGBLIGHT_ENABLE)
    keyboard_post_init_rgb_light();
#endif
    keyboard_post_init_keymap();
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
#ifdef OLED_DRIVER_ENABLE
    oled_off();
#endif
    suspend_power_down_keymap();
}

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) { suspend_wakeup_init_keymap(); }

__attribute__ ((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true;}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_record_keymap(keycode, record))
    {
        switch (keycode) {
            case KC_VRSN:  // Prints firmware version
                if (record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
                }
                break;
        }
    }
    return true;
}
