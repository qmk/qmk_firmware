/* Copyright 2021 Paul Cotter (@gr1mr3aver)
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
#include "print.h"

#include <qp.h>
#include <qp_internal.h>
#include <qp_utils.h>
#include <qp_fallback.h>
#include "qp_st7789.h"
#include "qp_st7789_opcodes.h"
#include <qp_st77xx.h>
#include <qp_st77xx_internal.h>
#include <qp_st77xx_opcodes.h>

// Driver storage
static st77xx_painter_device_t drivers[ST7789_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool qp_st7789_init(painter_device_t device, painter_rotation_t rotation) {

    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    lcd->rotation                 = rotation;

    // Initialize the SPI peripheral
    spi_init();

    // Set up pin directions and initial values
    setPinOutput(lcd->chip_select_pin);
    writePinHigh(lcd->chip_select_pin);

    setPinOutput(lcd->data_pin);
    writePinLow(lcd->data_pin);

    setPinOutput(lcd->reset_pin);

    // Perform a HW reset
    writePinLow(lcd->reset_pin);
    wait_ms(20);
    writePinHigh(lcd->reset_pin);
    wait_ms(100);

    // Enable the SPI comms to the LCD
    qp_st77xx_internal_lcd_start(lcd);

    // Set rgb565 color format
    qp_st77xx_internal_lcd_reg(lcd, ST77XX_SET_PIX_FMT, 0x55);

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    switch (rotation) {
        case QP_ROTATION_0:
            qp_st77xx_internal_lcd_reg(lcd, ST77XX_SET_MADCTL, 0b11000000);
            break;
        case QP_ROTATION_90:
            qp_st77xx_internal_lcd_reg(lcd, ST77XX_SET_MADCTL, 0b10100000);
            break;
        case QP_ROTATION_180:
            qp_st77xx_internal_lcd_reg(lcd, ST77XX_SET_MADCTL, 0b00000000);
            break;
        case QP_ROTATION_270:
            qp_st77xx_internal_lcd_reg(lcd, ST77XX_SET_MADCTL, 0b01100000);
            break;
    }

    // Turn on Inversion - THIS IS A HACK
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_CMD_INVERT_ON);

    // Turn on Normal mode
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_CMD_NORMAL_ON);
    wait_ms(20);

    // Turn off Sleep mode
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_CMD_SLEEP_OFF);
    wait_ms(20);

    // Turn on display
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_CMD_DISPLAY_ON);
    wait_ms(20);

    // Disable the SPI comms to the LCD
    qp_st77xx_internal_lcd_stop();

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Device creation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Factory function for creating a handle to the ST7789 device
painter_device_t qp_st7789_make_device(pin_t chip_select_pin, pin_t data_pin, pin_t reset_pin, uint16_t spi_divisor, bool uses_backlight, uint16_t lcd_width, uint16_t lcd_height) {

    for (uint32_t i = 0; i < ST7789_NUM_DEVICES; ++i) {
        st77xx_painter_device_t *driver = &drivers[i];
        if (!driver->allocated) {
            driver->allocated           = true;
            driver->qp_driver.init      = qp_st7789_init;
            driver->qp_driver.clear     = qp_st77xx_clear;
            driver->qp_driver.power     = qp_st77xx_power;
            driver->qp_driver.pixdata   = qp_st77xx_pixdata;
            driver->qp_driver.viewport  = qp_st77xx_viewport;
            driver->qp_driver.setpixel  = qp_st77xx_setpixel;
            driver->qp_driver.line      = qp_st77xx_line;
            driver->qp_driver.rect      = qp_st77xx_rect;
            driver->qp_driver.circle    = qp_st77xx_circle;
            driver->qp_driver.ellipse   = qp_fallback_ellipse;
            driver->qp_driver.drawimage = qp_st77xx_drawimage;
            driver->chip_select_pin     = chip_select_pin;
            driver->data_pin            = data_pin;
            driver->reset_pin           = reset_pin;
            driver->spi_divisor         = spi_divisor;
            driver->spi_mode            = LCD_SPI_MODE;
            driver->lcd_width           = lcd_width;
            driver->lcd_height          = lcd_height;
#ifdef BACKLIGHT_ENABLE
            driver->uses_backlight = uses_backlight;
#endif
            return (painter_device_t)driver;
        }
    }

    return NULL;
}




