// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_ortho_1x1(KC_A)};

#if defined(__AVR__)
#    pragma message "AVR uses polled waiting by default, running theses tests will not show any difference"
static inline void chThdSleepMicroseconds(uint32_t us) {
    wait_us(us);
}
#endif

void keyboard_post_init_user(void) {
    gpio_set_pin_output(QMK_WAITING_TEST_BUSY_PIN);
    gpio_set_pin_output(QMK_WAITING_TEST_YIELD_PIN);
}

static inline void wait_us_polling_with_strobe(uint32_t us) {
    gpio_write_pin_high(QMK_WAITING_TEST_BUSY_PIN);
    wait_us(us);
    gpio_write_pin_low(QMK_WAITING_TEST_BUSY_PIN);
}

static inline void wait_us_yield_with_strobe(uint32_t us) {
    gpio_write_pin_high(QMK_WAITING_TEST_YIELD_PIN);
    chThdSleepMicroseconds(us);
    gpio_write_pin_low(QMK_WAITING_TEST_YIELD_PIN);
}

static const uint32_t waiting_values[] = {0, 1, 5, 10, 25, 50, 100, 150, 200, 500, 1000};

void housekeeping_task_user(void) {
    static uint32_t last_bench = 0;
    if (timer_elapsed32(last_bench) > 500) {
        for (int i = 0; i < ARRAY_SIZE(waiting_values); i++) {
            wait_us_polling_with_strobe(waiting_values[i]);
            wait_us(10);
        }
        for (int i = 0; i < ARRAY_SIZE(waiting_values); i++) {
            wait_us_yield_with_strobe(waiting_values[i]);
            wait_us(10);
        }
        last_bench = timer_read32();
    }
}
