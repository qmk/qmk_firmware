// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

// Quantum Font File "QFF" File Format.
// See https://docs.qmk.fm/#/quantum_painter_qff for more information.

#include "qff.h"
#include "qp_draw.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QFF API

bool qff_read_font_descriptor(qp_stream_t *stream, uint8_t *line_height, bool *has_ascii_table, uint16_t *num_unicode_glyphs, uint8_t *bpp, bool *has_palette, bool *is_panel_native, painter_compression_t *compression_scheme, uint32_t *total_bytes) {
    // Seek to the start
    qp_stream_setpos(stream, 0);

    // Read and validate the font descriptor
    qff_font_descriptor_v1_t font_descriptor;
    if (qp_stream_read(&font_descriptor, sizeof(qff_font_descriptor_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read font_descriptor, expected length was not %d\n", (int)sizeof(qff_font_descriptor_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&font_descriptor.header, QFF_FONT_DESCRIPTOR_TYPEID, (sizeof(qff_font_descriptor_v1_t) - sizeof(qgf_block_header_v1_t)))) {
        return false;
    }

    // Make sure the magic and version are correct
    if (font_descriptor.magic != QFF_MAGIC || font_descriptor.qff_version != 0x01) {
        qp_dprintf("Failed to validate font_descriptor, expected magic 0x%06X was 0x%06X, expected version = 0x%02X was 0x%02X\n", (int)QFF_MAGIC, (int)font_descriptor.magic, (int)0x01, (int)font_descriptor.qff_version);
        return false;
    }

    // Make sure the file length is valid
    if (font_descriptor.neg_total_file_size != ~font_descriptor.total_file_size) {
        qp_dprintf("Failed to validate font_descriptor, expected negated length 0x%08X was 0x%08X\n", (int)(~font_descriptor.total_file_size), (int)font_descriptor.neg_total_file_size);
        return false;
    }

    // Copy out the required info
    if (line_height) {
        *line_height = font_descriptor.line_height;
    }
    if (has_ascii_table) {
        *has_ascii_table = font_descriptor.has_ascii_table;
    }
    if (num_unicode_glyphs) {
        *num_unicode_glyphs = font_descriptor.num_unicode_glyphs;
    }
    if (bpp || has_palette) {
        if (!qgf_parse_format(font_descriptor.format, bpp, has_palette, is_panel_native)) {
            return false;
        }
    }
    if (compression_scheme) {
        *compression_scheme = font_descriptor.compression_scheme;
    }
    if (total_bytes) {
        *total_bytes = font_descriptor.total_file_size;
    }

    return true;
}

static bool qff_validate_ascii_descriptor(qp_stream_t *stream) {
    // Read the raw descriptor
    qff_ascii_glyph_table_v1_t ascii_descriptor;
    if (qp_stream_read(&ascii_descriptor, sizeof(qff_ascii_glyph_table_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read ascii_descriptor, expected length was not %d\n", (int)sizeof(qff_ascii_glyph_table_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&ascii_descriptor.header, QFF_ASCII_GLYPH_DESCRIPTOR_TYPEID, (sizeof(qff_ascii_glyph_table_v1_t) - sizeof(qgf_block_header_v1_t)))) {
        return false;
    }

    return true;
}

static bool qff_validate_unicode_descriptor(qp_stream_t *stream, uint16_t num_unicode_glyphs) {
    // Read the raw descriptor
    qff_unicode_glyph_table_v1_t unicode_descriptor;
    if (qp_stream_read(&unicode_descriptor, sizeof(qff_unicode_glyph_table_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read unicode_descriptor, expected length was not %d\n", (int)sizeof(qff_unicode_glyph_table_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&unicode_descriptor.header, QFF_UNICODE_GLYPH_DESCRIPTOR_TYPEID, num_unicode_glyphs * 6)) {
        return false;
    }

    // Skip the necessary amount of data to get to the next block
    qp_stream_seek(stream, num_unicode_glyphs * sizeof(qff_unicode_glyph_v1_t), SEEK_CUR);

    return true;
}

bool qff_validate_stream(qp_stream_t *stream) {
    bool     has_ascii_table;
    uint16_t num_unicode_glyphs;

    if (!qff_read_font_descriptor(stream, NULL, &has_ascii_table, &num_unicode_glyphs, NULL, NULL, NULL, NULL, NULL)) {
        return false;
    }

    if (has_ascii_table) {
        if (!qff_validate_ascii_descriptor(stream)) {
            return false;
        }
    }

    if (num_unicode_glyphs > 0) {
        if (!qff_validate_unicode_descriptor(stream, num_unicode_glyphs)) {
            return false;
        }
    }

    return true;
}

uint32_t qff_get_total_size(qp_stream_t *stream) {
    // Get the original location
    uint32_t oldpos = qp_stream_tell(stream);

    // Read the font descriptor, grabbing the size
    uint32_t total_size;
    if (!qff_read_font_descriptor(stream, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &total_size)) {
        return false;
    }

    // Restore the original location
    qp_stream_setpos(stream, oldpos);
    return total_size;
}
