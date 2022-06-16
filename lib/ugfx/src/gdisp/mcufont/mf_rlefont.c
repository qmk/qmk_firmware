/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "mf_rlefont.h"

#ifndef MF_NO_COMPILE

/* Number of reserved codes before the dictionary entries. */
#define DICT_START 24

/* Special reference to mean "fill with zeros to the end of the glyph" */
#define REF_FILLZEROS 16

/* RLE codes */
#define RLE_CODEMASK    0xC0
#define RLE_VALMASK     0x3F
#define RLE_ZEROS       0x00
#define RLE_64ZEROS     0x40
#define RLE_ONES        0x80
#define RLE_SHADE       0xC0

/* Dictionary "fill entries" for encoding bits directly. */
#define DICT_START7BIT  4
#define DICT_START6BIT  132
#define DICT_START5BIT  196
#define DICT_START4BIT  228
#define DICT_START3BIT  244
#define DICT_START2BIT  252

/* Find a pointer to the glyph matching a given character by searching
 * through the character ranges. If the character is not found, return
 * pointer to the default glyph.
 */
static const gU8 *find_glyph(const struct mf_rlefont_s *font,
                                 gU16 character)
{
   unsigned i, index;
   const struct mf_rlefont_char_range_s *range;
   for (i = 0; i < font->char_range_count; i++)
   {
       range = &font->char_ranges[i];
       index = character - range->first_char;
       if (character >= range->first_char && index < range->char_count)
       {
           unsigned offset = range->glyph_offsets[index];
           return &range->glyph_data[offset];
       }
   }

   return 0;
}

/* Structure to keep track of coordinates of the next pixel to be written,
 * and also the bounds of the character. */
struct renderstate_r
{
    gI16 x_begin;
    gI16 x_end;
    gI16 x;
    gI16 y;
    gI16 y_end;
    mf_pixel_callback_t callback;
    void *state;
};

/* Call the callback to write one pixel to screen, and advance to next
 * pixel position. */
static void write_pixels(struct renderstate_r *rstate, gU16 count,
                         gU8 alpha)
{
    gU8 rowlen;
    
    /* Write row-by-row if the run spans multiple rows. */
    while (rstate->x + count >= rstate->x_end)
    {
        rowlen = rstate->x_end - rstate->x;
        rstate->callback(rstate->x, rstate->y, rowlen, alpha, rstate->state);
        count -= rowlen;
        rstate->x = rstate->x_begin;
        rstate->y++;
    }
    
    /* Write the remaining part */
    if (count)
    {
        rstate->callback(rstate->x, rstate->y, count, alpha, rstate->state);
        rstate->x += count;
    }
}

/* Skip the given number of pixels (0 alpha) */
static void skip_pixels(struct renderstate_r *rstate, gU16 count)
{
    rstate->x += count;
    while (rstate->x >= rstate->x_end)
    {
        rstate->x -= rstate->x_end - rstate->x_begin;
        rstate->y++;
    }
}

/* Decode and write out a RLE-encoded dictionary entry. */
static void write_rle_dictentry(const struct mf_rlefont_s *font,
                                struct renderstate_r *rstate,
                                gU8 index)
{
    gU16 offset = font->dictionary_offsets[index];
    gU16 length = font->dictionary_offsets[index + 1] - offset;
    gU16 i;
    
    for (i = 0; i < length; i++)
    {
        gU8 code = font->dictionary_data[offset + i];
        if ((code & RLE_CODEMASK) == RLE_ZEROS)
        {
            skip_pixels(rstate, code & RLE_VALMASK);
        }
        else if ((code & RLE_CODEMASK) == RLE_64ZEROS)
        {
            skip_pixels(rstate, ((code & RLE_VALMASK) + 1) * 64);
        }
        else if ((code & RLE_CODEMASK) == RLE_ONES)
        {
            write_pixels(rstate, (code & RLE_VALMASK) + 1, 255);
        }
        else if ((code & RLE_CODEMASK) == RLE_SHADE)
        {
            gU8 count, alpha;
            count = ((code & RLE_VALMASK) >> 4) + 1;
            alpha = ((code & RLE_VALMASK) & 0xF) * 0x11;
            write_pixels(rstate, count, alpha);
        }
    }
}

