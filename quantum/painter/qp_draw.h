// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp_internal.h"
#include "qp_stream.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter utility functions

// Global variable used for native pixel data streaming.
extern uint8_t qp_internal_global_pixdata_buffer[QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE];

// Check if the supplied bpp is capable of being rendered
bool qp_internal_bpp_capable(uint8_t bits_per_pixel);

// Returns the number of pixels that can fit in the pixdata buffer
uint32_t qp_internal_num_pixels_in_buffer(painter_device_t device);

// Fills the supplied buffer with equivalent native pixels matching the supplied HSV
void qp_internal_fill_pixdata(painter_device_t device, uint32_t num_pixels, uint8_t hue, uint8_t sat, uint8_t val);

// qp_setpixel internal implementation, but uses the global pixdata buffer with pre-converted native pixel. Only the first pixel is used.
bool qp_internal_setpixel_impl(painter_device_t device, uint16_t x, uint16_t y);

// qp_rect internal implementation, but uses the global pixdata buffer with pre-converted native pixels.
bool qp_internal_fillrect_helper_impl(painter_device_t device, uint16_t l, uint16_t t, uint16_t r, uint16_t b);

// Convert from input pixel data + palette to equivalent pixels
typedef int16_t (*qp_internal_byte_input_callback)(void* cb_arg);
typedef bool (*qp_internal_pixel_output_callback)(qp_pixel_t* palette, uint8_t index, void* cb_arg);
typedef bool (*qp_internal_byte_output_callback)(uint8_t byte, void* cb_arg);
bool qp_internal_decode_palette(painter_device_t device, uint32_t pixel_count, uint8_t bits_per_pixel, qp_internal_byte_input_callback input_callback, void* input_arg, qp_pixel_t* palette, qp_internal_pixel_output_callback output_callback, void* output_arg);
bool qp_internal_decode_grayscale(painter_device_t device, uint32_t pixel_count, uint8_t bits_per_pixel, qp_internal_byte_input_callback input_callback, void* input_arg, qp_internal_pixel_output_callback output_callback, void* output_arg);
bool qp_internal_decode_recolor(painter_device_t device, uint32_t pixel_count, uint8_t bits_per_pixel, qp_internal_byte_input_callback input_callback, void* input_arg, qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888, qp_internal_pixel_output_callback output_callback, void* output_arg);
bool qp_internal_send_bytes(painter_device_t device, uint32_t byte_count, qp_internal_byte_input_callback input_callback, void* input_arg, qp_internal_byte_output_callback output_callback, void* output_arg);

// Global variable used for interpolated pixel lookup table.
#if QUANTUM_PAINTER_SUPPORTS_256_PALETTE
extern qp_pixel_t qp_internal_global_pixel_lookup_table[256];
#else
extern qp_pixel_t qp_internal_global_pixel_lookup_table[16];
#endif

// Generates a color-interpolated lookup table based off the number of items, from foreground to background, for use with monochrome image rendering.
// Returns true if a palette was created, false if the palette is reused.
// As this uses a global, this may present a problem if using the same parameters but a different screen converts pixels -- use qp_internal_invalidate_palette() below to reset.
bool qp_internal_interpolate_palette(qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888, int16_t steps);

// Resets the global palette so that it can be regenerated. Only needed if the colors are identical, but a different display is used with a different internal pixel format.
void qp_internal_invalidate_palette(void);

// Helper shared between image and font rendering -- sets up the global palette to match the palette block specified in the asset. Expects the stream to be positioned at the start of the block header.
bool qp_internal_load_qgf_palette(qp_stream_t* stream, uint8_t bpp);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter codec functions

enum qp_internal_rle_mode_t {
    MARKER_BYTE,
    REPEATING_RUN,
    NON_REPEATING_RUN,
};

typedef struct qp_internal_byte_input_state_t {
    painter_device_t device;
    qp_stream_t*     src_stream;
    int16_t          curr;
    union {
        // RLE-specific
        struct {
            enum qp_internal_rle_mode_t mode;
            uint8_t                     remain; // number of bytes remaining in the current mode
        } rle;
    };
} qp_internal_byte_input_state_t;

typedef struct qp_internal_pixel_output_state_t {
    painter_device_t device;
    uint32_t         pixel_write_pos;
    uint32_t         max_pixels;
} qp_internal_pixel_output_state_t;

bool qp_internal_pixel_appender(qp_pixel_t* palette, uint8_t index, void* cb_arg);

typedef struct qp_internal_byte_output_state_t {
    painter_device_t device;
    uint32_t         byte_write_pos;
    uint32_t         max_bytes;
} qp_internal_byte_output_state_t;

bool qp_internal_byte_appender(uint8_t byteval, void* cb_arg);

qp_internal_byte_input_callback qp_internal_prepare_input_state(qp_internal_byte_input_state_t* input_state, painter_compression_t compression);
