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
        last_read = timer_read32();
        switch (usbpd_get_allowance()) {
            case USBPD_500MA:
                if (kb_state.current_setting != USBPD_500MA) {
                    dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(kb_state.current_setting), usbpd_str(USBPD_500MA));
                    kb_state.current_setting = USBPD_500MA;
                }
                break;
            case USBPD_1500MA:
                if (kb_state.current_setting != USBPD_1500MA) {
                    dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(kb_state.current_setting), usbpd_str(USBPD_1500MA));
                    kb_state.current_setting = USBPD_1500MA;
                }
                break;
            case USBPD_3000MA:
                if (kb_state.current_setting != USBPD_3000MA) {
                    dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(kb_state.current_setting), usbpd_str(USBPD_3000MA));
                    kb_state.current_setting = USBPD_3000MA;
                }
                break;
        }
    }
}