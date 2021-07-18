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

#include <debug.h>
#include <print.h>
#include <color.h>
#include <utf8.h>
#include <spi_master.h>


#ifdef BACKLIGHT_ENABLE
#    include <backlight/backlight.h>
#endif

#include <qp.h>
#include <qp_internal.h>
#include <qp_utils.h>
#include <qp_fallback.h>
#include "qp_st77xx.h"
#include "qp_st77xx_internal.h"
#include "qp_st77xx_opcodes.h"

#define BYTE_SWAP(x) (((((uint16_t)(x)) >> 8) & 0x00FF) | ((((uint16_t)(x)) << 8) & 0xFF00))
#define LIMIT(x, limit_min, limit_max) (x > limit_max ? limit_max : (x < limit_min ? limit_min : x))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Low-level LCD control functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Enable SPI comms
void qp_st77xx_internal_lcd_start(st77xx_painter_device_t *lcd) {
    spi_start(lcd->chip_select_pin, false, lcd->spi_mode, lcd->spi_divisor);
}

// Disable SPI comms
void qp_st77xx_internal_lcd_stop(void) {
        spi_stop();
}

// Send a command
void qp_st77xx_internal_lcd_cmd(st77xx_painter_device_t *lcd, uint8_t b) {
    writePinLow(lcd->data_pin);
    spi_write(b);
}

// Send data
void qp_st77xx_internal_lcd_sendbuf(st77xx_painter_device_t *lcd, const void *data, uint16_t len) {
    writePinHigh(lcd->data_pin);

    uint32_t       bytes_remaining = len;
    const uint8_t *p               = (const uint8_t *)data;
    while (bytes_remaining > 0) {
        uint32_t bytes_this_loop = bytes_remaining < 1024 ? bytes_remaining : 1024;
        spi_transmit(p, bytes_this_loop);
        p += bytes_this_loop;
        bytes_remaining -= bytes_this_loop;
    }
}

// Send data (single byte)
void qp_st77xx_internal_lcd_data(st77xx_painter_device_t *lcd, uint8_t b) { qp_st77xx_internal_lcd_sendbuf(lcd, &b, sizeof(b)); }

// Set a register value
void qp_st77xx_internal_lcd_reg(st77xx_painter_device_t *lcd, uint8_t reg, uint8_t val) {
    qp_st77xx_internal_lcd_cmd(lcd, reg);
    qp_st77xx_internal_lcd_data(lcd, val);
}

// Set the drawing viewport area
void qp_st77xx_internal_lcd_viewport(st77xx_painter_device_t *lcd, uint16_t xbegin, uint16_t ybegin, uint16_t xend, uint16_t yend) {
    // Set up the x-window
    uint8_t xbuf[4] = {xbegin >> 8, xbegin & 0xFF, xend >> 8, xend & 0xFF};
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_SET_COL_ADDR);  // column address set
    qp_st77xx_internal_lcd_sendbuf(lcd, xbuf, sizeof(xbuf));

    // Set up the y-window
    uint8_t ybuf[4] = {ybegin >> 8, ybegin & 0xFF, yend >> 8, yend & 0xFF};
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_SET_ROW_ADDR);  // page (row) address set
    qp_st77xx_internal_lcd_sendbuf(lcd, ybuf, sizeof(ybuf));

    // Lock in the window
    qp_st77xx_internal_lcd_cmd(lcd, ST77XX_SET_MEM);  // enable memory writes
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
// NOTE: The variables in this section are intentionally outside a stack frame. They are able to be defined with larger
//       sizes than the normal stack frames would allow, and as such need to be external.
//
//       **** DO NOT refactor this and decide to place the variables inside the function calling them -- you will ****
//       **** very likely get artifacts rendered to the LCD screen as a result.                                   ****
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Static buffer to contain a generated color palette
#if QUANTUM_PAINTER_SUPPORTS_256_PALETTE
HSV             hsv_lookup_table[256];
static rgb565_t rgb565_palette[256];
#else
HSV             hsv_lookup_table[16];
static rgb565_t rgb565_palette[16];
#endif

// Static buffer used for transmitting image data
static rgb565_t pixdata_transmit_buf[ST77XX_PIXDATA_BUFSIZE];

// Color conversion to LCD-native
static inline rgb565_t rgb_to_st77xx(uint8_t r, uint8_t g, uint8_t b) {
    rgb565_t rgb565 = (((rgb565_t)r) >> 3) << 11 | (((rgb565_t)g) >> 2) << 5 | (((rgb565_t)b) >> 3);
    return BYTE_SWAP(rgb565);
}

