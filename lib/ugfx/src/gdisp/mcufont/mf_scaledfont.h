/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* Generate scaled (nearest-neighbor) fonts. This can be used for displaying
 * larger text without spending the memory required for including larger fonts.
 */

#ifndef _MF_SCALEDFONT_H_
#define _MF_SCALEDFONT_H_

#include "mf_font.h"

struct mf_scaledfont_s
{
    struct mf_font_s font;
    
    const struct mf_font_s *basefont;
    gU8 x_scale;
    gU8 y_scale;
};

MF_EXTERN void mf_scale_font(struct mf_scaledfont_s *newfont,
                             const struct mf_font_s *basefont,
                             gU8 x_scale, gU8 y_scale);

#ifdef MF_SCALEDFONT_INTERNALS
/* Internal functions, don't use these directly. */
MF_EXTERN gU8 mf_scaled_render_character(const struct mf_font_s *font,
                                              gI16 x0, gI16 y0,
                                              gU16 character,
                                              mf_pixel_callback_t callback,
                                              void *state);

MF_EXTERN gU8 mf_scaled_character_width(const struct mf_font_s *font,
                                             gU16 character);
#endif

#endif
