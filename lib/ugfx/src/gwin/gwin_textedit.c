/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file	src/gwin/gwin_textedit.c
 * @brief	GWIN TextEdit widget header file
 */

#include "../../gfx.h"

#if GFX_USE_GWIN && GWIN_NEED_TEXTEDIT

#include "gwin_class.h"
#include <string.h>

// Some settings
#define TEXT_PADDING_LEFT		4
#define CURSOR_PADDING_LEFT		0
#define CURSOR_EXTRA_HEIGHT		1

// Macros to assist in data type conversions
#define gh2obj ((GTexteditObject *)gh)
#define gw2obj ((GTexteditObject *)gw)

static void TextEditRemoveChar(GHandle gh) {
	char		*p;
	const char	*q;
	unsigned	sz;
	unsigned	pos;

	sz = strlen(gh2obj->w.text);
	pos = gh2obj->cursorPos;
	if (pos > sz)
		pos = gh2obj->cursorPos = sz;
	q = gh2obj->w.text+pos;
	
	if (!(gh->flags & GWIN_FLG_ALLOCTXT)) {
		// Allocate and then copy
		if (!(p = gfxAlloc(sz)))
			return;
		if (pos)
			memcpy(p, gh2obj->w.text, pos);
		memcpy(p+pos, q+1, sz-pos);
		gh->flags |= GWIN_FLG_ALLOCTXT;
	} else {
		// Copy and then reallocate
		memcpy((char *)q, q+1, sz-pos);
		if (!(p = gfxRealloc((char *)gh2obj->w.text, sz+1, sz)))		// This should never fail as we are making it smaller
			return;
	}
	gh2obj->w.text = p;
}

static gBool TextEditAddChars(GHandle gh, unsigned cnt) {
	char		*p;
	const char	*q;
	unsigned	sz;
	unsigned	pos;

	// Get the size of the text buffer
	sz = strlen(gh2obj->w.text)+1;
	pos = gh2obj->cursorPos;
	if (pos >= sz)
		pos = gh2obj->cursorPos = sz-1;

	if (!(gh->flags & GWIN_FLG_ALLOCTXT)) {
		if (!(p = gfxAlloc(sz+cnt)))
			return gFalse;
		memcpy(p, gh2obj->w.text, pos);
		memcpy(p+pos+cnt, gh2obj->w.text+pos, sz-pos);
		gh->flags |= GWIN_FLG_ALLOCTXT;
		gh2obj->w.text = p;
	} else {
		if (!(p = gfxRealloc((char *)gh2obj->w.text, sz, sz+cnt)))
			return gFalse;
		gh2obj->w.text = p;
		q = p+pos;
		p += sz;
		while(--p >= q)
			p[cnt] = p[0];
	}
	return gTrue;
}

// Function that allows to set the cursor to any position in the string
// This should be optimized. Currently it is an O(n^2) problem and therefore very
// slow. An optimized version would copy the behavior of mf_get_string_width()
// and do the comparation directly inside of that loop so we only iterate
// the string once.
static void TextEditMouseDown(GWidgetObject* gw, gCoord x, gCoord y) {
	gU16 i = 0;

	(void)y;

	// Directly jump to the end of the string
	if (x > gdispGetStringWidth(gw->text, gw->g.font)) {
		gw2obj->cursorPos = strlen(gw->text);

	// Otherwise iterate through each character and get the size in pixels to compare
	} else {
		i = 1;
		while (gdispGetStringWidthCount(gw->text, gw->g.font, i) < x) {
			i++;
		}

		gw2obj->cursorPos = i-1;
	}

	_gwinUpdate((GHandle)gw);
}

#if (GFX_USE_GINPUT && GINPUT_NEED_KEYBOARD) || GWIN_NEED_KEYBOARD
	static void TextEditKeyboard(GWidgetObject* gw, GEventKeyboard* pke) {
		// Only react on KEYDOWN events. Ignore KEYUP events.
		if ((pke->keystate & GKEYSTATE_KEYUP) || !pke->bytecount)
			return;

		// Is it a special key?
		if (pke->keystate & GKEYSTATE_SPECIAL) {
			// Arrow keys to move the cursor
			gwinTextEditSendSpecialKey(&gw->g, (gU8)pke->c[0]);
			return;

		}

		gwinTextEditSendKey(&gw->g, pke->c, pke->bytecount);
	}
#endif

static const gwidgetVMT texteditVMT = {
	{
		"TextEdit",					// The class name
		sizeof(GTexteditObject),	// The object size
		_gwidgetDestroy,			// The destroy routine
		_gwidgetRedraw, 			// The redraw routine
		0,							// The after-clear routine
	},
	gwinTexteditDefaultDraw,		// default drawing routine
	#if GINPUT_NEED_MOUSE
		{
			TextEditMouseDown,		// Process mouse down events (NOT USED)
			0,						// Process mouse up events (NOT USED)
			0,						// Process mouse move events (NOT USED)
		},
	#endif
	#if (GFX_USE_GINPUT && GINPUT_NEED_KEYBOARD) || GWIN_NEED_KEYBOARD
		{
			TextEditKeyboard		// Process keyboard key down events
		},
	#endif
	#if GINPUT_NEED_TOGGLE
		{
			0,						// No toggle role
			0,						// Assign Toggles (NOT USED)
			0,						// Get Toggles (NOT USED)
			0,						// Process toggle off event (NOT USED)
			0,						// Process toggle on event (NOT USED)
		},
	#endif
	#if GINPUT_NEED_DIAL
		{
			0,						// No dial roles
			0,						// Assign Dials (NOT USED)
			0, 						// Get Dials (NOT USED)
			0,						// Procees dial move events (NOT USED)
		},
	#endif
};

