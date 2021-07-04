/* Copyright 2018-2021 James Laird-Wah, Islam Sharabash
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"
#include "i2c_master.h"
#include <string.h>
#include "raise.h"

/* If no key events have occurred, the scanners will time out on reads.
 * So we don't want to be too permissive here. */
// TODO(ibash) not convinced this is needed...
#define MY_I2C_TIMEOUT 10

static matrix_row_t rows[MATRIX_ROWS];
#define ROWS_PER_HAND (MATRIX_ROWS / 2)

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

static int i2c_read_hand(int hand) {
    uint8_t      buf[ROWS_PER_HAND + 1];
    i2c_status_t ret = i2c_receive(I2C_ADDR(hand), buf, sizeof(buf), MY_I2C_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        return 1;
    }

    if (buf[0] != TWI_REPLY_KEYDATA) {
        return 2;
    }

    int      start_row = hand ? ROWS_PER_HAND : 0;
    uint8_t *out       = &rows[start_row];
    memcpy(out, &buf[1], ROWS_PER_HAND);

    return 0;
}

static int i2c_set_keyscan_interval(int hand, int delay) {
    uint8_t      buf[] = {TWI_CMD_KEYSCAN_INTERVAL, delay};
    i2c_status_t ret   = i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), MY_I2C_TIMEOUT);
    return ret;
}

void matrix_init(void) {
    i2c_init();

    // ref: https://github.com/Dygmalab/Kaleidoscope/blob/7bac53de106c42ffda889e6854abc06cf43a3c6f/src/kaleidoscope/device/dygma/Raise.cpp#L83
    // ref: https://github.com/Dygmalab/Kaleidoscope/blob/7bac53de106c42ffda889e6854abc06cf43a3c6f/src/kaleidoscope/device/dygma/raise/Hand.cpp#L73
    i2c_set_keyscan_interval(LEFT, 50);
    i2c_set_keyscan_interval(RIGHT, 50);
    memset(rows, 0, sizeof(rows));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // TODO(ibash) set changed = true if the matrix has changed
    bool changed = false;

    // HACK(ibash) without the delay between the two calls to i2c_read_hand, the
    // second call to i2c_read_hand breaks. I observed that the i2s start isn't
    // sent, or maybe it is, but the address matcher in the attiny can't recognize
    // it. In any case, a short delay fixes it.
    i2c_read_hand(LEFT);
    wait_us(10);
    i2c_read_hand(RIGHT);

    matrix_scan_quantum();

    return (uint8_t)changed;
}

inline matrix_row_t matrix_get_row(uint8_t row) { return rows[row]; }

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

void keyboard_post_init_user(void) {
    // for debugging remember to set "CONSOLE_ENABLE = yes" in rules.mk
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}
