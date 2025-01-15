//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

bool backup_breath = 0; // Marked backlight breathing mode

void suspend_power_down_kb() {
    gpio_write_pin_high(MAC_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    gpio_write_pin_high(MAC_PIN);
    return shutdown_user(jump_to_bootloader);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {

       case BL_TOGG:
         if (record->event.pressed) {
            if (is_backlight_breathing()){
               backup_breath = 1;                //backup breathing before shut down backlight.
               backlight_disable_breathing();
            } else if (backup_breath){          //check backuped breathing before switching backlight
                backlight_enable_breathing();
                backup_breath = 0;
              }
           }
        return true;

      case BL_BRTG:
         if (!is_backlight_breathing() && !is_backlight_enabled()){
              return false;
            }else{
              return true;
            }

      case BL_UP:
         if (backup_breath){                      //check backuped breathing before creasing brightness
                backlight_enable_breathing();
                backup_breath = 0;
              }
         return true;

       case BL_DOWN:
        if (!is_backlight_breathing() && !is_backlight_enabled()){
              return false;
            }else{
              return true;
            }

      default:
         return true;
    }
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    gpio_write_pin(MAC_PIN, !layer_state_cmp(state, 1));
  return default_layer_state_set_user(state);
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    gpio_set_pin_output(MAC_PIN);
    gpio_write_pin_high(MAC_PIN);
}