// Color conversion to LCD-native
static inline rgb565_t hsv_to_st77xx(uint8_t hue, uint8_t sat, uint8_t val) {
    RGB rgb = hsv_to_rgb_nocie((HSV){hue, sat, val});
    return rgb_to_st77xx(rgb.r, rgb.g, rgb.b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Palette / Monochrome-format image rendering
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Palette renderer
static inline void lcd_send_palette_pixdata_impl(st77xx_painter_device_t *lcd, const rgb565_t *const rgb565_palette, uint8_t bits_per_pixel, uint32_t pixel_count, const void *const pixel_data, uint32_t byte_count) {
    const uint8_t  pixel_bitmask       = (1 << bits_per_pixel) - 1;
    const uint8_t  pixels_per_byte     = 8 / bits_per_pixel;
    const uint16_t max_transmit_pixels = ((ST77XX_PIXDATA_BUFSIZE / pixels_per_byte) * pixels_per_byte);  // the number of rgb565 pixels that we can completely fit in the buffer
    const uint8_t *pixdata             = (const uint8_t *)pixel_data;
    uint32_t       remaining_pixels    = pixel_count;  // don't try to derive from byte_count, we may not use an entire byte

    // Transmit each block of pixels
    while (remaining_pixels > 0) {
        uint16_t  transmit_pixels = remaining_pixels < max_transmit_pixels ? remaining_pixels : max_transmit_pixels;
        rgb565_t *target16        = (rgb565_t *)pixdata_transmit_buf;
        for (uint16_t p = 0; p < transmit_pixels; p += pixels_per_byte) {
            uint8_t pixval      = *pixdata;
            uint8_t loop_pixels = remaining_pixels < pixels_per_byte ? remaining_pixels : pixels_per_byte;
            for (uint8_t q = 0; q < loop_pixels; ++q) {
                *target16++ = rgb565_palette[pixval & pixel_bitmask];
                pixval >>= bits_per_pixel;
            }
            ++pixdata;
        }
        qp_st77xx_internal_lcd_sendbuf(lcd, pixdata_transmit_buf, transmit_pixels * sizeof(rgb565_t));
        remaining_pixels -= transmit_pixels;
    }
}

// Recolored renderer
static inline void lcd_send_palette_pixdata(st77xx_painter_device_t *lcd, const uint8_t *const rgb_palette, uint8_t bits_per_pixel, uint32_t pixel_count, const void *const pixel_data, uint32_t byte_count) {
    // Generate the color lookup table
    uint16_t items = 1 << bits_per_pixel;  // number of items we need to interpolate
    for (uint16_t i = 0; i < items; ++i) {
        rgb565_palette[i] = rgb_to_st77xx(rgb_palette[i * 3 + 0], rgb_palette[i * 3 + 1], rgb_palette[i * 3 + 2]);
    }

    // Transmit each block of pixels
    lcd_send_palette_pixdata_impl(lcd, rgb565_palette, bits_per_pixel, pixel_count, pixel_data, byte_count);
}

// Recolored renderer
static inline void lcd_send_mono_pixdata_recolor(st77xx_painter_device_t *lcd, uint8_t bits_per_pixel, uint32_t pixel_count, const void *const pixel_data, uint32_t byte_count, int16_t hue_fg, int16_t sat_fg, int16_t val_fg, int16_t hue_bg, int16_t sat_bg, int16_t val_bg) {
    // Memoize the last batch of colors so we're not regenerating the palette if we're not changing anything
    static uint8_t last_bits_per_pixel = UINT8_MAX;
    static int16_t last_hue_fg         = INT16_MIN;
    static int16_t last_sat_fg         = INT16_MIN;
    static int16_t last_val_fg         = INT16_MIN;
    static int16_t last_hue_bg         = INT16_MIN;
    static int16_t last_sat_bg         = INT16_MIN;
    static int16_t last_val_bg         = INT16_MIN;

    // Regenerate the palette only if the inputs have changed
    if (last_bits_per_pixel != bits_per_pixel || last_hue_fg != hue_fg || last_sat_fg != sat_fg || last_val_fg != val_fg || last_hue_bg != hue_bg || last_sat_bg != sat_bg || last_val_bg != val_bg) {
        last_bits_per_pixel = bits_per_pixel;
        last_hue_fg         = hue_fg;
        last_sat_fg         = sat_fg;
        last_val_fg         = val_fg;
        last_hue_bg         = hue_bg;
        last_sat_bg         = sat_bg;
        last_val_bg         = val_bg;

        // Generate the color lookup table
        uint16_t items = 1 << bits_per_pixel;  // number of items we need to interpolate
        qp_generate_palette(hsv_lookup_table, items, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
        for (uint16_t i = 0; i < items; ++i) {
            rgb565_palette[i] = hsv_to_st77xx(hsv_lookup_table[i].h, hsv_lookup_table[i].s, hsv_lookup_table[i].v);
        }
    }

    // Transmit each block of pixels
    lcd_send_palette_pixdata_impl(lcd, rgb565_palette, bits_per_pixel, pixel_count, pixel_data, byte_count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API internal implementations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Uncompressed image drawing helper
bool st77xx_drawimage_uncompressed_impl(st77xx_painter_device_t *lcd, painter_image_format_t image_format, uint8_t image_bpp, const uint8_t *pixel_data, uint32_t byte_count, int32_t width, int32_t height, const uint8_t *palette_data, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    uint32_t pixel_count = (width * height);
    if (image_format == IMAGE_FORMAT_RAW || image_format == IMAGE_FORMAT_RGB565) {
        // The pixel data is in the correct format already -- send it directly to the device
        qp_st77xx_internal_lcd_sendbuf(lcd, pixel_data, byte_count);
    } else if (image_format == IMAGE_FORMAT_GRAYSCALE) {
        // Supplied pixel data is in 4bpp monochrome -- decode it to the equivalent pixel data
        lcd_send_mono_pixdata_recolor(lcd, image_bpp, pixel_count, pixel_data, byte_count, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
    } else if (image_format == IMAGE_FORMAT_PALETTE) {
         // Supplied pixel data is in 1bpp monochrome -- decode it to the equivalent pixel data
        lcd_send_palette_pixdata(lcd, palette_data, image_bpp, pixel_count, pixel_data, byte_count);
    } else {
        dprint("ERROR: image format not recognized");
    }
    return true;
}

// Manually set a single pixel's color
bool qp_st77xx_internal_setpixel_impl(st77xx_painter_device_t *lcd, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val) {

    // Configure where we're going to be rendering to
    qp_st77xx_internal_lcd_viewport(lcd, x, y, x, y);

    // Convert the color to RGB565 and transmit to the device
    rgb565_t buf = hsv_to_st77xx(hue, sat, val);
    qp_st77xx_internal_lcd_sendbuf(lcd, &buf, sizeof(buf));

    return true;
}

bool qp_st77xx_internal_filled_rect_impl(st77xx_painter_device_t *lcd, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, rgb565_t fillbuffer[], uint16_t fillbufferlen) {

        // rectify coordinates
        if (left > right)
        {
            uint16_t tmpleft = left;
            left = right;
            right = tmpleft;
        }
        if (top > bottom)
        {
            uint16_t tmptop = top;
            top = bottom;
            bottom = tmptop;
        }

        // Configure where we're going to be rendering to
        qp_st77xx_internal_lcd_viewport(lcd, left, top, right, bottom);

        // Transmit the data to the LCD in chunks
        uint32_t remaining = (right - left + 1) * (bottom - top + 1);

        while (remaining > 0) {
            uint32_t transmit = (remaining < fillbufferlen ? remaining : fillbufferlen);
            uint32_t bytes    = transmit * sizeof(rgb565_t);
            qp_st77xx_internal_lcd_sendbuf(lcd, fillbuffer, bytes);
            remaining -= transmit;
        }
        return true;
}

// Utilize 8-way symmetry to draw circle
bool qp_st77xx_circle_drawpixels(painter_device_t device, uint16_t centerx, uint16_t centery, uint16_t offsetx, uint16_t offsety, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    /*
    Circles have the property of 8-way symmetry, so eight pixels can be drawn
    for each computed [offsetx,offsety] given the center coordinates
    represented by [centerx,centery].

    For filled circles, we can draw horizontal lines between each pair of
    pixels with the same final value of y.

    Two special cases exist and have been optimized:
    1) offsetx == offsety (the final point), makes half the coordinates
    equivalent, so we can omit them (and the corresponding fill lines)
    2) offsetx == 0 (the starting point) means that some horizontal lines
    would be a single pixel in length, so we write individual pixels instead.
    This also makes half the symmetrical points identical to their twins,
    so we only need four points or two points and one line
    */

    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    debug_enable = true;
    // Convert the color to RGB565
    rgb565_t clr = hsv_to_st77xx(hue, sat, val);
    uint16_t bufsize = offsety << 1 < ST77XX_PIXDATA_BUFSIZE ? offsety << 1 : ST77XX_PIXDATA_BUFSIZE;
    rgb565_t buf[bufsize];
    if (filled) {
        for (uint32_t i = 0; i < bufsize; ++i) buf[i] = clr;
    }
    uint16_t yplusy = LIMIT(centery + offsety, 0, lcd->lcd_height);
    uint16_t yminusy = LIMIT(centery - offsety, 0, lcd->lcd_height);
    uint16_t yplusx = LIMIT(centery + offsetx, 0, lcd->lcd_height);
    uint16_t yminusx = LIMIT(centery - offsetx, 0, lcd->lcd_height);
    uint16_t xplusx = LIMIT(centerx + offsetx, 0, lcd->lcd_width);
    uint16_t xminusx = LIMIT(centerx - offsetx, 0, lcd->lcd_width);
    uint16_t xplusy = LIMIT(centerx + offsety, 0, lcd->lcd_width);
    uint16_t xminusy = LIMIT(centerx - offsety, 0, lcd->lcd_width);

    centerx = LIMIT(centerx, 0, lcd->lcd_width);
    centery = LIMIT(centery, 0, lcd->lcd_height);

    bool retval = true;
    if (offsetx == 0) {
        if (!qp_st77xx_internal_setpixel_impl(lcd,centerx, yplusy, hue, sat, val)) {
            retval = false;
        }
        if (!qp_st77xx_internal_setpixel_impl(lcd,centerx, yminusy, hue, sat, val)) {
            retval = false;
        }
        if (filled) {
            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusy, centery, xminusy, centery, hue, sat, val, buf, bufsize)) {
                retval = false;
            }
        } else {
            if (!qp_st77xx_internal_setpixel_impl(lcd,xplusy, centery, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusy, centery, hue, sat, val)) {
                retval = false;
            }
        }
    } else if (offsetx == offsety) {
        if (filled) {
            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusy, yplusy, xminusy, yplusy, hue, sat, val, buf, bufsize)) {
                retval = false;
            }
            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusy, yminusy, xminusy, yminusy, hue, sat, val, buf, bufsize)) {
                retval = false;
            }

        } else {
            if (!qp_st77xx_internal_setpixel_impl(lcd,xplusy, yplusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusy, yplusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xplusy, yminusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusy, yminusy, hue, sat, val)) {
                retval = false;
            }
        }
    } else {
        if (filled) {
            // Build a larger buffer so we can stream to the LCD in larger chunks, for speed
            // rgb565_t buf[ST77XX_PIXDATA_BUFSIZE];
            // for (uint32_t i = 0; i < ST77XX_PIXDATA_BUFSIZE; ++i) buf[i] = clr;

            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusx, yplusy, xminusx, yplusy, hue, sat, val, buf, bufsize)) {
                retval = false;
            }
            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusx, yminusy, xminusx, yminusy, hue, sat, val, buf, bufsize)) {
                retval = false;
            }
            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusy, yplusx, xminusy, yplusx, hue, sat, val, buf, bufsize)) {
                retval = false;
            }
            if (!qp_st77xx_internal_filled_rect_impl(lcd, xplusy, yminusx, xminusy, yminusx, hue, sat, val, buf, bufsize)) {
                retval = false;
            }
        } else {
             if (!qp_st77xx_internal_setpixel_impl(lcd,xplusx, yplusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusx, yplusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xplusx, yminusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusx, yminusy, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xplusy, yplusx, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusy, yplusx, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xplusy, yminusx, hue, sat, val)) {
                retval = false;
            }
            if (!qp_st77xx_internal_setpixel_impl(lcd,xminusy, yminusx, hue, sat, val)) {
                retval = false;
            }
        }
    }

    return retval;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Screen clear
