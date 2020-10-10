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

#include "quantum.h"
#include "lufa.h"

// matrix power saving
#define MATRIX_POWER_SAVE 10000
static uint32_t matrix_last_modified = 0;

// matrix state buffer(1:on, 0:off)
static matrix_row_t *matrix;
static matrix_row_t *matrix_prev;
static matrix_row_t  _matrix0[MATRIX_ROWS];
static matrix_row_t  _matrix1[MATRIX_ROWS];

static inline void key_enable(void) { writePinLow(B6); }
static inline void key_unable(void) { writePinHigh(B6); }
static inline bool key_state(void) { return readPin(D7); }
static inline void key_prev_on(void) { writePinHigh(B7); }
static inline void key_prev_off(void) { writePinLow(B7); }
static inline bool key_power_state(void) { return true; }
static inline void key_power_on(void) {}
static inline void key_power_off(void) {}

static inline void key_select(uint8_t row, uint8_t col) { PORTB = (PORTB & 0xC0) | (((col)&0x07) << 3) | ((row)&0x07); }
static inline bool key_prev_was_on(uint8_t row, uint8_t col) { return matrix_prev[row] & (1 << col); }

void matrix_init(void) {
    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix      = _matrix0;
    matrix_prev = _matrix1;
    matrix_last_modified = timer_read32();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool matrix_has_changed = false;

    matrix_row_t *tmp;

    tmp         = matrix_prev;
    matrix_prev = matrix;
    matrix      = tmp;

    // power on
    if (!key_power_state()) {
        key_power_on();
    }
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            key_select(row, col);
            wait_us(5);

            // Hysteresis control: assert(1) when previous key state is on
            if (key_prev_was_on(row, col)) {
                key_prev_on();
            }
            wait_us(10);

            // NOTE: KEY_STATE is valid only in 20us after KEY_ENABLE.
            // If V-USB interrupts in this section we could lose 40us or so
            // and would read invalid value from KEY_STATE.
            uint8_t last = TIMER_RAW;

            key_enable();

            // Wait for KEY_STATE outputs its value.
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
            wait_us(5);

            if (key_state()) {
                matrix[row] &= ~(1 << col);
            } else {
                matrix[row] |= (1 << col);
            }

            // Ignore if this code region execution time elapses more than 20us.
            // MEMO: 20[us] * (TIMER_RAW_FREQ / 1000000)[count per us]
            // MEMO: then change above using this rule: a/(b/c) = a*1/(b/c) = a*(c/b)
            if (TIMER_DIFF_RAW(TIMER_RAW, last) > 20 / (1000000 / TIMER_RAW_FREQ)) {
                matrix[row] = matrix_prev[row];
            }

            wait_us(5);
            key_prev_off();
            key_unable();

            // NOTE: KEY_STATE keep its state in 20us after KEY_ENABLE.
            // This takes 25us or more to make sure KEY_STATE returns to idle state.

            wait_us(75);
        }
        if (matrix[row] ^ matrix_prev[row]) {
            matrix_has_changed   = true;
            matrix_last_modified = timer_read32();
        }
    }
    // power off
    if (key_power_state() && (USB_DeviceState == DEVICE_STATE_Suspended || USB_DeviceState == DEVICE_STATE_Unattached) && timer_elapsed32(matrix_last_modified) > MATRIX_POWER_SAVE) {
        key_power_off();
        suspend_power_down();
    }

    matrix_scan_quantum();

    return matrix_has_changed;
}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: %08b\n", row, bitrev(matrix_get_row(row)));
    }
}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

void matrix_power_up(void) { key_power_on(); }
void matrix_power_down(void) { key_power_off(); }
