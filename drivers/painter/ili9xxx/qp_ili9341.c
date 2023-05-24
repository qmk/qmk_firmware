// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_ili9341.h"
#include "qp_ili9xxx_opcodes.h"
#include "qp_tft_panel.h"

#ifdef QUANTUM_PAINTER_ILI9341_SPI_ENABLE
#    include <qp_comms_spi.h>
#endif // QUANTUM_PAINTER_ILI9341_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
tft_panel_dc_reset_painter_device_t ili9341_drivers[ILI9341_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization

bool qp_ili9341_init(painter_device_t device, painter_rotation_t rotation) {
    // clang-format off
    const uint8_t ili9341_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        ILI9XXX_CMD_RESET,            120,  0,
        ILI9XXX_CMD_SLEEP_OFF,          5,  0,
        ILI9XXX_POWER_CTL_A,            0,  5, 0x39, 0x2C, 0x00, 0x34, 0x02,
        ILI9XXX_POWER_CTL_B,            0,  3, 0x00, 0xD9, 0x30,
        ILI9XXX_POWER_ON_SEQ_CTL,       0,  4, 0x64, 0x03, 0x12, 0x81,
        ILI9XXX_SET_PUMP_RATIO_CTL,     0,  1, 0x20,
        ILI9XXX_SET_POWER_CTL_1,        0,  1, 0x26,
        ILI9XXX_SET_POWER_CTL_2,        0,  1, 0x11,
        ILI9XXX_SET_VCOM_CTL_1,         0,  2, 0x35, 0x3E,
        ILI9XXX_SET_VCOM_CTL_2,         0,  1, 0xBE,
        ILI9XXX_DRV_TIMING_CTL_A,       0,  3, 0x85, 0x10, 0x7A,
        ILI9XXX_DRV_TIMING_CTL_B,       0,  2, 0x00, 0x00,
        ILI9XXX_SET_BRIGHTNESS,         0,  1, 0xFF,
        ILI9XXX_ENABLE_3_GAMMA,         0,  1, 0x00,
        ILI9XXX_SET_GAMMA,              0,  1, 0x01,
        ILI9XXX_SET_PGAMMA,             0, 15, 0x0F, 0x29, 0x24, 0x0C, 0x0E, 0x09, 0x4E, 0x78, 0x3C, 0x09, 0x13, 0x05, 0x17, 0x11, 0x00,
        ILI9XXX_SET_NGAMMA,             0, 15, 0x00, 0x16, 0x1B, 0x04, 0x11, 0x07, 0x31, 0x33, 0x42, 0x05, 0x0C, 0x0A, 0x28, 0x2F, 0x0F,
        ILI9XXX_SET_PIX_FMT,            0,  1, 0x05,
        ILI9XXX_SET_FRAME_CTL_NORMAL,   0,  2, 0x00, 0x1B,
        ILI9XXX_SET_FUNCTION_CTL,       0,  2, 0x0A, 0xA2,
        ILI9XXX_CMD_PARTIAL_OFF,        0,  0,
        ILI9XXX_CMD_DISPLAY_ON,        20,  0
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, ili9341_init_sequence, sizeof(ili9341_init_sequence));

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = ILI9XXX_MADCTL_BGR,
        [QP_ROTATION_90]  = ILI9XXX_MADCTL_BGR | ILI9XXX_MADCTL_MX | ILI9XXX_MADCTL_MV,
        [QP_ROTATION_180] = ILI9XXX_MADCTL_BGR | ILI9XXX_MADCTL_MX | ILI9XXX_MADCTL_MY,
        [QP_ROTATION_270] = ILI9XXX_MADCTL_BGR | ILI9XXX_MADCTL_MV | ILI9XXX_MADCTL_MY,
    };
    qp_comms_command_databyte(device, ILI9XXX_SET_MEM_ACS_CTL, madctl[rotation]);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const struct tft_panel_dc_reset_painter_driver_vtable_t ili9341_driver_vtable = {
    .base =
        {
            .init            = qp_ili9341_init,
            .power           = qp_tft_panel_power,
            .clear           = qp_tft_panel_clear,
            .flush           = qp_tft_panel_flush,
            .pixdata         = qp_tft_panel_pixdata,
            .viewport        = qp_tft_panel_viewport,
            .palette_convert = qp_tft_panel_palette_convert,
            .append_pixels   = qp_tft_panel_append_pixels,
        },
    .rgb888_to_native16bit = qp_rgb888_to_rgb565_swapped,
    .num_window_bytes      = 2,
    .swap_window_coords    = false,
    .opcodes =
        {
            .display_on         = ILI9XXX_CMD_DISPLAY_ON,
            .display_off        = ILI9XXX_CMD_DISPLAY_OFF,
            .set_column_address = ILI9XXX_SET_COL_ADDR,
            .set_row_address    = ILI9XXX_SET_PAGE_ADDR,
            .enable_writes      = ILI9XXX_SET_MEM,
        },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_ILI9341_SPI_ENABLE

// Factory function for creating a handle to the ILI9341 device
painter_device_t qp_ili9341_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < ILI9341_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &ili9341_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const struct painter_driver_vtable_t *)&ili9341_driver_vtable;
            driver->base.comms_vtable          = (const struct painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
            driver->base.native_bits_per_pixel = 16; // RGB565
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;

            // SPI and other pin configuration
            driver->base.comms_config                              = &driver->spi_dc_reset_config;
            driver->spi_dc_reset_config.spi_config.chip_select_pin = chip_select_pin;
            driver->spi_dc_reset_config.spi_config.divisor         = spi_divisor;
            driver->spi_dc_reset_config.spi_config.lsb_first       = false;
            driver->spi_dc_reset_config.spi_config.mode            = spi_mode;
            driver->spi_dc_reset_config.dc_pin                     = dc_pin;
            driver->spi_dc_reset_config.reset_pin                  = reset_pin;
            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_ILI9341_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
