/*
Copyright 2011 Jun Wako <wakojun@gmail.com>
Copyright 2020 Kan-Ru Chen <kanru@kanru.info>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "matrix.h"
#include "debug.h"
#include "timer.h"
#include "wait.h"
#include "suspend.h"
#include <avr/interrupt.h>

#ifdef BLUETOOTH_ENABLE
#    include "adafruit_ble.h"
#endif

#define RELAX_TIME_US 5
#define ADC_READ_TIME_US 5

uint8_t power_save_level;

static uint32_t matrix_last_modified = 0;

static inline void key_strobe_high(void) { gpio_write_pin_low(B6); }
static inline void key_strobe_low(void) { gpio_write_pin_high(B6); }
static inline bool key_state(void) { return gpio_read_pin(D7); }
static inline void key_prev_on(void) { gpio_write_pin_high(B7); }
static inline void key_prev_off(void) { gpio_write_pin_low(B7); }
static inline bool key_power_state(void) { return !gpio_read_pin(D6); }

static inline void suspend_power_down_longer(void) {
    uint8_t times = 60;
    while (--times) suspend_power_down();
}

void matrix_power_up(void) {
    dprint("[matrix_on]\n");
    // change pins output
    DDRB  = 0xFF;
    PORTB = 0x40;
    // switch MOS FET on
    gpio_set_pin_output(D6);
    gpio_write_pin_low(D6);
}

void matrix_power_down(void) {
    dprint("[matrix_off]\n");
    // input with pull-up consumes less than without it when pin is open
    DDRB  = 0x00;
    PORTB = 0xFF;
    // switch MOS FET off
    gpio_set_pin_output(D6);
    gpio_write_pin_high(D6);
}

static inline void key_select_row(uint8_t row) { PORTB = (PORTB & 0b11111000) | ((row)&0b111); }
static inline void key_select_col(uint8_t col) { PORTB = (PORTB & 0b11000111) | (((col)&0b111) << 3); }
static inline bool key_prev_was_on(matrix_row_t matrix[], uint8_t row, uint8_t col) { return matrix[row] & (1 << col); }

void matrix_init_custom(void) { power_save_level = 0; }

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // power on
    if (!key_power_state()) {
        matrix_power_up();
    }
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t last_row_value = current_matrix[row];

        key_select_row(row);
        wait_us(RELAX_TIME_US);

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // Hysteresis control: assert(1) when previous key state is on
            if (key_prev_was_on(current_matrix, row, col)) {
                key_prev_on();
            } else {
                key_prev_off();
            }

            // Disable interrupts to encure the ADC timing is correct
            cli();

            // strobe
            key_select_col(col);
            key_strobe_high();

            // Wait for ADC to outputs its value.
            // 1us was ok on one HHKB, but not worked on another.
            // no   wait doesn't work on Teensy++ with pro(1us works)
            // no   wait does    work on tmk PCB(8MHz) with pro2
            // 1us  wait does    work on both of above
            // 1us  wait doesn't work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz/2)
            // 5us  wait does    work on tmk(8MHz)
            // 10us wait does    work on Teensy++ with pro
            // 10us wait does    work on 328p+iwrap with pro
            // 10us wait doesn't work on tmk PCB(8MHz) with pro2(very lagged scan)
            wait_us(ADC_READ_TIME_US);

            if (key_state()) {
                current_matrix[row] &= ~(1 << col);
            } else {
                current_matrix[row] |= (1 << col);
            }

            key_strobe_low();
            sei();

            // Make sure enough time has elapsed since the last call
            // This is to ensure the matrix voltages have relaxed
            wait_us(RELAX_TIME_US);
        }
        if (current_matrix[row] ^ last_row_value) {
            matrix_has_changed   = true;
            matrix_last_modified = timer_read32();
        }
    }

    // Power saving
    uint32_t time_diff = timer_elapsed32(matrix_last_modified);
    if (time_diff > MATRIX_POWER_SAVE_TIMEOUT_L3_MS) {
        power_save_level = 3;
        suspend_power_down_longer();
    } else if (time_diff > MATRIX_POWER_SAVE_TIMEOUT_L2_MS) {
        power_save_level = 2;
#ifdef BLUETOOTH_ENABLE
        if (!adafruit_ble_is_connected()) {
            power_save_level = 3;
        }
#endif
        suspend_power_down_longer();
    } else if (time_diff > MATRIX_POWER_SAVE_TIMEOUT_MS) {
        power_save_level = 1;
        suspend_power_down();
    } else {
        if (power_save_level != 0) {
            power_save_level = 0;
            suspend_wakeup_init();
        }
    }

    return matrix_has_changed;
}

bool adafruit_ble_delbonds(void);
bool adafruit_ble_reconnect(void);

bool command_extra(uint8_t code) {
    switch (code) {
#ifdef BLUETOOTH_ENABLE
        case KC_R:
            adafruit_ble_delbonds();
            return true;
        case KC_S:
            adafruit_ble_reconnect();
            return true;
#endif
        default:
            return false;
    }
}
