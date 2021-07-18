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

#include <debug.h>
#include <print.h>
#include <color.h>
#include <utf8.h>
#include <spi_master.h>
#include <wait.h>

#ifdef BACKLIGHT_ENABLE
#    include <backlight/backlight.h>
#endif

#include <qp_internal.h>
#include <qp_utils.h>
#include <qp_fallback.h>
#include <qp_ili9xxx.h>
#include <qp_ili9xxx_internal.h>
#include <qp_ili9xxx_opcodes.h>

#define BYTE_SWAP(x) (((((uint16_t)(x)) >> 8) & 0x00FF) | ((((uint16_t)(x)) << 8) & 0xFF00))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Low-level LCD control functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Enable SPI comms
void qp_ili9xxx_internal_lcd_start(ili9xxx_painter_device_t *lcd) { spi_start(lcd->chip_select_pin, false, 0, lcd->spi_divisor); }

// Disable SPI comms
void qp_ili9xxx_internal_lcd_stop(void) { spi_stop(); }

// Send a command
void qp_ili9xxx_internal_lcd_cmd(ili9xxx_painter_device_t *lcd, uint8_t b) {
    writePinLow(lcd->data_pin);
    spi_write(b);
}

// Send data
void qp_ili9xxx_internal_lcd_sendbuf(ili9xxx_painter_device_t *lcd, const void *data, uint16_t len) {
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
void qp_ili9xxx_internal_lcd_data(ili9xxx_painter_device_t *lcd, uint8_t b) { qp_ili9xxx_internal_lcd_sendbuf(lcd, &b, sizeof(b)); }

// Set a register value
void qp_ili9xxx_internal_lcd_reg(ili9xxx_painter_device_t *lcd, uint8_t reg, uint8_t val) {
    qp_ili9xxx_internal_lcd_cmd(lcd, reg);
    qp_ili9xxx_internal_lcd_data(lcd, val);
}

// Set the drawing viewport area
void qp_ili9xxx_internal_lcd_viewport(ili9xxx_painter_device_t *lcd, uint16_t xbegin, uint16_t ybegin, uint16_t xend, uint16_t yend) {
    // Set up the x-window
    uint8_t xbuf[4] = {xbegin >> 8, xbegin & 0xFF, xend >> 8, xend & 0xFF};
    qp_ili9xxx_internal_lcd_cmd(lcd, 0x2A);  // column address set
    qp_ili9xxx_internal_lcd_sendbuf(lcd, xbuf, sizeof(xbuf));

    // Set up the y-window
    uint8_t ybuf[4] = {ybegin >> 8, ybegin & 0xFF, yend >> 8, yend & 0xFF};
    qp_ili9xxx_internal_lcd_cmd(lcd, 0x2B);  // page (row) address set
    qp_ili9xxx_internal_lcd_sendbuf(lcd, ybuf, sizeof(ybuf));

    // Lock in the window
    qp_ili9xxx_internal_lcd_cmd(lcd, 0x2C);  // enable memory writes
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
// NOTE: The variables in this section are intentionally outside a stack frame. They are able to be defined with larger
//       sizes than the normal stack frames would allow, and as such need to be external.
//
//       **** DO NOT refactor this and decide to place the variables inside the function calling them -- you will ****
//       **** very likely get artifacts rendered to the screen as a result.                                       ****
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Static buffer to contain a generated color palette
#if QUANTUM_PAINTER_SUPPORTS_256_PALETTE
static HSV      hsv_lookup_table[256];
static rgb565_t rgb565_palette[256];
#else
static HSV      hsv_lookup_table[16];
static rgb565_t rgb565_palette[16];
#endif

// Static buffer used for transmitting image data
static rgb565_t pixdata_transmit_buf[ILI9XXX_PIXDATA_BUFSIZE];

// Color conversion to LCD-native
static inline rgb565_t rgb_to_ili9xxx(uint8_t r, uint8_t g, uint8_t b) {
    rgb565_t rgb565 = (((rgb565_t)r) >> 3) << 11 | (((rgb565_t)g) >> 2) << 5 | (((rgb565_t)b) >> 3);
    return BYTE_SWAP(rgb565);
}

// Color conversion to LCD-native
static inline rgb565_t hsv_to_ili9xxx(uint8_t hue, uint8_t sat, uint8_t val) {
    RGB rgb = hsv_to_rgb_nocie((HSV){hue, sat, val});
    return rgb_to_ili9xxx(rgb.r, rgb.g, rgb.b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Palette / Monochrome-format image rendering
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Palette renderer
static inline void lcd_send_palette_pixdata_impl(ili9xxx_painter_device_t *lcd, const rgb565_t *const rgb565_palette, uint8_t bits_per_pixel, uint32_t pixel_count, const void *const pixel_data, uint32_t byte_count) {
    const uint8_t  pixel_bitmask       = (1 << bits_per_pixel) - 1;
    const uint8_t  pixels_per_byte     = 8 / bits_per_pixel;
    const uint16_t max_transmit_pixels = ((ILI9XXX_PIXDATA_BUFSIZE / pixels_per_byte) * pixels_per_byte);  // the number of rgb565 pixels that we can completely fit in the buffer
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
        qp_ili9xxx_internal_lcd_sendbuf(lcd, pixdata_transmit_buf, transmit_pixels * sizeof(rgb565_t));
        remaining_pixels -= transmit_pixels;
    }
}

// Recolored renderer
static inline void lcd_send_palette_pixdata(ili9xxx_painter_device_t *lcd, const uint8_t *const rgb_palette, uint8_t bits_per_pixel, uint32_t pixel_count, const void *const pixel_data, uint32_t byte_count) {
    // Generate the color lookup table
    uint16_t items = 1 << bits_per_pixel;  // number of items we need to interpolate
    for (uint16_t i = 0; i < items; ++i) {
        rgb565_palette[i] = rgb_to_ili9xxx(rgb_palette[i * 3 + 0], rgb_palette[i * 3 + 1], rgb_palette[i * 3 + 2]);
    }

    // Transmit each block of pixels
    lcd_send_palette_pixdata_impl(lcd, rgb565_palette, bits_per_pixel, pixel_count, pixel_data, byte_count);
}

// Recolored renderer
static inline void lcd_send_mono_pixdata_recolor(ili9xxx_painter_device_t *lcd, uint8_t bits_per_pixel, uint32_t pixel_count, const void *const pixel_data, uint32_t byte_count, int16_t hue_fg, int16_t sat_fg, int16_t val_fg, int16_t hue_bg, int16_t sat_bg, int16_t val_bg) {
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
            rgb565_palette[i] = hsv_to_ili9xxx(hsv_lookup_table[i].h, hsv_lookup_table[i].s, hsv_lookup_table[i].v);
        }
    }

    // Transmit each block of pixels
    lcd_send_palette_pixdata_impl(lcd, rgb565_palette, bits_per_pixel, pixel_count, pixel_data, byte_count);
}

// Uncompressed image drawing helper
static bool drawimage_uncompressed_impl(ili9xxx_painter_device_t *lcd, painter_image_format_t image_format, uint8_t image_bpp, const uint8_t *pixel_data, uint32_t byte_count, int32_t width, int32_t height, const uint8_t *palette_data, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    // Stream data to the LCD
    if (image_format == IMAGE_FORMAT_RAW || image_format == IMAGE_FORMAT_RGB565) {
        // The pixel data is in the correct format already -- send it directly to the device
        qp_ili9xxx_internal_lcd_sendbuf(lcd, pixel_data, width * height);
    } else if (image_format == IMAGE_FORMAT_GRAYSCALE) {
        // Supplied pixel data is in 4bpp monochrome -- decode it to the equivalent pixel data
        lcd_send_mono_pixdata_recolor(lcd, image_bpp, width * height, pixel_data, byte_count, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
    } else if (image_format == IMAGE_FORMAT_PALETTE) {
        // Supplied pixel data is in 1bpp monochrome -- decode it to the equivalent pixel data
        lcd_send_palette_pixdata(lcd, palette_data, image_bpp, width * height, pixel_data, byte_count);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Screen clear
bool qp_ili9xxx_clear(painter_device_t device) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;

    // Re-init the LCD
    lcd->qp_driver.init(device, lcd->rotation);

    return true;
}

// Power control -- on/off (will also handle backlight if set to use the normal QMK backlight driver)
bool qp_ili9xxx_power(painter_device_t device, bool power_on) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;
    qp_ili9xxx_internal_lcd_start(lcd);

    // Turn on/off the display
    qp_ili9xxx_internal_lcd_cmd(lcd, power_on ? ILI9XXX_CMD_DISPLAY_ON : ILI9XXX_CMD_DISPLAY_OFF);

    qp_ili9xxx_internal_lcd_stop();

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
bool qp_ili9xxx_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;
    qp_ili9xxx_internal_lcd_start(lcd);

    // Configure where we're going to be rendering to
    qp_ili9xxx_internal_lcd_viewport(lcd, left, top, right, bottom);

    qp_ili9xxx_internal_lcd_stop();

    return true;
}

// Stream pixel data to the current write position in GRAM
bool qp_ili9xxx_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;
    qp_ili9xxx_internal_lcd_start(lcd);

    // Stream data to the LCD
    qp_ili9xxx_internal_lcd_sendbuf(lcd, pixel_data, native_pixel_count * sizeof(uint16_t));

    qp_ili9xxx_internal_lcd_stop();

    return true;
}

// Manually set a single pixel's color
bool qp_ili9xxx_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;
    qp_ili9xxx_internal_lcd_start(lcd);

    // Configure where we're going to be rendering to
    qp_ili9xxx_internal_lcd_viewport(lcd, x, y, x, y);

    // Convert the color to RGB565 and transmit to the device
    rgb565_t buf = hsv_to_ili9xxx(hue, sat, val);
    qp_ili9xxx_internal_lcd_sendbuf(lcd, &buf, sizeof(buf));

    qp_ili9xxx_internal_lcd_stop();

    return true;
}

