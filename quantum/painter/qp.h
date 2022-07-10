// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "deferred_exec.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter global configurables (add to your keyboard's config.h)

#ifndef QUANTUM_PAINTER_NUM_IMAGES
/**
 * @def This controls the maximum number of images that Quantum Painter can load at any one time. Images can be loaded
 *      using \ref qp_load_image_mem, and can be unloaded by calling \ref qp_close_image. Increasing this number in
 *      order to load more images increases the amount of RAM required. Image data is not held in RAM, just metadata.
 */
#    define QUANTUM_PAINTER_NUM_IMAGES 8
#endif // QUANTUM_PAINTER_NUM_IMAGES

#ifndef QUANTUM_PAINTER_NUM_FONTS
/**
 * @def This controls the maximum number of fonts that Quantum Painter can load. Fonts can be loaded using
 *      \ref qp_load_font_mem, and can be unloaded by calling \ref qp_close_font. Increasing this number in order to
 *      load more fonts increases the amount of RAM required. Font data is not held in RAM, unless
 *      \ref QUANTUM_PAINTER_LOAD_FONTS_TO_RAM is set to TRUE.
 */
#    define QUANTUM_PAINTER_NUM_FONTS 4
#endif // QUANTUM_PAINTER_NUM_FONTS

#ifndef QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
/**
 * @def This controls whether or not fonts should be cached in RAM. Under normal circumstances, fonts can have quite
 *      random access patterns, and due to timing of flash memory or external storage, it may be a significant speedup
 *      moving the font into RAM before use. Defaults to "off", but if it's enabled it will fallback to reading from the
 *      original location if corresponding RAM could not be allocated (such as being too large).
 */
#    define QUANTUM_PAINTER_LOAD_FONTS_TO_RAM FALSE
#endif

#ifndef QUANTUM_PAINTER_CONCURRENT_ANIMATIONS
/**
 * @def This controls the maximum number of animations that Quantum Painter can play simultaneously. Increasing this
 *      number in order to play more animations at the same time increases the amount of RAM required.
 */
#    define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 4
#endif // QUANTUM_PAINTER_CONCURRENT_ANIMATIONS

#ifndef QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE
/**
 * @def This controls the maximum size of the pixel data buffer used for single blocks of transmission. Larger buffers
 *      means more data is processed at one time, with less frequent transmissions, at the cost of RAM.
 */
#    define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 32
#endif

#ifndef QUANTUM_PAINTER_SUPPORTS_256_PALETTE
/**
 * @def This controls whether 256-color palettes are supported. This has relatively hefty requirements on RAM -- at
 *      least 1kB extra is required just to store the palette information, with more required for other metadata.
 */
#    define QUANTUM_PAINTER_SUPPORTS_256_PALETTE FALSE
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter types

/**
 * @typedef A handle to a Quantum Painter device, such as an LCD or OLED. Most Quantum Painter APIs require this
 *          argument in order to perform operations on the display.
 */
typedef const void *painter_device_t;

/**
 * @typedef The desired rotation of a panel. Used as a parameter to \ref qp_init, and can be queried by
 *          \ref qp_get_geometry.
 */
typedef enum { QP_ROTATION_0, QP_ROTATION_90, QP_ROTATION_180, QP_ROTATION_270 } painter_rotation_t;

/**
 * @typedef A descriptor for a Quantum Painter image.
 */
typedef struct painter_image_desc_t {
    uint16_t width;       ///< Image width
    uint16_t height;      ///< Image height
    uint16_t frame_count; ///< Number of frames in this image
} painter_image_desc_t;

/**
 * @typedef A handle to a Quantum Painter image.
 */
typedef const painter_image_desc_t *painter_image_handle_t;

/**
 * @typedef A descriptor for a Quantum Painter font.
 */
typedef struct painter_font_desc_t {
    uint8_t line_height; ///< The number of pixels in height for each line
} painter_font_desc_t;

/**
 * @typedef A handle to a Quantum Painter font.
 */
typedef const painter_font_desc_t *painter_font_handle_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API

/**
 * Initialize a device and set its rotation.
 *
 * @param device[in] the handle of the device to initialize
 * @param rotation[in] the rotation to use
 * @return true if initialization succeeded
 * @return false if initialization failed
 */
