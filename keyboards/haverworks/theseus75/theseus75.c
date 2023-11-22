// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "transactions.h"
#include <stdio.h>
#include "print.h"

void keyboard_pre_init_kb(void) {
    // Disable the PD peripheral in pre-init because its pins are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_pre_init_user();
    // Customise these values to desired behaviour:
    debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}

void keyboard_post_init_kb(void) {
    // If the keyboard is master
    if (is_keyboard_master()) {
        // Turn on power to the split half and to underglow LEDs
        setPinOutput(A15);      // PSW
        writePinHigh(A15);

        // Enable inputs used for current negotiation
        setPinInputHigh(F0);    // OUT1
        setPinInputHigh(F1);    // OUT2


        // Not needed in this mode (always high-Z with pull-up on PCB if port controller is sink)
        setPinInputHigh(A13);   // ID
    } else {
        // Prepare output to enable power for USB output after negotiation
        setPinOutput(A15);      // PSW

        // Switch the USB MUXes between hub and ports
        setPinOutput(A14);      // USBSW
        writePinHigh(A14);

        // Enable outputs used for current negotiation
        setPinOutput(F0);       // OUT1
        setPinOutput(F1);       // OUT2

        // For now: 500 mA only
        writePinLow(F0);
        writePinLow(F1);

        // Use ID pin to check if client is detected (if low: USB source port powered)
        setPinInputHigh(A13);

        // Set BUS_B low to indicate a bus-powered hub (Test)
        setPinOutput(C13);      // BUS_B
        writePinHigh(C13);
    }
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_post_init_user();
}

// Todo: Insert timer based delay to avoid spamming pin reads/writes, only set on pin change
void housekeeping_task_kb(void) {
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    housekeeping_task_user();

    static uint32_t usbcpd_timer = 0;
    if (timer_elapsed32(usbcpd_timer) > USBCPD_TIMESPAN) {
        // On master side: check F0 and F1 to determine current negotiated with host
        if (is_keyboard_master()) {
            bool out1 = readPin(F0);
            bool out2 = readPin(F1);
            uint8_t host_current = 0;    // 0: 500 mA, 1: 1500 mA, 2:3000 mA

            if (out1 == 1) {
                host_current = 0;
                printf("Host negotiated current: 500 mA\n");
            } else if (out2 == 1) {
                host_current = 1;
                printf("Host negotiated current: 1500 mA\n");
            } else {
                host_current = 2;
                printf("Host negotiated current: 3000 mA\n");
            };
            printf("Host current variable: %d\n", host_current);
        } else {
            printf("Im slave, you shouldn't see this\n");
            // On peripheral side - If A13 is low: USB client negotiated 5V successfully -> enable power routing
            // Check if A15 is not already high to avoid wasting time
            if(!readPin(A13) && !readPin(A15)) {
                writePinHigh(A15);
                printf("USB downstream device detected\n");
            };
        };
        usbcpd_timer = timer_read32();
    };
}
