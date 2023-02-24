// Copyright (c) 2021 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
     /* If none of the keys are pressed,
      *  there is no need to wait for time for the next line. */
     if (key_pressed) {
#    ifdef MATRIX_IO_DELAY
#        if MATRIX_IO_DELAY > 0
         wait_us(MATRIX_IO_DELAY);
#        endif
#    else
         wait_us(30);
#    endif
     }
}
