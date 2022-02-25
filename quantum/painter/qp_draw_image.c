// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_draw.h"
#include "qp_comms.h"
#include "qgf.h"
#include "deferred_exec.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QGF image handles

typedef struct qgf_image_handle_t {
    painter_image_desc_t base;
    bool                 validate_ok;
    union {
        qp_stream_t        stream;
        qp_memory_stream_t mem_stream;
#ifdef QP_STREAM_HAS_FILE_IO
        qp_file_stream_t file_stream;
#endif // QP_STREAM_HAS_FILE_IO
    };
} qgf_image_handle_t;

static qgf_image_handle_t image_descriptors[QUANTUM_PAINTER_NUM_IMAGES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_load_image_mem

painter_image_handle_t qp_load_image_mem(const void *buffer) {
    qp_dprintf("qp_load_image_mem: entry\n");
    qgf_image_handle_t *image = NULL;

    // Find a free slot
    for (int i = 0; i < QUANTUM_PAINTER_NUM_IMAGES; ++i) {
        if (!image_descriptors[i].validate_ok) {
            image = &image_descriptors[i];
            break;
        }
    }

    // Drop out if not found
    if (!image) {
        qp_dprintf("qp_load_image_mem: fail (no free slot)\n");
        return NULL;
    }

    // Assume we can read the graphics descriptor
    image->mem_stream = qp_make_memory_stream((void *)buffer, sizeof(qgf_graphics_descriptor_v1_t));

    // Update the length of the stream to match, and rewind to the start
    image->mem_stream.length   = qgf_get_total_size(&image->stream);
    image->mem_stream.position = 0;

    // Now that we know the length, validate the input data
    if (!qgf_validate_stream(&image->stream)) {
        qp_dprintf("qp_load_image_mem: fail (failed validation)\n");
        return NULL;
    }

    // Fill out the QP image descriptor
    qgf_read_graphics_descriptor(&image->stream, &image->base.width, &image->base.height, &image->base.frame_count, NULL);

    // Validation success, we can return the handle
    image->validate_ok = true;
    qp_dprintf("qp_load_image_mem: ok\n");
    return (painter_image_handle_t)image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_close_image

bool qp_close_image(painter_image_handle_t image) {
    qgf_image_handle_t *qgf_image = (qgf_image_handle_t *)image;
    if (!qgf_image->validate_ok) {
        qp_dprintf("qp_close_image: fail (invalid image)\n");
        return false;
    }

    // Free up this image for use elsewhere.
    qgf_image->validate_ok = false;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_drawimage

bool qp_drawimage(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image) {
    return qp_drawimage_recolor(device, x, y, image, 0, 0, 255, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_drawimage_recolor

typedef struct qgf_frame_info_t {
    painter_compression_t compression_scheme;
    uint8_t               bpp;
    bool                  has_palette;
    bool                  is_delta;
    uint16_t              left;
    uint16_t              top;
    uint16_t              right;
    uint16_t              bottom;
    uint16_t              delay;
} qgf_frame_info_t;

static bool qp_drawimage_prepare_frame_for_stream_read(painter_device_t device, qgf_image_handle_t *qgf_image, uint16_t frame_number, qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888, qgf_frame_info_t *info) {
    struct painter_driver_t *driver = (struct painter_driver_t *)device;

    // Drop out if we can't actually place the data we read out anywhere
    if (!info) {
        qp_dprintf("Failed to prepare stream for read, output info buffer unavailable\n");
        return false;
    }

    // Seek to the frame
    qgf_seek_to_frame_descriptor(&qgf_image->stream, frame_number);

    // Read the frame descriptor
    qgf_frame_v1_t frame_descriptor;
    if (qp_stream_read(&frame_descriptor, sizeof(qgf_frame_v1_t), 1, &qgf_image->stream) != 1) {
        qp_dprintf("Failed to read frame_descriptor, expected length was not %d\n", (int)sizeof(qgf_frame_v1_t));
        return false;
    }

    // Parse out the frame info
    if (!qgf_parse_frame_descriptor(&frame_descriptor, &info->bpp, &info->has_palette, &info->is_delta, &info->compression_scheme, &info->delay)) {
        return false;
    }

    // Ensure we aren't reusing any palette
    qp_internal_invalidate_palette();

    // Handle palette if needed
    const uint16_t palette_entries  = 1u << info->bpp;
    bool           needs_pixconvert = false;
    if (info->has_palette) {
        // Load the palette from the stream
        if (!qp_internal_load_qgf_palette((qp_stream_t *)&qgf_image->stream, info->bpp)) {
            return false;
        }

        needs_pixconvert = true;
    } else {
        // Interpolate from fg/bg
        needs_pixconvert = qp_internal_interpolate_palette(fg_hsv888, bg_hsv888, palette_entries);
    }

    if (!qp_internal_bpp_capable(info->bpp)) {
        qp_dprintf("qp_drawimage_recolor: fail (image bpp too high (%d), check QUANTUM_PAINTER_SUPPORTS_256_PALETTE)\n", (int)info->bpp);
        qp_comms_stop(device);
        return false;
    }

    if (needs_pixconvert) {
        // Convert the palette to native format
        if (!driver->driver_vtable->palette_convert(device, palette_entries, qp_internal_global_pixel_lookup_table)) {
            qp_dprintf("qp_drawimage_recolor: fail (could not convert pixels to native)\n");
            qp_comms_stop(device);
            return false;
        }
    }

    // Handle delta if needed
    if (info->is_delta) {
        qgf_delta_v1_t delta_descriptor;
        if (qp_stream_read(&delta_descriptor, sizeof(qgf_delta_v1_t), 1, &qgf_image->stream) != 1) {
            qp_dprintf("Failed to read delta_descriptor, expected length was not %d\n", (int)sizeof(qgf_delta_v1_t));
            return false;
        }

        info->left   = delta_descriptor.left;
        info->top    = delta_descriptor.top;
        info->right  = delta_descriptor.right;
        info->bottom = delta_descriptor.bottom;
    }

    // Read the data block
    qgf_data_v1_t data_descriptor;
    if (qp_stream_read(&data_descriptor, sizeof(qgf_data_v1_t), 1, &qgf_image->stream) != 1) {
        qp_dprintf("Failed to read data_descriptor, expected length was not %d\n", (int)sizeof(qgf_data_v1_t));
        return false;
    }

    // Stream is now at the point of being able to read pixdata
    return true;
}

static bool qp_drawimage_recolor_impl(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, int frame_number, qgf_frame_info_t *frame_info, qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888) {
    qp_dprintf("qp_drawimage_recolor: entry\n");
    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_drawimage_recolor: fail (validation_ok == false)\n");
        return false;
    }

    qgf_image_handle_t *qgf_image = (qgf_image_handle_t *)image;
    if (!qgf_image->validate_ok) {
        qp_dprintf("qp_drawimage_recolor: fail (invalid image)\n");
        return false;
    }

    // Read the frame info
    if (!qp_drawimage_prepare_frame_for_stream_read(device, qgf_image, frame_number, fg_hsv888, bg_hsv888, frame_info)) {
        qp_dprintf("qp_drawimage_recolor: fail (could not read frame %d)\n", frame_number);
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_drawimage_recolor: fail (could not start comms)\n");
        return false;
    }

    uint16_t l, t, r, b;
    if (frame_info->is_delta) {
        l = x + frame_info->left;
        t = y + frame_info->top;
        r = x + frame_info->right - 1;
        b = y + frame_info->bottom - 1;
    } else {
        l = x;
        t = y;
        r = x + image->width - 1;
        b = y + image->height - 1;
    }
    uint32_t pixel_count = ((uint32_t)(r - l + 1)) * (b - t + 1);

    // Configure where we're going to be rendering to
    if (!driver->driver_vtable->viewport(device, l, t, r, b)) {
        qp_dprintf("qp_drawimage_recolor: fail (could not set viewport)\n");
        qp_comms_stop(device);
        return false;
    }

    // Set up the input state
    struct qp_internal_byte_input_state input_state    = {.device = device, .src_stream = &qgf_image->stream};
    qp_internal_byte_input_callback     input_callback = qp_internal_prepare_input_state(&input_state, frame_info->compression_scheme);
    if (input_callback == NULL) {
        qp_dprintf("qp_drawimage_recolor: fail (invalid image compression scheme)\n");
        qp_comms_stop(device);
        return false;
    }

    // Set up the output state
    struct qp_internal_pixel_output_state output_state = {.device = device, .pixel_write_pos = 0, .max_pixels = qp_internal_num_pixels_in_buffer(device)};

    // Decode the pixel data and stream to the display
    bool ret = qp_internal_decode_palette(device, pixel_count, frame_info->bpp, input_callback, &input_state, qp_internal_global_pixel_lookup_table, qp_internal_pixel_appender, &output_state);

    // Any leftovers need transmission as well.
    if (ret && output_state.pixel_write_pos > 0) {
        ret &= driver->driver_vtable->pixdata(device, qp_internal_global_pixdata_buffer, output_state.pixel_write_pos);
    }

    qp_dprintf("qp_drawimage_recolor: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret;
}

bool qp_drawimage_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    qgf_frame_info_t frame_info = {0};
    qp_pixel_t       fg_hsv888  = {.hsv888 = {.h = hue_fg, .s = sat_fg, .v = val_fg}};
    qp_pixel_t       bg_hsv888  = {.hsv888 = {.h = hue_bg, .s = sat_bg, .v = val_bg}};
    return qp_drawimage_recolor_impl(device, x, y, image, 0, &frame_info, fg_hsv888, bg_hsv888);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_animate

deferred_token qp_animate(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image) {
    return qp_animate_recolor(device, x, y, image, 0, 0, 255, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_animate_recolor

typedef struct animation_state_t {
    painter_device_t       device;
    uint16_t               x;
    uint16_t               y;
    painter_image_handle_t image;
    qp_pixel_t             fg_hsv888;
    qp_pixel_t             bg_hsv888;
    uint16_t               frame_number;
    deferred_token         defer_token;
} animation_state_t;

static deferred_executor_t animation_executors[QUANTUM_PAINTER_CONCURRENT_ANIMATIONS] = {0};
static animation_state_t   animation_states[QUANTUM_PAINTER_CONCURRENT_ANIMATIONS]    = {0};

static deferred_token qp_render_animation_state(animation_state_t *state, uint16_t *delay_ms) {
    qgf_frame_info_t frame_info = {0};
    qp_dprintf("qp_render_animation_state: entry (frame #%d)\n", (int)state->frame_number);
    bool ret = qp_drawimage_recolor_impl(state->device, state->x, state->y, state->image, state->frame_number, &frame_info, state->fg_hsv888, state->bg_hsv888);
    if (ret) {
        ++state->frame_number;
        if (state->frame_number >= state->image->frame_count) {
            state->frame_number = 0;
        }
        *delay_ms = frame_info.delay;
    }
    qp_dprintf("qp_render_animation_state: %s (delay %dms)\n", ret ? "ok" : "fail", (int)(*delay_ms));
    return ret;
}

static uint32_t animation_callback(uint32_t trigger_time, void *cb_arg) {
    animation_state_t *state = (animation_state_t *)cb_arg;
    uint16_t           delay_ms;
    bool               ret = qp_render_animation_state(state, &delay_ms);
    if (!ret) {
        // Setting the device to NULL clears the animation slot
        state->device = NULL;
    }
    // If we're successful, keep animating -- returning 0 cancels the deferred execution
    return ret ? delay_ms : 0;
}

deferred_token qp_animate_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    qp_dprintf("qp_animate_recolor: entry\n");

    animation_state_t *anim_state = NULL;
    for (int i = 0; i < QUANTUM_PAINTER_CONCURRENT_ANIMATIONS; ++i) {
        if (animation_states[i].device == NULL) {
            anim_state = &animation_states[i];
            break;
        }
    }

    if (!anim_state) {
        qp_dprintf("qp_animate_recolor: fail (could not find free animation slot)\n");
        return INVALID_DEFERRED_TOKEN;
    }

    // Prepare the animation state
    anim_state->device       = device;
    anim_state->x            = x;
    anim_state->y            = y;
    anim_state->image        = image;
    anim_state->fg_hsv888    = (qp_pixel_t){.hsv888 = {.h = hue_fg, .s = sat_fg, .v = val_fg}};
    anim_state->bg_hsv888    = (qp_pixel_t){.hsv888 = {.h = hue_bg, .s = sat_bg, .v = val_bg}};
    anim_state->frame_number = 0;

    // Draw the first frame
    uint16_t delay_ms;
    if (!qp_render_animation_state(anim_state, &delay_ms)) {
        anim_state->device = NULL; // disregard the allocated animation slot
        qp_dprintf("qp_animate_recolor: fail (could not render first frame)\n");
        return INVALID_DEFERRED_TOKEN;
    }

    // Set up the timer
    anim_state->defer_token = defer_exec_advanced(animation_executors, QUANTUM_PAINTER_CONCURRENT_ANIMATIONS, delay_ms, animation_callback, anim_state);
    if (anim_state->defer_token == INVALID_DEFERRED_TOKEN) {
        anim_state->device = NULL; // disregard the allocated animation slot
        qp_dprintf("qp_animate_recolor: fail (could not set up animation executor)\n");
        return INVALID_DEFERRED_TOKEN;
    }

    qp_dprintf("qp_animate_recolor: ok (deferred token = %d)\n", (int)anim_state->defer_token);
    return anim_state->defer_token;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_stop_animation

void qp_stop_animation(deferred_token anim_token) {
    for (int i = 0; i < QUANTUM_PAINTER_CONCURRENT_ANIMATIONS; ++i) {
        if (animation_states[i].defer_token == anim_token) {
            cancel_deferred_exec_advanced(animation_executors, QUANTUM_PAINTER_CONCURRENT_ANIMATIONS, anim_token);
            animation_states[i].device = NULL;
            return;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter Core API: qp_internal_animation_tick

void qp_internal_animation_tick(void) {
    static uint32_t last_anim_exec = 0;
    deferred_exec_advanced_task(animation_executors, QUANTUM_PAINTER_CONCURRENT_ANIMATIONS, &last_anim_exec);
}
