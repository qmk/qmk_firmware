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

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    backlight_disable();
    if (jump_to_bootloader) {
        backlight_enable_breathing();
    } else {
        writePinLow(MAC_PIN);
    }
    return true;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    gpio_set_pin_output(MAC_PIN);
    gpio_write_pin_high(MAC_PIN);
}
