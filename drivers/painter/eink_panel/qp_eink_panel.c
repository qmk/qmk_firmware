// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdlib.h> // abs

#include "qp_comms.h"
#include "qp_draw.h"
#include "qp_eink_panel.h"
#include "qp_internal.h"
#include "qp_surface.h"
#include "qp_surface_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE: The way in which data is stored may break if QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE is not an even number of bytes

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper functions

// Reset can_flush flag back to true after timeout
uint32_t can_flush_callback(uint32_t trigger_time, void *cb_arg) {
    eink_panel_dc_reset_painter_device_t *driver = (eink_panel_dc_reset_painter_device_t *)cb_arg;
    driver->can_flush                            = true;
    return 0;
}

// Set can_flush to false and schedule its cleanup
void qp_eink_update_can_flush(painter_device_t device) {
    eink_panel_dc_reset_painter_device_t *driver = (eink_panel_dc_reset_painter_device_t *)device;
    driver->can_flush                            = false;
    defer_exec(driver->timeout, can_flush_callback, (void *)device);
}

static inline void decode_masked_pixels(uint8_t *pixels, uint32_t byte, uint8_t *black, uint8_t *color) {
    /* Convert pixel data into convenient representation, buffer holds data as:
     * B0C0 B1C1 B2C2 B3C3 || B4C4 B5C5 B6C6 B7C7 ...
     *
     * This function shuffles it so we get
     *   black_data: B7B6B5B4B3B2B1B0
     *   color_data: C7C6C5C4C3C2C1C0
     */
    uint16_t raw_data = (pixels[byte] << 8) | (pixels[byte + 1]);

    // clear data so we can simply |=
    *black = 0;
    *color = 0;

    uint16_t black_mask = 1 << 15;
    uint16_t color_mask = 1 << 14;

    for (uint8_t i = 0; i < 8; ++i) {
        bool black_bit = raw_data & black_mask;
        bool color_bit = raw_data & color_mask;

        black_mask >>= 2;
        color_mask >>= 2;

        *black |= black_bit << i;
        *color |= color_bit << i;
    }
}

// Used to interpolate any HSV888 to the nearest of the three colors
// Instead of doing sqrt(dx**2 + dy**2 + dz**2) - aka: pythagorean distance
// ... Lets just add the differences together, which is faster
static inline uint16_t hsv_distance(HSV hsv1, HSV hsv2) {
    return abs(hsv1.h - hsv2.h) + abs(hsv1.s - hsv2.s) + abs(hsv1.v - hsv2.v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

// Power control
bool qp_eink_panel_power(painter_device_t device, bool power_on) {
    painter_driver_t *                           driver = (painter_driver_t *)device;
    eink_panel_dc_reset_painter_driver_vtable_t *vtable = (eink_panel_dc_reset_painter_driver_vtable_t *)driver->driver_vtable;

    qp_comms_command(device, power_on ? vtable->opcodes.display_on : vtable->opcodes.display_off);

    return true;
}

// Screen clear
bool qp_eink_panel_clear(painter_device_t device) {
    painter_driver_t *driver = (painter_driver_t *)device;
    return qp_init(device, driver->rotation);
}

// Screen flush
bool qp_eink_panel_flush(painter_device_t device) {
    eink_panel_dc_reset_painter_device_t *       driver  = (eink_panel_dc_reset_painter_device_t *)device;
    eink_panel_dc_reset_painter_driver_vtable_t *vtable  = (eink_panel_dc_reset_painter_driver_vtable_t *)driver->base.driver_vtable;
    surface_painter_device_t *                   black   = (surface_painter_device_t *)driver->black_surface;
    surface_painter_device_t *                   color   = (surface_painter_device_t *)driver->color_surface;
    uint32_t                                     n_bytes = SURFACE_REQUIRED_BUFFER_BYTE_SIZE(driver->base.panel_width, driver->base.panel_height, 1);

    if (!black->dirty.is_dirty && !color->dirty.is_dirty) {
        qp_dprintf("qp_eink_panel_flush: done (no changes to be sent)\n");
        return true;
    }

    if (!driver->can_flush) {
        qp_dprintf("qp_eink_panel_flush: fail (can_flush == false)\n");
        return false;
    }

    qp_comms_command(device, vtable->opcodes.send_black_data);
    qp_comms_send(device, black->buffer, n_bytes);

    qp_comms_command(device, vtable->opcodes.send_color_data);
    qp_comms_send(device, color->buffer, n_bytes);

    qp_comms_command(device, vtable->opcodes.refresh);

    qp_eink_update_can_flush(device);

    // Clear dirty area
    qp_flush(driver->black_surface);
    qp_flush(driver->color_surface);

    return true;
}

// Viewport to draw to
bool qp_eink_panel_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    eink_panel_dc_reset_painter_device_t *driver = (eink_panel_dc_reset_painter_device_t *)device;

    bool ret = qp_viewport(driver->black_surface, left, top, right, bottom);
    ret &= qp_viewport(driver->color_surface, left, top, right, bottom);

    return ret;
}

// Stream pixel data to the current write position
bool qp_eink_panel_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    eink_panel_dc_reset_painter_device_t *driver = (eink_panel_dc_reset_painter_device_t *)device;
    uint8_t *                             pixels = (uint8_t *)pixel_data;

    uint32_t i   = 0;
    bool     ret = true;
    uint8_t  black_data, color_data;
    while (i < native_pixel_count) {
        // at most, 8 pixels per cycle
        uint8_t  pixels_this_loop = QP_MIN(native_pixel_count - i, 8);
        uint32_t byte             = i / 4;

        // stream data to display
        decode_masked_pixels(pixels, byte, &black_data, &color_data);

        // this is very slow with debugging on, should maybe call the vtable's function directly
        ret &= qp_pixdata(driver->black_surface, (const void *)&black_data, pixels_this_loop);
        ret &= qp_pixdata(driver->color_surface, (const void *)&color_data, pixels_this_loop);

        if (!ret) {
            qp_dprintf("qp_eink_panel_pixdata: something went wrong, quitting\n");
            return false;
        }

        // update position
        i += pixels_this_loop;
    }

    return ret;
}

