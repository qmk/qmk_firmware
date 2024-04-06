//  Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

bool dis_breath = 0;
uint8_t breath_level = 0;

void suspend_power_down_kb() {
    gpio_write_pin_low(MAC_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    switch (get_highest_layer(layer_state)) {
    case 0:
        gpio_write_pin_low(MAC_PIN);
        break;
    case 1:
        gpio_write_pin_high(MAC_PIN);
        break;
    }
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    backlight_disable();
    if (jump_to_bootloader) {
        backlight_enable_breathing();
    } else {
        gpio_write_pin_low(MAC_PIN);
    }
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
     case BL_TOGG:
      if (record->event.pressed) {
        if (is_backlight_breathing() && get_backlight_level()){
           dis_breath = 1;
           backlight_disable_breathing();
           backlight_enable();

        } else if (dis_breath && !is_backlight_enabled()){
            backlight_enable_breathing();
            dis_breath = 0;
        }
        return true;
      }

     case BL_BRTG:
      if (record->event.pressed) {
        if (dis_breath || !is_backlight_enabled()){
            return false;
        }
            return true;
        }

     case TO(0):
      if (record->event.pressed) {
       set_single_persistent_default_layer(0);  //Save default layer 0 to eeprom
      }
      return true; // continue all further processing of this key

     case TO(1):
      if (record->event.pressed) {
       set_single_persistent_default_layer(1);  //Save default layer 1 to eeprom
      }
      return true; // continue all further processing of this key

     default:
      return true;
    }
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    gpio_set_pin_output(MAC_PIN);
    gpio_write_pin_high(MAC_PIN);
    /*
     if (is_backlight_breathing()){
           backlight_disable_breathing();
           dis_breath = 1;
           backlight_enable();
        }
    */
}
