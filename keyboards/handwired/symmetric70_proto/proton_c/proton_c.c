#include "quantum.h"

void matrix_output_unselect_delay(void) {
#if MATRIX_IO_DELAY > 0
    wait_us(MATRIX_IO_DELAY);
#endif
}
