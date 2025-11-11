// Copyright 2021 Nick Brassel (@tzarc)
// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_ili9486.h"
#include "qp_ili9xxx_opcodes.h"
#include "qp_tft_panel.h"

#ifdef QUANTUM_PAINTER_ILI9486_SPI_ENABLE
#    include "spi_master.h"
#    include <qp_comms_spi.h>
#endif // QUANTUM_PAINTER_ILI9486_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
tft_panel_dc_reset_painter_device_t ili9486_drivers[ILI9486_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization

bool qp_ili9486_init(painter_device_t device, painter_rotation_t rotation) {
    // clang-format off
    const uint8_t ili9486_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        ILI9XXX_CMD_RESET,            120,  0,
        ILI9XXX_SET_PIX_FMT,            0,  1, 0x55,
        ILI9XXX_SET_PGAMMA,             0, 15, 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
        ILI9XXX_SET_NGAMMA,             0, 15, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
        ILI9XXX_SET_POWER_CTL_1,        0,  2, 0x0D, 0x0D,
        ILI9XXX_SET_POWER_CTL_2,        0,  2, 0x43, 0x00,
        ILI9XXX_SET_POWER_CTL_3,        0,  1, 0x00,
        ILI9XXX_SET_VCOM_CTL_1,         0,  4, 0x00, 0x48, 0x00, 0x48,
        ILI9XXX_SET_INVERSION_CTL,      0,  1, 0x02,
    };
    // clang-format on
    if (!qp_comms_bulk_command_sequence(device, ili9486_init_sequence, sizeof(ili9486_init_sequence))) {
        return false;
    }

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = ILI9XXX_MADCTL_BGR,
        [QP_ROTATION_90]  = ILI9XXX_MADCTL_BGR | ILI9XXX_MADCTL_MV,
        [QP_ROTATION_180] = ILI9XXX_MADCTL_BGR,
        [QP_ROTATION_270] = ILI9XXX_MADCTL_BGR | ILI9XXX_MADCTL_MV,
    };
    const uint8_t functl[] = {
        [QP_ROTATION_0]   = 0x42,
        [QP_ROTATION_90]  = 0x62,
        [QP_ROTATION_180] = 0x22,
        [QP_ROTATION_270] = 0x02,
    };

    // clang-format off
    uint8_t rotation_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        ILI9XXX_SET_MEM_ACS_CTL,        0,  1, madctl[rotation],
        ILI9XXX_SET_FUNCTION_CTL,       0,  2, 0x00, functl[rotation],
        ILI9XXX_CMD_SLEEP_OFF,          5,  0,
        ILI9XXX_CMD_DISPLAY_ON,         5,  0,
    };
    // clang-format on
    return qp_comms_bulk_command_sequence(device, rotation_sequence, sizeof(rotation_sequence));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

// waveshare variant needs some tweaks due to shift registers
static bool qp_comms_spi_dc_reset_send_command_odd_cs_pulse(painter_device_t device, uint8_t cmd) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    gpio_write_pin_low(comms_config->spi_config.chip_select_pin);
    qp_comms_spi_dc_reset_send_command(device, cmd);
    gpio_write_pin_high(comms_config->spi_config.chip_select_pin);

    return true;
}

static uint32_t qp_comms_spi_send_data_odd_cs_pulse(painter_device_t device, const void *data, uint32_t byte_count) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    uint32_t       bytes_remaining = byte_count;
    const uint8_t *p               = (const uint8_t *)data;
    uint32_t       max_msg_length  = 1024;

    gpio_write_pin_high(comms_config->dc_pin);
    while (bytes_remaining > 0) {
        uint32_t bytes_this_loop = MIN(bytes_remaining, max_msg_length);
        bool     odd_bytes       = bytes_this_loop & 1;

        // send data
        gpio_write_pin_low(comms_config->spi_config.chip_select_pin);
        spi_transmit(p, bytes_this_loop);
        p += bytes_this_loop;

        // extra CS toggle, for alignment
        if (odd_bytes) {
            gpio_write_pin_high(comms_config->spi_config.chip_select_pin);
            gpio_write_pin_low(comms_config->spi_config.chip_select_pin);
        }

        bytes_remaining -= bytes_this_loop;
    }

    return byte_count - bytes_remaining;
}

static uint32_t qp_ili9486_send_data_toggling(painter_device_t device, const uint8_t *data, uint32_t byte_count) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    uint32_t ret;
    for (uint8_t j = 0; j < byte_count; ++j) {
        gpio_write_pin_low(comms_config->spi_config.chip_select_pin);
        ret = qp_comms_spi_dc_reset_send_data(device, &data[j], 1);
        gpio_write_pin_high(comms_config->spi_config.chip_select_pin);
    }

    return ret;
}

