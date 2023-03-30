/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/bit_ops.h"

uint32_t __rev(uint32_t v) {
    v = ((v & 0x55555555u) << 1u) | ((v >> 1u) & 0x55555555u);
    v = ((v & 0x33333333u) << 2u) | ((v >> 2u) & 0x33333333u);
    v = ((v & 0x0f0f0f0fu) << 4u) | ((v >> 4u) & 0x0f0f0f0fu);
    return (v << 24u) | ((v & 0xff00u) << 8u) | ((v >> 8u) & 0xff00u) | (v >> 24u);
}

uint64_t __revll(uint64_t v) {
    v = ((v & 0x5555555555555555u) << 1u) | ((v >> 1u) & 0x5555555555555555u);
    v = ((v & 0x3333333333333333u) << 2u) | ((v >> 2u) & 0x3333333333333333u);
    v = ((v & 0x0f0f0f0f0f0f0f0fu) << 4u) | ((v >> 4u) & 0x0f0f0f0f0f0f0f0fu);
    v = ((v & 0x00ff00ff00ff00ffu) << 8u) | ((v >> 8u) & 0x00ff00ff00ff00ffu);
    return (v << 48u) | ((v & 0xffff0000u) << 16u) | ((v >> 16u) & 0xffff0000u) | (v >> 48u);
}
