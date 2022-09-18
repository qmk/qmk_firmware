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
painter_device_t qp_make_rgb565_surface(uint16_t panel_width, uint16_t panel_height, void *buffer);
bool             qp_rgb565_surface_draw(painter_device_t surface, painter_device_t display, uint16_t x, uint16_t y);
#endif // QUANTUM_PAINTER_RGB565_SURFACE_ENABLE
