// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spacemouse_module.h"
#include "pointing_device_internal.h"
#include "uart.h"

// REQUEST_DATA (the important part)
// Function: requests position data from the 3D-Sensor Command: 172 (0xAC)
// Returns: 16 bytes data
// Structure: B1 B2 ... B16
// Byte 1: start-byte 0x96 (150 decimal); every data set starts with this byte Byte 2: high byte of X value
// Byte 3: low byte of X value
// Byte 4: high byte of Y value
// Byte 5: low byte of Y value
// Byte 6: high byte of Z value
// Byte 7: low byte of Z value
// Byte 8: high byte of A value (X rotation) Byte 9: low byte of A value (X rotation) Byte 10: high byte of B value (Y rotation) Byte 11: low byte of B value (Y rotation) Byte 12: high byte of C value (Z rotation) Byte 13: low byte of C value (Z rotation) Byte 14: high byte of Checksum
// Byte 15: low byte of Checksum
// Byte 16: end-byte 0x8D; every response ends with this byte
//
// X, Y, Z, A, B, C values and the Checksum are transmitted as unsigned 14-Bit values. This is due to the fact, that the MSB of payload data is always cleared (logic 0).
// Calculating a value:
// high byte (X) low byte (X)
// 14-bit value (unsigned)
// Xvalue = (high byte (X) * 128 + low byte (X)) - 8192
// Transmitted Checksum:
// Checksumtrans = (high byte (Checksumtrans) * 128 + low byte (Checksumtrans))
// Calculating the Checksum:
// Checksumcalc = (Byte1 + Byte2 + ... + Byte13) & 0x3FFF.
// By masking the Checksum with 0x3FFF (logic AND operation), the value is reduced to a 14-Bit value.
// The value range for X, Y, Z, A, B, C values is -350 up to +350.

#define SPACEMOUSE_INPUT_OFFSET (8192)

bool spacemouse_send_command(uint8_t cmd) {
    uart_write(cmd);
    uint8_t buf[2];
    uart_receive(buf, 2);
    return (buf[0] == cmd && buf[1] == SPACEMOUSE_CMD_END);
}

/**
 * @brief Set the zero position of the module
 *
 * @return true command ran successfully
 * @return false command failed
 */
bool spacemouse_cmd_set_zero_position(void) {
    return spacemouse_send_command(SPACEMOUSE_CMD_SET_ZERO_POSITION);
}

/**
 * @brief Starts automatic transmission of data, at 30ms invervals
 * Automatic data transmission happens at 30 ms intervals, but device can be polled at 100/s or 10ms intervals
 * Since 10ms is what pointing device polling defaults to, we don't need need the stream command, but
 * it is here for completeness, in case somebody wants to implement it elsewhere.
 *
 * @return true command ran successfully
 * @return false command failed
 */
bool spacemouse_cmd_enable_stream(void) {
    return spacemouse_send_command(SPACEMOUSE_CMD_AUTO_DATA_ON);
}

/**
 * @brief Stops automatic transmission of data, at 30ms invervals
 *
 * @return true command ran successfully
 * @return false command failed
 */
bool spacemouse_cmd_disable_stream(void) {
    return spacemouse_send_command(SPACEMOUSE_CMD_AUTO_DATA_OFF);
}

/**
 * @brief Initialize UART connection and send command to zero out starting position.
 *
 * @return true
 * @return false
 */
bool spacemouse_init(void) {
    uart_init(SPACEMOUSE_BAUD_RATE);
    // position is zeroed out during device start, but re-zero it out to ensure that the
    // device is present and working properly.
    return spacemouse_cmd_set_zero_position();
}

spacemouse_data_t spacemouse_get_data(void) {
    spacemouse_data_t data           = {0};
    uint8_t           retry_attempts = 0, index = 0, payload[SPACEMOUSE_LENGTH_DATA + SPACEMOUSE_LENGTH_CHECKSUM] = {0};
    uint16_t          checksum = 0, checksum_received = 0;
    bool              has_started = false;
    uart_write(SPACEMOUSE_CMD_REQUEST_DATA);
    while (retry_attempts <= 15) {
        uint8_t buf = uart_read();
        if (buf == SPACEMOUSE_DATA_REQUEST_START) {
            has_started    = true;
            checksum       = buf;
            retry_attempts = 0;
            continue;
        } else if (has_started) {
            if (buf == SPACEMOUSE_CMD_END) {
                break;
            } else {
                if (index >= SPACEMOUSE_LENGTH_DATA) {
                    if (index == SPACEMOUSE_LENGTH_DATA) {
                        checksum_received = buf << 7;
                    } else {
                        checksum_received += buf;
                    }
                } else {
                    payload[index] = buf;
                    checksum += buf;
                }
                index++;
            }
        }
        retry_attempts++;
    };

    checksum &= 0x3FFF;

    if (has_started) {
        if (checksum_received == checksum) {
            data.x      = (int16_t)((payload[0] << 7) + payload[1]) - SPACEMOUSE_INPUT_OFFSET;
            data.z      = (int16_t)((payload[2] << 7) + payload[3]) - SPACEMOUSE_INPUT_OFFSET;
            data.y      = (int16_t)((payload[4] << 7) + payload[5]) - SPACEMOUSE_INPUT_OFFSET;
            data.tilt_y = (int16_t)((payload[6] << 7) + payload[7]) - SPACEMOUSE_INPUT_OFFSET;
            data.twist  = (int16_t)((payload[8] << 7) + payload[9]) - SPACEMOUSE_INPUT_OFFSET;
            data.tilt_x = (int16_t)((payload[10] << 7) + payload[11]) - SPACEMOUSE_INPUT_OFFSET;
        } else {
            pd_dprintf("Space Mouse Checksum error: 0x%04x != 0x%04x \n", checksum_received, checksum);
        }
    }

    return data;
}
