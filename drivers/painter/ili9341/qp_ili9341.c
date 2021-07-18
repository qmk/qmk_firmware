/* Copyright 2020 Nick Brassel (@tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <spi_master.h>
#include <wait.h>
#include <qp.h>
#include <qp_ili9341.h>
#include <qp_internal.h>
#include <qp_fallback.h>
#include <qp_ili9xxx_internal.h>
#include <qp_ili9xxx_opcodes.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool qp_ili9341_init(painter_device_t device, painter_rotation_t rotation) {
    static const uint8_t pgamma[15] = {0x0F, 0x29, 0x24, 0x0C, 0x0E, 0x09, 0x4E, 0x78, 0x3C, 0x09, 0x13, 0x05, 0x17, 0x11, 0x00};
    static const uint8_t ngamma[15] = {0x00, 0x16, 0x1B, 0x04, 0x11, 0x07, 0x31, 0x33, 0x42, 0x05, 0x0C, 0x0A, 0x28, 0x2F, 0x0F};

    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;
    lcd->rotation                 = rotation;

    // Initialize the SPI peripheral
    spi_init();

    // Set up pin directions and initial values
    setPinOutput(lcd->chip_select_pin);
    writePinHigh(lcd->chip_select_pin);

    setPinOutput(lcd->data_pin);
    writePinLow(lcd->data_pin);

    setPinOutput(lcd->reset_pin);

    // Perform a reset
    writePinLow(lcd->reset_pin);
    wait_ms(20);
    writePinHigh(lcd->reset_pin);
    wait_ms(20);

    // Enable the SPI comms to the LCD
    qp_ili9xxx_internal_lcd_start(lcd);

    // Configure power control
    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_POWER_CTL_A);
    qp_ili9xxx_internal_lcd_data(lcd, 0x39);
    qp_ili9xxx_internal_lcd_data(lcd, 0x2C);
    qp_ili9xxx_internal_lcd_data(lcd, 0x00);
    qp_ili9xxx_internal_lcd_data(lcd, 0x34);
    qp_ili9xxx_internal_lcd_data(lcd, 0x02);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_POWER_CTL_B);
    qp_ili9xxx_internal_lcd_data(lcd, 0x00);
    qp_ili9xxx_internal_lcd_data(lcd, 0xD9);
    qp_ili9xxx_internal_lcd_data(lcd, 0X30);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_POWER_ON_SEQ_CTL);
    qp_ili9xxx_internal_lcd_data(lcd, 0x64);
    qp_ili9xxx_internal_lcd_data(lcd, 0x03);
    qp_ili9xxx_internal_lcd_data(lcd, 0X12);
    qp_ili9xxx_internal_lcd_data(lcd, 0X81);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_PUMP_RATIO_CTL);
    qp_ili9xxx_internal_lcd_data(lcd, 0x20);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_POWER_CTL_1);
    qp_ili9xxx_internal_lcd_data(lcd, 0x26);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_POWER_CTL_2);
    qp_ili9xxx_internal_lcd_data(lcd, 0x11);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_VCOM_CTL_1);
    qp_ili9xxx_internal_lcd_data(lcd, 0x35);
    qp_ili9xxx_internal_lcd_data(lcd, 0x3E);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_VCOM_CTL_2);
    qp_ili9xxx_internal_lcd_data(lcd, 0xBE);

    // Configure timing control
    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_DRV_TIMING_CTL_A);
    qp_ili9xxx_internal_lcd_data(lcd, 0x85);
    qp_ili9xxx_internal_lcd_data(lcd, 0x10);
    qp_ili9xxx_internal_lcd_data(lcd, 0x7A);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_DRV_TIMING_CTL_B);
    qp_ili9xxx_internal_lcd_data(lcd, 0x00);
    qp_ili9xxx_internal_lcd_data(lcd, 0x00);

    // Configure brightness / gamma
    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_BRIGHTNESS);
    qp_ili9xxx_internal_lcd_data(lcd, 0xFF);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_ENABLE_3_GAMMA);
    qp_ili9xxx_internal_lcd_data(lcd, 0x00);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_GAMMA);
    qp_ili9xxx_internal_lcd_data(lcd, 0x01);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_PGAMMA);
    qp_ili9xxx_internal_lcd_sendbuf(lcd, pgamma, sizeof(pgamma));

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_NGAMMA);
    qp_ili9xxx_internal_lcd_sendbuf(lcd, ngamma, sizeof(ngamma));

    // Set the pixel format
    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_PIX_FMT);
    qp_ili9xxx_internal_lcd_data(lcd, 0x55);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_FRAME_CTL_NORMAL);
    qp_ili9xxx_internal_lcd_data(lcd, 0x00);
    qp_ili9xxx_internal_lcd_data(lcd, 0x1B);

    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_FUNCTION_CTL);
    qp_ili9xxx_internal_lcd_data(lcd, 0x0A);
    qp_ili9xxx_internal_lcd_data(lcd, 0xA2);

    // Set the default viewport to be fullscreen
    qp_ili9xxx_internal_lcd_viewport(lcd, 0, 0, 239, 319);

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    switch (rotation) {
        case QP_ROTATION_0:
            qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_MEM_ACS_CTL);
            qp_ili9xxx_internal_lcd_data(lcd, 0b00001000);
            break;
        case QP_ROTATION_90:
            qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_MEM_ACS_CTL);
            qp_ili9xxx_internal_lcd_data(lcd, 0b10101000);
            break;
        case QP_ROTATION_180:
            qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_MEM_ACS_CTL);
            qp_ili9xxx_internal_lcd_data(lcd, 0b11001000);
            break;
        case QP_ROTATION_270:
            qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_SET_MEM_ACS_CTL);
            qp_ili9xxx_internal_lcd_data(lcd, 0b01101000);
            break;
    }

    // Disable sleep mode
    qp_ili9xxx_internal_lcd_cmd(lcd, ILI9XXX_CMD_SLEEP_OFF);
    wait_ms(20);

    // Disable the SPI comms to the LCD
    qp_ili9xxx_internal_lcd_stop();

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Device creation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Driver storage
static ili9xxx_painter_device_t drivers[ILI9341_NUM_DEVICES] = {0};

// Factory function for creating a handle to the ILI9341 device
painter_device_t qp_ili9341_make_device(pin_t chip_select_pin, pin_t data_pin, pin_t reset_pin, uint16_t spi_divisor, bool uses_backlight) {
    for (uint32_t i = 0; i < ILI9341_NUM_DEVICES; ++i) {
        ili9xxx_painter_device_t *driver = &drivers[i];
        if (!driver->allocated) {
            driver->allocated           = true;
            driver->qp_driver.init      = qp_ili9341_init;
            driver->qp_driver.clear     = qp_ili9xxx_clear;
            driver->qp_driver.power     = qp_ili9xxx_power;
            driver->qp_driver.pixdata   = qp_ili9xxx_pixdata;
            driver->qp_driver.viewport  = qp_ili9xxx_viewport;
            driver->qp_driver.setpixel  = qp_ili9xxx_setpixel;
            driver->qp_driver.line      = qp_ili9xxx_line;
            driver->qp_driver.rect      = qp_ili9xxx_rect;
            driver->qp_driver.circle    = qp_fallback_circle;
            driver->qp_driver.ellipse   = qp_fallback_ellipse;
            driver->qp_driver.drawimage = qp_ili9xxx_drawimage;
            driver->qp_driver.drawtext  = qp_ili9xxx_drawtext;
            driver->chip_select_pin     = chip_select_pin;
            driver->data_pin            = data_pin;
            driver->reset_pin           = reset_pin;
            driver->spi_divisor         = spi_divisor;
#ifdef BACKLIGHT_ENABLE
            driver->uses_backlight = uses_backlight;
#endif
            return (painter_device_t)driver;
        }
    }
    return NULL;
}
