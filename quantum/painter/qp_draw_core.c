// Copyright 2021-2022 Nick Brassel (@tzarc)
// Copyright 2021 Paul Cotter (@gr1mr3aver)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "compiler_support.h"
#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_draw.h"
#include "qgf.h"

STATIC_ASSERT((QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE > 0) && (QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE % 16) == 0, "QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE needs to be a non-zero multiple of 16");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables
//
// NOTE: The variables in this section are intentionally outside a stack frame. They are able to be defined with larger
//       sizes than the normal stack frames would allow, and as such need to be external.
//
//       **** DO NOT refactor this and decide to place the variables inside the function calling them -- you will ****
//       **** very likely get artifacts rendered to the screen as a result.                                       ****
//

// Buffer used for transmitting native pixel data to the downstream device.
__attribute__((__aligned__(4))) uint8_t qp_internal_global_pixdata_buffer[QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE];

// Static buffer to contain a generated color palette
static bool                                       generated_palette = false;
static int16_t                                    generated_steps   = -1;
__attribute__((__aligned__(4))) static qp_pixel_t interpolated_fg_hsv888;
__attribute__((__aligned__(4))) static qp_pixel_t interpolated_bg_hsv888;
#if QUANTUM_PAINTER_SUPPORTS_256_PALETTE
__attribute__((__aligned__(4))) qp_pixel_t qp_internal_global_pixel_lookup_table[256];
#else
__attribute__((__aligned__(4))) qp_pixel_t qp_internal_global_pixel_lookup_table[16];
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

uint32_t qp_internal_num_pixels_in_buffer(painter_device_t device) {
    painter_driver_t *driver = (painter_driver_t *)device;
    return ((QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE * 8) / driver->native_bits_per_pixel);
}

// qp_setpixel internal implementation, but accepts a buffer with pre-converted native pixel. Only the first pixel is used.
bool qp_internal_setpixel_impl(painter_device_t device, uint16_t x, uint16_t y) {
    painter_driver_t *driver = (painter_driver_t *)device;
    return driver->driver_vtable->viewport(device, x, y, x, y) && driver->driver_vtable->pixdata(device, qp_internal_global_pixdata_buffer, 1);
}

// Fills the global native pixel buffer with equivalent pixels matching the supplied HSV
void qp_internal_fill_pixdata(painter_device_t device, uint32_t num_pixels, uint8_t hue, uint8_t sat, uint8_t val) {
    painter_driver_t *driver            = (painter_driver_t *)device;
    uint32_t          pixels_in_pixdata = qp_internal_num_pixels_in_buffer(device);
    num_pixels                          = MIN(pixels_in_pixdata, num_pixels);

    // Convert the color to native pixel format
    qp_pixel_t color = {.hsv888 = {.h = hue, .s = sat, .v = val}};
    driver->driver_vtable->palette_convert(device, 1, &color);

    // Append the required number of pixels
    uint8_t palette_idx = 0;
    for (uint32_t i = 0; i < num_pixels; ++i) {
        driver->driver_vtable->append_pixels(device, qp_internal_global_pixdata_buffer, &color, i, 1, &palette_idx);
    }
}

// Resets the global palette so that it can be regenerated. Only needed if the colors are identical, but a different display is used with a different internal pixel format.
void qp_internal_invalidate_palette(void) {
    generated_palette = false;
    generated_steps   = -1;
}

