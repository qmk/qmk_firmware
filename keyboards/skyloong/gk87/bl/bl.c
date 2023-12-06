//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

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
            writePinHigh(MAC_PIN);
         return true; // continue all further processing of this key

       case TO(1):
            set_single_persistent_default_layer(1);  //Save default layer 1 to eeprom
            writePinLow(MAC_PIN);
         return true; // continue all further processing of this key

      default:
         return true;
    }
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        writePinHigh(MAC_PIN);
        break;
    case 1:
        writePinLow(MAC_PIN);
        break;
    }
  return state;
}


void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    setPinOutput(MAC_PIN);
    writePinHigh(MAC_PIN);
}
