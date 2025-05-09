# QMK Graphics Format {#qmk-graphics-format}

QMK uses a graphics format _("Quantum Graphics Format" - QGF)_ specifically for resource-constrained systems.

This format is capable of encoding 1-, 2-, 4-, and 8-bit-per-pixel greyscale- and palette-based images. It also includes RLE for pixel data for some basic compression.

All integer values are in little-endian format.

The QGF is defined in terms of _blocks_ -- each _block_ contains a _header_ and an optional _blob_ of data. The _header_ contains the block's _typeid_, and the length of the _blob_ that follows. Each block type is denoted by a different _typeid_ has its own block definition below. All blocks are defined as packed structs, containing zero padding between fields.

The general structure of the file is:

* _Graphics descriptor block_
* _Frame offset block_
* Repeating list of frames:
    * _Frame descriptor block_
    * _Frame palette block_ (optional, depending on frame format)
    * _Frame delta block_ (optional, depending on delta flag)
    * _Frame data block_

Different frames within the file should be considered "isolated" and may have their own image format and/or palette.

## Block Header {#qgf-block-header}

This block header is present for all blocks, including the graphics descriptor.

_Block header_ format:

```c
typedef struct __attribute__((packed)) qgf_block_header_v1_t {
    uint8_t type_id;      // See each respective block type
    uint8_t neg_type_id;  // Negated type ID, used for detecting parsing errors
    uint24_t length;      // 24-bit blob length, allowing for block sizes of a maximum of 16MB
} qgf_block_header_v1_t;
// _Static_assert(sizeof(qgf_block_header_v1_t) == 5, "qgf_block_header_v1_t must be 5 bytes in v1 of QGF");
```
The _length_ describes the number of octets in the data following the block header -- a block header may specify a _length_ of `0` if no blob is specified.

## Graphics descriptor block {#qgf-graphics-descriptor}

* _typeid_ = 0x00
* _length_ = 18

This block must be located at the start of the file contents, and can exist a maximum of once in an entire QGF file. It is always followed by the _frame offset block_.

_Block_ format:

```c
typedef struct __attribute__((packed)) qgf_graphics_descriptor_v1_t {
    qgf_block_header_v1_t header;               // = { .type_id = 0x00, .neg_type_id = (~0x00), .length = 18 }
    uint24_t              magic;                // constant, equal to 0x464751 ("QGF")
    uint8_t               qgf_version;          // constant, equal to 0x01
    uint32_t              total_file_size;      // total size of the entire file, starting at offset zero
    uint32_t              neg_total_file_size;  // negated value of total_file_size, used for detecting parsing errors
    uint16_t              image_width;          // in pixels
    uint16_t              image_height;         // in pixels
    uint16_t              frame_count;          // minimum of 1
} qgf_graphics_descriptor_v1_t;
// _Static_assert(sizeof(qgf_graphics_descriptor_v1_t) == (sizeof(qgf_block_header_v1_t) + 18), "qgf_graphics_descriptor_v1_t must be 23 bytes in v1 of QGF");
```

## Frame offset block {#qgf-frame-offset-descriptor}

* _typeid_ = 0x01
* _length_ = variable

This block denotes the offsets within the file to each frame's _frame descriptor block_, relative to the start of the file. The _frame offset block_ always immediately follows the _graphics descriptor block_. The contents of this block are an array of U32's, with one entry for each frame.

Duplicate frame offsets in this block are allowed, if a certain frame is to be shown multiple times during animation.

_Block_ format:

```c
typedef struct __attribute__((packed)) qgf_frame_offsets_v1_t {
    qgf_block_header_v1_t header;    // = { .type_id = 0x01, .neg_type_id = (~0x01), .length = (N * sizeof(uint32_t)) }
    uint32_t              offset[N]; // where 'N' is the number of frames in the file
} qgf_frame_offsets_v1_t;
```

## Frame descriptor block {#qgf-frame-descriptor}

* _typeid_ = 0x02
* _length_ = 5

This block denotes the start of a frame.

_Block_ format:

```c
typedef struct __attribute__((packed)) qgf_frame_v1_t {
    qgf_block_header_v1_t header;              // = { .type_id = 0x02, .neg_type_id = (~0x02), .length = 5 }
    uint8_t               format;              // Frame format, see below.
    uint8_t               flags;               // Frame flags, see below.
    uint8_t               compression_scheme;  // Compression scheme, see below.
    uint8_t               transparency_index;  // palette index used for transparent pixels (not yet implemented)
    uint16_t              delay;               // frame delay time for animations (in units of milliseconds)
} qgf_frame_v1_t;
// _Static_assert(sizeof(qgf_frame_v1_t) == (sizeof(qgf_block_header_v1_t) + 6), "qgf_frame_v1_t must be 11 bytes in v1 of QGF");
```

