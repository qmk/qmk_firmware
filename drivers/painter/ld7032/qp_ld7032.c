// Copyright 2023 Nick Brassel (@tzarc)
// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_oled_panel.h"
#include "qp_ld7032.h"
#include "qp_ld7032_opcodes.h"
#include "qp_surface.h"
#include "qp_surface_internal.h"

typedef bool (*ld7032_driver_comms_send_command_and_data_func)(painter_device_t device, uint8_t cmd, uint8_t data);
typedef uint32_t (*ld7032_driver_comms_send_command_and_databuf_func)(painter_device_t device, uint8_t cmd, const void *data, uint32_t byte_count);

typedef struct ld7032_comms_with_command_vtable_t {
    painter_comms_vtable_t                            base; // must be first, so this object can be cast from the painter_comms_vtable_t* type
    painter_driver_comms_send_command_func            send_command;
    painter_driver_comms_bulk_command_sequence        bulk_command_sequence;
    ld7032_driver_comms_send_command_and_data_func    send_command_data;
    ld7032_driver_comms_send_command_and_databuf_func send_command_databuf;
} ld7032_comms_with_command_vtable_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LD7032 Internal API
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef QUANTUM_PAINTER_LD7032_I2C_ENABLE
bool ld7032_comms_i2c_send_command_and_data(painter_device_t device, uint8_t cmd, uint8_t data) {
    uint8_t buf[2] = {cmd, data};
    return qp_comms_i2c_send_data(device, buf, 2);
}

bool ld7032_comms_i2c_bulk_command_sequence(painter_device_t device, const uint8_t *sequence, size_t sequence_len) {
    uint8_t buf[32];
    for (size_t i = 0; i < sequence_len;) {
        uint8_t command   = sequence[i];
        uint8_t delay     = sequence[i + 1];
        uint8_t num_bytes = sequence[i + 2];
        buf[0]            = command;
        memcpy(&buf[1], &sequence[i + 3], num_bytes);
        if (!qp_comms_i2c_send_data(device, buf, num_bytes + 1)) {
            return false;
        }
        if (delay > 0) {
            wait_ms(delay);
        }
        i += (3 + num_bytes);
    }

    return true;
}

uint32_t ld7032_comms_i2c_send_command_and_databuf(painter_device_t device, uint8_t cmd, const void *data, uint32_t byte_count) {
    uint8_t buf[byte_count + 1];
    memset(buf, 0, sizeof(buf));
    buf[0] = cmd;
    memcpy(&buf[1], data, byte_count);
    return qp_comms_send(device, buf, byte_count + 1);
}
#endif // QUANTUM_PAINTER_LD7032_I2C_ENABLE

// Power control
bool qp_ld7032_power(painter_device_t device, bool power_on) {
    painter_driver_t *                  driver       = (painter_driver_t *)device;
    ld7032_comms_with_command_vtable_t *comms_vtable = (ld7032_comms_with_command_vtable_t *)driver->comms_vtable;

    comms_vtable->send_command_data(device, LD7032_DISP_ON_OFF, power_on ? 0x01 : 0x00);

    return true;
}