/* Get bit count for the "fill entries" */
static gU8 fillentry_bitcount(gU8 index)
{
    if (index >= DICT_START2BIT)
        return 2;
    else if (index >= DICT_START3BIT)
        return 3;
    else if (index >= DICT_START4BIT)
        return 4;
    else if (index >= DICT_START5BIT)
        return 5;
    else if (index >= DICT_START6BIT)
        return 6;
    else
        return 7;
}

/* Decode and write out a direct binary codeword */
static void write_bin_codeword(const struct mf_rlefont_s *font,
                                struct renderstate_r *rstate,
                                gU8 code)
{
    gU8 bitcount = fillentry_bitcount(code);
    gU8 byte = code - DICT_START7BIT;
    gU8 runlen = 0;
    (void) font;
    
    while (bitcount--)
    {
        if (byte & 1)
        {
            runlen++;
        }
        else 
        {
            if (runlen)
            {
                write_pixels(rstate, runlen, 255);
                runlen = 0;
            }
            
            skip_pixels(rstate, 1);
        }
        
        byte >>= 1;
    }
    
    if (runlen)
        write_pixels(rstate, runlen, 255);
}

/* Decode and write out a reference codeword */
static void write_ref_codeword(const struct mf_rlefont_s *font,
                                struct renderstate_r *rstate,
                                gU8 code)
{
    if (code <= 15)
    {
        write_pixels(rstate, 1, 0x11 * code);
    }
    else if (code == REF_FILLZEROS)
    {
        /* Fill with zeroes to end */
        rstate->y = rstate->y_end;
    }
    else if (code < DICT_START)
    {
        /* Reserved */
    }
    else if (code < DICT_START + font->rle_entry_count)
    {
        write_rle_dictentry(font, rstate, code - DICT_START);
    }
    else
    {
        write_bin_codeword(font, rstate, code);
    }
}

/* Decode and write out a reference encoded dictionary entry. */
static void write_ref_dictentry(const struct mf_rlefont_s *font,
                                struct renderstate_r *rstate,
                                gU8 index)
{
    gU16 offset = font->dictionary_offsets[index];
    gU16 length = font->dictionary_offsets[index + 1] - offset;
    gU16 i;
    
    for (i = 0; i < length; i++)
    {
        gU8 code = font->dictionary_data[offset + i];
        write_ref_codeword(font, rstate, code);
    }
}

/* Decode and write out an arbitrary glyph codeword */
static void write_glyph_codeword(const struct mf_rlefont_s *font,
                                struct renderstate_r *rstate,
                                gU8 code)
{
    if (code >= DICT_START + font->rle_entry_count &&
        code < DICT_START + font->dict_entry_count)
    {
        write_ref_dictentry(font, rstate, code - DICT_START);
    }
    else
    {
        write_ref_codeword(font, rstate, code);
    }
}


gU8 mf_rlefont_render_character(const struct mf_font_s *font,
                                    gI16 x0, gI16 y0,
                                    gU16 character,
                                    mf_pixel_callback_t callback,
                                    void *state)
{
    const gU8 *p;
    gU8 width;
    
    struct renderstate_r rstate;
    rstate.x_begin = x0;
    rstate.x_end = x0 + font->width;
    rstate.x = x0;
    rstate.y = y0;
    rstate.y_end = y0 + font->height;
    rstate.callback = callback;
    rstate.state = state;
    
   	p = find_glyph((struct mf_rlefont_s*)font, character);
    if (!p)
        return 0;
    
    width = *p++;
    while (rstate.y < rstate.y_end)
    {
        write_glyph_codeword((struct mf_rlefont_s*)font, &rstate, *p++);
    }
    
    return width;
}

gU8 mf_rlefont_character_width(const struct mf_font_s *font,
                                   gU16 character)
{
    const gU8 *p;
    p = find_glyph((struct mf_rlefont_s*)font, character);
    if (!p)
        return 0;
    
    return *p;
}

#endif //MF_NO_COMPILE
