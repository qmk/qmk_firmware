// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"
#include "qp_draw.h"
#include "qp_comms.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Palette / Monochrome-format decoder

static const qp_pixel_t qp_pixel_white = {.hsv888 = {.h = 0, .s = 0, .v = 255}};
static const qp_pixel_t qp_pixel_black = {.hsv888 = {.h = 0, .s = 0, .v = 0}};

bool qp_internal_bpp_capable(uint8_t bits_per_pixel) {
#if !(QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS)
#    if !(QUANTUM_PAINTER_SUPPORTS_256_PALETTE)
    if (bits_per_pixel > 4) {
        qp_dprintf("qp_internal_decode_palette: image bpp greater than 4\n");
        return false;
    }
#    endif

    if (bits_per_pixel > 8) {
        qp_dprintf("qp_internal_decode_palette: image bpp greater than 8\n");
        return false;
    }
#endif
    return true;
}

bool qp_internal_decode_palette(painter_device_t device, uint32_t pixel_count, uint8_t bits_per_pixel, qp_internal_byte_input_callback input_callback, void* input_arg, qp_pixel_t* palette, qp_internal_pixel_output_callback output_callback, void* output_arg) {
    const uint8_t pixel_bitmask    = (1 << bits_per_pixel) - 1;
    const uint8_t pixels_per_byte  = 8 / bits_per_pixel;
    uint32_t      remaining_pixels = pixel_count; // don't try to derive from byte_count, we may not use an entire byte
    while (remaining_pixels > 0) {
        int16_t byteval = input_callback(input_arg);
        if (byteval < 0) {
            return false;
        }
        uint8_t loop_pixels = remaining_pixels < pixels_per_byte ? remaining_pixels : pixels_per_byte;
        for (uint8_t q = 0; q < loop_pixels; ++q) {
            if (!output_callback(palette, byteval & pixel_bitmask, output_arg)) {
                return false;
            }
            byteval >>= bits_per_pixel;
        }
        remaining_pixels -= loop_pixels;
    }
    return true;
}

bool qp_internal_decode_grayscale(painter_device_t device, uint32_t pixel_count, uint8_t bits_per_pixel, qp_internal_byte_input_callback input_callback, void* input_arg, qp_internal_pixel_output_callback output_callback, void* output_arg) {
    return qp_internal_decode_recolor(device, pixel_count, bits_per_pixel, input_callback, input_arg, qp_pixel_white, qp_pixel_black, output_callback, output_arg);
}

bool qp_internal_decode_recolor(painter_device_t device, uint32_t pixel_count, uint8_t bits_per_pixel, qp_internal_byte_input_callback input_callback, void* input_arg, qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888, qp_internal_pixel_output_callback output_callback, void* output_arg) {
    painter_driver_t* driver = (painter_driver_t*)device;
    int16_t           steps  = 1 << bits_per_pixel; // number of items we need to interpolate
    if (qp_internal_interpolate_palette(fg_hsv888, bg_hsv888, steps)) {
        if (!driver->driver_vtable->palette_convert(device, steps, qp_internal_global_pixel_lookup_table)) {
            return false;
        }
    }

    return qp_internal_decode_palette(device, pixel_count, bits_per_pixel, input_callback, input_arg, qp_internal_global_pixel_lookup_table, output_callback, output_arg);
}

bool qp_internal_send_bytes(painter_device_t device, uint32_t byte_count, qp_internal_byte_input_callback input_callback, void* input_arg, qp_internal_byte_output_callback output_callback, void* output_arg) {
    uint32_t remaining_bytes = byte_count;
    while (remaining_bytes > 0) {
        int16_t byteval = input_callback(input_arg);
        if (byteval < 0) {
            return false;
        }
        if (!output_callback(byteval, output_arg)) {
            return false;
        }
        remaining_bytes -= 1;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Progressive pull of bytes, push of pixels

static inline int16_t qp_drawimage_byte_uncompressed_decoder(void* cb_arg) {
    qp_internal_byte_input_state_t* state = (qp_internal_byte_input_state_t*)cb_arg;
    state->curr                           = qp_stream_get(state->src_stream);
    return state->curr;
}

static inline int16_t qp_drawimage_byte_rle_decoder(void* cb_arg) {
    qp_internal_byte_input_state_t* state = (qp_internal_byte_input_state_t*)cb_arg;

    // Work out if we're parsing the initial marker byte
    if (state->rle.mode == MARKER_BYTE) {
        uint8_t c = qp_stream_get(state->src_stream);
        if (c >= 128) {
            state->rle.mode   = NON_REPEATING_RUN; // non-repeated run
            state->rle.remain = c - 127;
        } else {
            state->rle.mode   = REPEATING_RUN; // repeated run
            state->rle.remain = c;
        }

        state->curr = qp_stream_get(state->src_stream);
    }

    // Work out which byte we're returning
    uint8_t c = state->curr;

    // Decrement the counter of the bytes remaining
    state->rle.remain--;

    if (state->rle.remain > 0) {
        // If we're in a non-repeating run, queue up the next byte
        if (state->rle.mode == NON_REPEATING_RUN) {
            state->curr = qp_stream_get(state->src_stream);
        }
    } else {
        // Swap back to querying the marker byte mode
        state->rle.mode = MARKER_BYTE;
    }

    return c;
}

bool qp_internal_pixel_appender(qp_pixel_t* palette, uint8_t index, void* cb_arg) {
    qp_internal_pixel_output_state_t* state  = (qp_internal_pixel_output_state_t*)cb_arg;
    painter_driver_t*                 driver = (painter_driver_t*)state->device;

    if (!driver->driver_vtable->append_pixels(state->device, qp_internal_global_pixdata_buffer, palette, state->pixel_write_pos++, 1, &index)) {
        return false;
    }

    // If we've hit the transmit limit, send out the entire buffer and reset the write position
    if (state->pixel_write_pos == state->max_pixels) {
        if (!driver->driver_vtable->pixdata(state->device, qp_internal_global_pixdata_buffer, state->pixel_write_pos)) {
            return false;
        }
        state->pixel_write_pos = 0;
    }

    return true;
}

bool qp_internal_byte_appender(uint8_t byteval, void* cb_arg) {
    qp_internal_byte_output_state_t* state  = (qp_internal_byte_output_state_t*)cb_arg;
    painter_driver_t*                driver = (painter_driver_t*)state->device;

    if (!driver->driver_vtable->append_pixdata(state->device, qp_internal_global_pixdata_buffer, state->byte_write_pos++, byteval)) {
        return false;
    }

    // If we've hit the transmit limit, send out the entire buffer and reset the write position
    if (state->byte_write_pos == state->max_bytes) {
        painter_driver_t* driver = (painter_driver_t*)state->device;
        if (!driver->driver_vtable->pixdata(state->device, qp_internal_global_pixdata_buffer, state->byte_write_pos * 8 / driver->native_bits_per_pixel)) {
            return false;
        }
        state->byte_write_pos = 0;
    }

    return true;
}

qp_internal_byte_input_callback qp_internal_prepare_input_state(qp_internal_byte_input_state_t* input_state, painter_compression_t compression) {
    switch (compression) {
        case IMAGE_UNCOMPRESSED:
            return qp_drawimage_byte_uncompressed_decoder;
        case IMAGE_COMPRESSED_RLE:
            input_state->rle.mode   = MARKER_BYTE;
            input_state->rle.remain = 0;
            return qp_drawimage_byte_rle_decoder;
        default:
            return NULL;
    }
}