bool qp_st77xx_clear(painter_device_t device) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;

    // Re-init the LCD
    lcd->qp_driver.init(device, lcd->rotation);

    return true;
}

// Power control -- on/off (will also handle backlight if set to use the normal QMK backlight driver)
bool qp_st77xx_power(painter_device_t device, bool power_on) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    qp_st77xx_internal_lcd_start(lcd);

    // Turn on/off the display
    qp_st77xx_internal_lcd_cmd(lcd, power_on ? ST77XX_CMD_DISPLAY_ON : ST77XX_CMD_DISPLAY_OFF);

    qp_st77xx_internal_lcd_stop();

#ifdef BACKLIGHT_ENABLE
    // If we're using the backlight to control the display as well, toggle that too.
    if (lcd->uses_backlight) {
        if (power_on) {
            // There's a small amount of time for the LCD to get the display back on the screen -- it's all white beforehand.
            // Delay for a small amount of time and let the LCD catch up before turning the backlight on.
            wait_ms(20);
            backlight_set(get_backlight_level());
        } else {
            backlight_set(0);
        }
    }
#endif

    return true;
}

// Viewport to draw to
bool qp_st77xx_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    qp_st77xx_internal_lcd_start(lcd);

    // Configure where we're going to be rendering to
    qp_st77xx_internal_lcd_viewport(lcd, left, top, right, bottom);

    qp_st77xx_internal_lcd_stop();

    return true;
}

