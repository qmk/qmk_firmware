// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "analog.h"
#include "spi_master.h"

void keyboard_post_init_kb(void) {
    // Enable RGB current limiter and wait for a bit before allowing RGB to continue
    gpio_set_pin_output(RGB_ENABLE_PIN);
    gpio_write_pin_high(RGB_ENABLE_PIN);
    wait_ms(20);

    // Offload to the user func
    keyboard_post_init_user();
}

void matrix_init_custom(void) {
    // SPI Matrix
    gpio_set_pin_output(SPI_MATRIX_CHIP_SELECT_PIN);
    gpio_write_pin_high(SPI_MATRIX_CHIP_SELECT_PIN);
    spi_init();

    // Encoder pushbutton
    gpio_set_pin_input_low(ENCODER_PUSHBUTTON_PIN);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    // Read from SPI the matrix
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN, false, 0, SPI_MATRIX_DIVISOR);
    spi_receive((uint8_t*)temp_matrix, MATRIX_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
    spi_stop();

    // Read from the encoder pushbutton
    temp_matrix[5] = gpio_read_pin(ENCODER_PUSHBUTTON_PIN) ? 1 : 0;

    // Check if we've changed, return the last-read data
    bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return changed;
}
