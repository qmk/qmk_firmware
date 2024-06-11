// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter surface helpers

// Helper for determining buffer size required for a surface
#define SURFACE_REQUIRED_BUFFER_BYTE_SIZE(w, h, bpp) ((((w) * (h) * (bpp)) + 7) / 8)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter surface configurables (add to your keyboard's config.h)

#ifndef SURFACE_NUM_DEVICES
/**
 * @def This controls the maximum number of surface devices that Quantum Painter can use at any one time.
 *      Increasing this number allows for multiple framebuffers to be used. Each requires its own RAM allocation.
 */
#    define SURFACE_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations

#ifdef QUANTUM_PAINTER_SURFACE_ENABLE

// Surface struct
struct surface_painter_device_t;
typedef struct surface_painter_device_t surface_painter_device_t;

/**
 * Factory method for an RGB565 surface (aka framebuffer).
 *
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param buffer[in] pointer to a preallocated uint8_t buffer of size `SURFACE_REQUIRED_BUFFER_BYTE_SIZE(panel_width, panel_height, 16)`
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_make_rgb565_surface(uint16_t panel_width, uint16_t panel_height, void *buffer);

/**
 * Factory method for a 1bpp monochrome surface (aka framebuffer).
 *
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param buffer[in] pointer to a preallocated uint8_t buffer of size `SURFACE_REQUIRED_BUFFER_BYTE_SIZE(panel_width, panel_height, 1)`
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_make_mono1bpp_surface(uint16_t panel_width, uint16_t panel_height, void *buffer);

/**
 * Helper method to draw the contents of the framebuffer to the target device.
 *
 * After successful completion, the dirty area is reset.
 *
 * @param surface[in] the surface to copy from
 * @param target[in] the target device to copy into
 * @param x[in] the x-location of the original position of the framebuffer
 * @param y[in] the y-location of the original position of the framebuffer
 * @param entire_surface[in] whether the entire surface should be drawn, instead of just the dirty region
 * @return whether the draw operation completed successfully
 */
bool qp_surface_draw(painter_device_t surface, painter_device_t target, uint16_t x, uint16_t y, bool entire_surface);

#endif // QUANTUM_PAINTER_SURFACE_ENABLE
