// Copyright 2024 Fernando Birra
// SPDX-License-Identifier: GPL-2.0-or-later
#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_gc9107.h"
#include "qp_gc9xxx_opcodes.h"
#include "qp_gc9107_opcodes.h"
#include "qp_tft_panel.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tft_panel_dc_reset_painter_device_t gc9107_drivers[GC9107_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__attribute__((weak)) bool qp_gc9107_init(painter_device_t device, painter_rotation_t rotation) {
    // A lot of these "unknown" opcodes are sourced from other OSS projects and are seemingly required for this display to function.
    // clang-format off
    const uint8_t gc9107_init_sequence[] = {
        GC9XXX_SET_INTER_REG_ENABLE1,   5,  0,
        GC9XXX_SET_INTER_REG_ENABLE2,   5,  0,
        GC9107_SET_FUNCTION_CTL6, 0, 1, GC9107_ALLOW_SET_COMPLEMENT_RGB | 0x08 | GC9107_ALLOW_SET_FRAMERATE,
        GC9107_SET_COMPLEMENT_RGB, 0, 1, GC9107_COMPLEMENT_WITH_LSB,
        0xAB, 0, 1, 0x0E,
        GC9107_SET_FRAME_RATE, 0, 1, 0x19,
        GC9XXX_SET_PIXEL_FORMAT, 0, 1, GC9107_PIXEL_FORMAT_16_BPP_IFPF,
        GC9XXX_CMD_SLEEP_OFF,   120, 0,
        GC9XXX_CMD_DISPLAY_ON,  20,  0
    };

    // clang-format on
    if (!qp_comms_bulk_command_sequence(device, gc9107_init_sequence, sizeof(gc9107_init_sequence))) {
        return false;
    }

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = GC9XXX_MADCTL_BGR,
        [QP_ROTATION_90]  = GC9XXX_MADCTL_BGR | GC9XXX_MADCTL_MX | GC9XXX_MADCTL_MV,
        [QP_ROTATION_180] = GC9XXX_MADCTL_BGR | GC9XXX_MADCTL_MX | GC9XXX_MADCTL_MY,
        [QP_ROTATION_270] = GC9XXX_MADCTL_BGR | GC9XXX_MADCTL_MV | GC9XXX_MADCTL_MY,
    };
    return qp_comms_command_databyte(device, GC9XXX_SET_MEM_ACS_CTL, madctl[rotation]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tft_panel_dc_reset_painter_driver_vtable_t gc9107_driver_vtable = {
    .base =
        {
            .init            = qp_gc9107_init,
            .power           = qp_tft_panel_power,
            .clear           = qp_tft_panel_clear,
            .flush           = qp_tft_panel_flush,
            .pixdata         = qp_tft_panel_pixdata,
            .viewport        = qp_tft_panel_viewport,
            .palette_convert = qp_tft_panel_palette_convert_rgb565_swapped,
            .append_pixels   = qp_tft_panel_append_pixels_rgb565,
            .append_pixdata  = qp_tft_panel_append_pixdata,
        },
    .num_window_bytes   = 2,
    .swap_window_coords = false,
    .opcodes =
        {
            .display_on         = GC9XXX_CMD_DISPLAY_ON,
            .display_off        = GC9XXX_CMD_DISPLAY_OFF,
            .set_column_address = GC9XXX_SET_COL_ADDR,
            .set_row_address    = GC9XXX_SET_ROW_ADDR,
            .enable_writes      = GC9XXX_SET_MEM,
        },
};

#ifdef QUANTUM_PAINTER_GC9107_SPI_ENABLE
// Factory function for creating a handle to the GC9107 device
painter_device_t qp_gc9107_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < GC9107_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &gc9107_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&gc9107_driver_vtable;
            driver->base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
            driver->base.native_bits_per_pixel = 16; // RGB565
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 2;
            driver->base.offset_y              = 1;

            // SPI and other pin configuration
            driver->base.comms_config                                   = &driver->spi_dc_reset_config;
            driver->spi_dc_reset_config.spi_config.chip_select_pin      = chip_select_pin;
            driver->spi_dc_reset_config.spi_config.divisor              = spi_divisor;
            driver->spi_dc_reset_config.spi_config.lsb_first            = false;
            driver->spi_dc_reset_config.spi_config.mode                 = spi_mode;
            driver->spi_dc_reset_config.dc_pin                          = dc_pin;
            driver->spi_dc_reset_config.reset_pin                       = reset_pin;
            driver->spi_dc_reset_config.command_params_uses_command_pin = false;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(tft_panel_dc_reset_painter_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_GC9107_SPI_ENABLE
