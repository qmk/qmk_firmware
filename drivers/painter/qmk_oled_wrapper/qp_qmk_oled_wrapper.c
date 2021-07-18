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
#include <oled_driver.h>
#include <utf8.h>
#include <qp.h>
#include <qp_qmk_oled_wrapper.h>
#include <qp_internal.h>
#include <qp_fallback.h>
#include <qp_utils.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct qmk_oled_painter_device_t {
    struct painter_driver_t qp_driver;  // must be first, so it can be cast from the painter_device_t* type
    painter_rotation_t      rotation;

    // Manually manage the viewport for streaming pixel data to the display
    uint16_t viewport_l;
    uint16_t viewport_t;
    uint16_t viewport_r;
    uint16_t viewport_b;

    // Current write location to the display when streaming pixel data
    uint16_t pixdata_x;
    uint16_t pixdata_y;
} qmk_oled_painter_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void translate_pixel_location(qmk_oled_painter_device_t *oled, uint16_t *x, uint16_t *y) {
    switch (oled->rotation) {
        case QP_ROTATION_0:
            // No change
            break;
        case QP_ROTATION_90: {
            uint16_t new_x = (OLED_DISPLAY_WIDTH) - (*y) - 1;
            uint16_t new_y = *x;
            *x             = new_x;
            *y             = new_y;
        } break;
        case QP_ROTATION_180: {
            uint16_t new_x = (OLED_DISPLAY_WIDTH) - (*x) - 1;
            uint16_t new_y = (OLED_DISPLAY_HEIGHT) - (*y) - 1;
            *x             = new_x;
            *y             = new_y;
        } break;
        case QP_ROTATION_270: {
            uint16_t new_x = *y;
            uint16_t new_y = (OLED_DISPLAY_HEIGHT) - (*x) - 1;
            *x             = new_x;
            *y             = new_y;
        } break;
    }
}

void increment_pixdata_location(qmk_oled_painter_device_t *oled) {
    // Increment the X-position
    oled->pixdata_x++;

    // If the x-coord has gone past the right-side edge, loop it back around and increment the y-coord
    if (oled->pixdata_x > oled->viewport_r) {
        oled->pixdata_x = oled->viewport_l;
        oled->pixdata_y++;
    }

    // If the y-coord has gone past the bottom, loop it back to the top
    if (oled->pixdata_y > oled->viewport_b) {
        oled->pixdata_y = oled->viewport_t;
    }
}

void setpixel(qmk_oled_painter_device_t *oled, uint16_t x, uint16_t y, bool on) {
    translate_pixel_location(oled, &x, &y);
    oled_write_pixel(x, y, on);
}

void stream_pixdata(qmk_oled_painter_device_t *oled, const uint8_t *data, uint32_t native_pixel_count, bool invert) {
    for (uint32_t pixel_counter = 0; pixel_counter < native_pixel_count; ++pixel_counter) {
        uint16_t byte_offset = (uint16_t)(pixel_counter / 8);
        uint8_t  bit_offset  = (uint8_t)(pixel_counter % 8);
        bool     value       = (data[byte_offset] & (1 << bit_offset) ? true : false);
        setpixel(oled, oled->pixdata_x, oled->pixdata_y, invert ? !value : value);
        increment_pixdata_location(oled);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool qp_qmk_oled_wrapper_init(painter_device_t device, painter_rotation_t rotation) {
    qmk_oled_painter_device_t *oled = (qmk_oled_painter_device_t *)device;
    oled->rotation                  = rotation;
    oled_clear();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool qp_qmk_oled_wrapper_clear(painter_device_t device) {
    oled_clear();
    return true;
}

bool qp_qmk_oled_wrapper_power(painter_device_t device, bool power_on) {
    if (power_on)
        oled_on();
    else
        oled_off();
    return true;
}

bool qp_qmk_oled_wrapper_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    qmk_oled_painter_device_t *oled = (qmk_oled_painter_device_t *)device;
    const uint8_t *            data = (const uint8_t *)pixel_data;
    stream_pixdata(oled, data, native_pixel_count, false);
    return true;
}

bool qp_qmk_oled_wrapper_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    qmk_oled_painter_device_t *oled = (qmk_oled_painter_device_t *)device;

    // Set the viewport locations
    oled->viewport_l = left;
    oled->viewport_t = top;
    oled->viewport_r = right;
    oled->viewport_b = bottom;

    // Reset the write location to the top left
    oled->pixdata_x = left;
    oled->pixdata_y = top;
    return true;
}

bool qp_qmk_oled_wrapper_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val) {
    qmk_oled_painter_device_t *oled = (qmk_oled_painter_device_t *)device;
    setpixel(oled, x, y, (val >= 128 ? true : false));
    return true;
}

