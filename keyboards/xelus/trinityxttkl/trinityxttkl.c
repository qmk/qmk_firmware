#include "trinityxttkl.h"

// Tested and verified working on Trinity XT TKL
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }
