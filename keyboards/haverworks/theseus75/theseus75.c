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
        setPinInputHigh(F0);
        setPinInputHigh(F1);

        // Not needed in this mode (always high-Z with pull-up on PCB if port controller is sink)
        setPinInputHigh(A13);
    } else {
        // Prepare output to enable power for USB output after negotiation
        setPinOutput(A15);

        // Switch the USB MUXes between hub and ports
        setPinOutput(A14);
        writePinHigh(A14);

        // Enable outputs used for current negotiation
        setPinOutput(F0);
        setPinOutput(F1);

        // For now: 500 mA only
        writePinLow(F0);
        writePinLow(F1);

        // Use ID pin to check if client is detected (if low: USB source port powered)
        setPinInputHigh(A13);
    }
}

// Todo: Insert timer based delay to avoid spamming pin reads/writes, only set on pin change
void housekeeping_task_kb(void) {
    // On peripheral side - If A14 is low: USB client negotiated 5V successfully -> enable power routing
    if (!is_keyboard_master()) {
        if(!readPin(A13)) {
            writePinHigh(A15);
        }
    }
}
