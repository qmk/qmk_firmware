// Copyright 2022 YANG (YDKB)
// Copyright 2026 Laszlo Toth (@laszloth)
// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Athena 1800 custom matrix (CUSTOM_MATRIX = lite).
 * The keys are read one-at-a-time through a serial shift-register
 * "switch board": a single select bit is clocked through all
 * MATRIX_ROWS*MATRIX_COLS positions and the SDI line is read back per
 * position. Ported from the YDKB firmware, stripped of the
 * dual-core/display/eeprom coupling; QMK handles debounce.
 */
#include "matrix.h"
#include "gpio.h"
#include "wait.h"

#define KEY_SCK_PIN GP6 /* shift clock */
/* serial data out (select) AND key read-back line */
#define KEY_SDI_PIN GP7

static inline void key_sdi_off(void) {
    gpio_write_pin_low(KEY_SDI_PIN);
}
static inline void key_sdi_on(void) {
    gpio_write_pin_high(KEY_SDI_PIN);
}

/* switch SDI line to input pull-up so the selected key can be read */
static inline void get_key_ready(void) {
    gpio_write_pin_high(KEY_SDI_PIN);
    wait_us(2);
    gpio_set_pin_input_high(KEY_SDI_PIN);
    wait_us(6);
}

/* switch SDI line back to push-pull output to shift the select bit */
static inline void select_key_ready(void) {
    gpio_set_pin_output(KEY_SDI_PIN);
}

#define CLOCK_PULSE()                     \
    do {                                  \
        gpio_write_pin_high(KEY_SCK_PIN); \
        __asm__ volatile("nop");          \
        gpio_write_pin_low(KEY_SCK_PIN);  \
    } while (0)

static bool get_key(void) {
    return !gpio_read_pin(KEY_SDI_PIN); /* pressed pulls the line low */
}

static void select_key(uint8_t mode) {
    select_key_ready();
    if (mode == 0) {
        /* reset: flush the register, then load a single select bit */
        key_sdi_off();
        for (uint8_t i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
            CLOCK_PULSE();
        }
        key_sdi_on();
        CLOCK_PULSE();
    } else {
        /* advance the select bit by one position */
        key_sdi_off();
        CLOCK_PULSE();
    }
    get_key_ready();
}

void matrix_init_custom(void) {
    gpio_set_pin_output(KEY_SCK_PIN);
    gpio_set_pin_output(KEY_SDI_PIN);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    select_key(0);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t value = 0;
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (get_key()) {
                value |= ((matrix_row_t)1 << col);
            }
            select_key(1);
        }
        if (current_matrix[row] != value) {
            current_matrix[row] = value;
            changed             = true;
        }
    }

    return changed;
}