bool qp_init(painter_device_t device, painter_rotation_t rotation);

/**
 * Controls whether a display is on or off.
 *
 * @note If backlighting is used to control brightness (such as for an LCD), it will need to be handled external to
 *       Quantum Painter.
 *
 * @param device[in] the handle of the device to control
 * @param power_on[in] whether or not the device should be on
 * @return true if controlling the power state succeeded
 * @return false if controlling the power state failed
 */
bool qp_power(painter_device_t device, bool power_on);

/**
 * Clears a device's screen.
 *
 * @param device[in] the handle of the device to control
 * @return true if clearing the screen succeeded
 * @return false if clearing the screen failed
 */
bool qp_clear(painter_device_t device);

/**
 * Transmits any outstanding data to the screen in order to persist all changes to the display.
 *
 * @note Drivers without internal framebuffers will likely ignore this API.
 *
 * @param device[in] the handle of the device to control
 * @return true if flushing changes to the screen succeeded
 * @return false if flushing changes to the screen failed
 */
bool qp_flush(painter_device_t device);

/**
 * Retrieves the size, rotation, and offsets for the display.
 *
 * @note Any arguments of NULL will be ignored.
 *
 * @param device[in] the handle of the device to control
 * @param width[out] the device's width
 * @param height[out] the device's height
 * @param rotation[out] the device's rotation
 * @param offset_x[out] the device's x-offset applied while drawing
 * @param offset_y[out] the device's y-offset applied while drawing
 */
void qp_get_geometry(painter_device_t device, uint16_t *width, uint16_t *height, painter_rotation_t *rotation, uint16_t *offset_x, uint16_t *offset_y);

/**
 * Allows repositioning of the viewport if the panel geometry offsets are non-zero.
 *
 * @param device[in] the handle of the device to control
 * @param offset_x[in] the device's x-offset applied while drawing
 * @param offset_y[in] the device's y-offset applied while drawing
 */
void qp_set_viewport_offsets(painter_device_t device, uint16_t offset_x, uint16_t offset_y);

/**
 * Sets a pixel to the specified color.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position to draw onto the device
 * @param y[in] the y-position to draw onto the device
 * @param hue[in] the hue to use, with 0-360 mapped to 0-255
 * @param sat[in] the saturation to use, with 0-100% mapped to 0-255
 * @param val[in] the value to use, with 0-100% mapped to 0-255
 * @return true if setting the pixel succeeded
 * @return false if setting the pixel failed
 */
bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val);

/**
 * Draws a line using the specified color.
 *
 * @param device[in] the handle of the device to control
 * @param x0[in] the device's x-position to start
 * @param y0[in] the device's y-position to start
 * @param x1[in] the device's x-position to finish
 * @param y1[in] the device's y-position to finish
 * @param hue[in] the hue to use, with 0-360 mapped to 0-255
 * @param sat[in] the saturation to use, with 0-100% mapped to 0-255
 * @param val[in] the value to use, with 0-100% mapped to 0-255
 * @return true if drawing the line succeeded
 * @return false if drawing the line failed
 */
bool qp_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val);

/**
 * Draws a rectangle using the specified color, optionally filled.
 *
 * @param device[in] the handle of the device to control
 * @param left[in] the device's x-position to start
 * @param top[in] the device's y-position to start
 * @param right[in] the device's x-position to finish
 * @param bottom[in] the device's y-position to finish
 * @param hue[in] the hue to use, with 0-360 mapped to 0-255
 * @param sat[in] the saturation to use, with 0-100% mapped to 0-255
 * @param val[in] the value to use, with 0-100% mapped to 0-255
 * @param filled[in] whether the rectangle should be filled
 * @return true if drawing the rectangle succeeded
 * @return false if drawing the rectangle failed
 */
bool qp_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled);

/**
 * Draws a circle using the specified color, optionally filled.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position of the centre of the circle to draw onto the device
 * @param y[in] the y-position of the centre of the circle to draw onto the device
 * @param radius[in] the radius of the circle to draw
 * @param hue[in] the hue to use, with 0-360 mapped to 0-255
 * @param sat[in] the saturation to use, with 0-100% mapped to 0-255
 * @param val[in] the value to use, with 0-100% mapped to 0-255
 * @param filled[in] whether the circle should be filled
 * @return true if drawing the circle succeeded
 * @return false if drawing the circle failed
 */
