// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "color.h"
#include "qp_rgb565_surface.h"
#include "qp_draw.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Device definition
typedef struct rgb565_surface_painter_device_t {
    struct painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    // The target buffer
    uint16_t *buffer;

    // Manually manage the viewport for streaming pixel data to the display
    uint16_t viewport_l;
    uint16_t viewport_t;
    uint16_t viewport_r;
    uint16_t viewport_b;

    // Current write location to the display when streaming pixel data
    uint16_t pixdata_x;
    uint16_t pixdata_y;

    // Maintain a dirty region so we can stream only what we need
    bool     is_dirty;
    uint16_t dirty_l;
    uint16_t dirty_t;
    uint16_t dirty_r;
    uint16_t dirty_b;

} rgb565_surface_painter_device_t;

// Driver storage
rgb565_surface_painter_device_t surface_drivers[RGB565_SURFACE_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

static inline void increment_pixdata_location(rgb565_surface_painter_device_t *surface) {
    // Increment the X-position
    surface->pixdata_x++;

    // If the x-coord has gone past the right-side edge, loop it back around and increment the y-coord
    if (surface->pixdata_x > surface->viewport_r) {
        surface->pixdata_x = surface->viewport_l;
        surface->pixdata_y++;
    }

    // If the y-coord has gone past the bottom, loop it back to the top
    if (surface->pixdata_y > surface->viewport_b) {
        surface->pixdata_y = surface->viewport_t;
    }
}

static inline void setpixel(rgb565_surface_painter_device_t *surface, uint16_t x, uint16_t y, uint16_t rgb565) {
    // Skip messing with the dirty info if the original value already matches
    if (surface->buffer[y * surface->base.panel_width + x] != rgb565) {
        // Maintain dirty region
        if (surface->dirty_l > x) {
            surface->dirty_l = x;
        }
        if (surface->dirty_r < x) {
            surface->dirty_r = x;
        }
        if (surface->dirty_t > y) {
            surface->dirty_t = y;
        }
        if (surface->dirty_b < y) {
            surface->dirty_b = y;
        }

        // Always dirty after a setpixel
        surface->is_dirty = true;

        // Update the pixel data in the buffer
        surface->buffer[y * surface->base.panel_width + x] = rgb565;
    }
}

static inline void append_pixel(rgb565_surface_painter_device_t *surface, uint16_t rgb565) {
    setpixel(surface, surface->pixdata_x, surface->pixdata_y, rgb565);
    increment_pixdata_location(surface);
}

static inline void stream_pixdata(rgb565_surface_painter_device_t *surface, const uint16_t *data, uint32_t native_pixel_count) {
    for (uint32_t pixel_counter = 0; pixel_counter < native_pixel_count; ++pixel_counter) {
        append_pixel(surface, data[pixel_counter]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

static bool qp_rgb565_surface_init(painter_device_t device, painter_rotation_t rotation) {
    struct painter_driver_t *        driver  = (struct painter_driver_t *)device;
    rgb565_surface_painter_device_t *surface = (rgb565_surface_painter_device_t *)driver;
    memset(surface->buffer, 0, driver->panel_width * driver->panel_height * driver->native_bits_per_pixel / 8);
    return true;
}

static bool qp_rgb565_surface_power(painter_device_t device, bool power_on) {
    // No-op.
    return true;
}

static bool qp_rgb565_surface_clear(painter_device_t device) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    driver->driver_vtable->init(device, driver->rotation); // Re-init the surface
    return true;
}

static bool qp_rgb565_surface_flush(painter_device_t device) {
    struct painter_driver_t *        driver  = (struct painter_driver_t *)device;
    rgb565_surface_painter_device_t *surface = (rgb565_surface_painter_device_t *)driver;
    surface->dirty_l = surface->dirty_t = UINT16_MAX;
    surface->dirty_r = surface->dirty_b = 0;
    surface->is_dirty                   = false;
    return true;
}

static bool qp_rgb565_surface_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    struct painter_driver_t *        driver  = (struct painter_driver_t *)device;
    rgb565_surface_painter_device_t *surface = (rgb565_surface_painter_device_t *)driver;

    // Set the viewport locations
    surface->viewport_l = left;
    surface->viewport_t = top;
    surface->viewport_r = right;
    surface->viewport_b = bottom;

    // Reset the write location to the top left
    surface->pixdata_x = left;
    surface->pixdata_y = top;
    return true;
}

// Stream pixel data to the current write position in GRAM
static bool qp_rgb565_surface_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    struct painter_driver_t *        driver  = (struct painter_driver_t *)device;
    rgb565_surface_painter_device_t *surface = (rgb565_surface_painter_device_t *)driver;
    stream_pixdata(surface, (const uint16_t *)pixel_data, native_pixel_count);
    return true;
}

// Pixel colour conversion
static bool qp_rgb565_surface_palette_convert_rgb565_swapped(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    for (int16_t i = 0; i < palette_size; ++i) {
        RGB      rgb      = hsv_to_rgb_nocie((HSV){palette[i].hsv888.h, palette[i].hsv888.s, palette[i].hsv888.v});
        uint16_t rgb565   = (((uint16_t)rgb.r) >> 3) << 11 | (((uint16_t)rgb.g) >> 2) << 5 | (((uint16_t)rgb.b) >> 3);
        palette[i].rgb565 = __builtin_bswap16(rgb565);
    }
    return true;
}

// Append pixels to the target location, keyed by the pixel index
static bool qp_rgb565_surface_append_pixels_rgb565(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    uint16_t *buf = (uint16_t *)target_buffer;
    for (uint32_t i = 0; i < pixel_count; ++i) {
        buf[pixel_offset + i] = palette[palette_indices[i]].rgb565;
    }
    return true;
}

const struct painter_driver_vtable_t rgb565_surface_driver_vtable = {
    .init            = qp_rgb565_surface_init,
    .power           = qp_rgb565_surface_power,
    .clear           = qp_rgb565_surface_clear,
    .flush           = qp_rgb565_surface_flush,
    .pixdata         = qp_rgb565_surface_pixdata,
    .viewport        = qp_rgb565_surface_viewport,
    .palette_convert = qp_rgb565_surface_palette_convert_rgb565_swapped,
    .append_pixels   = qp_rgb565_surface_append_pixels_rgb565,
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comms vtable

static bool qp_rgb565_surface_comms_init(painter_device_t device) {
    // No-op.
    return true;
}
static bool qp_rgb565_surface_comms_start(painter_device_t device) {
    // No-op.
    return true;
}
static void qp_rgb565_surface_comms_stop(painter_device_t device) {
    // No-op.
}
uint32_t qp_rgb565_surface_comms_send(painter_device_t device, const void *data, uint32_t byte_count) {
    // No-op.
    return byte_count;
}

struct painter_comms_vtable_t rgb565_surface_driver_comms_vtable = {
    // These are all effective no-op's because they're not actually needed.
    .comms_init  = qp_rgb565_surface_comms_init,
    .comms_start = qp_rgb565_surface_comms_start,
    .comms_stop  = qp_rgb565_surface_comms_stop,
    .comms_send  = qp_rgb565_surface_comms_send};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Factory function for creating a handle to an rgb565 surface

painter_device_t qp_rgb565_make_surface(uint16_t panel_width, uint16_t panel_height, void *buffer) {
    for (uint32_t i = 0; i < RGB565_SURFACE_NUM_DEVICES; ++i) {
        rgb565_surface_painter_device_t *driver = &surface_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = &rgb565_surface_driver_vtable;
            driver->base.comms_vtable          = &rgb565_surface_driver_comms_vtable;
            driver->base.native_bits_per_pixel = 16; // RGB565
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;
            driver->buffer                     = (uint16_t *)buffer;
            return (painter_device_t)driver;
        }
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Drawing routine to copy out the dirty region and send it to another device

bool qp_rgb565_surface_draw(painter_device_t surface, painter_device_t display, uint16_t x, uint16_t y) {
    struct painter_driver_t *        surface_driver = (struct painter_driver_t *)surface;
    rgb565_surface_painter_device_t *surface_handle = (rgb565_surface_painter_device_t *)surface_driver;

    // If we're not dirty... we're done.
    if (!surface_handle->is_dirty) {
        return true;
    }

    // Set the target drawing area
    bool ok = qp_viewport(display, x + surface_handle->dirty_l, y + surface_handle->dirty_t, x + surface_handle->dirty_r, y + surface_handle->dirty_b);
    if (!ok) {
        return false;
    }

    // Housekeeping of the amount of pixels to transfer
    uint32_t  total_pixel_count = QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE / sizeof(uint16_t);
    uint32_t  pixel_counter     = 0;
    uint16_t *target_buffer     = (uint16_t *)qp_internal_global_pixdata_buffer;

    // Fill the global pixdata area so that we can start transferring to the panel
    for (uint16_t y = surface_handle->dirty_t; y <= surface_handle->dirty_b; ++y) {
        for (uint16_t x = surface_handle->dirty_l; x <= surface_handle->dirty_r; ++x) {
            // Update the target buffer
            target_buffer[pixel_counter++] = surface_handle->buffer[y * surface_handle->base.panel_width + x];

            // If we've accumulated enough data, send it
            if (pixel_counter == total_pixel_count) {
                ok = qp_pixdata(display, qp_internal_global_pixdata_buffer, pixel_counter);
                if (!ok) {
                    return false;
                }
                // Reset the counter
                pixel_counter = 0;
            }
        }
    }

    // If there's any leftover data, send it
    if (pixel_counter > 0) {
        ok = qp_pixdata(display, qp_internal_global_pixdata_buffer, pixel_counter);
        if (!ok) {
            return false;
        }
    }

    // Clear the dirty info for the surface
    return qp_flush(surface);
}
