// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "qp_internal.h"

#ifdef QUANTUM_PAINTER_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common TFT panel implementation using D/C, and RST pins.

// Driver vtable with extras
struct tft_panel_dc_reset_painter_driver_vtable_t {
    struct painter_driver_vtable_t base; // must be first, so it can be cast to/from the painter_driver_vtable_t* type

    // Number of bytes for transmitting x/y coordinates
    uint8_t num_window_bytes;

    // Whether or not the x/y coords should be swapped on 90/270 rotation
    bool swap_window_coords;

    // Opcodes for normal display operation
    struct {
        uint8_t display_on;
        uint8_t display_off;
        uint8_t set_column_address;
        uint8_t set_row_address;
        uint8_t enable_writes;
    } opcodes;
};

// Device definition
typedef struct tft_panel_dc_reset_painter_device_t {
    struct painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    union {
#ifdef QUANTUM_PAINTER_SPI_ENABLE
        // SPI-based configurables
        struct qp_comms_spi_dc_reset_config_t spi_dc_reset_config;
#endif // QUANTUM_PAINTER_SPI_ENABLE

        // TODO: I2C/parallel etc.
    };
} tft_panel_dc_reset_painter_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations for injecting into concrete driver vtables

bool qp_tft_panel_power(painter_device_t device, bool power_on);
bool qp_tft_panel_clear(painter_device_t device);
bool qp_tft_panel_flush(painter_device_t device);
bool qp_tft_panel_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
bool qp_tft_panel_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);

bool qp_tft_panel_palette_convert_rgb565_swapped(painter_device_t device, int16_t palette_size, qp_pixel_t *palette);
bool qp_tft_panel_palette_convert_rgb888(painter_device_t device, int16_t palette_size, qp_pixel_t *palette);

bool qp_tft_panel_append_pixels_rgb565(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices);
bool qp_tft_panel_append_pixels_rgb888(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices);
