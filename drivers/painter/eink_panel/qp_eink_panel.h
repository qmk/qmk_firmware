// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "qp_internal.h"
#include "qp_surface.h"

#ifdef QUANTUM_PAINTER_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper to create buffers with the apropiate size
#define EINK_BYTES_REQD(w, h) (SURFACE_REQUIRED_BUFFER_BYTE_SIZE(w, h, 2))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common TFT panel implementation using D/C, and RST pins.

// Driver vtable with extras
typedef struct eink_panel_dc_reset_painter_driver_vtable_t {
    painter_driver_vtable_t base; // must be first, so it can be cast to/from the painter_driver_vtable_t* type

    // Opcodes for normal display operation
    // some may not exist on some displays
    struct {
        uint8_t display_on;
        uint8_t display_off;
        uint8_t send_black_data;
        uint8_t send_color_data;
        uint8_t refresh;
    } opcodes;
} eink_panel_dc_reset_painter_driver_vtable_t;

// Device definition
typedef struct eink_panel_dc_reset_painter_device_t {
    painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    // have to wait between flushes to avoid damaging the screen, time in ms
    uint32_t timeout;
    bool     can_flush;

    /** Information about the pixel format, default values (non-inverted) are
     *
     * Black bit: 0 for white / 1 for black
     * Color bit: 0 for white or black / 1 for third color
     *
     * Represented as a bitmask where a 1 means "needs inversion"
     * 0000 00BC
     */
    HSV     color;
    uint8_t invert_mask;

    // Storage for each color's data
    painter_device_t black_surface;
    painter_device_t color_surface;

    union {
#ifdef QUANTUM_PAINTER_SPI_ENABLE
        // SPI-based configurables
        qp_comms_spi_dc_reset_config_t spi_dc_reset_config;
#endif // QUANTUM_PAINTER_SPI_ENABLE

        // TODO: I2C/parallel etc.
    };
} eink_panel_dc_reset_painter_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations for injecting into concrete driver vtables

bool qp_eink_panel_power(painter_device_t device, bool power_on);
bool qp_eink_panel_clear(painter_device_t device);

void qp_eink_update_can_flush(painter_device_t device);
bool qp_eink_panel_flush(painter_device_t device);

bool qp_eink_panel_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
bool qp_eink_panel_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);

bool qp_eink_panel_palette_convert(painter_device_t device, int16_t palette_size, qp_pixel_t *palette);

bool qp_eink_panel_append_pixels(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices);

bool qp_eink_panel_append_pixdata(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte);
