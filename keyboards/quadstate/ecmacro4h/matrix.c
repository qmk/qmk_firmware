// Copyright 2026 QuadState (@QuadState)
// SPDX-License-Identifier: GPL-2.0-or-later

// Lite custom matrix with a single row. The keys are measured one at a time
// (rc_pio.c): each scan checks whether the current measurement has
// finished, updates that key and starts the next one.

#include "ecmacro4h.h"
#include "rc_pio.h"

STATIC_ASSERT(MATRIX_ROWS == 1, "The ECmacro 4H keys form a single row");

static const pin_t sensor_pins[EC_KEY_COUNT] = EC_GPIO_PINS;

static uint8_t      current_key; // The key being measured
static matrix_row_t pressed;     // Keys that read pressed

static void record(uint8_t key, uint16_t ticks) {
    const matrix_row_t bit = (matrix_row_t)1 << key;

    ec_baseline_sample(key, ticks);

    // A failed measurement (0 ticks) counts as released. Between the two
    // thresholds the key keeps its state (hysteresis).
    if (ticks <= ec_release_threshold(key)) {
        pressed &= ~bit;
    } else if (ticks >= ec_press_threshold(key)) {
        pressed |= bit;
    }
}

void matrix_init_custom(void) {
    rc_pio_init();
    rc_pio_start(sensor_pins[current_key]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    uint16_t ticks;

    if (rc_pio_poll(&ticks)) {
        record(current_key, ticks);
        current_key = (current_key + 1) % EC_KEY_COUNT;
        rc_pio_start(sensor_pins[current_key]);
    }

    const bool changed = current_matrix[0] != pressed;
    current_matrix[0]  = pressed;
    return changed;
}
