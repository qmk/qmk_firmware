//  Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void suspend_power_down_kb() {
    writePinLow(MAC_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    switch (get_highest_layer(layer_state)) {
    case 0:
        writePinLow(MAC_PIN);
        break;
    case 1:
        writePinHigh(MAC_PIN);
        break;
    }
    suspend_wakeup_init_user();
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        writePinLow(MAC_PIN);
        break;
    case 1:
        writePinHigh(MAC_PIN);
        break;
    }
  return state;
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }

    if (jump_to_bootloader) {
        backlight_disable();
        writePinHigh(MAC_PIN);
    } else {
        backlight_enable_breathing();
    }
    return true;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    setPinOutput(MAC_PIN);
    writePinHigh(MAC_PIN);
}
