#include QMK_KEYBOARD_H
#include "printedpad.h"

void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
}

uint8_t current_layer = 0;
uint8_t current_display_mode = 0;

bool key_pressed = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed)
        key_pressed = true;
    else
        key_pressed = false;
#endif
    switch(keycode) {
        case LT(0, KC_NO):
            // on tap
            if (record->tap.count && record->event.pressed) {
                current_layer = (current_layer + 1) % 4;
                layer_move(current_layer);
            }
#ifdef OLED_ENABLE
            // on hold
            else if (record->event.pressed) {
                current_display_mode = (current_display_mode + 1) % 3;
            }
#endif
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
    
    return state;
}
#endif