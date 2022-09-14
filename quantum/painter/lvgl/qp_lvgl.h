// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter - LVGL global configurables (add to your keyboard's config.h)

#ifndef QUANTUM_PAINTER_LVGL_INIT_DELAY
/**
 * @def This controls the delay to start the deferred execution of the LVGL task.
 */
#    define QUANTUM_PAINTER_LVGL_INIT_DELAY 5
#endif // QUANTUM_PAINTER_LVGL_INIT_DELAY

#ifndef QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH
/**
 * @def Define width of display
 */
#    define QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH 240
#endif // QUANTUM_PAINTER_LVGL_DISPLaY_WIDTH

#ifndef QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT
/**
 * @def Define height of display
 */
#    define QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT 240
#endif // QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT

#ifndef QUANTUM_PAINTER_LVGL_COLOR_DEPTH
/**
 * @def Define color depth of display: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888)
 */
#    define QUANTUM_PAINTER_LVGL_COLOR_DEPTH 16
#endif // QUANTUM_PAINTER_LVGL_COLOR_DEPTH

#ifndef QUANTUM_PAINTER_LVGL_16BIT_SWAP_BYTES
/**
 * @def Define if LVGL should swap HILOW bits for 16-bit color displays
 */
#    define QUANTUM_PAINTER_LVGL_16BIT_SWAP_BYTES 1
#endif // QUANTUM_PAINTER_LVGL_16BIT_SWAP_BYTES

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter - LVGL External API

/**
 * Sets ups LVGL.
 *
 * @param device[in] the handle of the device to control
 * @return true if init. of LVGL succeeded
 * @return false if init. of LVGL failed
 */
bool qp_lvgl_start(painter_device_t device);

/**
 * Stops the tasks used by LVGL.
 */
void qp_lvgl_stop_tasks(void);
