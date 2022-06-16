

/* Start of automatically generated font definition for digital_7__mono_20. */

#ifndef MF_RLEFONT_INTERNALS
#define MF_RLEFONT_INTERNALS
#endif
#include "mf_rlefont.h"

#ifndef MF_RLEFONT_VERSION_4_SUPPORTED
#error The font file is not compatible with this version of mcufont.
#endif

static const gU8 mf_rlefont_digital_7__mono_20_dictionary_data[39] = {
    0x81, 0x05, 0x81, 0x05, 0x81, 0x05, 0x81, 0x05, 0x81, 0x06, 0x80, 0x01, 0x07, 0x80, 0x05, 0x85, 
    0x05, 0x80, 0x81, 0x03, 0x03, 0x85, 0x0f, 0x44, 0x84, 0x85, 0x86, 0x88, 0x44, 0x44, 0x44, 0x44, 
    0x24, 0x84, 0x44, 0x44, 0x18, 0xc4, 0x83, 
};

static const gU16 mf_rlefont_digital_7__mono_20_dictionary_offsets[13] = {
    0x0000, 0x0009, 0x000c, 0x000f, 0x0010, 0x0012, 0x0013, 0x0014, 
    0x0016, 0x001c, 0x0020, 0x0024, 0x0027, 
};

static const gU8 mf_rlefont_digital_7__mono_20_glyph_data_0[63] = {
    0x09, 0x1b, 0x18, 0x1c, 0x1a, 0x18, 0x1b, 0x09, 0x21, 0x19, 0x22, 0x21, 0x09, 0x83, 0x44, 0x21, 
    0x83, 0x20, 0x1f, 0x10, 0x09, 0x83, 0x44, 0x21, 0x82, 0x44, 0x21, 0x83, 0x09, 0x84, 0x23, 0x20, 
    0xec, 0x44, 0x09, 0x43, 0x20, 0x1f, 0x20, 0xec, 0x83, 0x09, 0x43, 0x20, 0x1f, 0x23, 0x0f, 0x09, 
    0x1b, 0x18, 0x22, 0x21, 0x09, 0x1b, 0x23, 0x23, 0x0f, 0x09, 0x1b, 0x23, 0x20, 0xec, 0x83, 
};

static const gU16 mf_rlefont_digital_7__mono_20_glyph_offsets_0[10] = {
    0x0000, 0x0007, 0x000c, 0x0014, 0x001c, 0x0022, 0x0029, 0x002f, 
    0x0034, 0x0039, 
};

static const struct mf_rlefont_char_range_s mf_rlefont_digital_7__mono_20_char_ranges[] = {
    {48, 10, mf_rlefont_digital_7__mono_20_glyph_offsets_0, mf_rlefont_digital_7__mono_20_glyph_data_0},
};

const struct mf_rlefont_s mf_rlefont_digital_7__mono_20 = {
    {
    "Digital-7 Mono Mono 20",
    "digital_7__mono_20",
    7, /* width */
    13, /* height */
    9, /* min x advance */
    9, /* max x advance */
    -1, /* baseline x */
    13, /* baseline y */
    11, /* line height */
    3, /* flags */
    32, /* fallback character */
    &mf_rlefont_character_width,
    &mf_rlefont_render_character,
    },
    4, /* version */
    mf_rlefont_digital_7__mono_20_dictionary_data,
    mf_rlefont_digital_7__mono_20_dictionary_offsets,
    8, /* rle dict count */
    12, /* total dict count */
    1, /* char range count */
    mf_rlefont_digital_7__mono_20_char_ranges,
};

#ifdef MF_INCLUDED_FONTS
/* List entry for searching fonts by name. */
static const struct mf_font_list_s mf_rlefont_digital_7__mono_20_listentry = {
    MF_INCLUDED_FONTS,
    (struct mf_font_s*)&mf_rlefont_digital_7__mono_20
};
#undef MF_INCLUDED_FONTS
#define MF_INCLUDED_FONTS (&mf_rlefont_digital_7__mono_20_listentry)
#endif


/* End of automatically generated font definition for digital_7__mono_20. */