// Stream pixel data to the current write position in GRAM
bool qp_st77xx_pixdata(painter_device_t device, const void *pixel_data, uint32_t byte_count) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    qp_st77xx_internal_lcd_start(lcd);

    // Stream data to the LCD
    qp_st77xx_internal_lcd_sendbuf(lcd, pixel_data, byte_count);

    qp_st77xx_internal_lcd_stop();

    return true;
}

// Manually set a single pixel's color
bool qp_st77xx_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    bool retval = true;
    qp_st77xx_internal_lcd_start(lcd);

    retval = qp_st77xx_internal_setpixel_impl(lcd, x, y, hue, sat, val);

    qp_st77xx_internal_lcd_stop();

    return retval;
}

// Draw a rectangle
bool qp_st77xx_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    bool retval = true;

    if (filled) {

        // Convert the color to RGB565
        rgb565_t clr = hsv_to_st77xx(hue, sat, val);

        uint32_t totalpixels = abs(right-left+1)*abs(bottom-top+1);

        totalpixels = totalpixels > ST77XX_PIXDATA_BUFSIZE ? ST77XX_PIXDATA_BUFSIZE : totalpixels;

        // Build a larger buffer so we can stream to the LCD in larger chunks for speed
        rgb565_t buf[totalpixels];

        for (uint32_t i = 0; i < totalpixels; ++i) buf[i] = clr;

        st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;

        qp_st77xx_internal_lcd_start(lcd);
        retval = qp_st77xx_internal_filled_rect_impl(lcd, left, top, right, bottom, hue, sat, val, buf, totalpixels);
        qp_st77xx_internal_lcd_stop();

    } else {
        if (!qp_st77xx_rect(device, left, top, right, top, hue, sat, val, true)) {
            return false;
        }
        if (top != bottom && !qp_st77xx_rect(device, left, bottom, right, bottom, hue, sat, val, true)) {
            return false;
        }
        if (!qp_st77xx_rect(device, left, top + 1, left, bottom - 1, hue, sat, val, true)) {
            return false;
        }
        if (left != right && !qp_st77xx_rect(device, right, top + 1, right, bottom - 1, hue, sat, val, true)) {
            return false;
        }
    }

    return retval;
}