// Draw a line
bool qp_ili9xxx_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val) {
    // If we're not doing horizontal or vertical, fallback to the base implementation
    if (x0 != x1 && y0 != y1) {
        return qp_fallback_line(device, x0, y0, x1, y1, hue, sat, val);
    }

    // If we're doing horizontal or vertical, just use the optimized rect draw so we don't need to deal with single pixels or buffers.
    return qp_ili9xxx_rect(device, x0, y0, x1, y1, hue, sat, val, true);
}

// Draw a rectangle
bool qp_ili9xxx_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;

    // Cater for cases where people have submitted the coordinates backwards
    uint16_t l = left < right ? left : right;
    uint16_t r = left > right ? left : right;
    uint16_t t = top < bottom ? top : bottom;
    uint16_t b = top > bottom ? top : bottom;

    if (filled) {
        // Convert the color to RGB565
        rgb565_t clr = hsv_to_ili9xxx(hue, sat, val);

        // Build a larger buffer so we can stream to the LCD in larger chunks, for speed
        rgb565_t buf[ILI9XXX_PIXDATA_BUFSIZE];
        for (uint32_t i = 0; i < ILI9XXX_PIXDATA_BUFSIZE; ++i) buf[i] = clr;

        qp_ili9xxx_internal_lcd_start(lcd);

        // Configure where we're going to be rendering to
        qp_ili9xxx_internal_lcd_viewport(lcd, l, t, r, b);

        // Transmit the data to the LCD in chunks
        uint32_t remaining = (r - l + 1) * (b - t + 1);
        while (remaining > 0) {
            uint32_t transmit = (remaining < ILI9XXX_PIXDATA_BUFSIZE ? remaining : ILI9XXX_PIXDATA_BUFSIZE);
            uint32_t bytes    = transmit * sizeof(rgb565_t);
            qp_ili9xxx_internal_lcd_sendbuf(lcd, buf, bytes);
            remaining -= transmit;
        }

        qp_ili9xxx_internal_lcd_stop();
    } else {
        if (!qp_ili9xxx_rect(device, l, t, r, t, hue, sat, val, true)) return false;
        if (!qp_ili9xxx_rect(device, l, b, r, b, hue, sat, val, true)) return false;
        if (!qp_ili9xxx_rect(device, l, t + 1, l, b - 1, hue, sat, val, true)) return false;
        if (!qp_ili9xxx_rect(device, r, t + 1, r, b - 1, hue, sat, val, true)) return false;
    }

    return true;
}