// Screen clear
bool qp_ld7032_clear(painter_device_t device) {
    qp_rect(device, 0, 0, 127, 127, 0, 0, 0, true); // clear memory
    painter_driver_t *driver = (painter_driver_t *)device;
    driver->driver_vtable->init(device, driver->rotation); // Re-init the display
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Flush helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ld7032_flush_0(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer, bool inverted) {
    painter_driver_t *                  driver       = (painter_driver_t *)device;
    ld7032_comms_with_command_vtable_t *comms_vtable = (ld7032_comms_with_command_vtable_t *)driver->comms_vtable;

    int     x_start       = dirty->l >> 3;
    int     x_end         = dirty->r >> 3;
    int     y_start       = dirty->t;
    int     y_end         = dirty->b;
    int     x_length      = (x_end - x_start) + 1;
    uint8_t x_view_offset = driver->offset_x >> 3;
    uint8_t y_view_offset = driver->offset_y;

    for (int y_pos = y_start; y_pos <= y_end; y_pos++) {
        int y_new_pos = y_pos;
        if (inverted) {
            y_new_pos = y_end - y_pos;
        }
        uint8_t packet[x_length];
        memcpy(packet, &framebuffer[(y_pos * (driver->panel_width >> 3)) + x_start], x_length);
        uint8_t x_write_start = MIN(x_start + x_view_offset, (128 >> 3));
        uint8_t x_write_end   = MIN(x_end + x_view_offset, (128 >> 3));
        uint8_t y_write_start = MIN(y_new_pos + y_view_offset, 39);
        uint8_t y_write_end   = MIN(y_new_pos + y_view_offset, 39);

        comms_vtable->send_command_data(device, LD7032_X_BOX_ADR_START, x_write_start);
        comms_vtable->send_command_data(device, LD7032_X_BOX_ADR_END, x_write_end);
        comms_vtable->send_command_data(device, LD7032_Y_BOX_ADR_START, y_write_start);
        comms_vtable->send_command_data(device, LD7032_Y_BOX_ADR_END, y_write_end);
        comms_vtable->send_command_databuf(device, LD7032_DATA_RW, packet, x_length);
    }
}

void ld7032_flush_90(painter_device_t device, surface_dirty_data_t *dirty, const uint8_t *framebuffer, bool inverted) {
    painter_driver_t *                  driver       = (painter_driver_t *)device;
    ld7032_comms_with_command_vtable_t *comms_vtable = (ld7032_comms_with_command_vtable_t *)driver->comms_vtable;

    int     x_start       = dirty->t >> 3;
    int     x_end         = dirty->b >> 3;
    int     y_start       = dirty->l;
    int     y_end         = dirty->r;
    int     x_length      = (x_end - x_start) + 1;
    uint8_t x_view_offset = driver->offset_x >> 3;
    uint8_t y_view_offset = driver->offset_y;

    for (int y_pos = y_start; y_pos <= y_end; y_pos++) {
        int y_new_pos = y_pos;
        if (inverted) {
            y_new_pos = y_end - y_pos;
        }
        uint8_t packet[x_length];
        memset(packet, 0, sizeof(packet));
        int count = 0;
        for (int x_pos = x_start; x_pos <= x_end; x_pos++) {
            for (int x = 0; x < 8; ++x) {
                uint32_t pixel_num   = (((x_pos << 3) + x) * driver->panel_height) + y_pos;
                uint32_t byte_offset = pixel_num / 8;
                uint8_t  bit_offset  = pixel_num % 8;
                packet[count] |= ((framebuffer[byte_offset] & (1 << bit_offset)) >> bit_offset) << x;
            }
            count++;
        }
        uint8_t x_width       = (driver->panel_width >> 3) - 1;
        uint8_t x_write_start = MAX((int)x_width - x_end - x_view_offset, 0);
        uint8_t x_write_end   = MAX((int)x_width - x_start - x_view_offset, 0);
        uint8_t y_write_start = MIN(y_new_pos + y_view_offset, 39);
        uint8_t y_write_end   = MIN(y_new_pos + y_view_offset, 39);

        comms_vtable->send_command_data(device, LD7032_X_BOX_ADR_START, x_write_start);
        comms_vtable->send_command_data(device, LD7032_X_BOX_ADR_END, x_write_end);
        comms_vtable->send_command_data(device, LD7032_Y_BOX_ADR_START, y_write_start);
        comms_vtable->send_command_data(device, LD7032_Y_BOX_ADR_END, y_write_end);
        comms_vtable->send_command_databuf(device, LD7032_DATA_RW, packet, x_length);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ld7032_device_t {
    oled_panel_painter_device_t oled;

    uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(128, 40, 1)];
} ld7032_device_t;

static ld7032_device_t ld7032_drivers[LD7032_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

// Initialisation
__attribute__((weak)) bool qp_ld7032_init(painter_device_t device, painter_rotation_t rotation) {
    ld7032_device_t *driver = (ld7032_device_t *)device;

    // Change the surface geometry based on the panel rotation
    if (rotation == QP_ROTATION_90 || rotation == QP_ROTATION_270) {
        driver->oled.surface.base.panel_width  = driver->oled.base.panel_height;
        driver->oled.surface.base.panel_height = driver->oled.base.panel_width;
    } else {
        driver->oled.surface.base.panel_width  = driver->oled.base.panel_width;
        driver->oled.surface.base.panel_height = driver->oled.base.panel_height;
    }

    // Init the internal surface
    if (!qp_init(&driver->oled.surface.base, QP_ROTATION_0)) {
        qp_dprintf("Failed to init internal surface in qp_ld7032_init\n");
        return false;
    }

    // clang-format off
    const uint8_t ld7032_init_sequence[] = {
        // Command,                    Delay,  N, Data[N]
        LD7032_DISP_STBY_ON_OFF, 0, 1, 0x00,
        LD7032_DISP_ON_OFF,      0, 1, 0x00,
        LD7032_DFRAME,           0, 1, 0x05,
        //LD7032_WRITE_DIRECTION, 0, 1, 0b00001000, // 0 Right, 1 Up, 2 Vertical, 3 Bit Order, 4-7 Unused
        LD7032_DISP_DIRECTION,  0, 1, 0x00,
        LD7032_PEAK_WIDTH,      0, 1, 0x1F,
        LD7032_PEAK_DELAY,      0, 1, 0x05,
        LD7032_SCAN_MODE,       0, 1, 0x01,
        LD7032_DOT_CURRENT,     0, 1, 0x1f,
        LD7032_VDD_SEL,         0, 1, 0x01,
    };
    // clang-format on

    if (!qp_comms_bulk_command_sequence(device, ld7032_init_sequence, sizeof(ld7032_init_sequence))) {
        return false;
    }

    uint8_t display_y_start = 40 - driver->oled.base.panel_height;
    uint8_t display_x_start = (128 - driver->oled.base.panel_width) / 2;

    // clang-format off
    uint8_t ld7032_memory_setup[] = {
        // Command,        Delay,  N, Data[N]
        LD7032_DISP_SIZE_X,     0, 2, 0x00, 0x7F,
        LD7032_DISP_SIZE_Y,     0, 2, 0x00, 0x27,
        LD7032_X_DISP_START,    0, 1, 0x0,
        LD7032_Y_DISP_START,    0, 1, 0x0,
    };
    // clang-format on

    ld7032_memory_setup[3]  = display_x_start;
    ld7032_memory_setup[4]  = display_x_start + driver->oled.base.panel_width - 1;
    ld7032_memory_setup[8]  = display_y_start;
    ld7032_memory_setup[9]  = display_y_start + driver->oled.base.panel_height - 1;
    ld7032_memory_setup[13] = ld7032_memory_setup[4] + 1;
    ld7032_memory_setup[17] = driver->oled.base.panel_height;

    if (!qp_comms_bulk_command_sequence(device, ld7032_memory_setup, sizeof(ld7032_memory_setup))) {
        return false;
    }

    uint8_t write_direction = 0;
    switch (rotation) {
        default:
        case QP_ROTATION_0:
            write_direction = 0b00001000;
            break;
        case QP_ROTATION_90:
            write_direction = 0b00000001;
            break;
        case QP_ROTATION_180:
            write_direction = 0b00000001;
            break;
        case QP_ROTATION_270:
            write_direction = 0b00001000;
            break;
    }

    painter_driver_t *                  pdriver      = (painter_driver_t *)device;
    ld7032_comms_with_command_vtable_t *comms_vtable = (ld7032_comms_with_command_vtable_t *)pdriver->comms_vtable;

    if (!comms_vtable->send_command_data(device, LD7032_WRITE_DIRECTION, write_direction)) {
        return false;
    }

    qp_ld7032_power(device, true);

    return true;
}

// Screen flush
bool qp_ld7032_flush(painter_device_t device) {
    ld7032_device_t *driver = (ld7032_device_t *)device;

    if (!driver->oled.surface.dirty.is_dirty) {
        return true;
    }

    switch (driver->oled.base.rotation) {
        default:
        case QP_ROTATION_0:
            ld7032_flush_0(device, &driver->oled.surface.dirty, driver->framebuffer, false);
            break;
        case QP_ROTATION_180:
            ld7032_flush_0(device, &driver->oled.surface.dirty, driver->framebuffer, true);
            break;
        case QP_ROTATION_90:
            ld7032_flush_90(device, &driver->oled.surface.dirty, driver->framebuffer, false);
            break;
        case QP_ROTATION_270:
            ld7032_flush_90(device, &driver->oled.surface.dirty, driver->framebuffer, true);
            break;
    }

    // Clear the dirty area
    qp_flush(&driver->oled.surface);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const painter_driver_vtable_t ld7032_driver_vtable = {
    .init            = qp_ld7032_init,
    .power           = qp_ld7032_power,
    .clear           = qp_ld7032_clear,
    .flush           = qp_ld7032_flush,
    .pixdata         = qp_oled_panel_passthru_pixdata,
    .viewport        = qp_oled_panel_passthru_viewport,
    .palette_convert = qp_oled_panel_passthru_palette_convert,
    .append_pixels   = qp_oled_panel_passthru_append_pixels,
    .append_pixdata  = qp_oled_panel_passthru_append_pixdata,
};

#ifdef QUANTUM_PAINTER_LD7032_SPI_ENABLE

const ld7032_comms_with_command_vtable_t ld7032_spi_comms_vtable = {
    .base =
        {
            .comms_init  = qp_comms_spi_dc_reset_init,
            .comms_start = qp_comms_spi_start,
            .comms_send  = qp_comms_spi_dc_reset_send_data,
            .comms_stop  = qp_comms_spi_stop,
        },
    .send_command          = qp_comms_spi_dc_reset_send_command,
    .send_command_data     = qp_comms_command_databyte,
    .send_command_databuf  = qp_comms_command_databuf,
    .bulk_command_sequence = qp_comms_spi_dc_reset_bulk_command_sequence,
};

// Factory function for creating a handle to the LD7032 device
painter_device_t qp_ld7032_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < LD7032_NUM_DEVICES; ++i) {
        ld7032_device_t *driver = &ld7032_drivers[i];
        if (!driver->oled.base.driver_vtable) {
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->oled.surface, 1, panel_width, panel_height, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            // Setup the OLED device
            driver->oled.base.driver_vtable         = (const painter_driver_vtable_t *)&ld7032_driver_vtable;
            driver->oled.base.comms_vtable          = (const painter_comms_vtable_t *)&ld7032_spi_comms_vtable;
            driver->oled.base.native_bits_per_pixel = 1; // 1bpp mono
            driver->oled.base.panel_width           = panel_width;
            driver->oled.base.panel_height          = panel_height;
            driver->oled.base.rotation              = QP_ROTATION_0;
            driver->oled.base.offset_x              = 0;
            driver->oled.base.offset_y              = 0;

            // SPI and other pin configuration
            driver->oled.base.comms_config                                   = &driver->oled.spi_dc_reset_config;
            driver->oled.spi_dc_reset_config.spi_config.chip_select_pin      = chip_select_pin;
            driver->oled.spi_dc_reset_config.spi_config.divisor              = spi_divisor;
            driver->oled.spi_dc_reset_config.spi_config.lsb_first            = false;
            driver->oled.spi_dc_reset_config.spi_config.mode                 = spi_mode;
            driver->oled.spi_dc_reset_config.dc_pin                          = dc_pin;
            driver->oled.spi_dc_reset_config.reset_pin                       = reset_pin;
            driver->oled.spi_dc_reset_config.command_params_uses_command_pin = true;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(ld7032_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_LD7032_SPI_ENABLE

#ifdef QUANTUM_PAINTER_LD7032_I2C_ENABLE

const ld7032_comms_with_command_vtable_t ld7032_i2c_comms_vtable = {
    .base =
        {
            .comms_init  = qp_comms_i2c_init,
            .comms_start = qp_comms_i2c_start,
            .comms_send  = qp_comms_i2c_send_data,
            .comms_stop  = qp_comms_i2c_stop,
        },
    .send_command          = NULL,
    .send_command_data     = ld7032_comms_i2c_send_command_and_data,
    .send_command_databuf  = ld7032_comms_i2c_send_command_and_databuf,
    .bulk_command_sequence = ld7032_comms_i2c_bulk_command_sequence,
};

// Factory function for creating a handle to the LD7032 device
painter_device_t qp_ld7032_make_i2c_device(uint16_t panel_width, uint16_t panel_height, uint8_t i2c_address) {
    for (uint32_t i = 0; i < LD7032_NUM_DEVICES; ++i) {
        ld7032_device_t *driver = &ld7032_drivers[i];
        if (!driver->oled.base.driver_vtable) {
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->oled.surface, 1, panel_width, panel_height, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            // Setup the OLED device
            driver->oled.base.driver_vtable         = (const painter_driver_vtable_t *)&ld7032_driver_vtable;
            driver->oled.base.comms_vtable          = (const painter_comms_vtable_t *)&ld7032_i2c_comms_vtable;
            driver->oled.base.native_bits_per_pixel = 1; // 1bpp mono
            driver->oled.base.panel_width           = panel_width;
            driver->oled.base.panel_height          = panel_height;
            driver->oled.base.rotation              = QP_ROTATION_0;
            driver->oled.base.offset_x              = 0;
            driver->oled.base.offset_y              = 0;

            // I2C configuration
            driver->oled.base.comms_config       = &driver->oled.i2c_config;
            driver->oled.i2c_config.chip_address = i2c_address;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(ld7032_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_LD7032_SPI_ENABLE
