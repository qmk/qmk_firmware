// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "gpio.h"
#include "wait.h"
#include "string.h"

#define SNES_CLOCK GP0
#define SNES_LATCH GP1
#define SNES_D0 GP2
#define SNES_D1 GP3
#define SNES_IO GP4

#define KBD_ROW0 GP24
#define KBD_ROW1 GP23
#define KBD_ROW2 GP22
#define KBD_NUM_ROWS 3

#define KBD_COL0 GP18
#define KBD_COL1 GP19
#define KBD_COL2 GP20
#define KBD_COL3 GP21
#define KBD_ROW_SETUP_DELAY_US 5

// The real snes will clock 16 bits out of the controller, but only really has 12 bits of data
#define SNES_DATA_BITS 16
#define SNES_DATA_SETUP_DELAY_US 10
#define SNES_CLOCK_PULSE_DURATION 10

static const int kbd_pin_map[] = {
    KBD_ROW0,
    KBD_ROW1,
    KBD_ROW2
};

void matrix_init_custom(void) {
    // init snes controller
    gpio_set_pin_input_high(SNES_D0);
    // todo: look into protocol for other strange snes controllers that use D1 and IO
    // gpio_set_pin_input_high(SNES_D1);
    // gpio_set_pin_input_high(SNES_IO);
    gpio_set_pin_output(SNES_CLOCK);
    gpio_set_pin_output(SNES_LATCH);
    gpio_write_pin_low(SNES_CLOCK);
    gpio_write_pin_low(SNES_LATCH);

    // init rows
    gpio_set_pin_output(KBD_ROW0);
    gpio_set_pin_output(KBD_ROW1);
    gpio_set_pin_output(KBD_ROW2);
    gpio_write_pin_high(KBD_ROW0);
    gpio_write_pin_high(KBD_ROW1);
    gpio_write_pin_high(KBD_ROW2);

    // init columns
    gpio_set_pin_input_high(KBD_COL0);
    gpio_set_pin_input_high(KBD_COL1);
    gpio_set_pin_input_high(KBD_COL2);
    gpio_set_pin_input_high(KBD_COL3);
}

static matrix_row_t readRow(size_t row, int setupDelay) {
    const int pin = kbd_pin_map[row];

    // select the row
    gpio_set_pin_output(pin);
    gpio_write_pin_low(pin);
    wait_us(setupDelay);

    // read the column data
    const matrix_row_t ret =
          (gpio_read_pin(KBD_COL0) ? 0 : 1 << 0)
        | (gpio_read_pin(KBD_COL1) ? 0 : 1 << 1)
        | (gpio_read_pin(KBD_COL2) ? 0 : 1 << 2)
        | (gpio_read_pin(KBD_COL3) ? 0 : 1 << 3);

    // deselect the row
    gpio_set_pin_output(pin);
    gpio_write_pin_high(pin);

    return ret;
}

static void readKeyboard(matrix_row_t current_matrix[]) {
    for (size_t row = 0; row < KBD_NUM_ROWS; ++row) {
        current_matrix[row] = readRow(row, KBD_ROW_SETUP_DELAY_US);
    }
}

static matrix_row_t getBits(uint16_t value, size_t bit0, size_t bit1, size_t bit2, size_t bit3) {
    matrix_row_t ret = 0;
    ret |= (value >> bit3) & 1;
    ret <<= 1;
    ret |= (value >> bit2) & 1;
    ret <<= 1;
    ret |= (value >> bit1) & 1;
    ret <<= 1;
    ret |= (value >> bit0) & 1;
    return ret;
}

static void readSnesController(matrix_row_t current_matrix[]) {
    uint16_t controller = 0;

    gpio_write_pin_high(SNES_LATCH);

    for (size_t bit = 0; bit < SNES_DATA_BITS; ++bit) {
        // Wait for shift register to setup the data line
        wait_us(SNES_DATA_SETUP_DELAY_US);

        // Shift accumulated data and read data pin
        controller <<= 1;
        controller |= gpio_read_pin(SNES_D0) ? 0 : 1;
        // todo: maybe read D1 and IO here too

        // Shift next bit in
        gpio_write_pin_high(SNES_CLOCK);
        wait_us(SNES_CLOCK_PULSE_DURATION);
        gpio_write_pin_low(SNES_CLOCK);
    }

    gpio_write_pin_low(SNES_LATCH);

    controller >>= 4;

    // SNES button order is pretty random, and we'd like them to be a bit tidier
    current_matrix[3] = getBits(controller, 1, 0, 8, 9);
    current_matrix[4] = getBits(controller, 7, 6, 5, 4);
    current_matrix[5] = getBits(controller, 3, 11, 2, 10);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    const size_t MATRIX_ARRAY_SIZE = MATRIX_ROWS * sizeof(matrix_row_t);

    // create a copy of the current_matrix, before we read hardware state
    matrix_row_t last_value[MATRIX_ROWS];
    memcpy(last_value, current_matrix, MATRIX_ARRAY_SIZE);

    // read hardware state into current_matrix
    readKeyboard(current_matrix);
    readSnesController(current_matrix);

    // check if anything changed
    return memcmp(last_value, current_matrix, MATRIX_ARRAY_SIZE) != 0;
}
