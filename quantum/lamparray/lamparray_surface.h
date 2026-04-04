// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/**
 * \brief lamparray_surface_enable
 */
void lamparray_surface_enable(bool enable);

/**
 * \brief lamparray_surface_set_item
 */
void lamparray_surface_set_item(uint16_t index, lamp_state_t color);

/**
 * \brief lamparray_surface_update_finished
 */
void lamparray_surface_update_finished(void);
