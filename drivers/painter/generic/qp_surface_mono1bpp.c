// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef QUANTUM_PAINTER_SURFACE_ENABLE

#    include "color.h"
#    include "qp_draw.h"
#    include "qp_surface_internal.h"
#    include "qp_comms_dummy.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Surface driver impl: mono1bpp

static inline void setpixel_mono1bpp(surface_painter_device_t *surface, uint16_t x, uint16_t y, bool mono_pixel) {
    uint16_t w = surface->base.panel_width;
    uint16_t h = surface->base.panel_height;

    // Drop out if it's off-screen
    if (x >= w || y >= h) {
        return;
    }

    // Figure out which location needs to be updated
    uint32_t pixel_num   = y * w + x;
    uint32_t byte_offset = pixel_num / 8;
    uint8_t  bit_offset  = pixel_num % 8;
    bool     curr_val    = (surface->u8buffer[byte_offset] & (1 << bit_offset)) ? true : false;

    // Skip messing with the dirty info if the original value already matches
    if (curr_val != mono_pixel) {
        // Update the dirty region
        qp_surface_update_dirty(&surface->dirty, x, y);

        // Update the pixel data in the buffer
        if (mono_pixel) {
            surface->u8buffer[byte_offset] |= (1 << bit_offset);
        } else {
            surface->u8buffer[byte_offset] &= ~(1 << bit_offset);
        }
    }
}

static inline void append_pixel_mono1bpp(surface_painter_device_t *surface, bool mono_pixel) {
    setpixel_mono1bpp(surface, surface->viewport.pixdata_x, surface->viewport.pixdata_y, mono_pixel);
    qp_surface_increment_pixdata_location(&surface->viewport);
}

static inline void stream_pixdata_mono1bpp(surface_painter_device_t *surface, const uint8_t *data, uint32_t native_pixel_count) {
    for (uint32_t pixel_counter = 0; pixel_counter < native_pixel_count; ++pixel_counter) {
        uint32_t byte_offset = pixel_counter / 8;
        uint8_t  bit_offset  = pixel_counter % 8;
        append_pixel_mono1bpp(surface, (data[byte_offset] & (1 << bit_offset)) ? true : false);
    }
}

// Stream pixel data to the current write position in GRAM
static bool qp_surface_pixdata_mono1bpp(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    painter_driver_t *        driver  = (painter_driver_t *)device;
    surface_painter_device_t *surface = (surface_painter_device_t *)driver;
    stream_pixdata_mono1bpp(surface, (const uint8_t *)pixel_data, native_pixel_count);
    return true;
}

// Pixel colour conversion
static bool qp_surface_palette_convert_mono1bpp(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    for (int16_t i = 0; i < palette_size; ++i) {
        palette[i].mono = (palette[i].hsv888.v > 127) ? 1 : 0;
    }
    return true;
}

// Append pixels to the target location, keyed by the pixel index
static bool qp_surface_append_pixels_mono1bpp(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    for (uint32_t i = 0; i < pixel_count; ++i) {
        uint32_t pixel_num   = pixel_offset + i;
        uint32_t byte_offset = pixel_num / 8;
        uint8_t  bit_offset  = pixel_num % 8;
        if (palette[palette_indices[i]].mono) {
            target_buffer[byte_offset] |= (1 << bit_offset);
        } else {
            target_buffer[byte_offset] &= ~(1 << bit_offset);
        }
    }
    return true;
}

static bool mono1bpp_target_pixdata_transfer(painter_driver_t *surface_driver, painter_driver_t *target_driver, uint16_t x, uint16_t y, bool entire_surface) {
    return false; // Not yet supported.
}

static bool qp_surface_append_pixdata_mono1bpp(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte) {
    return false; // Just use 1bpp images.
}

const surface_painter_driver_vtable_t mono1bpp_surface_driver_vtable = {
    .base =
        {
            .init            = qp_surface_init,
            .power           = qp_surface_power,
            .clear           = qp_surface_clear,
            .flush           = qp_surface_flush,
            .pixdata         = qp_surface_pixdata_mono1bpp,
            .viewport        = qp_surface_viewport,
            .palette_convert = qp_surface_palette_convert_mono1bpp,
            .append_pixels   = qp_surface_append_pixels_mono1bpp,
            .append_pixdata  = qp_surface_append_pixdata_mono1bpp,
        },
    .target_pixdata_transfer = mono1bpp_target_pixdata_transfer,
};

SURFACE_FACTORY_FUNCTION_IMPL(qp_make_mono1bpp_surface, mono1bpp_surface_driver_vtable, 1);

#endif // QUANTUM_PAINTER_SURFACE_ENABLE
