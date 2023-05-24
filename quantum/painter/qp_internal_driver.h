// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver callbacks

typedef bool (*painter_driver_init_func)(painter_device_t device, painter_rotation_t rotation);
typedef bool (*painter_driver_power_func)(painter_device_t device, bool power_on);
typedef bool (*painter_driver_clear_func)(painter_device_t device);
typedef bool (*painter_driver_flush_func)(painter_device_t device);
typedef bool (*painter_driver_viewport_func)(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
typedef bool (*painter_driver_pixdata_func)(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);
typedef bool (*painter_driver_convert_palette_func)(painter_device_t device, int16_t palette_size, qp_pixel_t *palette);
typedef bool (*painter_driver_append_pixels)(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices);

// Driver vtable definition
struct painter_driver_vtable_t {
    painter_driver_init_func            init;
    painter_driver_power_func           power;
    painter_driver_clear_func           clear;
    painter_driver_flush_func           flush;
    painter_driver_viewport_func        viewport;
    painter_driver_pixdata_func         pixdata;
    painter_driver_convert_palette_func palette_convert;
    painter_driver_append_pixels        append_pixels;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comms callbacks

typedef bool (*painter_driver_comms_init_func)(painter_device_t device);
typedef bool (*painter_driver_comms_start_func)(painter_device_t device);
typedef void (*painter_driver_comms_stop_func)(painter_device_t device);
typedef uint32_t (*painter_driver_comms_send_func)(painter_device_t device, const void *data, uint32_t byte_count);

struct painter_comms_vtable_t {
    painter_driver_comms_init_func  comms_init;
    painter_driver_comms_start_func comms_start;
    painter_driver_comms_stop_func  comms_stop;
    painter_driver_comms_send_func  comms_send;
};

typedef void (*painter_driver_comms_send_command_func)(painter_device_t device, uint8_t cmd);
typedef void (*painter_driver_comms_bulk_command_sequence)(painter_device_t device, const uint8_t *sequence, size_t sequence_len);

struct painter_comms_with_command_vtable_t {
    struct painter_comms_vtable_t              base; // must be first, so this object can be cast from the painter_comms_vtable_t* type
    painter_driver_comms_send_command_func     send_command;
    painter_driver_comms_bulk_command_sequence bulk_command_sequence;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver base definition

struct painter_driver_t {
    const struct painter_driver_vtable_t *driver_vtable;
    const struct painter_comms_vtable_t * comms_vtable;

    // Flag signifying if validation was successful
    bool validate_ok;

    // Panel geometry
    uint16_t panel_width;
    uint16_t panel_height;

    // Target drawing rotation
    painter_rotation_t rotation;

    // Automated offsets for setting viewport
    uint16_t offset_x;
    uint16_t offset_y;

    // Number of bits per pixel, used for determining how many pixels can be sent during a transmission of the pixdata buffer
    uint8_t native_bits_per_pixel;

    // Comms config pointer -- needs to point to an appropriate comms config if the comms driver requires it.
    void *comms_config;
};
