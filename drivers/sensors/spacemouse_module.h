// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

// Datasheet UART settings specify:
// - 38400 baud
// - 8 data bits
// - 1 stop bit
// - no parity
// - 100/s data rate

#define SPACEMOUSE_BAUD_RATE 38400

#define SPACEMOUSE_AXIS_COUNT 6

#define SPACEMOUSE_LENGTH_HEADER 1
#define SPACEMOUSE_LENGTH_DATA (2 * SPACEMOUSE_AXIS_COUNT)
#define SPACEMOUSE_LENGTH_CHECKSUM 2
#define SPACEMOUSE_LENGTH_FOOTER 1
#define SPACEMOUSE_LENGTH_PACKET (SPACEMOUSE_LENGTH_HEADER + SPACEMOUSE_LENGTH_DATA + SPACEMOUSE_LENGTH_CHECKSUM + SPACEMOUSE_LENGTH_FOOTER)

enum spacemouse_commands {
    SPACEMOUSE_CMD_REQUEST_DATA            = 0xAC,
    SPACEMOUSE_CMD_SET_ZERO_POSITION       = 0xAD,
    SPACEMOUSE_CMD_AUTO_DATA_ON            = 0xAE,
    SPACEMOUSE_CMD_AUTO_DATA_OFF           = 0xAF,
    SPACEMOUSE_CMD_END                     = 0x8D,
    SPACEMOUSE_DATA_REQUEST_START          = 0x96,
};

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t twist;
    int16_t tilt_x;
    int16_t tilt_y;
} spacemouse_data_t;

bool spacemouse_send_command(uint8_t cmd);
bool spacemouse_init(void);
spacemouse_data_t spacemouse_get_data(void);
