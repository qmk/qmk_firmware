/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* A compressed font format based on run length encoding and dictionary
 * compression.
 */

#ifndef _MF_RLEFONT_H_
#define _MF_RLEFONT_H_

#include "mf_font.h"

/* Versions of the RLE font format that are supported. */
#define MF_RLEFONT_VERSION_4_SUPPORTED 1

/* Structure for a range of characters. This implements a sparse storage of
 * character indices, so that you can e.g. pick a 100 characters in the middle
 * of the UTF16 range and just store them. */
struct mf_rlefont_char_range_s
{
    /* The number of the first character in this range. */
    gU16 first_char;
    
    /* The total count of characters in this range. */
    gU16 char_count;
    
    /* Lookup table with the start indices into glyph_data. */
    const gU16 *glyph_offsets;
    
    /* The encoded glyph data for glyphs in this range. */
    const gU8 *glyph_data;
};

/* Structure for a single encoded font. */
struct mf_rlefont_s
{
    struct mf_font_s font;
    
    /* Version of the font definition used. */
    const gU8 version;
    
    /* Big array of the data for all the dictionary entries. */
    const gU8 *dictionary_data;
    
    /* Lookup table with the start indices into dictionary_data.
     * Contains N+1 entries, so that the length of the entry can
     * be determined by subtracting from the next offset. */
    const gU16 *dictionary_offsets;
    
    /* Number of dictionary entries using the RLE encoding.
     * Entries starting at this index use the dictionary encoding. */
    const gU8 rle_entry_count;
    
    /* Total number of dictionary entries.
     * Entries after this are nonexistent. */
    const gU8 dict_entry_count;
    
    /* Number of discontinuous character ranges */
    const gU16 char_range_count;
    
    /* Array of the character ranges */
    const struct mf_rlefont_char_range_s *char_ranges;
};

#ifdef MF_RLEFONT_INTERNALS
/* Internal functions, don't use these directly. */
MF_EXTERN gU8 mf_rlefont_render_character(const struct mf_font_s *font,
                                              gI16 x0, gI16 y0,
                                              gU16 character,
                                              mf_pixel_callback_t callback,
                                              void *state);

MF_EXTERN gU8 mf_rlefont_character_width(const struct mf_font_s *font,
                                             gU16 character);
#endif

#endif
