/*Copyright 2024 Blake Drayson / Draytronics

Contact info@draytronics.co.uk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

This code is inspired by and adapted from the code used in the Printed Pad by Noah Beidelman (@noahbei)

It also references the concept and some pixel frames (the arasaka logo) form Aleks (@aleksbrgt)

Other pixel images are either created by me or use the resources of Velency Grpahics https://www.valencygraphics.com/cyberpunk-2077

No claim for licence or ownership is made for any logos or similarities to logos or brand names.
*/

#include QMK_KEYBOARD_H
#include "daisy_v2.h"

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
}

const uint8_t max_layer = 3;
uint8_t current_display_mode = 0;

bool hidden = false;

bool key_pressed = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
#ifdef OLED_ENABLE
    key_pressed = record->event.pressed;
#endif
    switch(keycode) {
        case LT(0, KC_NO):
            if (record->event.pressed) {
                // on tap
                if (record->tap.count) {
                    tap_code(KC_MUTE);
                }
#ifdef OLED_ENABLE
                // on hold
                else {
                    hidden = false;
                    current_display_mode = (current_display_mode + 1) % 4;
                }
#endif
            }
            return false;
    }
    return true;
}

#ifdef OLED_ENABLE
uint32_t flash_timer = 0;
bool layer_changed = false;

// when the layer is changed, flash the layer number on the screen
layer_state_t layer_state_set_kb(layer_state_t state) {
    flash_timer = timer_read();
    layer_changed = true;

    return layer_state_set_user(state);
}
#endif