GHandle gwinGTexteditCreate(GDisplay* g, GTexteditObject* wt, GWidgetInit* pInit, gMemSize maxSize)
{
	// Create the underlying widget
	if (!(wt = (GTexteditObject*)_gwidgetCreate(g, &wt->w, pInit, &texteditVMT)))
		return 0;

	wt->maxSize = maxSize;

	// Set cursor position
	wt->cursorPos = strlen(wt->w.text);

	gwinSetVisible(&wt->w.g, pInit->g.show);

	return (GHandle)wt;
}

#if (GFX_USE_GINPUT && GINPUT_NEED_KEYBOARD) || GWIN_NEED_KEYBOARD
	void gwinTextEditSendSpecialKey(GHandle gh, gU8 key) {
		unsigned sz;

 		// Is it a valid handle?
 		if (gh->vmt != (gwinVMT*)&texteditVMT)
 			return;
 
		// Check that cursor position is within buffer (in case text has been changed)
		sz = strlen(gh2obj->w.text);
		if (gh2obj->cursorPos > sz)
			gh2obj->cursorPos = sz;

		// Arrow keys to move the cursor
		switch (key) {
		case GKEY_LEFT:
			if (!gh2obj->cursorPos)
				return;
			gh2obj->cursorPos--;
			break;
		case GKEY_RIGHT:
			if (!gh2obj->w.text[gh2obj->cursorPos])
				return;
			gh2obj->cursorPos++;
			break;
		case GKEY_HOME:
			if (!gh2obj->cursorPos)
				return;
			gh2obj->cursorPos = 0;
			break;
		case GKEY_END:
			if (!gh2obj->w.text[gh2obj->cursorPos])
				return;
			gh2obj->cursorPos = sz;
			break;
		default:
			return;
		}

		_gwinUpdate(gh);
	}

	void gwinTextEditSendKey(GHandle gh, char *key, unsigned len) {
		// Is it a valid handle?
		if (gh->vmt != (gwinVMT*)&texteditVMT || !key || !len)
			return;

		// Normal key press
		switch((gU8)key[0]) {
		case GKEY_BACKSPACE:
			// Backspace
			if (!gh2obj->cursorPos)
				return;
			gh2obj->cursorPos--;
			TextEditRemoveChar(gh);
			break;
		case GKEY_TAB:
		case GKEY_LF:
		case GKEY_CR:
			// Move to the next field
			_gwinMoveFocus();
			return;
		case GKEY_DEL:
			// Delete
			if (!gh2obj->w.text[gh2obj->cursorPos])
				return;
			TextEditRemoveChar(gh);
			break;
		default:
			// Ignore any other control characters
			if ((gU8)key[0] < GKEY_SPACE)
				return;

			// Keep the edit length to less than the maximum
			if (gh2obj->maxSize && strlen(gh2obj->w.text)+len > gh2obj->maxSize)
				return;

			// Make space
			if (TextEditAddChars(gh, len)) {
				// Insert the characters
				memcpy((char *)gh2obj->w.text+gh2obj->cursorPos, key, len);
				gh2obj->cursorPos += len;
			}
			break;
		}

		_gwinUpdate(gh);
	}
#endif

void gwinTexteditDefaultDraw(GWidgetObject* gw, void* param)
{
	const char*			p;
	gCoord				cpos, tpos;
	const GColorSet*	pcol;

	(void)param;

	// Is it a valid handle?
	if (gw->g.vmt != (gwinVMT*)&texteditVMT)
		return;

	// Retrieve colors
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	// Adjust the text position so the cursor fits in the window
	p = gw->text;
	if (!gw2obj->cursorPos)
		tpos = 0;
	else {
		for(cpos = gw2obj->cursorPos; ; p++, cpos--) {
			tpos = gdispGetStringWidthCount(p, gw->g.font, cpos);
			if (tpos < gw->g.width-(TEXT_PADDING_LEFT+CURSOR_PADDING_LEFT))
				break;
		}
	}

	// Render background and string
	#if TEXT_PADDING_LEFT
		gdispGFillArea(gw->g.display, gw->g.x, gw->g.y, TEXT_PADDING_LEFT, gw->g.height, pcol->fill);
	#endif
	gdispGFillStringBox(gw->g.display, gw->g.x + TEXT_PADDING_LEFT, gw->g.y, gw->g.width-TEXT_PADDING_LEFT, gw->g.height, p, gw->g.font, pcol->text, pcol->fill, gJustifyLeft);

	// Render cursor (if focused)
	if (gwinGetFocus() == (GHandle)gw) {
		// Calculate cursor stuff

		// Draw cursor
		tpos += gw->g.x + CURSOR_PADDING_LEFT + TEXT_PADDING_LEFT + gdispGetFontMetric(gw->g.font, gFontBaselineX)/2;
		cpos = (gw->g.height - gdispGetFontMetric(gw->g.font, gFontHeight))/2 - CURSOR_EXTRA_HEIGHT;
		gdispGDrawLine(gw->g.display, tpos, gw->g.y + cpos, tpos, gw->g.y + gw->g.height - cpos, pcol->edge);
	}

	// Render border
	gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, pcol->edge);

	// Render highlighted border if focused
	_gwidgetDrawFocusRect(gw, 0, 0, gw->g.width, gw->g.height);

}

#undef gh2obj
#undef gw2obj

#endif // GFX_USE_GWIN && GWIN_NEED_TEXTEDIT
