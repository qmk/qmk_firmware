// Copyright 2021-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_ili9163.h"
#include "qp_ili9xxx_opcodes.h"
#include "qp_tft_panel.h"

#ifdef QUANTUM_PAINTER_ILI9163_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_ILI9163_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
tft_panel_dc_reset_painter_device_t ili9163_drivers[ILI9163_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization

__attribute__((weak)) bool qp_ili9163_init(painter_device_t device, painter_rotation_t rotation) {
    // clang-format off
    const uint8_t ili9163_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        ILI9XXX_CMD_RESET,            120,  0,
        ILI9XXX_CMD_SLEEP_OFF,          5,  0,
        ILI9XXX_SET_PIX_FMT,            0,  1, 0x55,
        ILI9XXX_SET_GAMMA,              0,  1, 0x04,
        ILI9XXX_ENABLE_3_GAMMA,         0,  1, 0x01,
        ILI9XXX_SET_FUNCTION_CTL,       0,  2, 0xFF, 0x06,
        ILI9XXX_SET_PGAMMA,             0, 15, 0x36, 0x29, 0x12, 0x22, 0x1C, 0x15, 0x42, 0xB7, 0x2F, 0x13, 0x12, 0x0A, 0x11, 0x0B, 0x06,
        ILI9XXX_SET_NGAMMA,             0, 15, 0x09, 0x16, 0x2D, 0x0D, 0x13, 0x15, 0x40, 0x48, 0x53, 0x0C, 0x1D, 0x25, 0x2E, 0x34, 0x39,
        ILI9XXX_SET_FRAME_CTL_NORMAL,   0,  2, 0x08, 0x02,
        ILI9XXX_SET_POWER_CTL_1,        0,  2, 0x0A, 0x02,
        ILI9XXX_SET_POWER_CTL_2,        0,  1, 0x02,
        ILI9XXX_SET_VCOM_CTL_1,         0,  2, 0x50, 0x63,
        ILI9XXX_SET_VCOM_CTL_2,         0,  1, 0x00,
        ILI9XXX_CMD_PARTIAL_OFF,        0,  0,
        ILI9XXX_CMD_DISPLAY_ON,        20,  0
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, ili9163_init_sequence, sizeof(ili9163_init_sequence));

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

const tft_panel_dc_reset_painter_driver_vtable_t ili9163_driver_vtable = {
    .base =
        {
            .init            = qp_ili9163_init,
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
            .display_on         = ILI9XXX_CMD_DISPLAY_ON,
            .display_off        = ILI9XXX_CMD_DISPLAY_OFF,
            .set_column_address = ILI9XXX_SET_COL_ADDR,
            .set_row_address    = ILI9XXX_SET_PAGE_ADDR,
            .enable_writes      = ILI9XXX_SET_MEM,
        },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_ILI9163_SPI_ENABLE

// Factory function for creating a handle to the ILI9163 device
painter_device_t qp_ili9163_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < ILI9163_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &ili9163_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&ili9163_driver_vtable;
            driver->base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
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

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(tft_panel_dc_reset_painter_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_ILI9163_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
