// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_ssd1351.h"
#include "qp_ssd1351_opcodes.h"
#include "qp_tft_panel.h"

#ifdef QUANTUM_PAINTER_SSD1351_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_SSD1351_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
tft_panel_dc_reset_painter_device_t ssd1351_drivers[SSD1351_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization

__attribute__((weak)) bool qp_ssd1351_init(painter_device_t device, painter_rotation_t rotation) {
    tft_panel_dc_reset_painter_device_t *driver = (tft_panel_dc_reset_painter_device_t *)device;

    // clang-format off
    const uint8_t ssd1351_init_sequence[] = {
        // Command,                 Delay, N, Data[N]
        SSD1351_COMMANDLOCK,           5,  1, 0x12,
        SSD1351_COMMANDLOCK,           5,  1, 0xB1,
        SSD1351_DISPLAYOFF,            5,  0,
        SSD1351_CLOCKDIV,              5,  1, 0xF1,
        SSD1351_MUXRATIO,              5,  1, 0x7F,
        SSD1351_DISPLAYOFFSET,         5,  1, 0x00,
        SSD1351_SETGPIO,               5,  1, 0x00,
        SSD1351_FUNCTIONSELECT,        5,  1, 0x01,
        SSD1351_PRECHARGE,             5,  1, 0x32,
        SSD1351_VCOMH,                 5,  1, 0x05,
        SSD1351_NORMALDISPLAY,         5,  0,
        SSD1351_CONTRASTABC,           5,  3, 0xC8, 0x80, 0xC8,
        SSD1351_CONTRASTMASTER,        5,  1, 0x0F,
        SSD1351_SETVSL,                5,  3, 0xA0, 0xB5, 0x55,
        SSD1351_PRECHARGE2,            5,  1, 0x01,
        SSD1351_DISPLAYON,             5,  0,
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, ssd1351_init_sequence, sizeof(ssd1351_init_sequence));

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = SSD1351_MADCTL_BGR | SSD1351_MADCTL_MY,
        [QP_ROTATION_90]  = SSD1351_MADCTL_BGR | SSD1351_MADCTL_MX | SSD1351_MADCTL_MY | SSD1351_MADCTL_MV,
        [QP_ROTATION_180] = SSD1351_MADCTL_BGR | SSD1351_MADCTL_MX,
        [QP_ROTATION_270] = SSD1351_MADCTL_BGR | SSD1351_MADCTL_MV,
    };
    qp_comms_command_databyte(device, SSD1351_SETREMAP, madctl[rotation]);
    qp_comms_command_databyte(device, SSD1351_STARTLINE, (rotation == QP_ROTATION_0 || rotation == QP_ROTATION_90) ? driver->base.panel_height : 0);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const struct tft_panel_dc_reset_painter_driver_vtable_t ssd1351_driver_vtable = {
    .base =
        {
            .init            = qp_ssd1351_init,
            .power           = qp_tft_panel_power,
            .clear           = qp_tft_panel_clear,
            .flush           = qp_tft_panel_flush,
            .pixdata         = qp_tft_panel_pixdata,
            .viewport        = qp_tft_panel_viewport,
            .palette_convert = qp_tft_panel_palette_convert_rgb565_swapped,
            .append_pixels   = qp_tft_panel_append_pixels_rgb565,
            .append_pixdata  = qp_tft_panel_append_pixdata,
        },
    .num_window_bytes   = 1,
    .swap_window_coords = true,
    .opcodes =
        {
            .display_on         = SSD1351_DISPLAYON,
            .display_off        = SSD1351_DISPLAYOFF,
            .set_column_address = SSD1351_SETCOLUMN,
            .set_row_address    = SSD1351_SETROW,
            .enable_writes      = SSD1351_WRITERAM,
        },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_SSD1351_SPI_ENABLE

// Factory function for creating a handle to the SSD1351 device
painter_device_t qp_ssd1351_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < SSD1351_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &ssd1351_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const struct painter_driver_vtable_t *)&ssd1351_driver_vtable;
            driver->base.comms_vtable          = (const struct painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;
            driver->base.native_bits_per_pixel = 16; // RGB565

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

#endif // QUANTUM_PAINTER_SSD1351_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
