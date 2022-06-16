/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "mf_scaledfont.h"

#ifndef MF_NO_COMPILE

struct scaled_renderstate
{
    mf_pixel_callback_t orig_callback;
    void *orig_state;
    gU8 x_scale;
    gU8 y_scale;
    gI16 x0;
    gI16 y0;
};

static void scaled_pixel_callback(gI16 x, gI16 y, gU8 count,
                                  gU8 alpha, void *state)
{
    struct scaled_renderstate *rstate = state;
    gU8 dy;
    
    count *= rstate->x_scale;
    x = rstate->x0 + x * rstate->x_scale;
    y = rstate->y0 + y * rstate->y_scale;
    
    for (dy = 0; dy < rstate->y_scale; dy++)
    {
        rstate->orig_callback(x, y + dy, count, alpha, rstate->orig_state);
    }
}
    
gU8 mf_scaled_character_width(const struct mf_font_s *font,
                                      gU16 character)
{
    struct mf_scaledfont_s *sfont = (struct mf_scaledfont_s*)font;
    gU8 basewidth;
    
    basewidth = sfont->basefont->character_width(sfont->basefont, character);
    
    return sfont->x_scale * basewidth;
}

gU8 mf_scaled_render_character(const struct mf_font_s *font,
                                       gI16 x0, gI16 y0,
                                       gU16 character,
                                       mf_pixel_callback_t callback,
                                       void *state)
{
    struct mf_scaledfont_s *sfont = (struct mf_scaledfont_s*)font;
    struct scaled_renderstate rstate;
    gU8 basewidth;
    
    rstate.orig_callback = callback;
    rstate.orig_state = state;
    rstate.x_scale = sfont->x_scale;
    rstate.y_scale = sfont->y_scale;
    rstate.x0 = x0;
    rstate.y0 = y0;
    
    basewidth = sfont->basefont->render_character(sfont->basefont, 0, 0,
                            character, scaled_pixel_callback, &rstate);
    
    return sfont->x_scale * basewidth;
}

void mf_scale_font(struct mf_scaledfont_s *newfont,
                   const struct mf_font_s *basefont,
                   gU8 x_scale, gU8 y_scale)
{
    newfont->font = *basefont;
    newfont->basefont = basefont;
    
    newfont->font.width *= x_scale;
    newfont->font.height *= y_scale;
    newfont->font.baseline_x *= x_scale;
    newfont->font.baseline_y *= y_scale;
    newfont->font.min_x_advance *= x_scale;
    newfont->font.max_x_advance *= x_scale;
    newfont->font.line_height *= y_scale;
    newfont->font.character_width = &mf_scaled_character_width;
    newfont->font.render_character = &mf_scaled_render_character;
    
    newfont->x_scale = x_scale;
    newfont->y_scale = y_scale;
}

#endif //MF_NO_COMPILE