// Draw an image
bool qp_ili9xxx_drawimage(painter_device_t device, uint16_t x, uint16_t y, const painter_image_descriptor_t *image, uint8_t hue, uint8_t sat, uint8_t val) {
    ili9xxx_painter_device_t *lcd = (ili9xxx_painter_device_t *)device;
    qp_ili9xxx_internal_lcd_start(lcd);

    // Configure where we're going to be rendering to
    qp_ili9xxx_internal_lcd_viewport(lcd, x, y, x + image->width - 1, y + image->height - 1);

    bool ret = false;
    if (image->compression == IMAGE_UNCOMPRESSED) {
        const painter_raw_image_descriptor_t *raw_image_desc = (const painter_raw_image_descriptor_t *)image;
        ret                                                  = drawimage_uncompressed_impl(lcd, image->image_format, image->image_bpp, raw_image_desc->image_data, raw_image_desc->byte_count, image->width, image->height, raw_image_desc->image_palette, hue, sat, val, hue, sat, 0);
    }

    qp_ili9xxx_internal_lcd_stop();

    return ret;
}

int16_t qp_ili9xxx_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    ili9xxx_painter_device_t *           lcd   = (ili9xxx_painter_device_t *)device;
    const painter_raw_font_descriptor_t *fdesc = (const painter_raw_font_descriptor_t *)font;

    qp_ili9xxx_internal_lcd_start(lcd);

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
                    uint16_t                                 byte_count;
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

                    qp_ili9xxx_internal_lcd_viewport(lcd, x, y, x + glyph_desc->width - 1, y + font->glyph_height - 1);
                    drawimage_uncompressed_impl(lcd, font->image_format, font->image_bpp, &fdesc->image_data[glyph_desc->offset], byte_count, glyph_desc->width, font->glyph_height, fdesc->image_palette, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
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
                            qp_ili9xxx_internal_lcd_viewport(lcd, x, y, x + glyph_desc->width - 1, y + font->glyph_height - 1);
                            drawimage_uncompressed_impl(lcd, font->image_format, font->image_bpp, &fdesc->image_data[glyph_desc->offset], byte_count, glyph_desc->width, font->glyph_height, fdesc->image_palette, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
                            x += glyph_desc->width;
                        }
                    }
                }
            }
#endif  // UNICODE_ENABLE
        }
    }

    qp_ili9xxx_internal_lcd_stop();

    return (int16_t)x;
}