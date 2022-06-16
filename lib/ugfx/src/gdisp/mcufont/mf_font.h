/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* Generic font type that supports fonts with multiple kinds of compression.
 * Provides an interface for decoding and rendering single characters.
 */

#ifndef _MF_FONT_H_
#define _MF_FONT_H_

#include "mf_encoding.h"

/* Callback function that writes pixels to screen / buffer / whatever.
 *
 * x:     X coordinate of the first pixel to write.
 * y:     Y coordinate of the first pixel to write.
 * count: Number of pixels to fill (horizontally).
 * alpha: The "opaqueness" of the pixels, 0 for background, 255 for text.
 * state: Free variable that was passed to render_character().
 */
typedef void (*mf_pixel_callback_t) (gI16 x, gI16 y, gU8 count,
                                     gU8 alpha, void *state);

/* General information about a font. */
struct mf_font_s
{
    /* Full name of the font, comes from the original font file. */
    const char *full_name;

    /* Short name of the font, comes from file name. */
    const char *short_name;

    /* Width and height of the character bounding box. */
    gU8 width;
    gU8 height;

    /* Minimum and maximum tracking width of characters. */
    gU8 min_x_advance;
    gU8 max_x_advance;

    /* Location of the text baseline relative to character. */
    gI8 baseline_x;
    gU8 baseline_y;

    /* Line height of the font (vertical advance). */
    gU8 line_height;

    /* Flags identifying various aspects of the font. */
    gU8 flags;

    /* Fallback character to use for missing glyphs. */
    gU16 fallback_character;

    /* Function to get character width. Should return 0 if character is
     * not found. */
    gU8 (*character_width)(const struct mf_font_s *font, gU16 character);

    /* Function to render a character. Returns the character width or 0 if
     * character is not found. */
    gU8 (*render_character)(const struct mf_font_s *font,
                                gI16 x0, gI16 y0,
                                gU16 character,
                                mf_pixel_callback_t callback,
                                void *state);
};

/* The flag definitions for the font.flags field. */
#define MF_FONT_FLAG_MONOSPACE 0x01
#define MF_FONT_FLAG_BW        0x02

/* Lookup structure for searching fonts by name. */
struct mf_font_list_s
{
    const struct mf_font_list_s *next;
    const struct mf_font_s *font;
};


/* Function to decode and render a single character.
 *
 * font:      Pointer to the font definition.
 * x0, y0:    Upper left corner of the target area.
 * character: The character code (unicode) to render.
 * callback:  Callback function to write out the pixels.
 * state:     Free variable for caller to use (can be NULL).
 *
 * Returns width of the character.
 */
MF_EXTERN gU8 mf_render_character(const struct mf_font_s *font,
                                      gI16 x0, gI16 y0,
                                      mf_char character,
                                      mf_pixel_callback_t callback,
                                      void *state);

/* Function to get the width of a single character.
 * This is not necessarily the bounding box of the character
 * data, but rather the tracking width.
 *
 * font:      Pointer to the font definition.
 * character: The character code (unicode) to render.
 *
 * Returns width of the character in pixels.
 */
MF_EXTERN gU8 mf_character_width(const struct mf_font_s *font,
                                     mf_char character);

/* Find a font based on name. The name can be either short name or full name.
 * Note: You can pass MF_INCLUDED_FONTS to search among all the included .h
 * files.
 *
 * name: Font name to search for.
 * fonts: Pointer to the first font search entry.
 *
 * Returns a pointer to the font or NULL if not found.
 */
MF_EXTERN const struct mf_font_s *mf_find_font(const char *name);

/* Get the list of included fonts */
MF_EXTERN const struct mf_font_list_s *mf_get_font_list(void);

#endif
