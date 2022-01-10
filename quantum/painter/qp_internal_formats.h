// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <qp_internal.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter pixel formats

// Datatype containing a pixel's color. The internal member used is dependent on the external context.
typedef union QP_PACKED qp_pixel_t {
    uint8_t mono;
    uint8_t palette_idx;

    struct QP_PACKED {
        uint8_t h;
        uint8_t s;
        uint8_t v;
    } hsv888;

    struct QP_PACKED {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } rgb888;

    uint16_t rgb565;

    uint32_t dummy;
} qp_pixel_t;
_Static_assert(sizeof(qp_pixel_t) == 4, "Invalid size for qp_pixel_t");
