/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* Uncompressed font format for storing black & white fonts. Very efficient
 * to decode and works well for small font sizes.
 */

#ifndef _MF_BWFONT_H_
#define _MF_BWFONT_H_

#include "mf_font.h"

/* Versions of the BW font format that are supported. */
#define MF_BWFONT_VERSION_4_SUPPORTED 1

/* Structure for a range of characters. */
struct mf_bwfont_char_range_s
{
    /* The number of the first character in this range. */
    gU16 first_char;
    
    /* The total count of characters in this range. */
    gU16 char_count;
    
    /* The left and top skips of the characters in this range.
     * This is the number of empty rows at left and at top. */
    gU8 offset_x;
    gU8 offset_y;
    
    /* Column height for glyphs in this range, in bytes and pixels. */
    gU8 height_bytes;
    gU8 height_pixels;
    
    /* Positive value if the width of all glyphs in this range is the
     * same, or zero if it is not. */
    gU8 width;
    
    /* Lookup table for the character widths. NULL if width is specified. */
    const gU8 *glyph_widths;
    
    /* Lookup table for the character offsets.  Multiply by height_bytes
     * to get the byte offset. Also allows lookup of the number of columns.
     * NULL if width is specified. */
    const gU16 *glyph_offsets;
    
    /* Table for the glyph data.
     * The data for each glyph is column-by-column, with N bytes per each
     * column. The LSB of the first byte is the top left pixel.
     */
    const gU8 *glyph_data;
};

/* Structure for the font */
struct mf_bwfont_s
{
    struct mf_font_s font;
    
    /* Version of the font format. */
    const gU8 version;
    
    /* Number of character ranges. */
    const gU16 char_range_count;
    
    /* Array of the character ranges */
    const struct mf_bwfont_char_range_s *char_ranges;
};

#ifdef MF_BWFONT_INTERNALS
/* Internal functions, don't use these directly. */
MF_EXTERN gU8 mf_bwfont_render_character(const struct mf_font_s *font,
                                             gI16 x0, gI16 y0,
                                             gU16 character,
                                             mf_pixel_callback_t callback,
                                             void *state);

MF_EXTERN gU8 mf_bwfont_character_width(const struct mf_font_s *font,
                                            gU16 character);
#endif

#endif
