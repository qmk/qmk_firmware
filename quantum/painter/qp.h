// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter global configurables (add to your keyboard's config.h)

// This controls the maximum size of the pixel data buffer used for single blocks of transmission. Larger buffers means
// more data is processed at one time, with less frequent transmissions, at the cost of RAM.
#ifndef QP_PIXDATA_BUFFER_SIZE
#    define QP_PIXDATA_BUFFER_SIZE 32
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVR split address space shenanigans

// Mark certain types that there should be no padding bytes between members.
#define QP_PACKED __attribute__((packed))

// Ensure we can mark certain data as being available in flash, only.
#ifdef __FLASH
#    define QP_RESIDENT_FLASH __flash
#else
// BEWARE: This case will also apply to C++ code on AVR as it has no concept of named address spaces
#    define QP_RESIDENT_FLASH
#endif

// Ensure we can mark certain data as being available in flash or ram.
#ifdef __MEMX
#    define QP_RESIDENT_FLASH_OR_RAM __memx
#else
// BEWARE: This case will also apply to C++ code on AVR as it has no concept of named address spaces
#    define QP_RESIDENT_FLASH_OR_RAM
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter types

// Device type
typedef const void *painter_device_t;

// Rotation type
typedef enum { QP_ROTATION_0, QP_ROTATION_90, QP_ROTATION_180, QP_ROTATION_270 } painter_rotation_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API

// Initialize a device and set its rotation -- need to create the device using its corresponding factory method first
bool qp_init(painter_device_t device, painter_rotation_t rotation);

// Handle turning a display on or off -- if a display backlight is controlled through the backlight subsystem, it will need to be handled externally to QP
bool qp_power(painter_device_t device, bool power_on);

// Clear's a device's screen
bool qp_clear(painter_device_t device);

// Transmits any outstanding data to the screen in order to persist all changes to the display -- some drivers without framebuffers will likely ignore this API.
bool qp_flush(painter_device_t device);

// Gets the size of the display
void qp_get_geometry(painter_device_t device, uint16_t *width, uint16_t *height, painter_rotation_t *rotation, uint16_t *offset_x, uint16_t *offset_y);

// Allows repositioning of the viewport if the panel geometry offsets are different to what's expected.
void qp_set_viewport_offsets(painter_device_t device, uint16_t offset_x, uint16_t offset_y);

// Set the viewport that native pixel data is to get streamed into
bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

// Stream pixel data in the device's native format into the previously-set viewport
bool qp_pixdata(painter_device_t device, const void QP_RESIDENT_FLASH_OR_RAM *pixel_data, uint32_t native_pixel_count);

// Set a specific pixel
bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val);
