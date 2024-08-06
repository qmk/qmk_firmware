// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_ls0xx.h"
#include "qp_ls0xx_panel.h"

#ifdef QUANTUM_PAINTER_LS0XX_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_LS0XX_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
mip_panel_painter_device_t ls0xx_device_t_drivers[LS0XX_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_LS0XX_SPI_ENABLE

// Factory function for creating a handle to the LS0XX device
painter_device_t qp_ls0xx_device_t_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode, void *buf) {
    for (uint32_t i = 0; i < LS0XX_NUM_DEVICES; ++i) {
        mip_panel_painter_device_t *driver = &ls0xx_device_t_drivers[i];
        if (!driver->base.driver_vtable) {
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->surface, 1, panel_width, panel_height, buf);
            if (!surface) {
                return NULL;
            }
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&ls0xx_driver_vtable;
            driver->base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_vtable;
            driver->base.native_bits_per_pixel = 1;
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;

            // SPI and other pin configuration
            driver->base.comms_config          = &driver->spi_config;
            driver->spi_config.chip_select_pin = chip_select_pin;
            driver->spi_config.cs_active_low   = false;
            driver->spi_config.lsb_first       = false;
            driver->spi_config.divisor         = spi_divisor;
            driver->spi_config.mode            = spi_mode;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(mip_panel_painter_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_LS0XX_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
