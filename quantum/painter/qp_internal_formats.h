// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "compiler_support.h"
#include "qp_internal.h"

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
STATIC_ASSERT(sizeof(qp_pixel_t) == 4, "Invalid size for qp_pixel_t");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter image format

typedef enum qp_image_format_t {
    // Pixel formats available in the QGF frame format
    GRAYSCALE_1BPP = 0x00,
    GRAYSCALE_2BPP = 0x01,
    GRAYSCALE_4BPP = 0x02,
    GRAYSCALE_8BPP = 0x03,
    PALETTE_1BPP   = 0x04,
    PALETTE_2BPP   = 0x05,
    PALETTE_4BPP   = 0x06,
    PALETTE_8BPP   = 0x07,
    RGB565_16BPP   = 0x08, // Natively streamed to the panel, no interpolation or palette handling
    RGB888_24BPP   = 0x09, // Natively streamed to the panel, no interpolation or palette handling
} qp_image_format_t;

typedef enum painter_compression_t { IMAGE_UNCOMPRESSED, IMAGE_COMPRESSED_RLE } painter_compression_t;
