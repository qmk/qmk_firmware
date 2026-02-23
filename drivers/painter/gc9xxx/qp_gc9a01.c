// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_gc9a01.h"
#include "qp_gc9xxx_opcodes.h"
#include "qp_gc9a01_opcodes.h"
#include "qp_tft_panel.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tft_panel_dc_reset_painter_device_t gc9a01_drivers[GC9A01_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__attribute__((weak)) bool qp_gc9a01_init(painter_device_t device, painter_rotation_t rotation) {
    // A lot of these "unknown" opcodes are sourced from other OSS projects and are seemingly required for this display to function.
    // clang-format off

    const uint8_t gc9a01_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        GC9XXX_SET_INTER_REG_ENABLE1,   0,  0,
        GC9XXX_SET_INTER_REG_ENABLE2,   0,  0,
        0x84,                           0,  1, 0x40,
        GC9A01_SET_FUNCTION_CTL,        0,  3, 0x00, GC9A01_SOURCE_OUTPUT_SCAN_DIRECTION_S360_TO_S1 | GC9A01_GATE_OUTPUT_SCAN_DIRECTION_G1_TO_G32, GC9A01_LCD_DRIVE_LINE_240, // Only works if the previous command is present (undocumented)
        GC9A01_SET_POWER_CTL_2,         0,  1, 0x20,
        GC9A01_SET_POWER_CTL_3,         0,  1, 0x20,
        GC9A01_SET_POWER_CTL_4,         0,  1, 0x22,
        GC9XXX_SET_GAMMA1,              0,  6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
        GC9XXX_SET_GAMMA2,              0,  6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
        GC9A01_SET_GAMMA3,              0,  6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
        GC9A01_SET_GAMMA4,              0,  6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
        0x66,                           0, 10, 0x3C, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00,
        0x67,                           0, 10, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98,
        GC9XXX_CMD_TEARING_ON,          0,  0,
        GC9XXX_SET_PIXEL_FORMAT,        0,  1, GC9A01_PIXEL_FORMAT_16_BPP_DBI,
        GC9XXX_CMD_INVERT_ON,           0,  0,
        GC9XXX_CMD_SLEEP_OFF,           120, 0,
        GC9XXX_CMD_DISPLAY_ON,          20,  0
    };
    // clang-format on

    if (!qp_comms_bulk_command_sequence(device, gc9a01_init_sequence, sizeof(gc9a01_init_sequence))) {
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

const tft_panel_dc_reset_painter_driver_vtable_t gc9a01_driver_vtable = {
    .base =
        {
            .init            = qp_gc9a01_init,
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

#ifdef QUANTUM_PAINTER_GC9A01_SPI_ENABLE
// Factory function for creating a handle to the ILI9341 device
painter_device_t qp_gc9a01_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < GC9A01_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &gc9a01_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&gc9a01_driver_vtable;
            driver->base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
            driver->base.native_bits_per_pixel = 16; // RGB565
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;

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

#endif // QUANTUM_PAINTER_GC9A01_SPI_ENABLE