// Interpolates between two colors to generate a palette
bool qp_internal_interpolate_palette(qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888, int16_t steps) {
    // Check if we need to generate a new palette -- if the input parameters match then assume the palette can stay unchanged.
    // This may present a problem if using the same parameters but a different screen converts pixels -- use qp_internal_invalidate_palette() to reset.
    if (generated_palette == true && generated_steps == steps && memcmp(&interpolated_fg_hsv888, &fg_hsv888, sizeof(fg_hsv888)) == 0 && memcmp(&interpolated_bg_hsv888, &bg_hsv888, sizeof(bg_hsv888)) == 0) {
        // We already have the correct palette, no point regenerating it.
        return false;
    }

    // Save the parameters so we know whether we can skip generation
    generated_palette      = true;
    generated_steps        = steps;
    interpolated_fg_hsv888 = fg_hsv888;
    interpolated_bg_hsv888 = bg_hsv888;

    int16_t hue_fg = fg_hsv888.hsv888.h;
    int16_t hue_bg = bg_hsv888.hsv888.h;

    // Make sure we take the "shortest" route from one hue to the other
    if ((hue_fg - hue_bg) >= 128) {
        hue_bg += 256;
    } else if ((hue_fg - hue_bg) <= -128) {
        hue_bg -= 256;
    }

    // Interpolate each of the lookup table entries
    for (int16_t i = 0; i < steps; ++i) {
        qp_internal_global_pixel_lookup_table[i].hsv888.h = (uint8_t)((hue_fg - hue_bg) * i / (steps - 1) + hue_bg);
        qp_internal_global_pixel_lookup_table[i].hsv888.s = (uint8_t)((fg_hsv888.hsv888.s - bg_hsv888.hsv888.s) * i / (steps - 1) + bg_hsv888.hsv888.s);
        qp_internal_global_pixel_lookup_table[i].hsv888.v = (uint8_t)((fg_hsv888.hsv888.v - bg_hsv888.hsv888.v) * i / (steps - 1) + bg_hsv888.hsv888.v);

        qp_dprintf("qp_internal_interpolate_palette: %3d of %d -- H: %3d, S: %3d, V: %3d\n", (int)(i + 1), (int)steps, (int)qp_internal_global_pixel_lookup_table[i].hsv888.h, (int)qp_internal_global_pixel_lookup_table[i].hsv888.s, (int)qp_internal_global_pixel_lookup_table[i].hsv888.v);
    }

    return true;
}

