// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "tex_hw.h"

static void iap_reset(void) {
    *(volatile uint32_t *)IAP_MAGIC_ADDR = IAP_MAGIC_VALUE;
    usbDisconnectBus(&USBD1);
    wait_ms(30);
    __disable_irq();
    NVIC_SystemReset();
}

void bootloader_jump(void) {
    iap_reset();
}

void mcu_reset(void) {
    __disable_irq();
    NVIC_SystemReset();
}

#ifdef VIA_ENABLE
// VIA's protocol has no bootloader command; flashing tools send SHURA_RAW_IAP 00.
bool via_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] == SHURA_RAW_IAP && data[1] == 0) {
        iap_reset();
    }
    return false;
}
#endif
