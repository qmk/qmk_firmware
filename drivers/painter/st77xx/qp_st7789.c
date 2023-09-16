// Copyright 2021 Paul Cotter (@gr1mr3aver)
// Copyright 2021-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_st7789.h"
#include "qp_st77xx_opcodes.h"
#include "qp_st7789_opcodes.h"
#include "qp_tft_panel.h"

#ifdef QUANTUM_PAINTER_ST7789_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_ST7789_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
tft_panel_dc_reset_painter_device_t st7789_drivers[ST7789_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatic viewport offsets

#ifndef ST7789_NO_AUTOMATIC_OFFSETS
static inline void st7789_automatic_viewport_offsets(painter_device_t device, painter_rotation_t rotation) {
    painter_driver_t *driver = (painter_driver_t *)device;

    // clang-format off
    const struct {
        uint16_t offset_x;
        uint16_t offset_y;
    } rotation_offsets_240x240[] = {
        [QP_ROTATION_0]   = { .offset_x =  0, .offset_y =  0 },
        [QP_ROTATION_90]  = { .offset_x =  0, .offset_y =  0 },
        [QP_ROTATION_180] = { .offset_x =  0, .offset_y = 80 },
        [QP_ROTATION_270] = { .offset_x = 80, .offset_y =  0 },
    };
    // clang-format on

    if (driver->panel_width == 240 && driver->panel_height == 240) {
        driver->offset_x = rotation_offsets_240x240[rotation].offset_x;
        driver->offset_y = rotation_offsets_240x240[rotation].offset_y;
    }
}
#endif // ST7789_NO_AUTOMATIC_OFFSETS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization

__attribute__((weak)) bool qp_st7789_init(painter_device_t device, painter_rotation_t rotation) {
    // clang-format off
    const uint8_t st7789_init_sequence[] = {
        // Command,                 Delay, N, Data[N]
        ST77XX_CMD_RESET,            120,  0,
        ST77XX_CMD_SLEEP_OFF,          5,  0,
        ST77XX_SET_PIX_FMT,            0,  1, 0x55,
        ST77XX_CMD_INVERT_ON,          0,  0,
        ST77XX_CMD_NORMAL_ON,          0,  0,
        ST77XX_CMD_DISPLAY_ON,        20,  0
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, st7789_init_sequence, sizeof(st7789_init_sequence));

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = ST77XX_MADCTL_RGB,
        [QP_ROTATION_90]  = ST77XX_MADCTL_RGB | ST77XX_MADCTL_MX | ST77XX_MADCTL_MV,
        [QP_ROTATION_180] = ST77XX_MADCTL_RGB | ST77XX_MADCTL_MX | ST77XX_MADCTL_MY,
        [QP_ROTATION_270] = ST77XX_MADCTL_RGB | ST77XX_MADCTL_MV | ST77XX_MADCTL_MY,
    };
    qp_comms_command_databyte(device, ST77XX_SET_MADCTL, madctl[rotation]);

#ifndef ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS
    st7789_automatic_viewport_offsets(device, rotation);
#endif // ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const tft_panel_dc_reset_painter_driver_vtable_t st7789_driver_vtable = {
    .base =
        {
            .init            = qp_st7789_init,
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
            .display_on         = ST77XX_CMD_DISPLAY_ON,
            .display_off        = ST77XX_CMD_DISPLAY_OFF,
            .set_column_address = ST77XX_SET_COL_ADDR,
            .set_row_address    = ST77XX_SET_ROW_ADDR,
            .enable_writes      = ST77XX_SET_MEM,
        },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_ST7789_SPI_ENABLE

// Factory function for creating a handle to the ST7789 device
painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < ST7789_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &st7789_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&st7789_driver_vtable;
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

#endif // QUANTUM_PAINTER_ST7789_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
