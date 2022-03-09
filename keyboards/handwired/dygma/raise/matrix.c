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
#include "wire-protocol-constants.h"

// shifting << 1 is because drivers/chibios/i2c_master.h expects the address
// shifted.
// 0x58 and 0x59 are the addresses defined in dygma/raise/Hand.h
#define I2C_ADDR_LEFT (0x58 << 1)
#define I2C_ADDR_RIGHT (0x59 << 1)
#define I2C_ADDR(hand) ((hand) ? I2C_ADDR_RIGHT : I2C_ADDR_LEFT)
#define LEFT 0
#define RIGHT 1

/* If no key events have occurred, the scanners will time out on reads.
 * So we don't want to be too permissive here. */
// TODO(ibash) not convinced this is needed...
#define MY_I2C_TIMEOUT 10
#define ROWS_PER_HAND (MATRIX_ROWS / 2)

typedef enum { CHANGED, OFFLINE, UNCHANGED } read_hand_t;

static read_hand_t last_state[2] = {OFFLINE, OFFLINE};

static read_hand_t i2c_read_hand(int hand, matrix_row_t current_matrix[]) {
    // dygma raise firmware says online is true iff we get the number of
    // expected bytes (e.g. 6 bytes or ROWS_PER_HAND + 1).
    // In the case where no keys are pressed the keyscanner will send the same 0
    // byte over and over. -- so this case is set.
    //
    // On the stm32 side if we don't get as many bytes as expecetd the
    // i2c_receive times out -- so online can be defined as getting
    // "I2C_STATUS_SUCCESS".

    uint8_t      buf[ROWS_PER_HAND + 1];
    i2c_status_t ret = i2c_receive(I2C_ADDR(hand), buf, sizeof(buf), MY_I2C_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        return OFFLINE;
    }

    if (buf[0] != TWI_REPLY_KEYDATA) {
        return UNCHANGED;
    }

    int           start_row = hand ? ROWS_PER_HAND : 0;
    matrix_row_t *out       = &current_matrix[start_row];
    memcpy(out, &buf[1], ROWS_PER_HAND);

    return CHANGED;
}

static int i2c_set_keyscan_interval(int hand, int delay) {
    uint8_t      buf[] = {TWI_CMD_KEYSCAN_INTERVAL, delay};
    i2c_status_t ret   = i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), MY_I2C_TIMEOUT);
    return ret;
}

void matrix_init_custom(void) {
    i2c_init();

    // ref: https://github.com/Dygmalab/Kaleidoscope/blob/7bac53de106c42ffda889e6854abc06cf43a3c6f/src/kaleidoscope/device/dygma/Raise.cpp#L83
    // ref: https://github.com/Dygmalab/Kaleidoscope/blob/7bac53de106c42ffda889e6854abc06cf43a3c6f/src/kaleidoscope/device/dygma/raise/Hand.cpp#L73
    i2c_set_keyscan_interval(LEFT, 50);
    i2c_set_keyscan_interval(RIGHT, 50);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // HACK(ibash) without the delay between the two calls to i2c_read_hand, the
    // second call to i2c_read_hand breaks. I observed that the i2s start isn't
    // sent, or maybe it is, but the address matcher in the attiny can't recognize
    // it. In any case, a short delay fixes it.
    read_hand_t left_state = i2c_read_hand(LEFT, current_matrix);
    wait_us(10);
    read_hand_t right_state = i2c_read_hand(RIGHT, current_matrix);


    if ((last_state[LEFT] == OFFLINE && left_state != OFFLINE) || (last_state[RIGHT] == OFFLINE && right_state != OFFLINE)) {
        // reinitialize both sides
        i2c_set_keyscan_interval(LEFT, 50);
        i2c_set_keyscan_interval(RIGHT, 50);
    }

    last_state[LEFT]  = left_state;
    last_state[RIGHT] = right_state;

    bool matrix_has_changed = left_state == CHANGED || right_state == CHANGED;

    return matrix_has_changed;
}
