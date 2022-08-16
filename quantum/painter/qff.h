// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Quantum Font File "QFF" File Format.
// See https://docs.qmk.fm/#/quantum_painter_qff for more information.

#include <stdint.h>
#include <stdbool.h>

#include "qp_stream.h"
#include "qp_internal.h"
#include "qgf.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QFF structures

/////////////////////////////////////////
// Font descriptor

#define QFF_FONT_DESCRIPTOR_TYPEID 0x00

typedef struct __attribute__((packed)) qff_font_descriptor_v1_t {
    qgf_block_header_v1_t header;              // = { .type_id = 0x00, .neg_type_id = (~0x00), .length = 20 }
    uint32_t              magic : 24;          // constant, equal to 0x464651 ("QFF")
    uint8_t               qff_version;         // constant, equal to 0x01
    uint32_t              total_file_size;     // total size of the entire file, starting at offset zero
    uint32_t              neg_total_file_size; // negated value of total_file_size, used for detecting parsing errors
    uint8_t               line_height;         // glyph height in pixels
    bool                  has_ascii_table;     // whether the font has an ascii table of glyphs (0x20...0x7E)
    uint16_t              num_unicode_glyphs;  // the number of glyphs in the unicode table -- no table specified if zero
    qp_image_format_t     format : 8;          // Frame format, see qp.h.
    uint8_t               flags;               // frame flags, see below.
    uint8_t               compression_scheme;  // compression scheme, see below.
    uint8_t               transparency_index;  // palette index used for transparent pixels (not yet implemented)
} qff_font_descriptor_v1_t;

_Static_assert(sizeof(qff_font_descriptor_v1_t) == (sizeof(qgf_block_header_v1_t) + 20), "qff_font_descriptor_v1_t must be 25 bytes in v1 of QFF");

#define QFF_MAGIC 0x464651

/////////////////////////////////////////
// ASCII glyph table descriptor

#define QFF_ASCII_GLYPH_DESCRIPTOR_TYPEID 0x01

#define QFF_GLYPH_WIDTH_BITS 6
#define QFF_GLYPH_WIDTH_MASK ((1 << QFF_GLYPH_WIDTH_BITS) - 1)
#define QFF_GLYPH_OFFSET_BITS 18
#define QFF_GLYPH_OFFSET_MASK (((1 << QFF_GLYPH_OFFSET_BITS) - 1) << QFF_GLYPH_WIDTH_BITS)

typedef struct __attribute__((packed)) qff_ascii_glyph_v1_t {
    uint32_t value : 24; // Uses QFF_GLYPH_*_(BITS|MASK) as bitfield ordering is compiler-defined
} qff_ascii_glyph_v1_t;

_Static_assert(sizeof(qff_ascii_glyph_v1_t) == 3, "qff_ascii_glyph_v1_t must be 3 bytes in v1 of QFF");

typedef struct __attribute__((packed)) qff_ascii_glyph_table_v1_t {
    qgf_block_header_v1_t header;    // = { .type_id = 0x01, .neg_type_id = (~0x01), .length = 285 }
    qff_ascii_glyph_v1_t  glyph[95]; // 95 glyphs, 0x20..0x7E
} qff_ascii_glyph_table_v1_t;

_Static_assert(sizeof(qff_ascii_glyph_table_v1_t) == (sizeof(qgf_block_header_v1_t) + (95 * sizeof(qff_ascii_glyph_v1_t))), "qff_ascii_glyph_table_v1_t must be 290 bytes in v1 of QFF");

/////////////////////////////////////////
// Unicode glyph table descriptor

#define QFF_UNICODE_GLYPH_DESCRIPTOR_TYPEID 0x02

typedef struct __attribute__((packed)) qff_unicode_glyph_v1_t {
    uint32_t code_point : 24;
    uint32_t value : 24; // Uses QFF_GLYPH_*_(BITS|MASK) as bitfield ordering is compiler-defined
} qff_unicode_glyph_v1_t;

_Static_assert(sizeof(qff_unicode_glyph_v1_t) == 6, "qff_unicode_glyph_v1_t must be 6 bytes in v1 of QFF");

typedef struct __attribute__((packed)) qff_unicode_glyph_table_v1_t {
    qgf_block_header_v1_t  header;   // = { .type_id = 0x02, .neg_type_id = (~0x02), .length = (N * 6) }
    qff_unicode_glyph_v1_t glyph[0]; // Extent of '0' signifies that this struct is immediately followed by the glyph data
} qff_unicode_glyph_table_v1_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QFF API

bool     qff_validate_stream(qp_stream_t *stream);
uint32_t qff_get_total_size(qp_stream_t *stream);
bool     qff_read_font_descriptor(qp_stream_t *stream, uint8_t *line_height, bool *has_ascii_table, uint16_t *num_unicode_glyphs, uint8_t *bpp, bool *has_palette, painter_compression_t *compression_scheme, uint32_t *total_bytes);
