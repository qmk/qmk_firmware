// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_draw.h"
#include "qp_oled_panel.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

// Power control
bool qp_oled_panel_power(painter_device_t device, bool power_on) {
    painter_driver_t *                  driver = (painter_driver_t *)device;
    oled_panel_painter_driver_vtable_t *vtable = (oled_panel_painter_driver_vtable_t *)driver->driver_vtable;
    qp_comms_command(device, power_on ? vtable->opcodes.display_on : vtable->opcodes.display_off);
    return true;
}

// Screen clear
bool qp_oled_panel_clear(painter_device_t device) {
    painter_driver_t *driver = (painter_driver_t *)device;
    driver->driver_vtable->init(device, driver->rotation); // Re-init the display
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Surface passthru
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool qp_oled_panel_passthru_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    oled_panel_painter_device_t *driver = (oled_panel_painter_device_t *)device;
    return driver->surface.base.validate_ok && driver->surface.base.driver_vtable->pixdata(&driver->surface.base, pixel_data, native_pixel_count);
}

bool qp_oled_panel_passthru_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    oled_panel_painter_device_t *driver = (oled_panel_painter_device_t *)device;
    return driver->surface.base.validate_ok && driver->surface.base.driver_vtable->viewport(&driver->surface.base, left, top, right, bottom);
}

bool qp_oled_panel_passthru_palette_convert(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    oled_panel_painter_device_t *driver = (oled_panel_painter_device_t *)device;
    return driver->surface.base.validate_ok && driver->surface.base.driver_vtable->palette_convert(&driver->surface.base, palette_size, palette);
}

bool qp_oled_panel_passthru_append_pixels(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    oled_panel_painter_device_t *driver = (oled_panel_painter_device_t *)device;
    return driver->surface.base.validate_ok && driver->surface.base.driver_vtable->append_pixels(&driver->surface.base, target_buffer, palette, pixel_offset, pixel_count, palette_indices);
}