// Convert supplied palette entries into their native equivalents
bool qp_eink_panel_palette_convert(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    eink_panel_dc_reset_painter_device_t *driver = (eink_panel_dc_reset_painter_device_t *)device;

    for (int16_t i = 0; i < palette_size; ++i) {
        HSV      hsv            = (HSV){palette[i].hsv888.h, palette[i].hsv888.s, palette[i].hsv888.v};
        uint16_t white_distance = hsv_distance(hsv, (HSV){HSV_WHITE});
        uint16_t black_distance = hsv_distance(hsv, (HSV){HSV_BLACK});
        uint16_t color_distance = hsv_distance(hsv, driver->color);

        // Default to white
        bool black = false;
        bool color = false;

        uint32_t min_distance = QP_MIN(white_distance, QP_MIN(black_distance, color_distance));
        if (min_distance == black_distance)
            black = true;
        else if (min_distance == color_distance)
            color = true;

        uint8_t converted = (black << 1) | (color << 0);

        palette[i].mono = converted ^ driver->invert_mask;
    }

    return true;
}

// Append pixels to the target location, keyed by the pixel index
bool qp_eink_panel_append_pixels(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    for (uint32_t i = 0; i < pixel_count; ++i) {
        uint32_t pixel_num = pixel_offset + i;

        // each pixel takes 2 bits, aka each byte holds 4 pixels, offset based on that
        uint32_t byte_offset = pixel_num / 4;
        uint8_t  bit_offset  = 3 - (pixel_num % 4);

        // check each color bit from palette
        bool black_bit = palette[palette_indices[i]].mono & 0b10;
        bool color_bit = palette[palette_indices[i]].mono & 0b01;

        // compute where data goes
        // Data ends up arranged: B0R0B1R1B2R2B3R3 | ...
        uint8_t black_mask = 1 << (2 * bit_offset + 1);
        uint8_t color_mask = 1 << (2 * bit_offset + 0);

        // add it
        if (black_bit)
            target_buffer[byte_offset] |= black_mask;
        else
            target_buffer[byte_offset] &= ~black_mask;

        if (color_bit)
            target_buffer[byte_offset] |= color_mask;
        else
            target_buffer[byte_offset] &= ~color_mask;
    }

    return true;
}

bool qp_eink_panel_append_pixdata(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte) {
    qp_dprintf("qp_eink_panel_append_pixdata: should not get here\n");
    return false;
}