// Draw a line
bool qp_st77xx_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val) {
    // If we're not doing horizontal or vertical, fallback to the base implementation for angled lines
    if (x0 != x1 && y0 != y1) {
        return qp_fallback_line(device, x0, y0, x1, y1, hue, sat, val);
    }

    // If we're doing horizontal or vertical, just use the filled rect implementation
    bool retval = true;
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    rgb565_t clr[1] = {hsv_to_st77xx(hue, sat, val)};
    qp_st77xx_internal_lcd_start(lcd);

    retval = qp_st77xx_internal_filled_rect_impl(lcd, x0, y0, x1, y1, hue, sat, val, clr, 1);

    qp_st77xx_internal_lcd_stop();
    return retval;

}

// Draw an image
bool qp_st77xx_drawimage(painter_device_t device, uint16_t x, uint16_t y, const painter_image_descriptor_t *image, uint8_t hue, uint8_t sat, uint8_t val) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;

    qp_st77xx_internal_lcd_start(lcd);

    // Configure where we're going to be rendering to
    qp_st77xx_internal_lcd_viewport(lcd, x, y, x + image->width - 1, y + image->height - 1);

    painter_raw_image_descriptor_t *raw_image_desc = (painter_raw_image_descriptor_t *)image;

    if (image->compression == IMAGE_UNCOMPRESSED) {
        st77xx_drawimage_uncompressed_impl(lcd, image->image_format, image->image_bpp, raw_image_desc->image_data, raw_image_desc->byte_count, image->width , image->height, NULL , hue, sat, val, hue, sat, 0);
    }

    qp_st77xx_internal_lcd_stop();

    return true;
}

