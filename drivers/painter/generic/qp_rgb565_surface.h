// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter RGB565 surface configurables (add to your keyboard's config.h)

#ifndef RGB565_SURFACE_NUM_DEVICES
/**
 * @def This controls the maximum number of surface devices that Quantum Painter can use at any one time.
 *      Increasing this number allows for multiple framebuffers to be used. Each requires its own RAM allocation.
 */
#    define RGB565_SURFACE_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations

#ifdef QUANTUM_PAINTER_RGB565_SURFACE_ENABLE
/**
 * Factory method for an RGB565 surface (aka framebuffer).
 *
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param buffer[in] pointer to a preallocated buffer of size `(sizeof(uint16_t) * panel_width * panel_height)`
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_rgb565_make_surface(uint16_t panel_width, uint16_t panel_height, void *buffer);

/**
 * Helper method to draw the dirty contents of the framebuffer to the target device.
 *
 * After successful completion, the dirty area is reset.
 *
 * @param surface[in] the surface to copy from
 * @param display[in] the display to copy into
 * @param x[in] the x-location of the original position of the framebuffer
 * @param y[in] the y-location of the original position of the framebuffer
 * @return whether the draw operation completed successfully
 */
bool qp_rgb565_surface_draw(painter_device_t surface, painter_device_t display, uint16_t x, uint16_t y);
#endif // QUANTUM_PAINTER_RGB565_SURFACE_ENABLE
