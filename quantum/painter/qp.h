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

#include <stdint.h>
#include <stdbool.h>

// This controls whether 256-color palettes are supported -- will require 1280 bytes of RAM at minimum for palette generation (instead of 112 for 16-color)
#ifndef QUANTUM_PAINTER_SUPPORTS_256_PALETTE
#    define QUANTUM_PAINTER_SUPPORTS_256_PALETTE FALSE
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter types
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Device type
typedef const void *painter_device_t;

// RGB565 Color definition
typedef uint16_t rgb565_t;

// Rotation type
typedef enum { QP_ROTATION_0, QP_ROTATION_90, QP_ROTATION_180, QP_ROTATION_270 } painter_rotation_t;

// Image format internal flags
typedef enum { IMAGE_FORMAT_RAW, IMAGE_FORMAT_RGB565, IMAGE_FORMAT_GRAYSCALE, IMAGE_FORMAT_PALETTE } painter_image_format_t;
typedef enum { IMAGE_UNCOMPRESSED } painter_compression_t;

// Image types -- handled by `qmk convert-image`
typedef struct painter_image_descriptor_t {
    const painter_image_format_t image_format;
    const uint8_t                image_bpp;
    const painter_compression_t  compression;
    const uint16_t               width;
    const uint16_t               height;
} painter_image_descriptor_t;
typedef const painter_image_descriptor_t *painter_image_t;

// Font types -- handled by `qmk painter-convert-font-image`
typedef struct painter_font_descriptor_t {
    const painter_image_format_t image_format;
    const uint8_t                image_bpp;
    const painter_compression_t  compression;
    const uint8_t                glyph_height;
} painter_font_descriptor_t;
typedef const painter_font_descriptor_t *painter_font_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Initialize a device and set its rotation -- need to create the device using its corresponding factory method first
bool qp_init(painter_device_t device, painter_rotation_t rotation);

// Clear's a device's screen
bool qp_clear(painter_device_t device);

// Handle turning a display on or off
bool qp_power(painter_device_t device, bool power_on);

// Handle configuring the lcd backlight brightness or contrast
bool qp_brightness(painter_device_t device, uint8_t val);

// Set the viewport that pixdata is to get streamed into
bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

// Stream pixel data in the device's native format into the previously-set viewport
bool qp_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);

// Set a specific pixel
bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val);

// Draw a line
bool qp_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val);

// Draw a rectangle
bool qp_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled);

// Draw a circle
bool qp_circle(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled);

// Draw an ellipse
bool qp_ellipse(painter_device_t device, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t hue, uint8_t sat, uint8_t val, bool filled);

// Draw an image on the device
bool qp_drawimage(painter_device_t device, uint16_t x, uint16_t y, painter_image_t image);
bool qp_drawimage_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_t image, uint8_t hue, uint8_t sat, uint8_t val);

// Draw text to the display
int16_t qp_textwidth(painter_font_t font, const char *str);
int16_t qp_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_t font, const char *str);
int16_t qp_drawtext_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_font_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
