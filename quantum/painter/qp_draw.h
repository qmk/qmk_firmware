// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <qp_internal.h>
#include <qp_stream.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter utility functions

// Global variable used for native pixel data streaming.
extern uint8_t qp_internal_global_pixdata_buffer[QP_PIXDATA_BUFFER_SIZE];

// Returns the number of pixels that can fit in the pixdata buffer
uint32_t qp_internal_num_pixels_in_buffer(painter_device_t device);

// Fills the supplied buffer with equivalent native pixels matching the supplied HSV
void qp_internal_fill_pixdata(painter_device_t device, uint32_t num_pixels, uint8_t hue, uint8_t sat, uint8_t val);

// qp_setpixel internal implementation, but uses the global pixdata buffer with pre-converted native pixel. Only the first pixel is used.
bool qp_internal_setpixel_impl(painter_device_t device, uint16_t x, uint16_t y);

// qp_rect internal implementation, but uses the global pixdata buffer with pre-converted native pixels.
bool qp_internal_fillrect_helper_impl(painter_device_t device, uint16_t l, uint16_t t, uint16_t r, uint16_t b);

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
