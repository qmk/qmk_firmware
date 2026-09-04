// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Custom matrix driver for the Metakey Tenet 70.
 *
 * 5 rows × 18 cols. Two special-case pins:
 *   - Col 14 = PA14 (SWCLK): forced out of SWD alt-fn at init.
 *   - Col 17 = PA11 (USB D-): alt-fn claimed/released around each scan so
 *     the key share doesn't disturb the USB peripheral.
 */

#include "quantum.h"
#include "matrix.h"

// HT32 AFIO registers for pin alt-function control.
#define HT_AFIO_GPACFGHR (*(volatile uint32_t *)0x40022024U)  // PA8-PA15

static const pin_t row_pins[MATRIX_ROWS] = { B8, B7, B6, C3, C2 };

// Col pins 0-16 (GPIO). Col 17 = A11 handled separately.
static const pin_t col_pins_gpio[17] = {
    A6, A7, C4, C5, C8, B13, B14, B15,
    C0, C10, C11, C12, C13, A8, A14, A9, A10
};

#define COL17_PIN A11
#define COL17_IDX 17

static inline void col17_claim(void) {
    HT_AFIO_GPACFGHR &= ~(0xFu << 12);
    gpio_set_pin_input_high(COL17_PIN);
}

static inline void col17_release(void) {
    HT_AFIO_GPACFGHR = (HT_AFIO_GPACFGHR & ~(0xFu << 12)) | (1u << 12);
}

void matrix_init_custom(void) {
    // Force PA13/PA14 out of SWD mode.
    HT_AFIO_GPACFGHR &= ~((0xFu << 20) | (0xFu << 24));

    // Init row pins as GPIO output high (inactive).
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        gpio_set_pin_output(row_pins[r]);
        gpio_write_pin_high(row_pins[r]);
    }

    // Init col pins 0-16 as input pull-up.
    for (uint8_t c = 0; c < 17; c++) {
        gpio_set_pin_input_high(col_pins_gpio[c]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        gpio_set_pin_output(row_pins[r]);
        gpio_write_pin_low(row_pins[r]);

        for (volatile int i = 0; i < 20; i++) {}

        matrix_row_t row_val = 0;
        for (uint8_t c = 0; c < 17; c++) {
            if (!gpio_read_pin(col_pins_gpio[c])) {
                row_val |= (1UL << c);
            }
        }

        // Col 17 (PA11 = USB D-).
        col17_claim();
        for (volatile int i = 0; i < 30; i++) {}
        if (!gpio_read_pin(COL17_PIN)) {
            row_val |= (1UL << COL17_IDX);
        }
        col17_release();

        gpio_write_pin_high(row_pins[r]);

        if (current_matrix[r] != row_val) {
            current_matrix[r] = row_val;
            changed = true;
        }
    }

    return changed;
}