// Draw an image
bool drawimage_impl(qmk_oled_painter_device_t *oled, uint16_t x, uint16_t y, int32_t width, int32_t height, const uint8_t *data, bool invert) {
    // Configure where we're rendering to
    qp_qmk_oled_wrapper_viewport(oled, x, y, x + width - 1, y + height - 1);
    stream_pixdata(oled, data, width * height, invert);
    return true;
}

bool qp_qmk_oled_wrapper_drawimage(painter_device_t device, uint16_t x, uint16_t y, const painter_image_descriptor_t *image, uint8_t hue, uint8_t sat, uint8_t val) {
    qmk_oled_painter_device_t *oled = (qmk_oled_painter_device_t *)device;

    // Can only render grayscale images if they're 1bpp
    if (image->image_format != IMAGE_FORMAT_GRAYSCALE || image->image_bpp != 1) return false;

    if (image->compression == IMAGE_UNCOMPRESSED) {
        const painter_raw_image_descriptor_t *raw_image_desc = (const painter_raw_image_descriptor_t *)image;
        return drawimage_impl(oled, x, y, image->width, image->height, raw_image_desc->image_data, (val == 0));  // assume a black value means we want to invert
    }

    return false;
}

int16_t qp_qmk_oled_wrapper_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    qmk_oled_painter_device_t *          oled  = (qmk_oled_painter_device_t *)device;
    const painter_raw_font_descriptor_t *fdesc = (const painter_raw_font_descriptor_t *)font;

    // Can only render grayscale images if they're 1bpp
    if (font->image_format != IMAGE_FORMAT_GRAYSCALE || font->image_bpp != 1) return false;

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
                    drawimage_impl(oled, x, y, glyph_desc->width, font->glyph_height, &fdesc->image_data[glyph_desc->offset], (val_fg == 0 && val_bg == 255));  // Assume black fg and white bg means invert
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
                            drawimage_impl(oled, x, y, glyph_desc->width, font->glyph_height, &fdesc->image_data[glyph_desc->offset], (val_fg == 0 && val_bg == 255));  // Assume black fg and white bg means invert
                            x += glyph_desc->width;
                        }
                    }
                }
            }
#endif  // UNICODE_ENABLE
        }
    }

    return (int16_t)x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Device creation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Driver storage
static qmk_oled_painter_device_t driver = {0};

// Factory function for creating a handle to the OLED wrapper device
painter_device_t qp_qmk_oled_wrapper_make_device(void) {
    driver.qp_driver.init      = qp_qmk_oled_wrapper_init;
    driver.qp_driver.clear     = qp_qmk_oled_wrapper_clear;
    driver.qp_driver.power     = qp_qmk_oled_wrapper_power;
    driver.qp_driver.pixdata   = qp_qmk_oled_wrapper_pixdata;
    driver.qp_driver.viewport  = qp_qmk_oled_wrapper_viewport;
    driver.qp_driver.setpixel  = qp_qmk_oled_wrapper_setpixel;
    driver.qp_driver.line      = qp_fallback_line;
    driver.qp_driver.rect      = qp_fallback_rect;
    driver.qp_driver.circle    = qp_fallback_circle;
    driver.qp_driver.ellipse   = qp_fallback_ellipse;
    driver.qp_driver.drawimage = qp_qmk_oled_wrapper_drawimage;
    driver.qp_driver.drawtext  = qp_qmk_oled_wrapper_drawtext;
    return (painter_device_t)&driver;
}