bool qp_oled_panel_passthru_append_pixdata(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte) {
    oled_panel_painter_device_t *driver = (oled_panel_painter_device_t *)device;
    return driver->surface.base.validate_ok && driver->surface.base.driver_vtable->append_pixdata(&driver->surface.base, target_buffer, pixdata_offset, pixdata_byte);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Flush helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qp_oled_panel_page_column_flush_rot0(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer) {
    painter_driver_t *                  driver = (painter_driver_t *)device;
    oled_panel_painter_driver_vtable_t *vtable = (oled_panel_painter_driver_vtable_t *)driver->driver_vtable;

    // TODO: account for offset_x/y in base driver
    int min_page   = dirty->t / 8;
    int max_page   = dirty->b / 8;
    int min_column = dirty->l;
    int max_column = dirty->r;

    for (int page = min_page; page <= max_page; ++page) {
        int     cols_required = max_column - min_column + 1;
        uint8_t column_data[cols_required];
        memset(column_data, 0, cols_required);
        for (int x = min_column; x <= max_column; ++x) {
            uint16_t data_offset = x - min_column;
            for (int y = 0; y < 8; ++y) {
                uint32_t pixel_num   = ((page * 8) + y) * driver->panel_width + x;
                uint32_t byte_offset = pixel_num / 8;
                uint8_t  bit_offset  = pixel_num % 8;
                column_data[data_offset] |= ((framebuffer[byte_offset] & (1 << bit_offset)) >> bit_offset) << y;
            }
        }

        int actual_page  = page;
        int start_column = min_column;
        qp_comms_command(device, vtable->opcodes.set_page | actual_page);
        qp_comms_command(device, vtable->opcodes.set_column_lsb | (start_column & 0x0F));
        qp_comms_command(device, vtable->opcodes.set_column_msb | (start_column & 0xF0) >> 4);
        qp_comms_send(device, column_data, cols_required);
    }
}

void qp_oled_panel_page_column_flush_rot90(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer) {
    painter_driver_t *                  driver = (painter_driver_t *)device;
    oled_panel_painter_driver_vtable_t *vtable = (oled_panel_painter_driver_vtable_t *)driver->driver_vtable;

    // TODO: account for offset_x/y in base driver
    int num_columns = driver->panel_width;
    int min_page    = dirty->l / 8;
    int max_page    = dirty->r / 8;
    int min_column  = dirty->t;
    int max_column  = dirty->b;

    for (int page = min_page; page <= max_page; ++page) {
        int     cols_required = max_column - min_column + 1;
        uint8_t column_data[cols_required];
        memset(column_data, 0, cols_required);
        for (int y = min_column; y <= max_column; ++y) {
            uint16_t data_offset = cols_required - 1 - (y - min_column);
            for (int x = 0; x < 8; ++x) {
                uint32_t pixel_num   = y * driver->panel_height + ((page * 8) + x);
                uint32_t byte_offset = pixel_num / 8;
                uint8_t  bit_offset  = pixel_num % 8;
                column_data[data_offset] |= ((framebuffer[byte_offset] & (1 << bit_offset)) >> bit_offset) << x;
            }
        }

        int actual_page  = page;
        int start_column = num_columns - 1 - max_column;
        qp_comms_command(device, vtable->opcodes.set_page | actual_page);
        qp_comms_command(device, vtable->opcodes.set_column_lsb | (start_column & 0x0F));
        qp_comms_command(device, vtable->opcodes.set_column_msb | (start_column & 0xF0) >> 4);
        qp_comms_send(device, column_data, cols_required);
    }
}

void qp_oled_panel_page_column_flush_rot180(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer) {
    painter_driver_t *                  driver = (painter_driver_t *)device;
    oled_panel_painter_driver_vtable_t *vtable = (oled_panel_painter_driver_vtable_t *)driver->driver_vtable;

    // TODO: account for offset_x/y in base driver
    int num_pages   = driver->panel_height / 8;
    int num_columns = driver->panel_width;
    int min_page    = dirty->t / 8;
    int max_page    = dirty->b / 8;
    int min_column  = dirty->l;
    int max_column  = dirty->r;

    for (int page = min_page; page <= max_page; ++page) {
        int     cols_required = max_column - min_column + 1;
        uint8_t column_data[cols_required];
        memset(column_data, 0, cols_required);
        for (int x = min_column; x <= max_column; ++x) {
            uint16_t data_offset = cols_required - 1 - (x - min_column);
            for (int y = 0; y < 8; ++y) {
                uint32_t pixel_num   = ((page * 8) + y) * driver->panel_width + x;
                uint32_t byte_offset = pixel_num / 8;
                uint8_t  bit_offset  = pixel_num % 8;
                column_data[data_offset] |= ((framebuffer[byte_offset] & (1 << bit_offset)) >> bit_offset) << (7 - y);
            }
        }

        int actual_page  = num_pages - 1 - page;
        int start_column = num_columns - 1 - max_column;
        qp_comms_command(device, vtable->opcodes.set_page | actual_page);
        qp_comms_command(device, vtable->opcodes.set_column_lsb | (start_column & 0x0F));
        qp_comms_command(device, vtable->opcodes.set_column_msb | (start_column & 0xF0) >> 4);
        qp_comms_send(device, column_data, cols_required);
    }
}

void qp_oled_panel_page_column_flush_rot270(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer) {
    painter_driver_t *                  driver = (painter_driver_t *)device;
    oled_panel_painter_driver_vtable_t *vtable = (oled_panel_painter_driver_vtable_t *)driver->driver_vtable;

    // TODO: account for offset_x/y in base driver
    int num_pages  = driver->panel_height / 8;
    int min_page   = dirty->l / 8;
    int max_page   = dirty->r / 8;
    int min_column = dirty->t;
    int max_column = dirty->b;

    for (int page = min_page; page <= max_page; ++page) {
        int     cols_required = max_column - min_column + 1;
        uint8_t column_data[cols_required];
        memset(column_data, 0, cols_required);
        for (int y = min_column; y <= max_column; ++y) {
            uint16_t data_offset = y - min_column;
            for (int x = 0; x < 8; ++x) {
                uint32_t pixel_num   = y * driver->panel_height + ((page * 8) + x);
                uint32_t byte_offset = pixel_num / 8;
                uint8_t  bit_offset  = pixel_num % 8;
                column_data[data_offset] |= ((framebuffer[byte_offset] & (1 << bit_offset)) >> bit_offset) << (7 - x);
            }
        }

        int actual_page  = num_pages - 1 - page;
        int start_column = min_column;
        qp_comms_command(device, vtable->opcodes.set_page | actual_page);
        qp_comms_command(device, vtable->opcodes.set_column_lsb | (start_column & 0x0F));
        qp_comms_command(device, vtable->opcodes.set_column_msb | (start_column & 0xF0) >> 4);
        qp_comms_send(device, column_data, cols_required);
    }
}
