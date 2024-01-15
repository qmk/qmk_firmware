//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

_Bool DIS_BRETH = 0;

void suspend_power_down_kb() {
    writePinHigh(MAC_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    writePinHigh(MAC_PIN);
    return shutdown_user(jump_to_bootloader);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
       case TO(0):
            set_single_persistent_default_layer(0); // Save default layer 0 to eeprom
         return true; // continue all further processing of this key

       case TO(1):
            set_single_persistent_default_layer(1);  //Save default layer 1 to eeprom
            writePinLow(MAC_PIN);
         return true; // continue all further processing of this key

       case BL_TOGG:
           if (record->event.pressed){
               if(is_backlight_breathing()) {
                    backlight_disable_breathing();
                    DIS_BRETH = 1;

                }else if(DIS_BRETH && !(is_backlight_enabled())){
                    backlight_enable_breathing();
                    DIS_BRETH = 0;
                }
           }
         return true;

       case BL_BRTG:
           if (record->event.pressed){
               if(DIS_BRETH || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

       case BL_UP:
           DIS_BRETH = 0;
         return true;

       case BL_DOWN:
           if (record->event.pressed){
               if(DIS_BRETH || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

      default:
         return true;
    }
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    writePin(MAC_PIN, !layer_state_cmp(state, 1));
  return state;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    setPinOutput(MAC_PIN);
    writePinHigh(MAC_PIN);
}
