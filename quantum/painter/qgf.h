// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Quantum Graphics File "QGF" File Format.
// See https://docs.qmk.fm/#/quantum_painter_qgf for more information.

#include <stdint.h>
#include <stdbool.h>

#include "compiler_support.h"
#include "qp_stream.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QGF structures

/////////////////////////////////////////
// Common block header

typedef struct QP_PACKED qgf_block_header_v1_t {
    uint8_t  type_id;     // See each respective block type below.
    uint8_t  neg_type_id; // Negated type ID, used for detecting parsing errors.
    uint32_t length : 24; // 24-bit blob length, allowing for block sizes of a maximum of 16MB.
} qgf_block_header_v1_t;

STATIC_ASSERT(sizeof(qgf_block_header_v1_t) == 5, "qgf_block_header_v1_t must be 5 bytes in v1 of QGF");

/////////////////////////////////////////
// Graphics descriptor

#define QGF_GRAPHICS_DESCRIPTOR_TYPEID 0x00

typedef struct QP_PACKED qgf_graphics_descriptor_v1_t {
    qgf_block_header_v1_t header;              // = { .type_id = 0x00, .neg_type_id = (~0x00), .length = 18 }
    uint32_t              magic : 24;          // constant, equal to 0x464751 ("QGF")
    uint8_t               qgf_version;         // constant, equal to 0x01
    uint32_t              total_file_size;     // total size of the entire file, starting at offset zero
    uint32_t              neg_total_file_size; // negated value of total_file_size
    uint16_t              image_width;         // in pixels
    uint16_t              image_height;        // in pixels
    uint16_t              frame_count;         // minimum of 1
} qgf_graphics_descriptor_v1_t;

STATIC_ASSERT(sizeof(qgf_graphics_descriptor_v1_t) == (sizeof(qgf_block_header_v1_t) + 18), "qgf_graphics_descriptor_v1_t must be 23 bytes in v1 of QGF");

#define QGF_MAGIC 0x464751

/////////////////////////////////////////
// Frame offset descriptor

#define QGF_FRAME_OFFSET_DESCRIPTOR_TYPEID 0x01

typedef struct QP_PACKED qgf_frame_offsets_v1_t {
    qgf_block_header_v1_t header;    // = { .type_id = 0x01, .neg_type_id = (~0x01), .length = (N * sizeof(uint32_t)) }
    uint32_t              offset[0]; // '0' signifies that this struct is immediately followed by the frame offsets
} qgf_frame_offsets_v1_t;

STATIC_ASSERT(sizeof(qgf_frame_offsets_v1_t) == sizeof(qgf_block_header_v1_t), "qgf_frame_offsets_v1_t must only contain qgf_block_header_v1_t in v1 of QGF");

/////////////////////////////////////////
// Frame descriptor

#define QGF_FRAME_DESCRIPTOR_TYPEID 0x02

typedef struct QP_PACKED qgf_frame_v1_t {
    qgf_block_header_v1_t header;                 // = { .type_id = 0x02, .neg_type_id = (~0x02), .length = 6 }
    qp_image_format_t     format : 8;             // Frame format, see qp_internal_formats.h.
    uint8_t               flags;                  // Frame flags, see below.
    painter_compression_t compression_scheme : 8; // Compression scheme, see qp.h.
    uint8_t               transparency_index;     // palette index used for transparent pixels (not yet implemented)
    uint16_t              delay;                  // frame delay time for animations (in units of milliseconds)
} qgf_frame_v1_t;

STATIC_ASSERT(sizeof(qgf_frame_v1_t) == (sizeof(qgf_block_header_v1_t) + 6), "qgf_frame_v1_t must be 11 bytes in v1 of QGF");

#define QGF_FRAME_FLAG_DELTA 0x02
#define QGF_FRAME_FLAG_TRANSPARENT 0x01

/////////////////////////////////////////
// Frame palette descriptor

#define QGF_FRAME_PALETTE_DESCRIPTOR_TYPEID 0x03

typedef struct QP_PACKED qgf_palette_entry_v1_t {
    uint8_t h; // hue component: `[0,360)` degrees is mapped to `[0,255]` uint8_t.
    uint8_t s; // saturation component: `[0,1]` is mapped to `[0,255]` uint8_t.
    uint8_t v; // value component: `[0,1]` is mapped to `[0,255]` uint8_t.
} qgf_palette_entry_v1_t;

STATIC_ASSERT(sizeof(qgf_palette_entry_v1_t) == 3, "Palette entry is not 3 bytes in size");

typedef struct QP_PACKED qgf_palette_v1_t {
    qgf_block_header_v1_t  header; // = { .type_id = 0x03, .neg_type_id = (~0x03), .length = (N * 3 * sizeof(uint8_t)) }
    qgf_palette_entry_v1_t hsv[0]; // N * hsv, where N is the number of palette entries depending on the frame format in the descriptor
} qgf_palette_v1_t;

STATIC_ASSERT(sizeof(qgf_palette_v1_t) == sizeof(qgf_block_header_v1_t), "qgf_palette_v1_t must only contain qgf_block_header_v1_t in v1 of QGF");

/////////////////////////////////////////
// Frame delta descriptor

#define QGF_FRAME_DELTA_DESCRIPTOR_TYPEID 0x04

typedef struct QP_PACKED qgf_delta_v1_t {
    qgf_block_header_v1_t header; // = { .type_id = 0x04, .neg_type_id = (~0x04), .length = 8 }
    uint16_t              left;   // The left pixel location to draw the delta image
    uint16_t              top;    // The top pixel location to draw the delta image
    uint16_t              right;  // The right pixel location to to draw the delta image
    uint16_t              bottom; // The bottom pixel location to to draw the delta image
} qgf_delta_v1_t;

STATIC_ASSERT(sizeof(qgf_delta_v1_t) == (sizeof(qgf_block_header_v1_t) + 8), "qgf_delta_v1_t must be 13 bytes in v1 of QGF");

/////////////////////////////////////////
// Frame data descriptor

#define QGF_FRAME_DATA_DESCRIPTOR_TYPEID 0x05

typedef struct QP_PACKED qgf_data_v1_t {
    qgf_block_header_v1_t header;  // = { .type_id = 0x05, .neg_type_id = (~0x05), .length = N }
    uint8_t               data[0]; // 0 signifies that this struct is immediately followed by the length of data specified in the header
} qgf_data_v1_t;

STATIC_ASSERT(sizeof(qgf_data_v1_t) == sizeof(qgf_block_header_v1_t), "qgf_data_v1_t must only contain qgf_block_header_v1_t in v1 of QGF");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QGF API

uint32_t qgf_get_total_size(qp_stream_t *stream);
bool     qgf_validate_stream(qp_stream_t *stream);
bool     qgf_validate_block_header(qgf_block_header_v1_t *desc, uint8_t expected_typeid, int32_t expected_length);
bool     qgf_read_graphics_descriptor(qp_stream_t *stream, uint16_t *image_width, uint16_t *image_height, uint16_t *frame_count, uint32_t *total_bytes);
bool     qgf_parse_format(qp_image_format_t format, uint8_t *bpp, bool *has_palette, bool *is_panel_native);
void     qgf_seek_to_frame_descriptor(qp_stream_t *stream, uint16_t frame_number);
bool     qgf_parse_frame_descriptor(qgf_frame_v1_t *frame_descriptor, uint8_t *bpp, bool *has_palette, bool *is_panel_native, bool *is_delta, painter_compression_t *compression_scheme, uint16_t *delay);