If this frame is grayscale, the _frame descriptor block_ (or _frame delta block_ if flags denote a delta frame) is immediately followed by this frame's corresponding _frame data block_.

If the frame uses an indexed palette, the _frame descriptor block_ (or _frame delta block_ if flags denote a delta frame) is immediately followed by this frame's corresponding _frame palette block_.

Frame format possible values:

* `0x00`: 1bpp grayscale, no palette, `0` = black, `1` = white, LSb first pixel
* `0x01`: 2bpp grayscale, no palette, `0` = black, `3` = white, linear interpolation of brightness, LSb first pixel
* `0x02`: 4bpp grayscale, no palette, `0` = black, `15` = white, linear interpolation of brightness, LSb first pixel
* `0x03`: 8bpp grayscale, no palette, `0` = black, `255` = white, linear interpolation of brightness, LSb first pixel
* `0x04`: 1bpp indexed palette, 2 colors, LSb first pixel
* `0x05`: 2bpp indexed palette, 4 colors, LSb first pixel
* `0x06`: 4bpp indexed palette, 16 colors, LSb first pixel
* `0x07`: 8bpp indexed palette, 256 colors, LSb first pixel

Frame flags is a bitmask with the following format:

| `bit 7` | `bit 6` | `bit 5` | `bit 4` | `bit 3` | `bit 2` | `bit 1` | `bit 0`      |
|---------|---------|---------|---------|---------|---------|---------|--------------|
| -       | -       | -       | -       | -       | -       | Delta   | Transparency |

* `[1]` -- Delta: Signifies that the current frame is a delta frame, which specifies only a sub-image. The _frame delta block_ follows the _frame palette block_ if the image format specifies a palette, otherwise it directly follows the _frame descriptor block_.
* `[0]` -- Transparency: The transparent palette index in the _blob_ is considered valid and should be used when considering which pixels should be transparent during rendering this frame, if possible.

Compression scheme possible values:

* `0x00`: No compression
* `0x01`: [QMK RLE](quantum_painter_rle)

## Frame palette block {#qgf-frame-palette-descriptor}

* _typeid_ = 0x03
* _length_ = variable

This block describes the palette used for the frame. The _blob_ contains an array of palette entries -- one palette entry is present for each color used -- each palette entry is in QMK HSV888 format:

```c
typedef struct __attribute__((packed)) qgf_palette_v1_t {
    qgf_block_header_v1_t header;     // = { .type_id = 0x03, .neg_type_id = (~0x03), .length = (N * 3 * sizeof(uint8_t)) }
    struct {  // container for a single HSV palette entry
        uint8_t h;                    // hue component: `[0,360)` degrees is mapped to `[0,255]` uint8_t.
        uint8_t s;                    // saturation component: `[0,1]` is mapped to `[0,255]` uint8_t.
        uint8_t v;                    // value component: `[0,1]` is mapped to `[0,255]` uint8_t.
    } hsv[N];                         // N * hsv, where N is the number of palette entries depending on the frame format in the descriptor
} qgf_palette_v1_t;
```

## Frame delta block {#qgf-frame-delta-descriptor}

* _typeid_ = 0x04
* _length_ = 8

This block describes where the delta frame should be drawn, with respect to the top left location of the image.

```c
typedef struct __attribute__((packed)) qgf_delta_v1_t {
    qgf_block_header_v1_t header;  // = { .type_id = 0x04, .neg_type_id = (~0x04), .length = 8 }
    uint16_t left;                 // The left pixel location to draw the delta image
    uint16_t top;                  // The top pixel location to draw the delta image
    uint16_t right;                // The right pixel location to to draw the delta image
    uint16_t bottom;               // The bottom pixel location to to draw the delta image
} qgf_delta_v1_t;
// _Static_assert(sizeof(qgf_delta_v1_t) == 13, "qgf_delta_v1_t must be 13 bytes in v1 of QGF");
```

## Frame data block {#qgf-frame-data-descriptor}

* _typeid_ = 0x05
* _length_ = variable

This block describes the data associated with the frame. The _blob_ contains an array of bytes containing the data corresponding to the frame's image format:

```c
typedef struct __attribute__((packed)) qgf_data_v1_t {
    qgf_block_header_v1_t header;   // = { .type_id = 0x05, .neg_type_id = (~0x05), .length = N }
    uint8_t               data[N];  // N data octets
} qgf_data_v1_t;
```
