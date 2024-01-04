# QMK Font Format :id=qmk-font-format

QMK uses a font format _("Quantum Font Format" - QFF)_ specifically for resource-constrained systems.

This format is capable of encoding 1-, 2-, 4-, and 8-bit-per-pixel greyscale- and palette-based images into a font. It also includes RLE for pixel data for some basic compression.

All integer values are in little-endian format.

The QFF is defined in terms of _blocks_ -- each _block_ contains a _header_ and an optional _blob_ of data. The _header_ contains the block's _typeid_, and the length of the _blob_ that follows. Each block type is denoted by a different _typeid_ has its own block definition below. All blocks are defined as packed structs, containing zero padding between fields.

The general structure of the file is:

* _Font descriptor block_
* _ASCII glyph block_ (optional, only if ASCII glyphs are included)
* _Unicode glyph block_ (optional, only if Unicode glyphs are included)
* _Font palette block_ (optional, depending on frame format)
* _Font data block_

## Block Header :id=qff-block-header

The block header is identical to [QGF's block header](quantum_painter_qgf.md#qgf-block-header), and is present for all blocks, including the font descriptor.

## Font descriptor block :id=qff-font-descriptor

* _typeid_ = 0x00
* _length_ = 20

This block must be located at the start of the file contents, and can exist a maximum of once in an entire QGF file. It is always followed by either the _ASCII glyph table_ or the _Unicode glyph table_, depending on which glyphs are included in the font.

_Block_ format:

```c
typedef struct __attribute__((packed)) qff_font_descriptor_v1_t {
    qgf_block_header_v1_t header;               // = { .type_id = 0x00, .neg_type_id = (~0x00), .length = 20 }
    uint24_t              magic;                // constant, equal to 0x464651 ("QFF")
    uint8_t               qff_version;          // constant, equal to 0x01
    uint32_t              total_file_size;      // total size of the entire file, starting at offset zero
    uint32_t              neg_total_file_size;  // negated value of total_file_size, used for detecting parsing errors
    uint8_t               line_height;          // glyph height in pixels
    bool                  has_ascii_table;      // whether the font has an ascii table of glyphs (0x20...0x7E)
    uint16_t              num_unicode_glyphs;   // the number of glyphs in the unicode table -- no table specified if zero
    uint8_t               format;               // frame format, see below.
    uint8_t               flags;                // frame flags, see below.
    uint8_t               compression_scheme;   // compression scheme, see below.
    uint8_t               transparency_index;   // palette index used for transparent pixels (not yet implemented)
} qff_font_descriptor_v1_t;
// _Static_assert(sizeof(qff_font_descriptor_v1_t) == (sizeof(qgf_block_header_v1_t) + 20), "qff_font_descriptor_v1_t must be 25 bytes in v1 of QFF");
```

The values for `format`, `flags`, `compression_scheme`, and `transparency_index` match [QGF's frame descriptor block](quantum_painter_qgf.md#qgf-frame-descriptor), with the exception that the `delta` flag is ignored by QFF.

## ASCII glyph table :id=qff-ascii-table

* _typeid_ = 0x01
* _length_ = 290

If the font contains ascii characters, the _ASCII glyph block_ must be located directly after the _font descriptor block_.

```c
#define QFF_GLYPH_WIDTH_BITS 6
#define QFF_GLYPH_WIDTH_MASK ((1<<QFF_GLYPH_WIDTH_BITS)-1)
#define QFF_GLYPH_OFFSET_BITS 18
#define QFF_GLYPH_OFFSET_MASK (((1<<QFF_GLYPH_OFFSET_BITS)-1) << QFF_GLYPH_WIDTH_BITS)

typedef struct __attribute__((packed)) qff_ascii_glyph_table_v1_t {
    qgf_block_header_v1_t header;  // = { .type_id = 0x01, .neg_type_id = (~0x01), .length = 285 }
    uint24_t glyph[95];            // 95 glyphs, 0x20..0x7E, see bits/masks above for values
} qff_ascii_glyph_table_v1_t;
// _Static_assert(sizeof(qff_ascii_glyph_table_v1_t) == (sizeof(qgf_block_header_v1_t) + 285), "qff_ascii_glyph_table_v1_t must be 290 bytes in v1 of QFF");
```

## Unicode glyph table :id=qff-unicode-table

* _typeid_ = 0x02
* _length_ = variable

If this font contains unicode characters, the _unicode glyph block_ must be located directly after the _ASCII glyph table block_, or the _font descriptor block_ if the font does not contain ASCII characters.

```c
typedef struct __attribute__((packed)) qff_unicode_glyph_table_v1_t {
    qgf_block_header_v1_t header;     // = { .type_id = 0x02, .neg_type_id = (~0x02), .length = (N * 6) }
    struct __attribute__((packed)) {  // container for a single unicode glyph
        uint24_t code_point;          // the unicode code point
        uint24_t glyph;               // the glyph information, as per ASCII glyphs above
    } glyph[N];                       // N glyphs worth of data
} qff_unicode_glyph_table_v1_t;
```

## Font palette block :id=qff-palette-descriptor

* _typeid_ = 0x03
* _length_ = variable

The _font palette block_ is identical to [QGF's frame palette block](quantum_painter_qgf.md#qgf-frame-palette-descriptor), retaining the same _typeid_ of 0x03.

It is only specified in the QFF if the font is palette-based, and follows the _unicode glyph block_ if the font contains any Unicode glyphs, or the _ASCII glyph block_ if the font contains only ASCII glyphs.

## Font data block :id=qff-data-descriptor

* _typeid_ = 0x04
* _length_ = variable

The _font data block_ is the last block in the file and is identical to [QGF's frame data block](quantum_painter_qgf.md#qgf-frame-data-descriptor), however has a different _typeid_ of 0x04 in QFF.
