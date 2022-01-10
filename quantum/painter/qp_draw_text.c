// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <quantum.h>
#include <utf8.h>

#include <qp_internal.h>
#include <qp_draw.h>
#include <qff.h>

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
#endif  // QP_STREAM_HAS_FILE_IO
    };
#if QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
    bool  owns_buffer;
    void *buffer;
#endif  // QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
} qff_font_handle_t;

static qff_font_handle_t font_descriptors[QUANTUM_PAINTER_NUM_FONTS] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_load_font_mem

painter_font_handle_t qp_load_font_mem(const void QP_RESIDENT_FLASH_OR_RAM *buffer) {
    qp_dprintf("qp_load_font_mem: entry\n");
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
        qp_dprintf("qp_load_font_mem: fail (no free slot)\n");
        return NULL;
    }

    // Assume we can read the graphics descriptor
    font->mem_stream = qp_make_memory_stream((void QP_RESIDENT_FLASH_OR_RAM *)buffer, sizeof(qff_font_descriptor_v1_t));

    // Update the length of the stream to match, and rewind to the start
    font->mem_stream.length   = qff_get_total_size(&font->stream);
    font->mem_stream.position = 0;

    // Now that we know the length, validate the input data
    if (!qff_validate_stream(&font->stream)) {
        qp_dprintf("qp_load_font_mem: fail (failed validation)\n");
        return NULL;
    }

#if QUANTUM_PAINTER_LOAD_FONTS_TO_RAM
    // Clear out any existing data
    font->owns_buffer = false;
    font->buffer      = NULL;

    void *ram_buffer = malloc(font->mem_stream.length);
    if (ram_buffer == NULL) {
        qp_dprintf("qp_load_font_mem: could not allocate enough RAM for font, falling back to original\n");
    } else {
        do {
            // Copy the data into RAM
            if (qp_stream_read(ram_buffer, 1, font->mem_stream.length, &font->mem_stream) != font->mem_stream.length) {
                qp_dprintf("qp_load_font_mem: could not copy from flash to RAM, falling back to original\n");
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
#endif  // QUANTUM_PAINTER_LOAD_FONTS_TO_RAM

    // Read the info (parsing already successful above, no need to check return value)
    qff_read_font_descriptor(&font->stream, &font->base.line_height, &font->has_ascii_table, &font->num_unicode_glyphs, &font->bpp, &font->has_palette, &font->compression_scheme, NULL);

    // Validation success, we can return the handle
    font->validate_ok = true;
    qp_dprintf("qp_load_font_mem: ok\n");
    return (painter_font_handle_t)font;
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
#endif  // QUANTUM_PAINTER_LOAD_FONTS_TO_RAM

    // Free up this font for use elsewhere.
    qff_font->validate_ok = false;
    return true;
}
