#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_surface_internal.h"
#include "qp_oled_panel.h"
#include "qp_sh1107.h"
#include "qp_sh1107_opcodes.h"
#include "qp_surface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct sh1107_device_t {
    oled_panel_painter_device_t oled;

    uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(128, 128, 1)];
} sh1107_device_t;

static sh1107_device_t sh1107_drivers[SH1107_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

// Initialisation
__attribute__((weak)) bool qp_sh1107_init(painter_device_t device, painter_rotation_t rotation) {
    sh1107_device_t *driver = (sh1107_device_t *)device;

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
        qp_dprintf("Failed to init internal surface in qp_sh1107_init\n");
        return false;
    }

    // clang-format off
    uint8_t sh1107_init_sequence[] = {
        // Command,                 Delay,  N, Data[N]
        SH1107_SET_MUX_RATIO,           0,  1, 0x7F,      // 1/128 duty
        SH1107_DISPLAY_OFFSET,          0,  1, 0x00,
        SH1107_SET_START_LINE,          0,  1, 0x00,      // Different from SH1106
        SH1107_SET_SEGMENT_REMAP_INV,   0,  0,
        SH1107_COM_SCAN_DIR_DEC,        0,  0,
        SH1107_COM_PADS_HW_CFG,         0,  1, 0x12,
        SH1107_SET_CONTRAST,            0,  1, 0x7F,
        SH1107_ALL_ON_RESUME,           0,  0,
        SH1107_NON_INVERTING_DISPLAY,   0,  0,
        SH1107_SET_OSC_DIVFREQ,         0,  1, 0x80,
        SH1107_SET_CHARGE_PUMP,         0,  1, 0x14,
        SH1107_DISPLAY_ON,              0,  0,
    };
    // clang-format on

    // If the display width is anything other than the default 128 pixels, change SH1107_SET_MUX_RATIO data byte to the correct value.
    if (driver->oled.base.panel_width != 128) {
        sh1107_init_sequence[3] = driver->oled.base.panel_width - 1;
    }

    // If the display width is less than the default 128 pixels, change SH1107_DISPLAY_OFFSET to use the center columns.
    if (driver->oled.base.panel_width < 128) {
        sh1107_init_sequence[7] = (128U - driver->oled.base.panel_width) / 2;
    }

    // For smaller displays, change SH1107_COM_PADS_HW_CFG data byte from alternative (0x12) to sequential (0x02) configuration
    if (driver->oled.base.panel_height <= 64) {
        sh1107_init_sequence[20] = 0x02;
    }

    return qp_comms_bulk_command_sequence(device, sh1107_init_sequence, sizeof(sh1107_init_sequence));
}

// Screen flush
bool qp_sh1107_flush(painter_device_t device) {
    sh1107_device_t *driver = (sh1107_device_t *)device;

    if (!driver->oled.surface.dirty.is_dirty) {
        return true;
    }

    switch (driver->oled.base.rotation) {
        default:
        case QP_ROTATION_0:
            qp_oled_panel_page_column_flush_rot0(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
        case QP_ROTATION_90:
            qp_oled_panel_page_column_flush_rot90(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
        case QP_ROTATION_180:
            qp_oled_panel_page_column_flush_rot180(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
        case QP_ROTATION_270:
            qp_oled_panel_page_column_flush_rot270(device, &driver->oled.surface.dirty, driver->framebuffer);
            break;
    }

    // Clear the dirty area
    qp_flush(&driver->oled.surface);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const oled_panel_painter_driver_vtable_t sh1107_driver_vtable = {
    .base =
        {
            .init            = qp_sh1107_init,
            .power           = qp_oled_panel_power,
            .clear           = qp_oled_panel_clear,
            .flush           = qp_sh1107_flush,
            .pixdata         = qp_oled_panel_passthru_pixdata,
            .viewport        = qp_oled_panel_passthru_viewport,
            .palette_convert = qp_oled_panel_passthru_palette_convert,
            .append_pixels   = qp_oled_panel_passthru_append_pixels,
            .append_pixdata  = qp_oled_panel_passthru_append_pixdata,
        },
    .opcodes =
        {
            .display_on     = SH1107_DISPLAY_ON,
            .display_off    = SH1107_DISPLAY_OFF,
            .set_page       = SH1107_PAGE_ADDR,
            .set_column_lsb = SH1107_SETCOLUMN_LSB,
            .set_column_msb = SH1107_SETCOLUMN_MSB,
        },
};

#ifdef QUANTUM_PAINTER_SH1107_SPI_ENABLE
// Factory function for creating a handle to the SH1107 device
painter_device_t qp_sh1107_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < SH1107_NUM_DEVICES; ++i) {
        sh1107_device_t *driver = &sh1107_drivers[i];
        if (!driver->oled.base.driver_vtable) {
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->oled.surface, 1, panel_width, panel_height, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            // Setup the OLED device
            driver->oled.base.driver_vtable         = (const painter_driver_vtable_t *)&sh1107_driver_vtable;
            driver->oled.base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_with_dc_vtable;
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
                memset(driver, 0, sizeof(sh1107_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_SH1107_SPI_ENABLE

#ifdef QUANTUM_PAINTER_SH1107_I2C_ENABLE
// Factory function for creating a handle to the SH1107 device
painter_device_t qp_sh1107_make_i2c_device(uint16_t panel_width, uint16_t panel_height, uint8_t i2c_address) {
    for (uint32_t i = 0; i < SH1107_NUM_DEVICES; ++i) {
        sh1107_device_t *driver = &sh1107_drivers[i];
        if (!driver->oled.base.driver_vtable) {
            // Instantiate the surface
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->oled.surface, 1, panel_width, panel_height, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            // Setup the OLED device
            driver->oled.base.driver_vtable         = (const painter_driver_vtable_t *)&sh1107_driver_vtable;
            driver->oled.base.comms_vtable          = (const painter_comms_vtable_t *)&i2c_comms_cmddata_vtable;
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
                memset(driver, 0, sizeof(sh1107_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_SH1107_I2C_ENABLE
