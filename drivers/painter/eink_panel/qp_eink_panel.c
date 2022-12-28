// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_draw.h"
#include "qp_eink_panel.h"
#include "qp_surface.h"

// TODO: Add support for screens with partial refresh
// TODO: Add support for displays with builtin RAM

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

// Power control
bool qp_eink_panel_power(painter_device_t device, bool power_on) {
    struct painter_driver_t                            *driver = (struct painter_driver_t *)device;
    struct eink_panel_dc_reset_painter_driver_vtable_t *vtable = (struct eink_panel_dc_reset_painter_driver_vtable_t *)driver->driver_vtable;

    qp_comms_command(device, power_on ? vtable->opcodes.display_on : vtable->opcodes.display_off);

    return true;
}

// Screen clear
bool qp_eink_panel_clear(painter_device_t device) {
    struct eink_panel_dc_reset_painter_device_t *driver = (struct eink_panel_dc_reset_painter_device_t *)device;

    qp_init(driver->black_surface, driver->base.rotation);
    qp_init(driver->red_surface, driver->base.rotation);

    return true;
}

uint32_t can_flush_callback(uint32_t trigger_time, void *cb_arg) {
    struct eink_panel_dc_reset_painter_device_t *driver = (struct eink_panel_dc_reset_painter_device_t *)cb_arg;
    driver->can_flush                                   = true;
    return 0;
}

// Screen flush
bool qp_eink_panel_flush(painter_device_t device) {
    // Flushing sends the framebuffers in RAM + refresh command to apply them
    struct eink_panel_dc_reset_painter_device_t        *driver = (struct eink_panel_dc_reset_painter_device_t *)device;
    struct eink_panel_dc_reset_painter_driver_vtable_t *vtable = (struct eink_panel_dc_reset_painter_driver_vtable_t *)driver->base.driver_vtable;
    struct surface_painter_device_t                    *black  = (struct surface_painter_device_t *)driver->black_surface;
    struct surface_painter_device_t                    *red    = (struct surface_painter_device_t *)driver->red_surface;

    if (!driver->can_flush) {
        qp_dprintf("qp_eink_panel_flush: fail (can_flush is false)\n");
        return false;
    }

    uint32_t n_bytes = driver->base.panel_width * driver->base.panel_height / 8;

    qp_comms_command(device, vtable->opcodes.send_black_data);
    qp_comms_send(device, black->buffer, n_bytes);

    qp_comms_command(device, vtable->opcodes.send_red_data);
    qp_comms_send(device, red->buffer, n_bytes);

    qp_comms_command(device, vtable->opcodes.refresh);

    // Set device on can't flush mode and schedule a function to clean the flag after timeout
    driver->can_flush = false;
    defer_exec(driver->timeout, can_flush_callback, (void *)device);

    return true;
}

// Viewport to draw to
bool qp_eink_panel_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    struct eink_panel_dc_reset_painter_device_t *driver = (struct eink_panel_dc_reset_painter_device_t *)device;

    qp_viewport(driver->black_surface, left, top, right, bottom);
    qp_viewport(driver->red_surface, left, top, right, bottom);

    return true;
}

// Stream pixel data to the current write position in GRAM
bool qp_eink_panel_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    struct eink_panel_dc_reset_painter_device_t *driver = (struct eink_panel_dc_reset_painter_device_t *)device;
    struct painter_driver_t                     *black  = (struct painter_driver_t *)driver->black_surface;
    struct painter_driver_t                     *red    = (struct painter_driver_t *)driver->red_surface;

    uint8_t *pixels = (uint8_t *)pixel_data;

    for (uint32_t i = 0; i < native_pixel_count; ++i) {
        // Calling driver function manually instead of `qp_pixdata` to avoid getting LOTS of `qp_dprintf` slowing it
        black->driver_vtable->pixdata((const void *)black, (const void *)(pixels[i] >> 0), 1);
        red->driver_vtable->pixdata((const void *)red, (const void *)(pixels[i] >> 1), 1);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert supplied palette entries into their native equivalents

uint16_t hsv_distance(uint8_t h, uint8_t s, uint8_t v, HSV hsv) {
    return (h - hsv.h) * (h - hsv.h) + (s - hsv.s) * (s - hsv.s) + (v - hsv.v) * (v - hsv.v);
}

bool qp_eink_panel_palette_convert_eink3(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    for (int16_t i = 0; i < palette_size; ++i) {
        HSV      hsv            = (HSV){palette[i].hsv888.h, palette[i].hsv888.s, palette[i].hsv888.v};
        uint16_t black_distance = hsv_distance(HSV_BLACK, hsv);
        uint16_t red_distance   = hsv_distance(HSV_RED, hsv);
        uint16_t white_distance = hsv_distance(HSV_WHITE, hsv);

        uint8_t  value;
        uint16_t min_distance = QP_MIN(black_distance, QP_MIN(red_distance, white_distance));
        if (min_distance == black_distance)
            value = 0b01;

        else if (min_distance == red_distance)
            value = 0b10;

        else
            value = 0b00;

        palette[i].mono = value;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Append pixels to the target location, keyed by the pixel index

bool qp_eink_panel_append_pixels_eink3(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    // Black data
    for (uint32_t i = 0; i < pixel_count; ++i) {
        // TODO: Optimize code so that each pixel takes 2 bits instead of a whole byte
        // Current format: | 0000 00BR | 0000 00BR | ...
        target_buffer[pixel_offset + i] = palette[palette_indices[i]].mono;
    }

    return true;
}
