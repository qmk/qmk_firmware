// Copyright 2023 Noah Beidelman (@noahbei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "printedpad.h"

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
}

const uint8_t max_layer = 3;
uint8_t current_display_mode = 0;

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
                    if (get_highest_layer(layer_state) >= max_layer) {
                        layer_clear(); 
                    } else { 
                        layer_move(get_highest_layer(layer_state) + 1);
                    }
                }
#ifdef OLED_ENABLE
                // on hold
                else {
                    current_display_mode = (current_display_mode + 1) % 3;
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