bool qp_circle(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled);

/**
 * Draws a ellipse using the specified color, optionally filled.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position of the centre of the ellipse to draw onto the device
 * @param y[in] the y-position of the centre of the ellipse to draw onto the device
 * @param sizex[in] the horizontal size of the ellipse
 * @param sizey[in] the vertical size of the ellipse
 * @param hue[in] the hue to use, with 0-360 mapped to 0-255
 * @param sat[in] the saturation to use, with 0-100% mapped to 0-255
 * @param val[in] the value to use, with 0-100% mapped to 0-255
 * @param filled[in] whether the ellipse should be filled
 * @return true if drawing the ellipse succeeded
 * @return false if drawing the ellipse failed
 */
bool qp_ellipse(painter_device_t device, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t hue, uint8_t sat, uint8_t val, bool filled);

/**
 * Sets up the location on the display to stream raw pixel data to the display, using \ref qp_pixdata.
 *
 * @note This is for advanced uses only, and should not be required for normal Quantum Painter functionality.
 *
 * @param device[in] the handle of the device to control
 * @param left[in] the device's x-position to start
 * @param top[in] the device's y-position to start
 * @param right[in] the device's x-position to finish
 * @param bottom[in] the device's y-position to finish
 * @return true if setting the viewport succeeded
 * @return false if setting the viewport failed
 */
bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

/**
 * Streams raw pixel data (in the native panel format) to the area previously set by \ref qp_viewport.
 *
 * @note This is for advanced uses only, and should not be required for normal Quantum Painter functionality.
 *
 * @param device[in] the handle of the device to control
 * @param pixel_data[in] pointer to buffer data
 * @param native_pixel_count[in] the number of pixels to transmit
 * @return true if streaming of data succeeded
 * @return false if streaming of data failed
 */
bool qp_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);

/**
 * Loads an image into memory.
 *
 * @note Images can be unloaded by calling \ref qp_close_image.
 *
 * @param buffer[in] the image data to load
 * @return an image handle usable with \ref qp_drawimage, \ref qp_drawimage_recolor, \ref qp_animate, and
 *         \ref qp_animate_recolor.
 * @return NULL if loading the image failed
 */
painter_image_handle_t qp_load_image_mem(const void *buffer);

/**
 * Closes an image handle when no longer in use.
 *
 * @param image[in] the handle of the image to unload
 * @return true if unloading the image succeeded
 * @return false if unloading the image failed
 */
bool qp_close_image(painter_image_handle_t image);

/**
 * Draws an image to the display.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position where the image should be drawn onto the device
 * @param y[in] the y-position where the image should be drawn onto the device
 * @param image[in] the handle of the image to draw
 * @return true if drawing the image succeeded
 * @return false if drawing the image failed
 */
bool qp_drawimage(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);

/**
 * Draws an image to the display, recoloring monochrome images to the desired foreground/background.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position where the image should be drawn onto the device
 * @param y[in] the y-position where the image should be drawn onto the device
 * @param image[in] the handle of the image to draw
 * @param hue_fg[in] the foreground hue to use, with 0-360 mapped to 0-255
 * @param sat_fg[in] the foreground saturation to use, with 0-100% mapped to 0-255
 * @param val_fg[in] the foreground value to use, with 0-100% mapped to 0-255
 * @param hue_bg[in] the background hue to use, with 0-360 mapped to 0-255
 * @param sat_bg[in] the background saturation to use, with 0-100% mapped to 0-255
 * @param val_bg[in] the background value to use, with 0-100% mapped to 0-255
 * @return true if drawing the image succeeded
 * @return false if drawing the image failed
 */
bool qp_drawimage_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

/**
 * Draws an animation to the display.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position where the image should be drawn onto the device
 * @param y[in] the y-position where the image should be drawn onto the device
 * @param image[in] the handle of the image to draw
 * @return the \ref deferred_token to use with \ref qp_stop_animation in order to stop animating
 * @return INVALID_DEFERRED_TOKEN if animating the image failed
 */
deferred_token qp_animate(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);

