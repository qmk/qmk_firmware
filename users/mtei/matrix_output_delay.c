// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

// The implementation of wait_cpuclock(n) in platforms/chibios/_wait.h has an upper bound on the value of the argument.
// The following implementation of wait_cpuclock_local() bypasses that limitation.

static void wait_cpuclock_local(unsigned int n) {
    unsigned int l = n / 128;
    n &= (128-1);
    for (; l > 0; l--) {
        wait_cpuclock(128);
    }
    wait_cpuclock(n);
}

static void wait_us_local(unsigned int n) {
    wait_cpuclock_local(n * (CPU_CLOCK / 1000000L));
}

void matrix_output_select_delay(void) {
    wait_cpuclock_local(GPIO_INPUT_PIN_DELAY);
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
#ifdef MATRIX_UNSELECT_DELAY_ONDEMAND
     if (!key_pressed) {
         /* If none of the keys are pressed,
          *  there is no need to wait for time for the next line. */
         return;
     }
#endif
     /* In platforms/chibios/_wait.h, the implementation for PROTOCOL_CHIBIOS
      * calls 'chThdSleepMicroseconds(1)' when 'wait_us(0)'.
      * However, 'wait_us(0)' should do nothing. */
     if (MATRIX_IO_DELAY > 0) {
         wait_us_local(MATRIX_IO_DELAY);
     }
}
