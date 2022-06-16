/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_GDISP && GDISP_NEED_TEXT

#include "mcufont/mcufont.h"

#define FONT_FLAG_DYNAMIC	0x80		// Custom flag to indicate dynamically allocated font
#define FONT_FLAG_UNLISTED	0x40		// Custom flag to indicate font is not currently listed

static const struct mf_font_list_s *fontList;

/**
 * Match a pattern against the font name.
 */
static gBool matchfont(const char *pattern, const char *name) {
	while(1) {
		switch (pattern[0]) {
		case '*':
			if (name[0] == 0)
				return pattern[1] == 0;
			if (pattern[1] == name[0])
				pattern++;
			else
				name++;
			break;
		case 0:
			return name[0] == 0;
		default:
			if (name[0] != pattern[0])
				return gFalse;
			pattern++;
			name++;
			break;
		}
	}
}

gFont gdispOpenFont(const char *name) {
	const struct mf_font_list_s *fp;
	
	if (!fontList)
		fontList = mf_get_font_list();
		
	// Try the long names first
	for(fp = fontList; fp; fp = fp->next) {
		if (matchfont(name, fp->font->full_name))
			return fp->font;
	}

	// Try the short names if no long names match
	for(fp = fontList; fp; fp = fp->next) {
		if (matchfont(name, fp->font->short_name))
			return fp->font;
	}
	
	/* Return default builtin font.. better than nothing. */
	return mf_get_font_list()->font;
}

void gdispCloseFont(gFont font) {
	if ((font->flags & (FONT_FLAG_DYNAMIC|FONT_FLAG_UNLISTED)) == (FONT_FLAG_DYNAMIC|FONT_FLAG_UNLISTED)) {
		/* Make sure that no-one can successfully use font after closing */
		((struct mf_font_s *)font)->render_character = 0;
		
		/* Release the allocated memory */
		gfxFree((void *)font);
	}
}

gFont gdispScaleFont(gFont font, gU8 scale_x, gU8 scale_y)
{
	struct mf_scaledfont_s *newfont;
	
	if (!(newfont = gfxAlloc(sizeof(struct mf_scaledfont_s))))
		return 0;
	
	mf_scale_font(newfont, font, scale_x, scale_y);
	((struct mf_font_s *)newfont)->flags |= FONT_FLAG_DYNAMIC|FONT_FLAG_UNLISTED;
	return (gFont)newfont;
}

const char *gdispGetFontName(gFont font) {
	return font->short_name;
}

gBool gdispAddFont(gFont font) {
	struct mf_font_list_s *hdr;

	if ((font->flags & (FONT_FLAG_DYNAMIC|FONT_FLAG_UNLISTED)) != (FONT_FLAG_DYNAMIC|FONT_FLAG_UNLISTED))
		return gFalse;
		
	if (!(hdr = gfxAlloc(sizeof(struct mf_font_list_s))))
		return gFalse;

	if (!fontList)
		fontList = mf_get_font_list();
	hdr->font = (const struct mf_font_s *)font;
	hdr->next = fontList;
	((struct mf_font_s *)font)->flags &= ~FONT_FLAG_UNLISTED;
	fontList = hdr;
	return gTrue;
}

#endif /* GFX_USE_GDISP && GDISP_NEED_TEXT */
