// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef QUANTUM_PAINTER_SURFACE_ENABLE

#    include "color.h"
#    include "qp_draw.h"
#    include "qp_surface_internal.h"
#    include "qp_comms_dummy.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Surface driver impl: rgb565

static inline void setpixel_rgb565(surface_painter_device_t *surface, uint16_t x, uint16_t y, uint16_t rgb565) {
    uint16_t w = surface->base.panel_width;
    uint16_t h = surface->base.panel_height;

    // Drop out if it's off-screen
    if (x >= w || y >= h) {
        return;
    }

    // Skip messing with the dirty info if the original value already matches
    if (surface->u16buffer[y * w + x] != rgb565) {
        // Update the dirty region
        qp_surface_update_dirty(&surface->dirty, x, y);

        // Update the pixel data in the buffer
        surface->u16buffer[y * w + x] = rgb565;
    }
}

static inline void append_pixel_rgb565(surface_painter_device_t *surface, uint16_t rgb565) {
    setpixel_rgb565(surface, surface->viewport.pixdata_x, surface->viewport.pixdata_y, rgb565);
    qp_surface_increment_pixdata_location(&surface->viewport);
}

static inline void stream_pixdata_rgb565(surface_painter_device_t *surface, const uint16_t *data, uint32_t native_pixel_count) {
    for (uint32_t pixel_counter = 0; pixel_counter < native_pixel_count; ++pixel_counter) {
        append_pixel_rgb565(surface, data[pixel_counter]);
    }
}

// Stream pixel data to the current write position in GRAM
static bool qp_surface_pixdata_rgb565(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    painter_driver_t *        driver  = (painter_driver_t *)device;
    surface_painter_device_t *surface = (surface_painter_device_t *)driver;
    stream_pixdata_rgb565(surface, (const uint16_t *)pixel_data, native_pixel_count);
    return true;
}

// Pixel colour conversion
static bool qp_surface_palette_convert_rgb565_swapped(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    for (int16_t i = 0; i < palette_size; ++i) {
        rgb_t    rgb      = hsv_to_rgb_nocie((hsv_t){palette[i].hsv888.h, palette[i].hsv888.s, palette[i].hsv888.v});
        uint16_t rgb565   = (((uint16_t)rgb.r) >> 3) << 11 | (((uint16_t)rgb.g) >> 2) << 5 | (((uint16_t)rgb.b) >> 3);
        palette[i].rgb565 = __builtin_bswap16(rgb565);
    }
    return true;
}

// Append pixels to the target location, keyed by the pixel index
static bool qp_surface_append_pixels_rgb565(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    uint16_t *buf = (uint16_t *)target_buffer;
    for (uint32_t i = 0; i < pixel_count; ++i) {
        buf[pixel_offset + i] = palette[palette_indices[i]].rgb565;
    }
    return true;
}

static bool rgb565_target_pixdata_transfer(painter_driver_t *surface_driver, painter_driver_t *target_driver, uint16_t x, uint16_t y, bool entire_surface) {
    surface_painter_device_t *surface_handle = (surface_painter_device_t *)surface_driver;

    uint16_t l = entire_surface ? 0 : surface_handle->dirty.l;
    uint16_t t = entire_surface ? 0 : surface_handle->dirty.t;
    uint16_t r = entire_surface ? (surface_handle->base.panel_width - 1) : surface_handle->dirty.r;
    uint16_t b = entire_surface ? (surface_handle->base.panel_height - 1) : surface_handle->dirty.b;

    // Set the target drawing area
    bool ok = qp_viewport((painter_device_t)target_driver, x + l, y + t, x + r, y + b);
    if (!ok) {
        qp_dprintf("rgb565_target_pixdata_transfer: fail (could not set target viewport)\n");
        return false;
    }

    // Housekeeping of the amount of pixels to transfer
    uint32_t  total_pixel_count = (8 * QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE) / surface_driver->native_bits_per_pixel;
    uint32_t  pixel_counter     = 0;
    uint16_t *target_buffer     = (uint16_t *)qp_internal_global_pixdata_buffer;

    // Fill the global pixdata area so that we can start transferring to the panel
    for (uint16_t y = t; y <= b; ++y) {
        for (uint16_t x = l; x <= r; ++x) {
            // Update the target buffer
            target_buffer[pixel_counter++] = surface_handle->u16buffer[y * surface_handle->base.panel_width + x];

            // If we've accumulated enough data, send it
            if (pixel_counter == total_pixel_count) {
                ok = qp_pixdata((painter_device_t)target_driver, qp_internal_global_pixdata_buffer, pixel_counter);
                if (!ok) {
                    qp_dprintf("rgb565_target_pixdata_transfer: fail (could not stream pixdata to target)\n");
                    return false;
                }
                // Reset the counter
                pixel_counter = 0;
            }
        }
    }

    // If there's any leftover data, send it
    if (pixel_counter > 0) {
        ok = qp_pixdata((painter_device_t)target_driver, qp_internal_global_pixdata_buffer, pixel_counter);
        if (!ok) {
            qp_dprintf("rgb565_target_pixdata_transfer: fail (could not stream pixdata to target)\n");
            return false;
        }
    }

    return true;
}

static bool qp_surface_append_pixdata_rgb565(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte) {
    target_buffer[pixdata_offset] = pixdata_byte;
    return true;
}

const surface_painter_driver_vtable_t rgb565_surface_driver_vtable = {
    .base =
        {
            .init            = qp_surface_init,
            .power           = qp_surface_power,
            .clear           = qp_surface_clear,
            .flush           = qp_surface_flush,
            .pixdata         = qp_surface_pixdata_rgb565,
            .viewport        = qp_surface_viewport,
            .palette_convert = qp_surface_palette_convert_rgb565_swapped,
            .append_pixels   = qp_surface_append_pixels_rgb565,
            .append_pixdata  = qp_surface_append_pixdata_rgb565,
        },
    .target_pixdata_transfer = rgb565_target_pixdata_transfer,
};

SURFACE_FACTORY_FUNCTION_IMPL(qp_make_rgb565_surface, rgb565_surface_driver_vtable, 16);

#endif // QUANTUM_PAINTER_SURFACE_ENABLE
