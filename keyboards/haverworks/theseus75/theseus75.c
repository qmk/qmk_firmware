// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
}
void keyboard_post_init_kb(void) {
    // If the keyboard is master
    if (is_keyboard_master()) {
        // Turn on power to the split half and to underglow LEDs
        setPinOutput(A15);
        writePinHigh(A15);

        // Enable inputs used for current negotiation
        setPinInput(F0);
        setPinInput(F1);

        // Not needed in this mode (always high-Z with pull-up on PCB if port controller is sink)
        setPinInput(A14);
    } else {
        // Do not turn on power to the USB source port (let the port controller handle VBUS)
        setPinOutput(A15);
        //writePinHigh(A15);

        // Disable the hub, route USB from split con to USB connector for downstream port
        setPinOutput(A13);
        writePinHigh(A13);

        // Enable outputs used for current negotiation
        setPinOutput(F0);
        setPinOutput(F1);

        // For now: 500 mA only
        writePinLow(F0);
        writePinLow(F1);

        // Use ID pin to check if client is detected (if low: USB source port powered)
        setPinInput(A14);
    };
}