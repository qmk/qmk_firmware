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
