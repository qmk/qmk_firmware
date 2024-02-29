// Copyright 2023 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "util.h"

/**
 * @brief Common USB 2.0 control request structure
 */
typedef struct {
    uint8_t bmRequestType; // [0] (Bitmask)
    uint8_t bRequest;      // [1]
    union {
        struct {
            uint8_t lbyte; // [2] (LSB)
            uint8_t hbyte; // [3] (MSB)
        };
        uint16_t word; // [2,3] (LSB,MSB)
    } wValue;
    uint16_t wIndex;  // [4,5] (LSB,MSB)
    uint16_t wLength; // [6,7] (LSB,MSB)
} PACKED usb_control_request_t;
