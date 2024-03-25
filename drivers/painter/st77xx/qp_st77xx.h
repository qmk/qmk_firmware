// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"

/**
 * Function to control color inversion on a ST77XX device.
 *
 * @param device[in] device handle to operate on.
 * @param invert[in] whether to invert colors or not.
 * @return Whether the operation was successful.
 */
bool qp_st77xx_set_inversion(painter_device_t device, bool invert);
