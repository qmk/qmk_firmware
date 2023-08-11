// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <quantum.h>
#include <utf8.h>

#include "qp_internal.h"
#include "qp_draw.h"
#include "qp_comms.h"
#include "qff.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QFF font handles

typedef struct qff_font_handle_t {
    painter_font_desc_t   base;
    bool                  validate_ok;
    bool                  has_ascii_table;
    uint16_t              num_unicode_glyphs;
    uint8_t               bpp;
    bool                  has_palette;
    painter_compression_t compression_scheme;
    union {
        qp_stream_t        stream;
        qp_memory_stream_t mem_stream;
#ifdef QP_STREAM_HAS_FILE_IO
        qp_file_stream_t file_stream;
#endif // QP_STREAM_HAS_FILE_IO
    };
#if QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
    bool  owns_buffer;
    void *buffer;
#endif // QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
} qff_font_handle_t;

static qff_font_handle_t font_descriptors[QUANTUM_PAINTER_NUM_FONTS] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper: load font from stream

static painter_font_handle_t qp_load_font_internal(bool (*stream_factory)(qff_font_handle_t *font, void *arg), void *arg) {
    qp_dprintf("qp_load_font: entry\n");
    qff_font_handle_t *font = NULL;

    // Find a free slot
    for (int i = 0; i < QUANTUM_PAINTER_NUM_FONTS; ++i) {
        if (!font_descriptors[i].validate_ok) {
            font = &font_descriptors[i];
            break;
        }
    }

    // Drop out if not found
    if (!font) {
        qp_dprintf("qp_load_font: fail (no free slot)\n");
        return NULL;
    }

    if (!stream_factory(font, arg)) {
        qp_dprintf("qp_load_font: fail (could not create stream)\n");
        return NULL;
    }

    // Now that we know the length, validate the input data
    if (!qff_validate_stream(&font->stream)) {
        qp_dprintf("qp_load_font: fail (failed validation)\n");
        return NULL;
    }

#if QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
    // Clear out any existing data
    font->owns_buffer = false;
    font->buffer      = NULL;

    void *ram_buffer = malloc(font->mem_stream.length);
    if (ram_buffer == NULL) {
        qp_dprintf("qp_load_font: could not allocate enough RAM for font, falling back to original\n");
    } else {
        do {
            // Copy the data into RAM
            if (qp_stream_read(ram_buffer, 1, font->mem_stream.length, &font->mem_stream) != font->mem_stream.length) {
                qp_dprintf("qp_load_font: could not copy from flash to RAM, falling back to original\n");
                break;
            }

            // Create the new stream with the new buffer
            font->buffer      = ram_buffer;
            font->owns_buffer = true;
            font->mem_stream  = qp_make_memory_stream(font->buffer, font->mem_stream.length);
        } while (0);
    }

    // Free the buffer if we were unable to recreate the RAM copy.
    if (ram_buffer != NULL && !font->owns_buffer) {
        free(ram_buffer);
    }
#endif // QUANTUM_PAINTER_LOAD_FONTS_TO_RAM

    // Read the info (parsing already successful above, no need to check return value)
    qff_read_font_descriptor(&font->stream, &font->base.line_height, &font->has_ascii_table, &font->num_unicode_glyphs, &font->bpp, &font->has_palette, &font->compression_scheme, NULL);

    if (!qp_internal_bpp_capable(font->bpp)) {
        qp_dprintf("qp_load_font: fail (image bpp too high (%d), check QUANTUM_PAINTER_SUPPORTS_256_PALETTE or QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS)\n", (int)font->bpp);
        qp_close_font((painter_font_handle_t)font);
        return NULL;
    }

    // Validation success, we can return the handle
    font->validate_ok = true;
    qp_dprintf("qp_load_font: ok\n");
    return (painter_font_handle_t)font;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_load_font_mem

static inline bool font_mem_stream_factory(qff_font_handle_t *font, void *arg) {
    void *buffer = arg;

    // Assume we can read the graphics descriptor
    font->mem_stream = qp_make_memory_stream(buffer, sizeof(qff_font_descriptor_v1_t));

    // Update the length of the stream to match, and rewind to the start
    font->mem_stream.length   = qff_get_total_size(&font->stream);
    font->mem_stream.position = 0;

    return true;
}

painter_font_handle_t qp_load_font_mem(const void *buffer) {
    return qp_load_font_internal(font_mem_stream_factory, (void *)buffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_close_font

bool qp_close_font(painter_font_handle_t font) {
    qff_font_handle_t *qff_font = (qff_font_handle_t *)font;
    if (!qff_font->validate_ok) {
        qp_dprintf("qp_close_font: fail (invalid font)\n");
        return false;
    }

#if QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
    // Nuke the buffer, if required
    if (qff_font->owns_buffer) {
        free(qff_font->buffer);
        qff_font->buffer      = NULL;
        qff_font->owns_buffer = false;
    }
#endif // QUANTUM_PAINTER_LOAD_FONTS_TO_RAM

    // Free up this font for use elsewhere.
    qp_stream_close(&qff_font->stream);
    qff_font->validate_ok = false;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

// Callback to be invoked for each codepoint detected in the UTF8 input string
typedef bool (*code_point_handler)(qff_font_handle_t *qff_font, uint32_t code_point, uint8_t width, uint8_t height, void *cb_arg);

// Helper that sets up the palette (if required) and returns the offset in the stream that the data starts
static inline bool qp_drawtext_prepare_font_for_render(painter_device_t device, qff_font_handle_t *qff_font, qp_pixel_t fg_hsv888, qp_pixel_t bg_hsv888, uint32_t *data_offset) {
    painter_driver_t *driver = (painter_driver_t *)device;

    // Drop out if we can't actually place the data we read out anywhere
    if (!data_offset) {
        qp_dprintf("Failed to prepare stream for read, output info buffer unavailable\n");
        return false;
    }

    // Work out where we're reading from
    uint32_t offset = sizeof(qff_font_descriptor_v1_t);
    if (qff_font->has_ascii_table) {
        offset += sizeof(qff_ascii_glyph_table_v1_t);
    }
    if (qff_font->num_unicode_glyphs > 0) {
        offset += sizeof(qff_unicode_glyph_table_v1_t) + (qff_font->num_unicode_glyphs * 6);
    }

    // Handle palette if needed
    const uint16_t palette_entries  = 1u << qff_font->bpp;
    bool           needs_pixconvert = false;
    if (qff_font->has_palette) {
        // If this font has a palette, we need to read it out and set up the pixel lookup table
        qp_stream_setpos(&qff_font->stream, offset);
        if (!qp_internal_load_qgf_palette(&qff_font->stream, qff_font->bpp)) {
            return false;
        }

        // Skip this block, as far as offset calculations go
        offset += sizeof(qgf_palette_v1_t) + (palette_entries * 3);
        needs_pixconvert = true;
    } else {
        // Interpolate from fg/bg
        int16_t palette_entries = 1 << qff_font->bpp;
        needs_pixconvert        = qp_internal_interpolate_palette(fg_hsv888, bg_hsv888, palette_entries);
    }

    if (needs_pixconvert) {
        // Convert the palette to native format
        if (!driver->driver_vtable->palette_convert(device, palette_entries, qp_internal_global_pixel_lookup_table)) {
            qp_dprintf("qp_drawtext_recolor: fail (could not convert pixels to native)\n");
            qp_comms_stop(device);
            return false;
        }
    }

    *data_offset = offset;
    return true;
}

static inline bool qp_drawtext_prepare_glyph_for_render(qff_font_handle_t *qff_font, uint32_t code_point, uint8_t *width) {
    if (code_point >= 0x20 && code_point < 0x7F && qff_font->has_ascii_table) {
        // Do ascii table
        qff_ascii_glyph_v1_t glyph_info;
        uint32_t             glyph_info_offset = sizeof(qff_font_descriptor_v1_t)          // Skip the font descriptor
                                     + sizeof(qgf_block_header_v1_t)                       // Skip the ascii table header
                                     + (code_point - 0x20) * sizeof(qff_ascii_glyph_v1_t); // Jump direct to the data offset based on the glyph index
        if (qp_stream_setpos(&qff_font->stream, glyph_info_offset) < 0) {
            qp_dprintf("Failed to set stream position while reading ascii glyph info\n");
            return false;
        }

        if (qp_stream_read(&glyph_info, sizeof(qff_ascii_glyph_v1_t), 1, &qff_font->stream) != 1) {
            qp_dprintf("Failed to read glyph info\n");
            return false;
        }

        uint8_t  glyph_width  = (uint8_t)(glyph_info.value & QFF_GLYPH_WIDTH_MASK);
        uint32_t glyph_offset = ((glyph_info.value & QFF_GLYPH_OFFSET_MASK) >> QFF_GLYPH_WIDTH_BITS);
        uint32_t data_offset  = sizeof(qff_font_descriptor_v1_t)                                                                                                                   // Skip the font descriptor
                               + (qff_font->has_ascii_table ? sizeof(qff_ascii_glyph_table_v1_t) : 0)                                                                              // Skip the ascii table
                               + (qff_font->num_unicode_glyphs > 0 ? (sizeof(qff_unicode_glyph_table_v1_t) + (qff_font->num_unicode_glyphs * sizeof(qff_unicode_glyph_v1_t))) : 0) // Skip the unicode table
                               + (qff_font->has_palette ? (sizeof(qgf_palette_v1_t) + ((1 << qff_font->bpp) * sizeof(qgf_palette_entry_v1_t))) : 0)                                // Skip the palette
                               + sizeof(qgf_block_header_v1_t)                                                                                                                     // Skip the data block header
                               + glyph_offset;                                                                                                                                     // Jump to the specified glyph offset

        if (qp_stream_setpos(&qff_font->stream, data_offset) < 0) {
            qp_dprintf("Failed to set stream position while preparing ascii glyph data\n");
            return false;
        }

        *width = glyph_width;
        return true;
    } else {
        // Do unicode table, which may include singular ascii glyphs if full ascii table isn't specified
        uint32_t glyph_info_offset = sizeof(qff_font_descriptor_v1_t)                                       // Skip the font descriptor
                                     + (qff_font->has_ascii_table ? sizeof(qff_ascii_glyph_table_v1_t) : 0) // Skip the ascii table
                                     + sizeof(qgf_block_header_v1_t);                                       // Skip the unicode block header

        if (qp_stream_setpos(&qff_font->stream, glyph_info_offset) < 0) {
            qp_dprintf("Failed to set stream position while preparing glyph data\n");
            return false;
        }

        qff_unicode_glyph_v1_t glyph_info;
        for (uint16_t i = 0; i < qff_font->num_unicode_glyphs; ++i) {
            if (qp_stream_read(&glyph_info, sizeof(qff_unicode_glyph_v1_t), 1, &qff_font->stream) != 1) {
                qp_dprintf("Failed to set stream position while reading unicode glyph info\n");
                return false;
            }

            if (glyph_info.code_point == code_point) {
                uint8_t  glyph_width  = (uint8_t)(glyph_info.value & QFF_GLYPH_WIDTH_MASK);
                uint32_t glyph_offset = ((glyph_info.value & QFF_GLYPH_OFFSET_MASK) >> QFF_GLYPH_WIDTH_BITS);
                uint32_t data_offset  = sizeof(qff_font_descriptor_v1_t)                                                                                                                   // Skip the font descriptor
                                       + (qff_font->has_ascii_table ? sizeof(qff_ascii_glyph_table_v1_t) : 0)                                                                              // Skip the ascii table
                                       + (qff_font->num_unicode_glyphs > 0 ? (sizeof(qff_unicode_glyph_table_v1_t) + (qff_font->num_unicode_glyphs * sizeof(qff_unicode_glyph_v1_t))) : 0) // Skip the unicode table
                                       + (qff_font->has_palette ? (sizeof(qgf_palette_v1_t) + ((1 << qff_font->bpp) * sizeof(qgf_palette_entry_v1_t))) : 0)                                // Skip the palette
                                       + sizeof(qgf_block_header_v1_t)                                                                                                                     // Skip the data block header
                                       + glyph_offset;                                                                                                                                     // Jump to the specified glyph offset

                if (qp_stream_setpos(&qff_font->stream, data_offset) < 0) {
                    qp_dprintf("Failed to set stream position while preparing unicode glyph data\n");
                    return false;
                }

                *width = glyph_width;
                return true;
            }
        }

        // Not found
        qp_dprintf("Failed to find unicode glyph info\n");
        return false;
    }
    return false;
}

// Function to iterate over each UTF8 codepoint, invoking the callback for each decoded glyph
static inline bool qp_iterate_code_points(qff_font_handle_t *qff_font, const char *str, code_point_handler handler, void *cb_arg) {
    while (*str) {
        int32_t code_point = 0;
        str                = decode_utf8(str, &code_point);
        if (code_point < 0) {
            qp_dprintf("Invalid unicode code point decoded. Cannot render.\n");
            return false;
        }

        uint8_t width;
        if (!qp_drawtext_prepare_glyph_for_render(qff_font, code_point, &width)) {
            qp_dprintf("Failed to prepare glyph for rendering.\n");
            return false;
        }

        if (!handler(qff_font, code_point, width, qff_font->base.line_height, cb_arg)) {
            qp_dprintf("Failed to execute glyph handler.\n");
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String width calculation

// Callback state
typedef struct code_point_iter_calcwidth_state_t {
    int16_t width;
} code_point_iter_calcwidth_state_t;

// Codepoint handler callback: width calc
static inline bool qp_font_code_point_handler_calcwidth(qff_font_handle_t *qff_font, uint32_t code_point, uint8_t width, uint8_t height, void *cb_arg) {
    code_point_iter_calcwidth_state_t *state = (code_point_iter_calcwidth_state_t *)cb_arg;

    // Increment the overall width by this glyph's width
    state->width += width;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String drawing implementation

// Callback state
typedef struct code_point_iter_drawglyph_state_t {
    painter_device_t                  device;
    int16_t                           xpos;
    int16_t                           ypos;
    qp_internal_byte_input_callback   input_callback;
    qp_internal_byte_input_state_t *  input_state;
    qp_internal_pixel_output_state_t *output_state;
} code_point_iter_drawglyph_state_t;

// Codepoint handler callback: drawing
static inline bool qp_font_code_point_handler_drawglyph(qff_font_handle_t *qff_font, uint32_t code_point, uint8_t width, uint8_t height, void *cb_arg) {
    code_point_iter_drawglyph_state_t *state  = (code_point_iter_drawglyph_state_t *)cb_arg;
    painter_driver_t *                 driver = (painter_driver_t *)state->device;

    // Reset the input state's RLE mode -- the stream should already be correctly positioned by qp_iterate_code_points()
    state->input_state->rle.mode = MARKER_BYTE; // ignored if not using RLE

    // Reset the output state
    state->output_state->pixel_write_pos = 0;

    // Configure where we're going to be rendering to
    driver->driver_vtable->viewport(state->device, state->xpos, state->ypos, state->xpos + width - 1, state->ypos + height - 1);

    // Move the x-position for the next glyph
    state->xpos += width;

    // Decode the pixel data for the glyph
    uint32_t pixel_count = ((uint32_t)width) * height;
    bool     ret         = qp_internal_decode_palette(state->device, pixel_count, qff_font->bpp, state->input_callback, state->input_state, qp_internal_global_pixel_lookup_table, qp_internal_pixel_appender, state->output_state);

    // Any leftovers need transmission as well.
    if (ret && state->output_state->pixel_write_pos > 0) {
        ret &= driver->driver_vtable->pixdata(state->device, qp_internal_global_pixdata_buffer, state->output_state->pixel_write_pos);
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_textwidth

int16_t qp_textwidth(painter_font_handle_t font, const char *str) {
    qff_font_handle_t *qff_font = (qff_font_handle_t *)font;
    if (!qff_font->validate_ok) {
        qp_dprintf("qp_textwidth: fail (invalid font)\n");
        return false;
    }

    // Create the codepoint iterator state
    code_point_iter_calcwidth_state_t state = {.width = 0};
    // Iterate each codepoint, return the calculated width if successful.
    return qp_iterate_code_points(qff_font, str, qp_font_code_point_handler_calcwidth, &state) ? state.width : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_drawtext

int16_t qp_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str) {
    // Offload to the recolor variant, substituting fg=white bg=black.
    // Traditional LCDs with those colors will need to manually invoke qp_drawtext_recolor with the colors reversed.
    return qp_drawtext_recolor(device, x, y, font, str, 0, 0, 255, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_drawtext_recolor

int16_t qp_drawtext_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg) {
    qp_dprintf("qp_drawtext_recolor: entry\n");
    painter_driver_t *driver = (painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_drawtext_recolor: fail (validation_ok == false)\n");
        return 0;
    }

    qff_font_handle_t *qff_font = (qff_font_handle_t *)font;
    if (!qff_font->validate_ok) {
        qp_dprintf("qp_drawtext_recolor: fail (invalid font)\n");
        return false;
    }

    if (!qp_comms_start(device)) {
        qp_dprintf("qp_drawtext_recolor: fail (could not start comms)\n");
        return 0;
    }

    // Set up the byte input state and input callback
    qp_internal_byte_input_state_t  input_state    = {.device = device, .src_stream = &qff_font->stream};
    qp_internal_byte_input_callback input_callback = qp_internal_prepare_input_state(&input_state, qff_font->compression_scheme);
    if (input_callback == NULL) {
        qp_dprintf("qp_drawtext_recolor: fail (invalid font compression scheme)\n");
        qp_comms_stop(device);
        return false;
    }

    // Set up the pixel output state
    qp_internal_pixel_output_state_t output_state = {.device = device, .pixel_write_pos = 0, .max_pixels = qp_internal_num_pixels_in_buffer(device)};

    // Set up the codepoint iteration state
    code_point_iter_drawglyph_state_t state = {// Common
                                               .device = device,
                                               .xpos   = x,
                                               .ypos   = y,
                                               // Input
                                               .input_callback = input_callback,
                                               .input_state    = &input_state,
                                               // Output
                                               .output_state = &output_state};

    qp_pixel_t fg_hsv888 = {.hsv888 = {.h = hue_fg, .s = sat_fg, .v = val_fg}};
    qp_pixel_t bg_hsv888 = {.hsv888 = {.h = hue_bg, .s = sat_bg, .v = val_bg}};
    uint32_t   data_offset;
    if (!qp_drawtext_prepare_font_for_render(driver, qff_font, fg_hsv888, bg_hsv888, &data_offset)) {
        qp_dprintf("qp_drawtext_recolor: fail (failed to prepare font for rendering)\n");
        qp_comms_stop(device);
        return false;
    }

    // Iterate the codepoints with the drawglyph callback
    bool ret = qp_iterate_code_points(qff_font, str, qp_font_code_point_handler_drawglyph, &state);

    qp_dprintf("qp_drawtext_recolor: %s\n", ret ? "ok" : "fail");
    qp_comms_stop(device);
    return ret ? (state.xpos - x) : 0;
}
