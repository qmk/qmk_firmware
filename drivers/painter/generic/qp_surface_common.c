// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "qp_draw.h"
#include "qp_surface_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage

surface_painter_device_t surface_drivers[SURFACE_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

void qp_surface_increment_pixdata_location(surface_viewport_data_t *viewport) {
    // Increment the X-position
    viewport->pixdata_x++;

    // If the x-coord has gone past the right-side edge, loop it back around and increment the y-coord
    if (viewport->pixdata_x > viewport->viewport_r) {
        viewport->pixdata_x = viewport->viewport_l;
        viewport->pixdata_y++;
    }

    // If the y-coord has gone past the bottom, loop it back to the top
    if (viewport->pixdata_y > viewport->viewport_b) {
        viewport->pixdata_y = viewport->viewport_t;
    }
}

void qp_surface_update_dirty(surface_dirty_data_t *dirty, uint16_t x, uint16_t y) {
    // Maintain dirty region
    if (dirty->l > x) {
        dirty->l        = x;
        dirty->is_dirty = true;
    }
    if (dirty->r < x) {
        dirty->r        = x;
        dirty->is_dirty = true;
    }
    if (dirty->t > y) {
        dirty->t        = y;
        dirty->is_dirty = true;
    }
    if (dirty->b < y) {
        dirty->b        = y;
        dirty->is_dirty = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

bool qp_surface_init(painter_device_t device, painter_rotation_t rotation) {
    painter_driver_t *        driver  = (painter_driver_t *)device;
    surface_painter_device_t *surface = (surface_painter_device_t *)driver;
    memset(surface->buffer, 0, SURFACE_REQUIRED_BUFFER_BYTE_SIZE(driver->panel_width, driver->panel_height, driver->native_bits_per_pixel));

    surface->dirty.l        = 0;
    surface->dirty.t        = 0;
    surface->dirty.r        = surface->base.panel_width - 1;
    surface->dirty.b        = surface->base.panel_height - 1;
    surface->dirty.is_dirty = true;

    return true;
}

bool qp_surface_power(painter_device_t device, bool power_on) {
    // No-op.
    return true;
}

bool qp_surface_clear(painter_device_t device) {
    painter_driver_t *driver = (painter_driver_t *)device;
    driver->driver_vtable->init(device, driver->rotation); // Re-init the surface
    return true;
}

bool qp_surface_flush(painter_device_t device) {
    painter_driver_t *        driver  = (painter_driver_t *)device;
    surface_painter_device_t *surface = (surface_painter_device_t *)driver;
    surface->dirty.l = surface->dirty.t = UINT16_MAX;
    surface->dirty.r = surface->dirty.b = 0;
    surface->dirty.is_dirty             = false;
    return true;
}

bool qp_surface_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    painter_driver_t *        driver  = (painter_driver_t *)device;
    surface_painter_device_t *surface = (surface_painter_device_t *)driver;

    // Set the viewport locations
    surface->viewport.viewport_l = left;
    surface->viewport.viewport_t = top;
    surface->viewport.viewport_r = right;
    surface->viewport.viewport_b = bottom;

    // Reset the write location to the top left
    surface->viewport.pixdata_x = left;
    surface->viewport.pixdata_y = top;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Drawing routine to copy out the dirty region and send it to another device

bool qp_surface_draw(painter_device_t surface, painter_device_t target, uint16_t x, uint16_t y, bool entire_surface) {
    painter_driver_t *        surface_driver = (painter_driver_t *)surface;
    surface_painter_device_t *surface_handle = (surface_painter_device_t *)surface_driver;
    painter_driver_t *        target_driver  = (painter_driver_t *)target;

    // If we're not dirty... we're done.
    if (!surface_handle->dirty.is_dirty) {
        qp_dprintf("qp_surface_draw: ok (not dirty, skipping)\n");
        return true;
    }

    // If we have incompatible bit depths, drop out
    if (surface_driver->native_bits_per_pixel != target_driver->native_bits_per_pixel) {
        qp_dprintf("qp_surface_draw: fail (incompatible bpp: surface=%d, target=%d)\n", (int)surface_driver->native_bits_per_pixel, (int)target_driver->native_bits_per_pixel);
        return false;
    }

    // Offload to the pixdata transfer function
    surface_painter_driver_vtable_t *vtable = (surface_painter_driver_vtable_t *)surface_driver->driver_vtable;
    bool                             ok     = vtable->target_pixdata_transfer(surface_driver, target_driver, x, y, entire_surface);
    if (!ok) {
        qp_dprintf("qp_surface_draw: fail (could not transfer pixel data)\n");
        return false;
    }

    // Clear the dirty info for the surface
    ok = qp_flush(surface);
    if (!ok) {
        qp_dprintf("qp_surface_draw: fail (could not flush)\n");
        return false;
    }
    qp_dprintf("qp_surface_draw: ok\n");
    return true;
}