// Helper shared between image and font rendering -- sets up the global palette to match the palette block specified in the asset. Expects the stream to be positioned at the start of the block header.
bool qp_internal_load_qgf_palette(qp_stream_t *stream, uint8_t bpp) {
    qgf_palette_v1_t palette_descriptor;
    if (qp_stream_read(&palette_descriptor, sizeof(qgf_palette_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read palette_descriptor, expected length was not %d\n", (int)sizeof(qgf_palette_v1_t));
        return false;
    }

    // BPP determines the number of palette entries, each entry is a HSV888 triplet.
    const uint16_t palette_entries = 1u << bpp;

    // Ensure we aren't reusing any palette
    qp_internal_invalidate_palette();

    // Read the palette entries
    for (uint16_t i = 0; i < palette_entries; ++i) {
        // Read the palette entry
        qgf_palette_entry_v1_t entry;
        if (qp_stream_read(&entry, sizeof(qgf_palette_entry_v1_t), 1, stream) != 1) {
            return false;
        }

        // Update the lookup table
        qp_internal_global_pixel_lookup_table[i].hsv888.h = entry.h;
        qp_internal_global_pixel_lookup_table[i].hsv888.s = entry.s;
        qp_internal_global_pixel_lookup_table[i].hsv888.v = entry.v;

        qp_dprintf("qp_internal_load_qgf_palette: %3d of %d -- H: %3d, S: %3d, V: %3d\n", (int)(i + 1), (int)palette_entries, (int)qp_internal_global_pixel_lookup_table[i].hsv888.h, (int)qp_internal_global_pixel_lookup_table[i].hsv888.s, (int)qp_internal_global_pixel_lookup_table[i].hsv888.v);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_setpixel

bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val) {
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_setpixel: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("Failed to start comms in qp_setpixel\n");
        return false;
    }

    qp_internal_fill_pixdata(device, 1, hue, sat, val);
    bool ret = qp_internal_setpixel_impl(device, x, y);
    qp_comms_stop(device);
    qp_dprintf("qp_setpixel: %s\n", ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_line

bool qp_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val) {
    if (x0 == x1 || y0 == y1) {
        qp_dprintf("qp_line(%d, %d, %d, %d): entry (deferring to qp_rect)\n", (int)x0, (int)y0, (int)x1, (int)y1);
        bool ret = qp_rect(device, x0, y0, x1, y1, hue, sat, val, true);
        qp_dprintf("qp_line(%d, %d, %d, %d): %s (deferred to qp_rect)\n", (int)x0, (int)y0, (int)x1, (int)y1, ret ? "ok" : "fail");
        return ret;
    }

    qp_dprintf("qp_line(%d, %d, %d, %d): entry\n", (int)x0, (int)y0, (int)x1, (int)y1);
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_line: fail (validation_ok == false)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("Failed to start comms in qp_line\n");
        return false;
    }

    qp_internal_fill_pixdata(device, 1, hue, sat, val);

    // draw angled line using Bresenham's algo
    int16_t x      = ((int16_t)x0);
    int16_t y      = ((int16_t)y0);
    int16_t slopex = ((int16_t)x0) < ((int16_t)x1) ? 1 : -1;
    int16_t slopey = ((int16_t)y0) < ((int16_t)y1) ? 1 : -1;
    int16_t dx     = abs(((int16_t)x1) - ((int16_t)x0));
    int16_t dy     = -abs(((int16_t)y1) - ((int16_t)y0));

    int16_t e  = dx + dy;
    int16_t e2 = 2 * e;

    bool ret = true;
    while (x != x1 || y != y1) {
        if (!qp_internal_setpixel_impl(device, x, y)) {
            ret = false;
            break;
        }
        e2 = 2 * e;
        if (e2 >= dy) {
            e += dy;
            x += slopex;
        }
        if (e2 <= dx) {
            e += dx;
            y += slopey;
        }
    }
    // draw the last pixel
    if (!qp_internal_setpixel_impl(device, x, y)) {
        ret = false;
    }

    qp_comms_stop(device);
    qp_dprintf("qp_line(%d, %d, %d, %d): %s\n", (int)x0, (int)y0, (int)x1, (int)y1, ret ? "ok" : "fail");
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_rect

bool qp_internal_fillrect_helper_impl(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    uint32_t          pixels_in_pixdata = qp_internal_num_pixels_in_buffer(device);
    painter_driver_t *driver            = (painter_driver_t *)device;

    uint16_t l = MIN(left, right);
    uint16_t r = MAX(left, right);
    uint16_t t = MIN(top, bottom);
    uint16_t b = MAX(top, bottom);
    uint16_t w = r - l + 1;
    uint16_t h = b - t + 1;

    uint32_t remaining = w * h;
    driver->driver_vtable->viewport(device, l, t, r, b);
    while (remaining > 0) {
        uint32_t transmit = MIN(remaining, pixels_in_pixdata);
        if (!driver->driver_vtable->pixdata(device, qp_internal_global_pixdata_buffer, transmit)) {
            return false;
        }
        remaining -= transmit;
    }
    return true;
}

bool qp_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    qp_dprintf("qp_rect(%d, %d, %d, %d): entry\n", (int)left, (int)top, (int)right, (int)bottom);
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver || !driver->validate_ok) {
        qp_dprintf("qp_rect: fail (validation_ok == false)\n");
        return false;
    }

    // Cater for cases where people have submitted the coordinates backwards
    uint16_t l = MIN(left, right);
    uint16_t r = MAX(left, right);
    uint16_t t = MIN(top, bottom);
    uint16_t b = MAX(top, bottom);
    uint16_t w = r - l + 1;
    uint16_t h = b - t + 1;

    bool ret = true;
    if (!qp_comms_start(device)) {
        qp_dprintf("Failed to start comms in qp_rect\n");
        return false;
    }

    if (filled) {
        // Fill up the pixdata buffer with the required number of native pixels
        qp_internal_fill_pixdata(device, w * h, hue, sat, val);

        // Perform the draw
        ret = qp_internal_fillrect_helper_impl(device, l, t, r, b);
    } else {
        // Fill up the pixdata buffer with the required number of native pixels
        qp_internal_fill_pixdata(device, MAX(w, h), hue, sat, val);

        // Draw 4x filled single-width rects to create an outline
        if (!qp_internal_fillrect_helper_impl(device, l, t, r, t) || !qp_internal_fillrect_helper_impl(device, l, b, r, b) || !qp_internal_fillrect_helper_impl(device, l, t + 1, l, b - 1) || !qp_internal_fillrect_helper_impl(device, r, t + 1, r, b - 1)) {
            ret = false;
        }
    }

    qp_comms_stop(device);
    qp_dprintf("qp_rect(%d, %d, %d, %d): %s\n", (int)l, (int)t, (int)r, (int)b, ret ? "ok" : "fail");
    return ret;
}
