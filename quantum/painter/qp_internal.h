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

#pragma once

#include <qp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum painter image types
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Uncompressed raw image descriptor
typedef struct painter_raw_image_descriptor_t {
    const painter_image_descriptor_t base;
    const uint32_t                   byte_count;     // number of bytes in the image
    const uint8_t *const             image_palette;  // pointer to the image palette
    const uint8_t *const             image_data;     // pointer to the image data
} painter_raw_image_descriptor_t;

// ASCII font glyph offset descriptor
typedef struct painter_font_ascii_glyph_offset_t {
    uint32_t offset : 24;  // The offset into the data block where it starts
    uint8_t  width;        // The width of the glyph (in pixels)
} painter_font_ascii_glyph_offset_t;

#ifdef UNICODE_ENABLE
// Extra font glyph offset descriptor
typedef struct painter_font_unicode_glyph_offset_t {
    int32_t  unicode_glyph;  // The unicode glyph
    uint32_t offset : 24;    // The offset into the data block where it starts
    uint8_t  width;          // The width of the glyph (in pixels)
} painter_font_unicode_glyph_offset_t;
#endif  // UNICODE_ENABLE

// Uncompressed raw font descriptor
typedef struct painter_raw_font_descriptor_t {
    const painter_font_descriptor_t                base;
    const uint8_t *const                           image_palette;            // pointer to the image palette
    const uint8_t *const                           image_data;               // pointer to the image data
    const uint32_t                                 byte_count;               // number of bytes in the image
    const painter_font_ascii_glyph_offset_t *const ascii_glyph_definitions;  // list of offsets/widths for ASCII, range 0x20..0x7E
#ifdef UNICODE_ENABLE
    const painter_font_unicode_glyph_offset_t *const unicode_glyph_definitions;  // Unicode glyph descriptors for unicode rendering
    const uint16_t                                   unicode_glyph_count;        // Number of unicode glyphs defined
#endif                                                                           // UNICODE_ENABLE
} painter_raw_font_descriptor_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Callback function types
typedef bool (*painter_driver_init_func)(painter_device_t driver, painter_rotation_t rotation);
typedef bool (*painter_driver_clear_func)(painter_device_t driver);
typedef bool (*painter_driver_power_func)(painter_device_t driver, bool power_on);
typedef bool (*painter_driver_brightness_func)(painter_device_t driver, uint8_t val);
typedef bool (*painter_driver_viewport_func)(painter_device_t driver, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
typedef bool (*painter_driver_pixdata_func)(painter_device_t driver, const void *pixel_data, uint32_t native_pixel_count);
typedef bool (*painter_driver_setpixel_func)(painter_device_t driver, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val);
typedef bool (*painter_driver_line_func)(painter_device_t driver, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val);
typedef bool (*painter_driver_rect_func)(painter_device_t driver, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
typedef bool (*painter_driver_circle_func)(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
typedef bool (*painter_driver_ellipse_func)(painter_device_t device, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
typedef bool (*painter_driver_drawimage_func)(painter_device_t device, uint16_t x, uint16_t y, const painter_image_descriptor_t *image, uint8_t hue, uint8_t sat, uint8_t val);
typedef int16_t (*painter_driver_drawtext_func)(painter_device_t device, uint16_t x, uint16_t y, painter_font_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

// Driver base definition
struct painter_driver_t {
    painter_driver_init_func       init;
    painter_driver_clear_func      clear;
    painter_driver_power_func      power;
    painter_driver_brightness_func brightness;
    painter_driver_viewport_func   viewport;
    painter_driver_pixdata_func    pixdata;
    painter_driver_setpixel_func   setpixel;
    painter_driver_line_func       line;
    painter_driver_rect_func       rect;
    painter_driver_circle_func     circle;
    painter_driver_ellipse_func    ellipse;
    painter_driver_drawimage_func  drawimage;
    painter_driver_drawtext_func   drawtext;
};
