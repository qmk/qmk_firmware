#include "quantum.h"

#ifndef MATRIX_IO_DELAY_DEFAULT
/* In tmk_core/common/wait.h, the implementation for PROTOCOL_CHIBIOS
 * calls 'chThdSleepMicroseconds(1)' when 'wait_us(0)'.
 * However, 'wait_us(0)' should do nothing. */
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
#    if !defined(MATRIX_IO_DELAY) || MATRIX_IO_DELAY > 0
    matrix_io_delay();
#    endif
}
#endif
