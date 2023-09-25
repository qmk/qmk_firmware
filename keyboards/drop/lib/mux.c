// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include "keyboard.h"
#include "analog.h"
#include "gpio.h"
#include "wait.h"

#define S_UP        B12
#define E_UP_N      B13
#define S_DN1       B14
#define E_DN1_N     B15
#define E_VBUS_1    A8
#define E_VBUS_2    A15
#define SRC_1       B8
#define SRC_2       B9
#define HUB_RESET_N D2
#define IRST        B1
#define SDB_N       B2
#define C1_A5_SENSE A4
#define C1_B5_SENSE A7
#define C2_A5_SENSE C4
#define C2_B5_SENSE B0

static inline void digital_write(pin_t pin, uint8_t level) {
    setPinOutput(pin);
    writePin(pin, level);
}

uint16_t v_con_1 = 0;
uint16_t v_con_2 = 0;
uint16_t v_con_3 = 0;
uint16_t v_con_4 = 0;

void keyboard_USB_enable(void) {
    // initial state
    digital_write(S_UP, 0);
    digital_write(E_UP_N, 1);
    digital_write(S_DN1, 1);
    digital_write(E_DN1_N, 1);
    digital_write(E_VBUS_1, 0);
    digital_write(E_VBUS_2, 0);
    digital_write(SRC_1, 1);
    digital_write(SRC_2, 1);

    setPinInput(C1_A5_SENSE);
    setPinInput(C1_B5_SENSE);
    setPinInput(C2_A5_SENSE);
    setPinInput(C2_B5_SENSE);

    // reset hub
    digital_write(HUB_RESET_N, 0);
    wait_ms(100);
    digital_write(HUB_RESET_N, 1);

    wait_ms(500); // Allow power dissipation time on CC lines

    v_con_1 = analogReadPin(C1_A5_SENSE);
    v_con_2 = analogReadPin(C1_B5_SENSE);
    v_con_3 = analogReadPin(C2_A5_SENSE);
    v_con_4 = analogReadPin(C2_B5_SENSE);

    // TODO: dynamic port port configure logic?
    digital_write(E_UP_N, 0);   // HOST enable
    digital_write(E_DN1_N, 0);  // EXTRA enable
    digital_write(E_VBUS_1, 1); // USBC-1 enable full power I/O
    digital_write(E_VBUS_2, 1); // USBC-2 enable full power I/O

    if ((v_con_1 + v_con_2) > (v_con_3 + v_con_4)) {
        digital_write(S_UP, 0);  // HOST to USBC-1
        digital_write(S_DN1, 1); // EXTRA to USBC-2
        digital_write(SRC_1, 1); // HOST on USBC-1
        digital_write(SRC_2, 0); // EXTRA available on USBC-2
    } else {
        digital_write(S_UP, 1);  // EXTRA to USBC-1
        digital_write(S_DN1, 0); // HOST to USBC-2
        digital_write(SRC_1, 0); // EXTRA available on USBC-1
        digital_write(SRC_2, 1); // HOST on USBC-2
    }
}

void keyboard_ISSI_enable(void) {
#ifdef RGB_MATRIX_ENABLE
    digital_write(IRST, 0);
    digital_write(SDB_N, 1);
#endif
}


void keyboard_pre_init_kb(void) {
    keyboard_USB_enable();
    keyboard_ISSI_enable();

    keyboard_pre_init_user();
}
