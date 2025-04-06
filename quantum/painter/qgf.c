// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

// Quantum Graphics File "QGF" File Format.
// See https://docs.qmk.fm/#/quantum_painter_qgf for more information.

#include "qgf.h"
#include "qp_draw.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QGF API

bool qgf_validate_block_header(qgf_block_header_v1_t *desc, uint8_t expected_typeid, int32_t expected_length) {
    if (desc->type_id != expected_typeid || desc->neg_type_id != ((~expected_typeid) & 0xFF)) {
        qp_dprintf("Failed to validate header, expected typeid 0x%02X, was 0x%02X, expected negated typeid 0x%02X, was 0x%02X\n", (int)expected_typeid, (int)desc->type_id, (int)((~desc->type_id) & 0xFF), (int)desc->neg_type_id);
        return false;
    }

    if (expected_length >= 0 && desc->length != expected_length) {
        qp_dprintf("Failed to validate header (typeid 0x%02X), expected length %d, was %d\n", (int)desc->type_id, (int)expected_length, (int)desc->length);
        return false;
    }

    return true;
}

bool qgf_parse_format(qp_image_format_t format, uint8_t *bpp, bool *has_palette, bool *is_panel_native) {
    // clang-format off
    static const struct QP_PACKED {
        uint8_t bpp;
        bool    has_palette;
        bool is_panel_native;
    } formats[] = {
        [GRAYSCALE_1BPP] = {.bpp = 1, .has_palette = false, .is_panel_native = false},
        [GRAYSCALE_2BPP] = {.bpp = 2, .has_palette = false, .is_panel_native = false},
        [GRAYSCALE_4BPP] = {.bpp = 4, .has_palette = false, .is_panel_native = false},
        [GRAYSCALE_8BPP] = {.bpp = 8, .has_palette = false, .is_panel_native = false},
        [PALETTE_1BPP] = {.bpp = 1, .has_palette = true, .is_panel_native = false},
        [PALETTE_2BPP] = {.bpp = 2, .has_palette = true, .is_panel_native = false},
        [PALETTE_4BPP] = {.bpp = 4, .has_palette = true, .is_panel_native = false},
        [PALETTE_8BPP] = {.bpp = 8, .has_palette = true, .is_panel_native = false},
        [RGB565_16BPP] = {.bpp = 16, .has_palette = false, .is_panel_native = true},
        [RGB888_24BPP] = {.bpp = 24, .has_palette = false, .is_panel_native = true},
    };
    // clang-format on

    // Copy out the required info
    if (format > RGB888_24BPP) {
        qp_dprintf("Failed to parse frame_descriptor, invalid format 0x%02X\n", (int)format);
        return false;
    }

    // Copy out the required info
    if (bpp) {
        *bpp = formats[format].bpp;
    }
    if (has_palette) {
        *has_palette = formats[format].has_palette;
    }
    if (is_panel_native) {
        *is_panel_native = formats[format].is_panel_native;
    }

    return true;
}

bool qgf_parse_frame_descriptor(qgf_frame_v1_t *frame_descriptor, uint8_t *bpp, bool *has_palette, bool *is_panel_native, bool *is_delta, painter_compression_t *compression_scheme, uint16_t *delay) {
    // Decode the format
    qgf_parse_format(frame_descriptor->format, bpp, has_palette, is_panel_native);

    // Copy out the required info
    if (is_delta) {
        *is_delta = (frame_descriptor->flags & QGF_FRAME_FLAG_DELTA) == QGF_FRAME_FLAG_DELTA;
    }
    if (compression_scheme) {
        *compression_scheme = frame_descriptor->compression_scheme;
    }
    if (delay) {
        *delay = frame_descriptor->delay;
    }

    return true;
}

