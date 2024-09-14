// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

/* Code adapted from Zephyr's and Adafruit's drivers
 *
 * Should support several LS0xx because they are pretty much
 * the same, with different sizes.
 *
 * Driver was developed on a LS013B7DH03, cant grant anything else will work as is.
 *
 * Note: xx does not mean 2 chars, names are pretty long
 */

#include "qp_internal.h"
#include "qp_surface.h"
#include "qp_surface_internal.h"
#include "qp_ls0xx_panel.h"
#include "qp_ls0xx_opcodes.h"

#ifdef QUANTUM_PAINTER_SPI_ENABLE
#    include "spi_master.h"
#endif // QUANTUM_PAINTER_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

__attribute__((weak)) bool qp_ls0xx_init(painter_device_t device, painter_rotation_t rotation) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    painter_driver_t *          surface = (painter_driver_t *)&mip_dev->surface;

    // Change the surface geometry based on the panel rotation
    if (rotation == QP_ROTATION_90 || rotation == QP_ROTATION_270) {
        surface->panel_width  = mip_dev->base.panel_height;
        surface->panel_height = mip_dev->base.panel_width;
    } else {
        surface->panel_width  = mip_dev->base.panel_width;
        surface->panel_height = mip_dev->base.panel_height;
    }

    // Init the internal surface
    if (!surface->driver_vtable->init(surface, QP_ROTATION_0)) {
        qp_dprintf("Failed to init internal surface in qp_ls0xx_init\n");
        return false;
    }

    mip_dev->base.rotation = rotation;

    writePinHigh(mip_dev->spi_config.chip_select_pin);
    const uint8_t ls0xx_init_sequence[] = {LS0XX_CLEAR, 0};
    spi_transmit(ls0xx_init_sequence, ARRAY_SIZE(ls0xx_init_sequence));
    writePinLow(mip_dev->spi_config.chip_select_pin);

    return true;
}

bool qp_ls0xx_passthru_power(painter_device_t device, bool power_on) {
    // No-op
    return true;
}

bool qp_ls0xx_passthru_clear(painter_device_t device) {
    // Just re-init the display
    painter_driver_t *driver = (painter_driver_t *)device;
    return qp_ls0xx_init(device, driver->rotation);
}

bool qp_ls0xx_flush(painter_device_t device) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    surface_painter_device_t *  surface = &(mip_dev->surface);
    surface_dirty_data_t        dirty   = surface->dirty;

    if (!dirty.is_dirty) {
        // nothing to be sent
        return true;
    }

    // find out dirty area
    // update is done on **complete** horizontal lines
    // which means that if the device is rotated 90 or 270 we need to check l/r instead
    uint16_t top, bottom;
    switch (mip_dev->base.rotation) {
        case QP_ROTATION_0:
            top    = dirty.t;
            bottom = dirty.b;
            break;

        // TODO: Check whether this are backwards
        case QP_ROTATION_90:
            top    = dirty.l;
            bottom = dirty.r;
            break;

        case QP_ROTATION_180:
            top    = dirty.b;
            bottom = dirty.t;
            break;

        case QP_ROTATION_270:
            top    = dirty.r;
            bottom = dirty.l;
            break;
    }

    // bytes sent for each row's data
    uint8_t bytes_per_line = (mip_dev->base.panel_width + 7) / 8 * mip_dev->base.native_bits_per_pixel;
    // offset used to access such data
    uint16_t buffer_offset = top * bytes_per_line;

    // start sending
    writePinHigh(mip_dev->spi_config.chip_select_pin);
    uint8_t cmd = LS0XX_WRITE | LS0XX_VCOM;
    spi_transmit(&cmd, 1);

    // dummy data for alignment, value doesnt matter
    uint8_t dummy = 0;

    // iterate over the lines
    for (uint8_t i = 0; i < bottom + 1 - top; ++i) {
        // set y-pos (counts from 1, needs the `+1`)
        uint8_t n_line = bitrev(i + top + 1);
        spi_transmit(&n_line, 1);

        // send data
        spi_transmit(&surface->u8buffer[buffer_offset], bytes_per_line);
        buffer_offset += bytes_per_line;

        spi_transmit(&dummy, 1);
    }

    spi_transmit(&dummy, 1);
    writePinLow(mip_dev->spi_config.chip_select_pin);

    // clear surface's dirty area, no API to prevent extra prints
    surface->base.driver_vtable->flush(surface);

    return true;
}

bool qp_ls0xx_passthru_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    painter_driver_t *          surface = (painter_driver_t *)&mip_dev->surface;

    return surface->driver_vtable->viewport(surface, left, top, right, bottom);
}

bool qp_ls0xx_passthru_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    painter_driver_t *          surface = (painter_driver_t *)&mip_dev->surface;

    return surface->driver_vtable->pixdata(surface, pixel_data, native_pixel_count);
}

bool qp_ls0xx_passthru_palette_convert(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    painter_driver_t *          surface = (painter_driver_t *)&mip_dev->surface;

    return surface->driver_vtable->palette_convert(surface, palette_size, palette);
}

bool qp_ls0xx_passthru_append_pixels(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    painter_driver_t *          surface = (painter_driver_t *)&mip_dev->surface;

    return surface->driver_vtable->append_pixels(surface, target_buffer, palette, pixel_offset, pixel_count, palette_indices);
}

bool qp_ls0xx_passthru_append_pixdata(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)device;
    painter_driver_t *          surface = (painter_driver_t *)&mip_dev->surface;

    return surface->driver_vtable->append_pixdata(surface, target_buffer, pixdata_offset, pixdata_byte);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const painter_driver_vtable_t ls0xx_driver_vtable = {
    .init            = qp_ls0xx_init,
    .power           = qp_ls0xx_passthru_power,
    .clear           = qp_ls0xx_passthru_clear,
    .flush           = qp_ls0xx_flush,
    .pixdata         = qp_ls0xx_passthru_pixdata,
    .viewport        = qp_ls0xx_passthru_viewport,
    .palette_convert = qp_ls0xx_passthru_palette_convert,
    .append_pixels   = qp_ls0xx_passthru_append_pixels,
    .append_pixdata  = qp_ls0xx_passthru_append_pixdata,
};
