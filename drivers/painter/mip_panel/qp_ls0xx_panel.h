// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp_internal.h"
#include "qp_surface_internal.h"

#include "qp_comms_spi.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common MIP panel implementation for Sharp displays, using 3-wire SPI.

// Device definition
typedef struct mip_panel_painter_device_t {
    painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    union {
#ifdef QUANTUM_PAINTER_SPI_ENABLE
        // SPI-based configurables
        qp_comms_spi_config_t spi_config;
#endif // QUANTUM_PAINTER_SPI_ENABLE

        // TODO: I2C/parallel etc.
    };

    surface_painter_device_t surface;
} mip_panel_painter_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations for injecting into concrete driver vtables
extern const painter_driver_vtable_t ls0xx_driver_vtable;
