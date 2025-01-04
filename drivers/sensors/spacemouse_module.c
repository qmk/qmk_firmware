// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spacemouse_module.h"
#include "pointing_device_internal.h"
#include "uart.h"

// datasheet available at https://3dconnexion.com/cn/wp-content/uploads/2020/02/HW-Spec-3DX-700039_Rev001_serial.pdf

/* Datasheet UART settings specify:
 * baud rate: 38400
 * data bits: 8
 * parity:    none
 * stop bits: 1
 * data rate: max 100/s
 */

#define SPACEMOUSE_BAUD_RATE 38400
#define SPACEMOUSE_AXIS_COUNT 6
#define SPACEMOUSE_LENGTH_DATA (2 * SPACEMOUSE_AXIS_COUNT)
#define SPACEMOUSE_INPUT_OFFSET (8192)


const pointing_device_driver_t pointing_device_driver = {
    .init       = spacemouse_init,
    .get_report = spacemouse_get_report,
    .set_cpi    = NULL,
    .get_cpi    = NULL
};

static bool spacemouse_present = false;

enum spacemouse_commands {
    SPACEMOUSE_CMD_REQUEST_DATA      = 0xAC,
    SPACEMOUSE_CMD_SET_ZERO_POSITION = 0xAD,
    SPACEMOUSE_CMD_AUTO_DATA_ON      = 0xAE,
    SPACEMOUSE_CMD_AUTO_DATA_OFF     = 0xAF,
    SPACEMOUSE_CMD_END               = 0x8D,
    SPACEMOUSE_DATA_REQUEST_START    = 0x96,
};

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
 * Automatic data transmission happens at 30 ms intervals, we don't need need the stream command,
 * but it is here for completeness, in case somebody wants to implement it elsewhere.
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
 */
void spacemouse_init(void) {
    uart_init(SPACEMOUSE_BAUD_RATE);
    // position is zeroed out during device start, but re-zero it out to ensure that the
    // device is present and working properly.
    spacemouse_present = spacemouse_cmd_set_zero_position();
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


__attribute__((weak)) void spacemouse_module_handle_axes(spacemouse_data_t* spacemouse_data, report_mouse_t* mouse_report) {
#    ifdef SPACEMOUSE_USE_TILT_AXIS
    mouse_report->x = CONSTRAIN_HID_XY(spacemouse_data->tilt_x);
    mouse_report->y = CONSTRAIN_HID_XY(spacemouse_data->tilt_y);
#    else
    mouse_report->x = CONSTRAIN_HID_XY(spacemouse_data->x);
    mouse_report->y = CONSTRAIN_HID_XY(spacemouse_data->y);
#    endif
}

report_mouse_t spacemouse_get_report(report_mouse_t mouse_report) {
    if (spacemouse_present) {
        spacemouse_data_t data = spacemouse_get_data();

        if (data.x || data.y || data.z || data.twist || data.tilt_x || data.tilt_y) {
            pd_dprintf("Raw ] X: %d, Y: %d, Z: %d, twist: %d, tilt X: %d, tilt Y: %d\n", data.x, data.y, data.z, data.twist, data.tilt_x, data.tilt_y);
        }
        spacemouse_module_handle_axes(&data, &mouse_report);
    }
    return mouse_report;
}