// Draw a circle
bool qp_st77xx_circle(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    st77xx_painter_device_t *lcd = (st77xx_painter_device_t *)device;
    // plot the initial set of points for x, y and r
    int16_t xcalc = 0;
    int16_t ycalc = (int16_t)radius;
    int16_t err   = ((5 - (radius >> 2)) >> 2);

    qp_st77xx_internal_lcd_start(lcd);

    qp_st77xx_circle_drawpixels(lcd, x, y, xcalc, ycalc, hue, sat, val, filled);
    while (xcalc < ycalc) {
        xcalc++;
        if (err < 0) {
            err += (xcalc << 1) + 1;
        } else {
            ycalc--;
            err += ((xcalc - ycalc) << 1) + 1;
        }
        qp_st77xx_circle_drawpixels(lcd, x, y, xcalc, ycalc, hue, sat, val, filled);
    }

    qp_st77xx_internal_lcd_stop();

    return true;
}

int16_t qp_st77xx_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    st77xx_painter_device_t *           lcd   = (st77xx_painter_device_t *)device;
    const painter_raw_font_descriptor_t *fdesc = (const painter_raw_font_descriptor_t *)font;

    qp_st77xx_internal_lcd_start(lcd);

    const char *c = str;
    while (*c) {
        int32_t code_point = 0;
        c                  = decode_utf8(c, &code_point);

        if (code_point >= 0) {
            if (code_point >= 0x20 && code_point < 0x7F) {
                    if (fdesc->ascii_glyph_definitions != NULL) {
                    // Search the font's ascii table
                    uint8_t                                  index      = code_point - 0x20;
                    const painter_font_ascii_glyph_offset_t *glyph_desc = &fdesc->ascii_glyph_definitions[index];
                    uint16_t                                 byte_count = 0;

                    if (code_point < 0x7E) {
                        byte_count = (glyph_desc + 1)->offset - glyph_desc->offset;
                    } else if (code_point == 0x7E) {
#ifdef UNICODE_ENABLE
                        // Unicode glyphs directly follow ascii glyphs, so we take the first's offset
                        if (fdesc->unicode_glyph_count > 0) {
                            byte_count = fdesc->unicode_glyph_definitions[0].offset - glyph_desc->offset;
                        } else {
                            byte_count = fdesc->byte_count - glyph_desc->offset;
                        }
#else   // UNICODE_ENABLE
                        byte_count = fdesc->byte_count - glyph_desc->offset;
#endif  // UNICODE_ENABLE
                    }

                    qp_st77xx_internal_lcd_viewport(lcd, x, y, x + glyph_desc->width - 1, y + font->glyph_height - 1);
                    st77xx_drawimage_uncompressed_impl(lcd, font->image_format, font->image_bpp, &fdesc->image_data[glyph_desc->offset], byte_count, glyph_desc->width, font->glyph_height, fdesc->image_palette, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
                    x += glyph_desc->width;
                }
            }
#ifdef UNICODE_ENABLE
            else {
                // Search the font's unicode table
                if (fdesc->unicode_glyph_definitions != NULL) {
                    for (uint16_t index = 0; index < fdesc->unicode_glyph_count; ++index) {
                        const painter_font_unicode_glyph_offset_t *glyph_desc = &fdesc->unicode_glyph_definitions[index];
                        if (glyph_desc->unicode_glyph == code_point) {
                            uint16_t byte_count = (index == fdesc->unicode_glyph_count - 1) ? (fdesc->byte_count - glyph_desc->offset) : ((glyph_desc + 1)->offset - glyph_desc->offset);
                            qp_st77xx_internal_lcd_viewport(lcd, x, y, x + glyph_desc->width - 1, y + font->glyph_height - 1);
                            st77xx_drawimage_uncompressed_impl(lcd, font->image_format, font->image_bpp, &fdesc->image_data[glyph_desc->offset], byte_count, glyph_desc->width, font->glyph_height, fdesc->image_palette, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
                            x += glyph_desc->width;
                        }
                    }
                }
            }
#endif  // UNICODE_ENABLE
        }
    }

    qp_st77xx_internal_lcd_stop();

    return (int16_t)x;
}
