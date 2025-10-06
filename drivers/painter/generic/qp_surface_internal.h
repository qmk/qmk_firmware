// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef QUANTUM_PAINTER_SURFACE_ENABLE

#    include "qp_surface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal declarations

// Surface vtable
typedef struct surface_painter_driver_vtable_t {
    painter_driver_vtable_t base; // must be first, so it can be cast to/from the painter_driver_vtable_t* type

    bool (*target_pixdata_transfer)(painter_driver_t *surface_driver, painter_driver_t *target_driver, uint16_t x, uint16_t y, bool entire_surface);
} surface_painter_driver_vtable_t;

typedef struct surface_dirty_data_t {
    bool     is_dirty;
    uint16_t l;
    uint16_t t;
    uint16_t r;
    uint16_t b;
} surface_dirty_data_t;

typedef struct surface_viewport_data_t {
    // Manually manage the viewport for streaming pixel data to the display
    uint16_t viewport_l;
    uint16_t viewport_t;
    uint16_t viewport_r;
    uint16_t viewport_b;

    // Current write location to the display when streaming pixel data
    uint16_t pixdata_x;
    uint16_t pixdata_y;
} surface_viewport_data_t;

// Surface struct
typedef struct surface_painter_device_t {
    painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    // The target buffer
    union {
        void *    buffer;
        uint8_t * u8buffer;
        uint16_t *u16buffer;
        rgb_t *   rgbbuffer;
    };

    // Manually manage the viewport for streaming pixel data to the display
    surface_viewport_data_t viewport;

    // Maintain a dirty region so we can stream only what we need
    surface_dirty_data_t dirty;
} surface_painter_device_t;

/**
 * Factory method for an RGB565 surface (aka framebuffer). Accepts an external device table.
 *
 * @param device_table[in] the table of devices to use for instantiation
 * @param device_table_len[in] the length of the table of devices
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param buffer[in] pointer to a preallocated uint8_t buffer of size `SURFACE_REQUIRED_BUFFER_BYTE_SIZE(panel_width, panel_height, 16)`
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_make_rgb565_surface_advanced(surface_painter_device_t *device_table, size_t device_table_len, uint16_t panel_width, uint16_t panel_height, void *buffer);

/**
 * Factory method for a 1bpp monochrome surface (aka framebuffer).
 *
 * @param device_table[in] the table of devices to use for instantiation
 * @param device_table_len[in] the length of the table of devices
 * @param panel_width[in] the width of the display panel
 * @param panel_height[in] the height of the display panel
 * @param buffer[in] pointer to a preallocated uint8_t buffer of size `SURFACE_REQUIRED_BUFFER_BYTE_SIZE(panel_width, panel_height, 16)`
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_make_mono1bpp_surface_advanced(surface_painter_device_t *device_table, size_t device_table_len, uint16_t panel_width, uint16_t panel_height, void *buffer);

// Driver storage
extern surface_painter_device_t surface_drivers[SURFACE_NUM_DEVICES];

// Surface common APIs
bool qp_surface_init(painter_device_t device, painter_rotation_t rotation);
bool qp_surface_power(painter_device_t device, bool power_on);
bool qp_surface_clear(painter_device_t device);
bool qp_surface_flush(painter_device_t device);
bool qp_surface_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
void qp_surface_increment_pixdata_location(surface_viewport_data_t *viewport);
void qp_surface_update_dirty(surface_dirty_data_t *dirty, uint16_t x, uint16_t y);

#endif // QUANTUM_PAINTER_SURFACE_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Factory functions for creating a handle to a surface

#define SURFACE_FACTORY_FUNCTION_IMPL(function_name, vtable, bpp)                                                                                                             \
    painter_device_t(function_name##_advanced)(surface_painter_device_t * device_table, size_t device_table_len, uint16_t panel_width, uint16_t panel_height, void *buffer) { \
        for (uint32_t i = 0; i < device_table_len; ++i) {                                                                                                                     \
            surface_painter_device_t *driver = &device_table[i];                                                                                                              \
            if (!driver->base.driver_vtable) {                                                                                                                                \
                driver->base.driver_vtable         = (painter_driver_vtable_t *)&(vtable);                                                                                    \
                driver->base.native_bits_per_pixel = (bpp);                                                                                                                   \
                driver->base.comms_vtable          = &dummy_comms_vtable;                                                                                                     \
                driver->base.panel_width           = panel_width;                                                                                                             \
                driver->base.panel_height          = panel_height;                                                                                                            \
                driver->base.rotation              = QP_ROTATION_0;                                                                                                           \
                driver->base.offset_x              = 0;                                                                                                                       \
                driver->base.offset_y              = 0;                                                                                                                       \
                driver->buffer                     = buffer;                                                                                                                  \
                return (painter_device_t)driver;                                                                                                                              \
            }                                                                                                                                                                 \
        }                                                                                                                                                                     \
        return NULL;                                                                                                                                                          \
    }                                                                                                                                                                         \
    painter_device_t(function_name)(uint16_t panel_width, uint16_t panel_height, void *buffer) {                                                                              \
        return (function_name##_advanced)(surface_drivers, SURFACE_NUM_DEVICES, panel_width, panel_height, buffer);                                                           \
    }