/**
 * Draws an animation to the display, recoloring monochrome images to the desired foreground/background.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position where the image should be drawn onto the device
 * @param y[in] the y-position where the image should be drawn onto the device
 * @param image[in] the handle of the image to draw
 * @param hue_fg[in] the foreground hue to use, with 0-360 mapped to 0-255
 * @param sat_fg[in] the foreground saturation to use, with 0-100% mapped to 0-255
 * @param val_fg[in] the foreground value to use, with 0-100% mapped to 0-255
 * @param hue_bg[in] the background hue to use, with 0-360 mapped to 0-255
 * @param sat_bg[in] the background saturation to use, with 0-100% mapped to 0-255
 * @param val_bg[in] the background value to use, with 0-100% mapped to 0-255
 * @return the \ref deferred_token to use with \ref qp_stop_animation in order to stop animating
 * @return INVALID_DEFERRED_TOKEN if animating the image failed
 */
deferred_token qp_animate_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

/**
 * Cancels a running animation.
 *
 * @param anim_token[in] the animation token returned by \ref qp_animate, or \ref qp_animate_recolor.
 */
void qp_stop_animation(deferred_token anim_token);

/**
 * Loads a font into memory.
 *
 * @note Fonts can be unloaded by calling \ref qp_close_font.
 *
 * @param buffer[in] the font data to load
 * @return an image handle usable with \ref qp_textwidth, \ref qp_drawtext, and \ref qp_drawtext_recolor.
 * @return NULL if loading the font failed
 */
painter_font_handle_t qp_load_font_mem(const void *buffer);

/**
 * Closes a font handle when no longer in use.
 *
 * @param font[in] the handle of the font to unload
 * @return true if unloading the font succeeded
 * @return false if unloading the font failed
 */
bool qp_close_font(painter_font_handle_t font);

/**
 * Measures the width (in pixels) of the supplied string, given the specified font.
 *
 * @param font[in] the handle of the font
 * @param str[in] the string to measure
 * @return the width (in pixels) needed to draw the specified string
 */
int16_t qp_textwidth(painter_font_handle_t font, const char *str);

/**
 * Draws text to the display.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position where the text should be drawn onto the device
 * @param y[in] the y-position where the text should be drawn onto the device
 * @param font[in] the handle of the font
 * @param str[in] the string to draw
 * @return the width (in pixels) used when drawing the specified string
 */
int16_t qp_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str);

/**
 * Draws text to the display, recoloring monochrome fonts to the desired foreground/background.
 *
 * @param device[in] the handle of the device to control
 * @param x[in] the x-position where the text should be drawn onto the device
 * @param y[in] the y-position where the text should be drawn onto the device
 * @param font[in] the handle of the font
 * @param str[in] the string to draw
 * @param hue_fg[in] the foreground hue to use, with 0-360 mapped to 0-255
 * @param sat_fg[in] the foreground saturation to use, with 0-100% mapped to 0-255
 * @param val_fg[in] the foreground value to use, with 0-100% mapped to 0-255
 * @param hue_bg[in] the background hue to use, with 0-360 mapped to 0-255
 * @param sat_bg[in] the background saturation to use, with 0-100% mapped to 0-255
 * @param val_bg[in] the background value to use, with 0-100% mapped to 0-255
 * @return the width (in pixels) used when drawing the specified string
 */
int16_t qp_drawtext_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter Drivers

#ifdef QUANTUM_PAINTER_ILI9163_ENABLE
#    include "qp_ili9163.h"
#endif // QUANTUM_PAINTER_ILI9163_ENABLE

#ifdef QUANTUM_PAINTER_ILI9341_ENABLE
#    include "qp_ili9341.h"
#endif // QUANTUM_PAINTER_ILI9341_ENABLE

#ifdef QUANTUM_PAINTER_ILI9488_ENABLE
#    include "qp_ili9488.h"
#endif // QUANTUM_PAINTER_ILI9488_ENABLE

#ifdef QUANTUM_PAINTER_ST7789_ENABLE
#    include "qp_st7789.h"
#endif // QUANTUM_PAINTER_ST7789_ENABLE

#ifdef QUANTUM_PAINTER_GC9A01_ENABLE
#    include "qp_gc9a01.h"
#endif // QUANTUM_PAINTER_GC9A01_ENABLE

#ifdef QUANTUM_PAINTER_SSD1351_ENABLE
#    include "qp_ssd1351.h"
#endif // QUANTUM_PAINTER_SSD1351_ENABLE
