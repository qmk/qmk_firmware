// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_il91874.h"
#include "qp_il91874_opcodes.h"
#include "qp_eink_panel.h"
#include "qp_surface.h"

#ifdef QUANTUM_PAINTER_IL91874_SPI_ENABLE
#    include <qp_comms_spi.h>
#endif // QUANTUM_PAINTER_IL91874_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
eink_panel_dc_reset_painter_device_t il91874_drivers[IL91874_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization

bool qp_il91874_init(painter_device_t device, painter_rotation_t rotation) {
    struct eink_panel_dc_reset_painter_device_t *driver = (struct eink_panel_dc_reset_painter_device_t *)device;

    // clang-format off
    const uint8_t il91874_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        IL91874_POWER_ON,             120,  0,
        IL91874_PANEL_SETTING,          0,  1, 0xAF,
        IL91874_PLL,                    0,  1, 0x3A,
        IL91874_POWER_SETTING,          0,  5, 0x03, 0x00, 0x2B, 0x2B, 0x09,
        IL91874_BOOSTER_SOFT_START,     0,  3, 0x07, 0x07, 0x17,
        IL91874_MISTERY_COMMAND,        0,  2, 0x60, 0xA5,
        IL91874_MISTERY_COMMAND,        0,  2, 0x89, 0xA5,
        IL91874_MISTERY_COMMAND,        0,  2, 0x90, 0x00,
        IL91874_MISTERY_COMMAND,        0,  2, 0x93, 0xAD,
        IL91874_MISTERY_COMMAND,        0,  2, 0x73, 0x41,
        IL91874_VCM_DC_SETTING,         0,  1, 0x12,
        IL91874_CDI,                    0,  1, 0x87,
        IL91874_LUT1,                   0, 44, 0x0, 0x0, 0x0, 0x1A, 0x1A, 0x0, 0x0, 0x01, 0x0, 0xA, 0xA, 0x0, 0x0, 0x8, 0x0, 0xE, 0x1, 0xE, 0x1, 0x10, 0x0, 0xA, 0xA, 0x0, 0x0, 0x8, 0x0, 0x4, 0x10, 0x0, 0x0, 0x5, 0x0, 0x3, 0xE, 0x0, 0x0, 0xA, 0x0, 0x23, 0x0, 0x0, 0x0, 0x1,
        IL91874_LUTWW,                  0, 42, 0x90, 0x1A, 0x1A, 0x0, 0x0, 0x1, 0x40, 0x0A, 0x0A, 0x0, 0x0, 0x8, 0x84, 0xE, 0x1, 0xE, 0x1, 0x10, 0x80, 0xA, 0xA, 0x0, 0x0, 0x8, 0x0, 0x4, 0x10, 0x0, 0x0, 0x5, 0x0, 0x3, 0xE, 0x0, 0x0, 0xA, 0x0, 0x23, 0x0, 0x0, 0x0, 0x1,
        IL91874_LUTBW,                  0, 42, 0xA0, 0x1A, 0x1A, 0x0, 0x0, 0x1, 0x0, 0xA, 0xA, 0x0, 0x0, 0x8, 0x84, 0xE, 0x1, 0xE, 0x1, 0x10, 0x90, 0xA, 0xA, 0x0, 0x0, 0x8, 0xB0, 0x4, 0x10, 0x0, 0x0, 0x5, 0xB0, 0x3, 0xE, 0x0, 0x0, 0xA, 0xC0, 0x23, 0x0, 0x0, 0x0, 0x1,
        IL91874_LUTWB,                  0, 42, 0x90, 0x1A, 0x1A, 0x0, 0x0, 0x1, 0x40, 0xA, 0xA, 0x0, 0x0, 0x8, 0x84, 0xE, 0x1, 0xE, 0x1, 0x10, 0x80, 0xA, 0xA, 0x0, 0x0, 0x8, 0x0, 0x4, 0x10, 0x0, 0x0, 0x5, 0x0, 0x3, 0xE, 0x0, 0x0, 0xA, 0x0, 0x23, 0x0, 0x0, 0x0, 0x1,
        IL91874_LUTBB,                  0, 42, 0x90, 0x1a, 0x1A, 0x0, 0x0, 0x1, 0x20, 0xA, 0xA, 0x0, 0x0, 0x8, 0x84, 0xE, 0x1, 0xE, 0x1, 0x10, 0x10, 0xA, 0xA, 0x0, 0x0, 0x8, 0x0, 0x4, 0x10, 0x0, 0x0, 0x5, 0x0, 0x3, 0xE, 0x0, 0x0, 0xA, 0x0, 0x23, 0x0, 0x0, 0x0, 0x1,
        IL91874_RESOLUTION,             0,  4, (driver->base.panel_width >> 8) & 0xFF, (driver->base.panel_width) & 0xFF, (driver->base.panel_height >> 8) & 0xFF, (driver->base.panel_height) & 0xFF,
        IL91874_PDRF,                   0,  1, 0x00
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, il91874_init_sequence, sizeof(il91874_init_sequence));
    driver->base.rotation = rotation;

    qp_init(driver->black_surface, rotation);
    qp_init(driver->red_surface,   rotation);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const struct eink_panel_dc_reset_painter_driver_vtable_t il91874_driver_vtable = {
    .base =
        {
            .init            = qp_il91874_init,
            .power           = qp_eink_panel_power,
            .clear           = qp_eink_panel_clear,
            .flush           = qp_eink_panel_flush,
            .pixdata         = qp_eink_panel_pixdata,
            .viewport        = qp_eink_panel_viewport,
            .palette_convert = qp_eink_panel_palette_convert_eink3,
            .append_pixels   = qp_eink_panel_append_pixels_eink3,
        },
    .num_window_bytes   = 2,
    .swap_window_coords = false,
    .opcodes =
        {
            .display_on  = IL91874_POWER_ON,
            .display_off = IL91874_POWER_OFF,
            .send_black_data = IL91874_SEND_BLACK,
            .send_red_data = IL91874_SEND_RED,
            .refresh = IL91874_DISPLAY_REFRESH,
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_IL91874_SPI_ENABLE

// Factory function for creating a handle to the IL91874 device
painter_device_t qp_il91874_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode, void *ptr) {
    for (uint32_t i = 0; i < IL91874_NUM_DEVICES; ++i) {
        eink_panel_dc_reset_painter_device_t *driver = &il91874_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const struct painter_driver_vtable_t *)&il91874_driver_vtable;
            driver->base.comms_vtable          = (const struct painter_comms_vtable_t *)&spi_comms_with_dc_shiftreg_vtable;
            driver->base.native_bits_per_pixel = 8; // Black and red channels
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;

            driver->black_surface = qp_make_mono1bpp_surface(panel_width, panel_height, ptr);
            driver->red_surface = qp_make_mono1bpp_surface(panel_width, panel_height, ptr+SURFACE_REQUIRED_BUFFER_BYTE_SIZE(panel_width, panel_height, 1));

            driver->timeout = 3 * 60 * 1000; // 3 minutes as suggested by Adafruit
            driver->can_flush = true;

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

#endif // QUANTUM_PAINTER_IL91874_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