bool qgf_read_graphics_descriptor(qp_stream_t *stream, uint16_t *image_width, uint16_t *image_height, uint16_t *frame_count, uint32_t *total_bytes) {
    // Seek to the start
    qp_stream_setpos(stream, 0);

    // Read and validate the graphics descriptor
    qgf_graphics_descriptor_v1_t graphics_descriptor;
    if (qp_stream_read(&graphics_descriptor, sizeof(qgf_graphics_descriptor_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read graphics_descriptor, expected length was not %d\n", (int)sizeof(qgf_graphics_descriptor_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&graphics_descriptor.header, QGF_GRAPHICS_DESCRIPTOR_TYPEID, (sizeof(qgf_graphics_descriptor_v1_t) - sizeof(qgf_block_header_v1_t)))) {
        return false;
    }

    // Make sure the magic and version are correct
    if (graphics_descriptor.magic != QGF_MAGIC || graphics_descriptor.qgf_version != 0x01) {
        qp_dprintf("Failed to validate graphics_descriptor, expected magic 0x%06X was 0x%06X, expected version = 0x%02X was 0x%02X\n", (int)QGF_MAGIC, (int)graphics_descriptor.magic, (int)0x01, (int)graphics_descriptor.qgf_version);
        return false;
    }

    // Make sure the file length is valid
    if (graphics_descriptor.neg_total_file_size != ~graphics_descriptor.total_file_size) {
        qp_dprintf("Failed to validate graphics_descriptor, expected negated length 0x%08X was 0x%08X\n", (int)(~graphics_descriptor.total_file_size), (int)graphics_descriptor.neg_total_file_size);
        return false;
    }

    // Copy out the required info
    if (image_width) {
        *image_width = graphics_descriptor.image_width;
    }
    if (image_height) {
        *image_height = graphics_descriptor.image_height;
    }
    if (frame_count) {
        *frame_count = graphics_descriptor.frame_count;
    }
    if (total_bytes) {
        *total_bytes = graphics_descriptor.total_file_size;
    }

    return true;
}

static bool qgf_read_frame_offset(qp_stream_t *stream, uint16_t frame_number, uint32_t *frame_offset) {
    uint16_t frame_count;
    if (!qgf_read_graphics_descriptor(stream, NULL, NULL, &frame_count, NULL)) {
        return false;
    }

    // Read the frame offsets descriptor
    qgf_frame_offsets_v1_t frame_offsets;
    if (qp_stream_read(&frame_offsets, sizeof(qgf_frame_offsets_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read frame_offsets, expected length was not %d\n", (int)sizeof(qgf_frame_offsets_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&frame_offsets.header, QGF_FRAME_OFFSET_DESCRIPTOR_TYPEID, (frame_count * sizeof(uint32_t)))) {
        return false;
    }

    if (frame_number >= frame_count) {
        qp_dprintf("Invalid frame number, was %d but only %d frames in image\n", (int)frame_number, (int)frame_count);
        return false;
    }

    // Skip the necessary amount of data to get to the requested frame offset
    qp_stream_seek(stream, frame_number * sizeof(uint32_t), SEEK_CUR);

    // Read the frame offset
    uint32_t offset = 0;
    if (qp_stream_read(&offset, sizeof(uint32_t), 1, stream) != 1) {
        qp_dprintf("Failed to read frame offset, expected length was not %d\n", (int)sizeof(uint32_t));
        return false;
    }

    // Copy out the required info
    if (frame_offset) {
        *frame_offset = offset;
    }

    return true;
}

void qgf_seek_to_frame_descriptor(qp_stream_t *stream, uint16_t frame_number) {
    // Read the offset
    uint32_t offset = 0;
    qgf_read_frame_offset(stream, frame_number, &offset);

    // Move to the offset
    qp_stream_setpos(stream, offset);
}

bool qgf_validate_frame_descriptor(qp_stream_t *stream, uint16_t frame_number, uint8_t *bpp, bool *has_palette, bool *is_panel_native, bool *is_delta) {
    // Seek to the correct location
    qgf_seek_to_frame_descriptor(stream, frame_number);

    // Read the raw descriptor
    qgf_frame_v1_t frame_descriptor;
    if (qp_stream_read(&frame_descriptor, sizeof(qgf_frame_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read frame_descriptor, expected length was not %d\n", (int)sizeof(qgf_frame_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&frame_descriptor.header, QGF_FRAME_DESCRIPTOR_TYPEID, (sizeof(qgf_frame_v1_t) - sizeof(qgf_block_header_v1_t)))) {
        return false;
    }

    return qgf_parse_frame_descriptor(&frame_descriptor, bpp, has_palette, is_panel_native, is_delta, NULL, NULL);
}

bool qgf_validate_palette_descriptor(qp_stream_t *stream, uint16_t frame_number, uint8_t bpp) {
    // Read the palette descriptor
    qgf_palette_v1_t palette_descriptor;
    if (qp_stream_read(&palette_descriptor, sizeof(qgf_palette_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read palette_descriptor, expected length was not %d\n", (int)sizeof(qgf_palette_v1_t));
        return false;
    }

    // Make sure this block is valid
    uint32_t expected_length = (1 << bpp) * 3 * sizeof(uint8_t);
    if (!qgf_validate_block_header(&palette_descriptor.header, QGF_FRAME_PALETTE_DESCRIPTOR_TYPEID, expected_length)) {
        return false;
    }

    // Move forward in the stream to the next block
    qp_stream_seek(stream, expected_length, SEEK_CUR);
    return true;
}

bool qgf_validate_delta_descriptor(qp_stream_t *stream, uint16_t frame_number) {
    // Read the delta descriptor
    qgf_delta_v1_t delta_descriptor;
    if (qp_stream_read(&delta_descriptor, sizeof(qgf_delta_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read delta_descriptor, expected length was not %d\n", (int)sizeof(qgf_delta_v1_t));
        return false;
    }

    // Make sure this block is valid
    if (!qgf_validate_block_header(&delta_descriptor.header, QGF_FRAME_DELTA_DESCRIPTOR_TYPEID, (sizeof(qgf_delta_v1_t) - sizeof(qgf_block_header_v1_t)))) {
        return false;
    }

    return true;
}

bool qgf_validate_frame_data_descriptor(qp_stream_t *stream, uint16_t frame_number) {
    // Read and validate the data block
    qgf_data_v1_t data_descriptor;
    if (qp_stream_read(&data_descriptor, sizeof(qgf_data_v1_t), 1, stream) != 1) {
        qp_dprintf("Failed to read data_descriptor, expected length was not %d\n", (int)sizeof(qgf_data_v1_t));
        return false;
    }

    if (!qgf_validate_block_header(&data_descriptor.header, QGF_FRAME_DATA_DESCRIPTOR_TYPEID, -1)) {
        return false;
    }

    return true;
}

bool qgf_validate_stream(qp_stream_t *stream) {
    uint16_t frame_count;
    if (!qgf_read_graphics_descriptor(stream, NULL, NULL, &frame_count, NULL)) {
        return false;
    }

    // Read and validate all the frames (automatically validates the frame offset descriptor in the process)
    for (uint16_t i = 0; i < frame_count; ++i) {
        // Validate the frame descriptor block
        uint8_t bpp             = 0;
        bool    has_palette     = false;
        bool    is_panel_native = false;
        bool    has_delta       = false;
        if (!qgf_validate_frame_descriptor(stream, i, &bpp, &has_palette, &is_panel_native, &has_delta)) {
            return false;
        }

        // If we've got a palette block, check it
        if (has_palette && !qgf_validate_palette_descriptor(stream, i, bpp)) {
            return false;
        }

        // If we've got a delta block, check it
        if (has_delta && !qgf_validate_delta_descriptor(stream, i)) {
            return false;
        }

        // Check the data block
        if (!qgf_validate_frame_data_descriptor(stream, i)) {
            return false;
        }
    }

    return true;
}

// Work out the total size of an image definition, assuming we can read far enough into the file
uint32_t qgf_get_total_size(qp_stream_t *stream) {
    // Get the original location
    uint32_t oldpos = qp_stream_tell(stream);

    // Read the graphics descriptor, grabbing the size
    uint32_t total_size;
    if (!qgf_read_graphics_descriptor(stream, NULL, NULL, NULL, &total_size)) {
        return false;
    }

    // Restore the original location
    qp_stream_setpos(stream, oldpos);
    return total_size;
}
