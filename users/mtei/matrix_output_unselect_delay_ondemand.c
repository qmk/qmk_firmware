// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
     if (!key_pressed) {
         /* If none of the keys are pressed,
          *  there is no need to wait for time for the next line. */
         return;
     }
     /* In platforms/chibios/_wait.h, the implementation for PROTOCOL_CHIBIOS
      * calls 'chThdSleepMicroseconds(1)' when 'wait_us(0)'.
      * However, 'wait_us(0)' should do nothing. */
     if (MATRIX_IO_DELAY > 0) {
         wait_us(MATRIX_IO_DELAY);
     }
}
