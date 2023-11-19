// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <string.h>
#include "quantum.h"
#include "djinn.h"

const char* usbpd_str(usbpd_allowance_t allowance) {
    switch (allowance) {
        default:
        case USBPD_500MA:
            return "500mA";
        case USBPD_1500MA:
            return "1500mA";
        case USBPD_3000MA:
            return "3000mA";
    }
}

void usbpd_update(void) {
    static uint32_t last_read = 0;
    if (timer_elapsed32(last_read) > 250) {
        usbpd_allowance_t allowance = usbpd_get_allowance();
        if (kb_state.current_setting != allowance) {
            dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(kb_state.current_setting), usbpd_str(allowance));
            kb_state.current_setting = allowance;
        }
    }
}
