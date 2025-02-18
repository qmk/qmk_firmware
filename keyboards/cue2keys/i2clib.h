// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdio.h>
#include "keycodes.h"
#include "debug.h"

// # of System Key
#define SYSTEM_KEY_NUM 10
// maximum number of modules per channel
#define MAX_KEY_PER_CH_NUM 8
#define MAX_RE_PER_CH_NUM 4
#define CH_BUFFER_NUM 16 // for future modules

// 0x18 is the beginning of PCA9557
#define PCA9557_FROM_ADDR 0x18
#define PCA9557_END_ADDR (0x18 + MAX_KEY_PER_CH_NUM)

// 0x20 is the beginning of XL9555/TCA9535
#define XL9555_FROM_ADDR 0x20
#define XL9555_END_ADDR (0x20 + MAX_KEY_PER_CH_NUM)

// 0x38 is the beginning of PCA9534A
// NOTICE: OLED resides on 0x3C, thus MAX_RE_PER_CH_NUM is 4 to skip this address.
// Additionally, on the hardware side, the A2 pin needs to be low.
#define PCA9534A_FROM_ADDR 0x38
#define PCA9534A_END_ADDR (PCA9534A_FROM_ADDR + MAX_RE_PER_CH_NUM)

#define I2C_MULTIPX_ADDR 0x70

#define MY_I2C_TIMEOUT 1

#define MAX_MEX_CH 4
#define MAX_MCP_NUM 60

typedef enum _Type {
    Type_Unknown = 0,

    Type_PCA9557_Keys4 = 1,
    Type_PCA9557_Keys5 = 2,

    Type_XL9555_Keys4 = 3,
    Type_XL9555_Keys5 = 4,

    Type_PCA9534A_RE_CLICKABLE = 5,
} Type;

typedef struct {
    Type    type;
    uint8_t data[2]; // key input, joysticks, etc
} Keys_Data;

typedef struct {
    Type     type;
    uint8_t  ch;
    uint8_t  address;
    uint16_t keymapShift;
} DeviceList;

bool      change_channel(uint8_t channel);
Keys_Data read_PCA9557_register(uint8_t address);
Keys_Data read_XL9555_register(uint8_t address);
Keys_Data read_PCA9534A_register(uint8_t address);
void      do_scan(void);
