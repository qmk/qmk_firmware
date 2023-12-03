// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "color.h"
#include "qp_internal.h"
#include "qp_surface_internal.h"

#ifdef QUANTUM_PAINTER_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_SPI_ENABLE

#ifdef QUANTUM_PAINTER_I2C_ENABLE
#    include "qp_comms_i2c.h"
#endif // QUANTUM_PAINTER_I2C_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common OLED panel implementation

// Driver vtable with extras
typedef struct oled_panel_painter_driver_vtable_t {
    painter_driver_vtable_t base; // must be first, so it can be cast to/from the painter_driver_vtable_t* type

    // Opcodes for normal display operation
    struct {
        uint8_t display_on;
        uint8_t display_off;
        uint8_t set_page;
        uint8_t set_column_lsb;
        uint8_t set_column_msb;
    } opcodes;
} oled_panel_painter_driver_vtable_t;

// Device definition
typedef struct oled_panel_painter_device_t {
    painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    union {
#ifdef QUANTUM_PAINTER_SPI_ENABLE
        // SPI-based configurables
        qp_comms_spi_dc_reset_config_t spi_dc_reset_config;
#endif // QUANTUM_PAINTER_SPI_ENABLE
#ifdef QUANTUM_PAINTER_I2C_ENABLE
        // I2C-based configurables
        qp_comms_i2c_config_t i2c_config;
#endif // QUANTUM_PAINTER_I2C_ENABLE
    };

    surface_painter_device_t surface;
} oled_panel_painter_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations for injecting into concrete driver vtables

bool qp_oled_panel_power(painter_device_t device, bool power_on);
bool qp_oled_panel_clear(painter_device_t device);

bool qp_oled_panel_passthru_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);
bool qp_oled_panel_passthru_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
bool qp_oled_panel_passthru_palette_convert(painter_device_t device, int16_t palette_size, qp_pixel_t *palette);
bool qp_oled_panel_passthru_append_pixels(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices);
bool qp_oled_panel_passthru_append_pixdata(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte);

// Helpers for flushing data from the dirty region to the correct location on the OLED
void qp_oled_panel_page_column_flush_rot0(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer);
void qp_oled_panel_page_column_flush_rot90(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer);
void qp_oled_panel_page_column_flush_rot180(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer);
void qp_oled_panel_page_column_flush_rot270(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer);
