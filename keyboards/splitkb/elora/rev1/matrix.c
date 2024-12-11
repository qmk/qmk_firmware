// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "spi_master.h"

// The matrix is hooked up to a chain of 74xx165 shift registers.
// Pin F0 acts as Chip Select (active-low)
// The signal goes to a NOT gate, whose output is wired to
// a) the latch pin of the shift registers
// b) the "enable" pin of a tri-state buffer,
//    attached between the shift registers and MISO
// F0 has an external pull-up.
// SCK works as usual.
//
// Note that the matrix contains a variety of data.
// In addition to the keys, it also reads the rotary encoders
// and whether the board is the left/right half.

void matrix_init_custom(void) {
    // Note: `spi_init` has already been called
    // in `keyboard_pre_init_kb()`, so nothing to do here
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // Enough to hold the shift registers
    uint16_t length = 5;
    uint8_t  data[length];

    // Matrix SPI config
    // 1) Pin
    // 2) Mode: Register shifts on rising clock, and clock idles low
    //      pol = 0 & pha = 0 => mode 0
    // 3) LSB first: Register outputs H first, and we want H as MSB,
    //      as this result in a neat A-H order in the layout macro.
    // 4) Divisor: 2 is the fastest possible, at Fclk / 2.
    //      range is 2-128
    spi_start(GP13, false, 0, 128);
    spi_receive(data, length);
    spi_stop();

    bool matrix_has_changed = false;
    for (uint8_t i = 0; i < length; i++) {
        // Bitwise NOT because we use pull-ups,
        // and switches short the pin to ground,
        // but the matrix uses 1 to indicate a pressed switch
        uint8_t word = ~data[i];
        matrix_has_changed |= current_matrix[i] ^ word;
        current_matrix[i] = word;
    }
#ifdef MYRIAD_ENABLE
    bool myriad_hook_matrix(matrix_row_t current_matrix[]);
    return matrix_has_changed || myriad_hook_matrix(current_matrix);
#else
    return matrix_has_changed;
#endif
}