static bool qp_comms_spi_send_command_sequence_odd_cs_pulse(painter_device_t device, const uint8_t *sequence, size_t sequence_len) {
    for (size_t i = 0; i < sequence_len;) {
        uint8_t command   = sequence[i];
        uint8_t delay     = sequence[i + 1];
        uint8_t num_bytes = sequence[i + 2];

        qp_comms_spi_dc_reset_send_command_odd_cs_pulse(device, command);
        if (num_bytes > 0) {
            qp_ili9486_send_data_toggling(device, &sequence[i + 3], num_bytes);
        }

        if (delay > 0) {
            wait_ms(delay);
        }
        i += (3 + num_bytes);
    }

    return true;
}

static bool qp_ili9486_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    painter_driver_t *                          driver = (painter_driver_t *)device;
    tft_panel_dc_reset_painter_driver_vtable_t *vtable = (tft_panel_dc_reset_painter_driver_vtable_t *)driver->driver_vtable;

    // Fix up the drawing location if required
    left += driver->offset_x;
    right += driver->offset_x;
    top += driver->offset_y;
    bottom += driver->offset_y;

    // Check if we need to manually swap the window coordinates based on whether or not we're in a sideways rotation
    if (vtable->swap_window_coords && (driver->rotation == QP_ROTATION_90 || driver->rotation == QP_ROTATION_270)) {
        uint16_t temp;

        temp = left;
        left = top;
        top  = temp;

        temp   = right;
        right  = bottom;
        bottom = temp;
    }

    // Set up the x-window
    uint8_t xbuf[4] = {left >> 8, left & 0xFF, right >> 8, right & 0xFF};
    qp_comms_spi_dc_reset_send_command_odd_cs_pulse(device, vtable->opcodes.set_column_address);
    qp_ili9486_send_data_toggling(device, xbuf, 4);

    // Set up the y-window
    uint8_t ybuf[4] = {top >> 8, top & 0xFF, bottom >> 8, bottom & 0xFF};
    qp_comms_spi_dc_reset_send_command_odd_cs_pulse(device, vtable->opcodes.set_row_address);
    qp_ili9486_send_data_toggling(device, ybuf, 4);

    // Lock in the window
    qp_comms_spi_dc_reset_send_command_odd_cs_pulse(device, vtable->opcodes.enable_writes);
    return true;
}

// Regular
const tft_panel_dc_reset_painter_driver_vtable_t ili9486_driver_vtable = {
    .base =
        {
            .init            = qp_ili9486_init,
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

// Waveshare tweaks
const tft_panel_dc_reset_painter_driver_vtable_t ili9486_waveshare_driver_vtable = {
    .base =
        {
            .init            = qp_ili9486_init,
            .power           = qp_tft_panel_power,
            .clear           = qp_tft_panel_clear,
            .flush           = qp_tft_panel_flush,
            .pixdata         = qp_tft_panel_pixdata,
            .viewport        = qp_ili9486_viewport,
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

static const painter_comms_with_command_vtable_t spi_comms_odd_cs_pulse_vtable = {
    .base =
        {
            .comms_init  = qp_comms_spi_dc_reset_init,
            .comms_start = qp_comms_spi_start,
            .comms_send  = qp_comms_spi_send_data_odd_cs_pulse,
            .comms_stop  = qp_comms_spi_stop,
        },
    .send_command          = qp_comms_spi_dc_reset_send_command_odd_cs_pulse,
    .bulk_command_sequence = qp_comms_spi_send_command_sequence_odd_cs_pulse,
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_ILI9486_SPI_ENABLE

// Factory function for creating a handle to the ILI9486 device
painter_device_t qp_ili9486_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < ILI9486_NUM_DEVICES; ++i) {
        tft_panel_dc_reset_painter_device_t *driver = &ili9486_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&ili9486_driver_vtable;
            driver->base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
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

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(tft_panel_dc_reset_painter_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

painter_device_t qp_ili9486_make_spi_waveshare_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    painter_device_t device = qp_ili9486_make_spi_device(panel_width, panel_height, chip_select_pin, dc_pin, reset_pin, spi_divisor, spi_mode);
    if (device) {
        tft_panel_dc_reset_painter_device_t *driver = (tft_panel_dc_reset_painter_device_t *)device;
        driver->base.driver_vtable                  = (const painter_driver_vtable_t *)&ili9486_waveshare_driver_vtable;
        driver->base.comms_vtable                   = (const painter_comms_vtable_t *)&spi_comms_odd_cs_pulse_vtable;
    }
    return device;
}

#endif // QUANTUM_PAINTER_ILI9486_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
