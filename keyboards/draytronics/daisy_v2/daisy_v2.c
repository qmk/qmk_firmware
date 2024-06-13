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

It also references the concept of glitching animations from Aleks (@aleksbrgt)

The pixel graphics used here are from a combination of sources;

1. Layer indicators are created by myself and free to use by anyone.
2. "Revengeday", "Cyber Cafe", "Cortex Implant" logos are used with kind permission of OBEY THE SYSTEM.
   A collective of Fediverse instances and creatives. https://git.cyberwa.re/obey-the-system.
   They are licenced as Non-Commercial and for use by members of the network, with attribution.
3. Key press indicator graphics were commissioned for this project and were designed by the
   amazing https://corteximplant.com/@jadedtwin / https://www.jadedtwin.com/
*/
#include "daisy_v2.h"

enum my_keycodes {
  ENCODER_PRESS = QK_KB,
};

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
}

const uint8_t max_layer = 3;
uint8_t current_display_mode = 0;

bool hidden = false;

uint8_t key_pressed = 0;


/* EEPROM Stuct and function to allow init / saving of OLED mode */
typedef union {
uint32_t raw;
struct {
    uint8_t oled_mode :8;
};
} kb_config_t;

kb_config_t kb_config;

void eeconfig_init_kb(void) {
        //Init initial value and save to EEPROM.
        kb_config.raw = 0;
        eeconfig_update_kb(kb_config.raw);
}
/* End */

void keyboard_post_init_user(void) {
    //Read user value and set current_display_mode.
    kb_config.oled_mode = eeconfig_read_kb();
    current_display_mode = kb_config.oled_mode;

    //This is an adjustment to resolve the issue that occurs when there is a
    //static colour underglow the first LED can be a different colour on first init.
    rgblight_disable_noeeprom();
    rgblight_enable_noeeprom();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    #ifdef OLED_ENABLE
    if (record->event.pressed) {
        key_pressed++;
    } else {
       if (key_pressed)
           key_pressed--;
    }
    #endif
    switch(keycode) {
        case LT(0, ENCODER_PRESS):
            if (record->event.pressed) {
                // on tap
                if (record->tap.count) {
                    tap_code(KC_MUTE);
                }
                #ifdef OLED_ENABLE
                // on hold
                else {
                    hidden = false;
                    current_display_mode = (current_display_mode + 1) % 5;
                    // When mode changes update EEPROM.
                    kb_config.oled_mode = current_display_mode;
                    eeconfig_update_kb(kb_config.raw);
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
