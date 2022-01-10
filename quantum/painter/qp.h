// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <deferred_exec.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter global configurables (add to your keyboard's config.h)

// This controls the maximum number of images that Quantum Painter can load. Increasing this number in order to load
// more images increases the amount of RAM required.
#ifndef QUANTUM_PAINTER_NUM_IMAGES
#    define QUANTUM_PAINTER_NUM_IMAGES 8
#endif  // QUANTUM_PAINTER_NUM_IMAGES

// This controls the maximum number of fonts that Quantum Painter can load. Increasing this number in order to load
// more fonts increases the amount of RAM required.
#ifndef QUANTUM_PAINTER_NUM_FONTS
#    define QUANTUM_PAINTER_NUM_FONTS 4
#endif  // QUANTUM_PAINTER_NUM_FONTS

// This controls whether or not fonts should be cached in RAM. Under normal circumstances, fonts can have quite random
// access patterns, and due to timing of flash memory or external storage, it can be a significant speedup moving the
// font into RAM before use. Defaults to "off", but if it's enabled it will fallback to reading from the original
// location if corresponding RAM could not be allocated (such as being too large).
// Final note: don't bother setting this to TRUE for AVR. Fonts fit in the available RAM.
#ifndef QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
#    define QUANTUM_PAINTER_LOAD_FONTS_TO_RAM FALSE
#endif

// This controls the maximum number of animations that Quantum Painter can play simultaneously. Increasing this number
// in order to play more animations at the same time increases the amount of RAM required.
#ifndef QUANTUM_PAINTER_CONCURRENT_ANIMATIONS
#    define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 4
#endif  // QUANTUM_PAINTER_CONCURRENT_ANIMATIONS

// This controls the maximum size of the pixel data buffer used for single blocks of transmission. Larger buffers means
// more data is processed at one time, with less frequent transmissions, at the cost of RAM.
#ifndef QP_PIXDATA_BUFFER_SIZE
#    define QP_PIXDATA_BUFFER_SIZE 32
#endif

// This controls whether 256-color palettes are supported -- basically unusable on AVR due to the associated RAM
// requirements on the internal buffer sizes.
#ifndef QUANTUM_PAINTER_SUPPORTS_256_PALETTE
#    define QUANTUM_PAINTER_SUPPORTS_256_PALETTE FALSE
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AVR split address space shenanigans

// Mark certain types that there should be no padding bytes between members.
#define QP_PACKED __attribute__((packed))

// Ensure we can mark certain data as being available in flash, only.
#ifdef __FLASH
#    define QP_RESIDENT_FLASH __flash
#else
// BEWARE: This case will also apply to C++ code on AVR as it has no concept of named address spaces
#    define QP_RESIDENT_FLASH
#endif

// Ensure we can mark certain data as being available in flash or ram.
#ifdef __MEMX
#    define QP_RESIDENT_FLASH_OR_RAM __memx
#else
// BEWARE: This case will also apply to C++ code on AVR as it has no concept of named address spaces
#    define QP_RESIDENT_FLASH_OR_RAM
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter types

// Device type
typedef const void *painter_device_t;

// Rotation type
typedef enum { QP_ROTATION_0, QP_ROTATION_90, QP_ROTATION_180, QP_ROTATION_270 } painter_rotation_t;

// Image handle type
typedef struct painter_image_desc_t {
    uint16_t width;
    uint16_t height;
    uint16_t frame_count;
} painter_image_desc_t;
typedef const painter_image_desc_t *painter_image_handle_t;

// Font handle type
typedef struct painter_font_desc_t {
    uint8_t line_height;
} painter_font_desc_t;
typedef const painter_font_desc_t *painter_font_handle_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API

// Initialize a device and set its rotation -- need to create the device using its corresponding factory method first
bool qp_init(painter_device_t device, painter_rotation_t rotation);

// Handle turning a display on or off -- if a display backlight is controlled through the backlight subsystem, it will need to be handled externally to QP
bool qp_power(painter_device_t device, bool power_on);

// Clear's a device's screen
bool qp_clear(painter_device_t device);

// Transmits any outstanding data to the screen in order to persist all changes to the display -- some drivers without framebuffers will likely ignore this API.
bool qp_flush(painter_device_t device);

// Gets the size of the display
void qp_get_geometry(painter_device_t device, uint16_t *width, uint16_t *height, painter_rotation_t *rotation, uint16_t *offset_x, uint16_t *offset_y);

// Allows repositioning of the viewport if the panel geometry offsets are different to what's expected.
void qp_set_viewport_offsets(painter_device_t device, uint16_t offset_x, uint16_t offset_y);

// Set the viewport that native pixel data is to get streamed into
bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

// Stream pixel data in the device's native format into the previously-set viewport
bool qp_pixdata(painter_device_t device, const void QP_RESIDENT_FLASH_OR_RAM *pixel_data, uint32_t native_pixel_count);

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

// Load an image from memory. Image can be unloaded by invoking qp_close_image() below
// - Returns NULL if unable to load
painter_image_handle_t qp_load_image_mem(const void QP_RESIDENT_FLASH_OR_RAM *buffer);

// Closes an image handle when no longer in use. Returns true if successfully closed.
bool qp_close_image(painter_image_handle_t image);

// Draw an image on the device
bool qp_drawimage(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);
bool qp_drawimage_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

// Draw an animation on the device. Returns INVALID_DEFERRED_TOKEN if the animation could not be kicked off. Animation can be canceled by passing the token to qp_stop_animation() below.
deferred_token qp_animate(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);
deferred_token qp_animate_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

// Cancels an animation
void qp_stop_animation(deferred_token anim_token);

// Load a font from memory. Font can be unloaded by invoking qp_close_font() below
// - Returns NULL if unable to load
painter_font_handle_t qp_load_font_mem(const void QP_RESIDENT_FLASH_OR_RAM *buffer);

// Closes a font handle when no longer in use. Returns true if successfully closed.
bool qp_close_font(painter_font_handle_t font);

// Draw text to the display
int16_t qp_textwidth(painter_font_handle_t font, const char QP_RESIDENT_FLASH_OR_RAM *str);
int16_t qp_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char QP_RESIDENT_FLASH_OR_RAM *str);
int16_t qp_drawtext_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char QP_RESIDENT_FLASH_OR_RAM *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
