/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "mf_kerning.h"

#ifndef MF_NO_COMPILE

#include <stdbool.h>

#if MF_USE_KERNING

/* Structure for keeping track of the edge of the glyph as it is rendered. */
struct kerning_state_s
{
    gU8 edgepos[MF_KERNING_ZONES];
    gU8 zoneheight;
};

/* Pixel callback for analyzing the left edge of a glyph. */
static void fit_leftedge(gI16 x, gI16 y, gU8 count, gU8 alpha,
                         void *state)
{
    struct kerning_state_s *s = state;
    (void)count;
    
    if (alpha > 7)
    {
        gU8 zone = y / s->zoneheight;
        if (x < s->edgepos[zone])
            s->edgepos[zone] = x;
    }
}

/* Pixel callback for analyzing the right edge of a glyph. */
static void fit_rightedge(gI16 x, gI16 y, gU8 count, gU8 alpha,
                         void *state)
{
    struct kerning_state_s *s = state;
    
    if (alpha > 7)
    {
        gU8 zone = y / s->zoneheight;
        x += count - 1;
        if (x > s->edgepos[zone])
            s->edgepos[zone] = x;
    }
}

/* Should kerning be done against this character? */
static bool do_kerning(mf_char c)
{
    /* Just a speed optimization, spaces would be ignored anyway. */
    if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
        return false;
    
    /* Do not kern against digits, in order to keep values in tables nicely
     * aligned. Most fonts have constant width for digits. */
    if (c >= '0' && c <= '9')
        return false;
    
    return true;
}

//static gI16 min16(gI16 a, gI16 b) { return (a < b) ? a : b; }
static gI16 max16(gI16 a, gI16 b) { return (a > b) ? a : b; }
static gI16 avg16(gI16 a, gI16 b) { return (a + b) / 2; }

gI8 mf_compute_kerning(const struct mf_font_s *font,
                          mf_char c1, mf_char c2)
{
    struct kerning_state_s leftedge, rightedge;
    gU8 w1, w2, i, min_space;
    gI16 normal_space, adjust, max_adjust;
    
    if (font->flags & MF_FONT_FLAG_MONOSPACE)
        return 0; /* No kerning for monospace fonts */
    
    if (!do_kerning(c1) || !do_kerning(c2))
        return 0;
    
    /* Compute the height of one kerning zone in pixels */
    i = (font->height + MF_KERNING_ZONES - 1) / MF_KERNING_ZONES;
    if (i < 1) i = 1;
    
    /* Initialize structures */
    leftedge.zoneheight = rightedge.zoneheight = i;
    for (i = 0; i < MF_KERNING_ZONES; i++)
    {
        leftedge.edgepos[i] = 255;
        rightedge.edgepos[i] = 0;
    }
    
    /* Analyze the edges of both glyphs. */
    w1 = mf_render_character(font, 0, 0, c1, fit_rightedge, &rightedge);
    w2 = mf_render_character(font, 0, 0, c2, fit_leftedge, &leftedge);
    
    /* Find the minimum horizontal space between the glyphs. */
    min_space = 255;
    for (i = 0; i < MF_KERNING_ZONES; i++)
    {
        gU8 space;
        if (leftedge.edgepos[i] == 255 || rightedge.edgepos[i] == 0)
            continue; /* Outside glyph area. */
        
        space = w1 - rightedge.edgepos[i] + leftedge.edgepos[i];
        if (space < min_space)
            min_space = space;
    }
    
    if (min_space == 255)
        return 0; /* One of the characters is space, or both are punctuation. */
    
    /* Compute the adjustment of the glyph position. */
    normal_space = avg16(w1, w2) * MF_KERNING_SPACE_PERCENT / 100;
    normal_space += MF_KERNING_SPACE_PIXELS;
    adjust = normal_space - min_space;
    max_adjust = -max16(w1, w2) * MF_KERNING_LIMIT / 100;
    
    if (adjust > 0) adjust = 0;
    if (adjust < max_adjust) adjust = max_adjust;
    
    return adjust;
}

#endif

#endif //MF_NO_COMPILE
