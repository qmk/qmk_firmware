/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "mf_bwfont.h"

#ifndef MF_NO_COMPILE

#include <stdbool.h>

/* Find the character range and index that contains a given glyph.. */
static const struct mf_bwfont_char_range_s *find_char_range(
    const struct mf_bwfont_s *font, gU16 character, gU16 *index_ret)
{
    unsigned i, index;
    const struct mf_bwfont_char_range_s *range;
    for (i = 0; i < font->char_range_count; i++)
    {
        range = &font->char_ranges[i];
        index = character - range->first_char;
        if (character >= range->first_char && index < range->char_count)
        {
            *index_ret = index;
            return range;
        }
    }
    
    return 0;
}

static gU8 get_width(const struct mf_bwfont_char_range_s *r, gU16 index)
{
    if (r->width)
    {
        return r->width + r->offset_x;
    }
    else
    {
        return r->glyph_widths[index];
    }
}

static gU8 render_char(const struct mf_bwfont_char_range_s *r,
                           gI16 x0, gI16 y0, gU16 index,
                           mf_pixel_callback_t callback,
                           void *state)
{
    const gU8 *data, *p;
    gU8 stride, runlen;
    gU8 x, y, height, num_cols;
    gU8 bit, byte, mask;
    bool oldstate, newstate;
    
    if (r->width)
    {
        data = r->glyph_data + r->width * index * r->height_bytes;
        num_cols = r->width;
    }
    else
    {
        data = r->glyph_data + r->glyph_offsets[index] * r->height_bytes;
        num_cols = r->glyph_offsets[index + 1] - r->glyph_offsets[index];
    }
    
    stride = r->height_bytes;
    height = r->height_pixels;
    y0 += r->offset_y;
    x0 += r->offset_x;
    bit = 0;
    byte = 0;
    
    for (y = 0; y < height; y++)
    {
        mask = (1 << bit);
        
        oldstate = false;
        runlen = 0;
        p = data + byte;
        for (x = 0; x < num_cols; x++, p += stride)
        {
            newstate = *p & mask;
            if (newstate != oldstate)
            {
                if (oldstate && runlen)
                {
                    callback(x0 + x - runlen, y0 + y, runlen, 255, state);
                }
                
                oldstate = newstate;
                runlen = 0;
            }
            
            runlen++;
        }
        
        if (oldstate && runlen)
        {
            callback(x0 + x - runlen, y0 + y, runlen, 255, state);
        }
        
        bit++;
        if (bit > 7)
        {
            bit = 0;
            byte++;
        }
    }
    
    return get_width(r, index);
}

gU8 mf_bwfont_render_character(const struct mf_font_s *font,
                                   gI16 x0, gI16 y0,
                                   gU16 character,
                                   mf_pixel_callback_t callback,
                                   void *state)
{
    const struct mf_bwfont_s *bwfont = (const struct mf_bwfont_s*)font;
    const struct mf_bwfont_char_range_s *range;
    gU16 index;
    
    range = find_char_range(bwfont, character, &index);
    if (!range)
        return 0;
    
    return render_char(range, x0, y0, index, callback, state);
}

gU8 mf_bwfont_character_width(const struct mf_font_s *font,
                                  gU16 character)
{
    const struct mf_bwfont_s *bwfont = (const struct mf_bwfont_s*)font;
    const struct mf_bwfont_char_range_s *range;
    gU16 index;
    
    range = find_char_range(bwfont, character, &index);
    if (!range)
        return 0;
    
    return get_width(range, index);
}

#endif //MF_NO_COMPILE
