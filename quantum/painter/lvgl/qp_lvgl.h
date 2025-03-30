// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"
#include "lvgl.h"

#ifndef QP_LVGL_TASK_PERIOD
#    define QP_LVGL_TASK_PERIOD 5
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter - LVGL External API

/**
 * Sets up LVGL with the supplied display.
 *
 * @param device[in] the handle of the device to control
 * @return true if init. of LVGL succeeded
 * @return false if init. of LVGL failed
 */
bool qp_lvgl_attach(painter_device_t device);

/**
 * Disconnects LVGL from any attached display
 */
void qp_lvgl_detach(void);
