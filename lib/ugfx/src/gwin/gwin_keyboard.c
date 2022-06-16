/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gwin/gwin_keyboard.c
 * @brief   GWIN sub-system virtual keyboard code
 */

#include "../../gfx.h"

#if GFX_USE_GWIN && GWIN_NEED_KEYBOARD

#include "gwin_class.h"
#include "gwin_keyboard_layout.h"

typedef gU8		utf8;
typedef gU16	utf16;
typedef gU32	utf32;

// A character code - note this is not UTF-32 but a representation of the UTF-8 code stream for a single character.
typedef gU32	ucode;

static GSourceHandle	AllKeyboards;

// Get the length of a UTF-8 string
static int UTF8StrLen(const utf8 *s) {
	int				len;

	len = 0;
	if (s) {
		while (*s) {
			len++;
			if (!(s[0] & 0x80))
				s++;
			else if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80)
				s+=2;
			else if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80)
				s+=3;
			else if ((s[0] & 0xF8) == 0xF0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80)
				s+=4;
			else
				// Invalid UTF-8 sequence - assume a single byte
				s++;
		}
	}
	return len;
}

// Return the nth character of a UTF8 string
static ucode UTF8CharAt(const utf8 *s, int n) {
	ucode		u;

	u = 0;
	if (!s) return 0;

	while(*s) {
		if (!(s[0] & 0x80)) {
			u = s[0];
			s++;
		} else if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80) {
			u = s[1] | ((ucode)s[0] << 8);
			s+=2;
		} else if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80) {
			u = s[2] | ((ucode)s[1] << 8) | ((ucode)s[0] << 16);
			s+=3;
		} else if ((s[0] & 0xF8) == 0xF0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80) {
			u = s[3] | ((ucode)s[2] << 8) | ((ucode)s[1] << 16) | ((ucode)s[0] << 24);
			s+=4;
		} else {
			// Invalid UTF-8 sequence - assume a single byte
			u = s[0];
			s++;
		}
		if (--n < 0)
			return u;
	}
	return 0;
}

// Convert a ucode to a UTF8 string (with no NULL on the end). Returns the number of bytes.
static unsigned UCode2UTF8(utf8 *dst, ucode u) {
	if (!(u & 0xFFFFFF00)) {
		dst[0] = u;
		return 1;
	}
	if (!(u & 0xFFFF0000)) {
		dst[0] = u >> 8;
		dst[1] = u;
		return 2;
	}
	if (!(u & 0xFF000000)) {
		dst[0] = u >> 16;
		dst[1] = u >> 8;
		dst[2] = u;
		return 3;
	}
	dst[0] = u >> 24;
	dst[1] = u >> 16;
	dst[2] = u >> 8;
	dst[3] = u;
	return 4;
}

static int NumKeyRows(const char **keyset) {
	int				len;

	len = 0;
	while(*keyset++)
		len++;
	return len;
}

static void SendVirtualKeyEventToListener(GSourceListener	*psl, GKeyboardObject *gk) {
	GEventKeyboard		*pe;
	const GVSpecialKey	*skey;
	unsigned			i;

	// If there is no event buffer just mark a missed event
	if (!(pe = (GEventKeyboard *)geventGetEventBuffer(psl))) {
		// This listener is missing - save the meta events that have happened
		psl->srcflags |= GKEYSTATE_MISSED_EVENT;
		return;
	}

	// The virtual keyboard can't generate repeats
	//if ((psl->listenflags & GLISTEN_KEYREPEATSOFF) && (k->keystate & GKEYSTATE_REPEAT))
	//	return;

	// The virtual keyboard can't generate special keys
	//if ((psl->listenflags & GLISTEN_KEYNOSPECIALS) && (k->keystate & GKEYSTATE_SPECIAL))
	//	return;

	// The virtual keyboard treats a key release as a keydown
	//if (!(psl->listenflags & GLISTEN_KEYUP) && (k->keystate & GKEYSTATE_KEYUP))
	//	k->cntc = 0;

	// The virtual keyboard has no transitions
	//if (!(psl->listenflags & GLISTEN_KEYTRANSITIONS) && !k->cntc)
	//	return;

	pe->type = GEVENT_KEYBOARD;
	if (gk->key < 0x20) {
		skey = &gk->keytable->skeys[gk->key-1];
		for(i=0; skey->sendkey[i]; i++)
			pe->c[i] = skey->sendkey[i];
	} else
		i = UCode2UTF8((utf8 *)pe->c, gk->key);
	pe->bytecount = i;
	for(; i < 8; i++)
		pe->c[i] = 0;
	pe->keystate = psl->srcflags;
	psl->srcflags = 0;
	geventSendEvent(psl);
}

static void SendVirtualKeyEvent(GKeyboardObject *gk) {
	GSourceListener	*psl;

	// Send to the "All Keyboards" source listeners
	psl = 0;
	while ((psl = geventGetSourceListener(AllKeyboards, psl)))
		SendVirtualKeyEventToListener(psl, gk);

	// Send to the keyboard specific source listeners
	psl = 0;
	while ((psl = geventGetSourceListener((GSourceHandle)gk, psl)))
		SendVirtualKeyEventToListener(psl, gk);
}


#if GINPUT_NEED_MOUSE
	// Find the key from the keyset and the x, y position
	static void KeyFindKey(GKeyboardObject *gk, gCoord x, gCoord y) {
		const utf8		*krow;
		fixed			f;
		int				idx;

		if (x < 0 || y < 0 || x >= gk->w.g.width || y >= gk->w.g.height) {
			gk->keyrow = gk->keycol = GKEY_BAD_ROWCOL;
			return;
		}

		// Get the y parameters
		f = FIXED(gk->w.g.height) / NumKeyRows(gk->keyset);
		gk->keyrow = FIXED(y) / f;
		gk->keyy = NONFIXED(f * gk->keyrow + FIXED0_5);
		gk->keycy = NONFIXED(f * (gk->keyrow+1) + FIXED0_5) - gk->keyy;

		// Get the current row
		krow = (const utf8 *)gk->keyset[gk->keyrow];

		// Get the x parameters
		f = FIXED(gk->w.g.width) / UTF8StrLen(krow);
		gk->keycol = FIXED(x) / f;

		// Get the key
		gk->key = UTF8CharAt(krow, gk->keycol);

		// Amalgamate identical keys into one big key
		idx = gk->keycol;
		while(gk->keycol > 0 && UTF8CharAt(krow, gk->keycol-1) == gk->key)
			gk->keycol--;
		while(UTF8CharAt(krow, ++idx) == gk->key);
		gk->keyx = NONFIXED(f * gk->keycol + FIXED0_5);
		gk->keycx = NONFIXED(f * idx + FIXED0_5) - gk->keyx;
	}

	// A mouse up has occurred (it may or may not be over the button)
	static void KeyMouseUp(GWidgetObject *gw, gCoord x, gCoord y) {
		#define gk		((GKeyboardObject *)gw)

		KeyFindKey(gk, x, y);

		// Do we have a valid key?
		if (gk->keyrow == GKEY_BAD_ROWCOL) {
			if (gk->lastkeyrow != GKEY_BAD_ROWCOL) {
				gw->g.flags |= GKEYBOARD_FLG_QUICKUPDATE;
				_gwinUpdate((GHandle)gw);
			}
			return;
		}

		// We are turning off the display of the key
		gk->keyrow = gk->keycol = GKEY_BAD_ROWCOL;

		// Is this one of the special keys
		if (gk->key < 0x20) {
			// This is a special key
			const GVSpecialKey	*skey;

			skey = &gk->keytable->skeys[gk->key - 1];

			if ((skey->flags & GVKEY_SINGLESET)) {
				// Single character switch to a new layout
				gk->keyset = gk->keytable->ksets[skey->newset];
				gk->w.g.flags &= ~(GKEYBOARD_FLG_QUICKUPDATE|GKEYBOARD_FLG_REVERTSET);
				gk->w.g.flags |= GKEYBOARD_FLG_REVERTSET;

			} else if ((skey->flags & GVKEY_LOCKSET)) {
				// Locked switch to a new layout
				gk->keyset = gk->keytable->ksets[skey->newset];
				gk->w.g.flags &= ~(GKEYBOARD_FLG_QUICKUPDATE|GKEYBOARD_FLG_REVERTSET);

			} else if ((gk->w.g.flags & GKEYBOARD_FLG_REVERTSET)) {
				// Revert to default layout
				gk->keyset = gk->keytable->ksets[0];
				gk->w.g.flags &= ~(GKEYBOARD_FLG_QUICKUPDATE|GKEYBOARD_FLG_REVERTSET);

			} else {
				// Just turning off a key
				gw->g.flags |= GKEYBOARD_FLG_QUICKUPDATE;
			}

			// Send the key if required
			if (skey->sendkey && skey->sendkey[0])
				SendVirtualKeyEvent(gk);

			// Update the display
			_gwinUpdate((GHandle)gw);

			return;
		}

		// Do we need to revert to the standard layout?
		if ((gk->w.g.flags & GKEYBOARD_FLG_REVERTSET)) {
			gk->keyset = gk->keytable->ksets[0];
			gk->w.g.flags &= ~(GKEYBOARD_FLG_QUICKUPDATE|GKEYBOARD_FLG_REVERTSET);
		} else {
			gw->g.flags |= GKEYBOARD_FLG_QUICKUPDATE;
		}

		// Send the key
		SendVirtualKeyEvent(gk);

		// Update the display
		_gwinUpdate((GHandle)gw);
	}

	// A mouse move has occurred (it may or may not be over the button)
	static void KeyMouseMove(GWidgetObject *gw, gCoord x, gCoord y) {
		#define gk		((GKeyboardObject *)gw)

		KeyFindKey(gk, x, y);

		if (gk->keyrow != gk->lastkeyrow || gk->keycol != gk->lastkeycol) {
			gk->w.g.flags |= GKEYBOARD_FLG_QUICKUPDATE;
			_gwinUpdate((GHandle)gw);
		}
		#undef gk
	}
#endif

extern const GVKeyTable GWIN_KEYBOARD_DEFAULT_LAYOUT;

// The button VMT table
static const gwidgetVMT keyboardVMT = {
	{
		"VKeyboard",				// The classname
		sizeof(GKeyboardObject),	// The object size
		_gwidgetDestroy,			// The destroy routine
		_gwidgetRedraw,				// The redraw routine
		0,							// The after-clear routine
	},
	gwinKeyboardDraw_Normal,		// The default drawing routine
	#if GINPUT_NEED_MOUSE
		{
			KeyMouseMove,			// Process mouse down events
			KeyMouseUp,				// Process mouse up events
			KeyMouseMove,			// Process mouse move events
		},
	#endif
	#if GINPUT_NEED_KEYBOARD || GWIN_NEED_KEYBOARD
		{
			0						// Process keyboard events
		},
	#endif
	#if GINPUT_NEED_TOGGLE
		{
			0,						// No toggle roles
			0,						// Assign Toggles
			0,						// Get Toggles
			0,						// Process toggle off events
			0,						// Process toggle on events
		},
	#endif
	#if GINPUT_NEED_DIAL
		{
			0,						// No dial roles
			0,						// Assign Dials (NOT USED)
			0,						// Get Dials (NOT USED)
			0,						// Process dial move events (NOT USED)
		},
	#endif
};

GHandle gwinGKeyboardCreate(GDisplay *g, GKeyboardObject *gk, const GWidgetInit *pInit) {
	if (!(gk = (GKeyboardObject *)_gwidgetCreate(g, &gk->w, pInit, &keyboardVMT)))
		return 0;

	gk->keytable = &GWIN_KEYBOARD_DEFAULT_LAYOUT;
	gk->keyset = gk->keytable->ksets[0];
	gk->lastkeyrow = gk->lastkeycol = gk->keyrow = gk->keycol = GKEY_BAD_ROWCOL;

	if (!AllKeyboards)
		AllKeyboards = ginputGetKeyboard(GKEYBOARD_ALL_INSTANCES);

	gwinSetVisible((GHandle)gk, pInit->g.show);
	return (GHandle)gk;
}

GSourceHandle gwinKeyboardGetEventSource(GHandle gh) {
	if (gh->vmt != (gwinVMT *)&keyboardVMT)
		return 0;
	return (GSourceHandle)gh;
}

void gwinKeyboardSetLayout(GHandle gh, const struct GVKeyTable *layout) {
	#define gk		((GKeyboardObject *)gh)

	if (gh->vmt != (gwinVMT *)&keyboardVMT)
		return;

	if (!layout)
		layout = &GWIN_KEYBOARD_DEFAULT_LAYOUT;
	gk->keytable = layout;
	gk->keyset = gk->keytable->ksets[0];
	gk->lastkeyrow = gk->lastkeycol = gk->keyrow = gk->keycol = GKEY_BAD_ROWCOL;
	gk->w.g.flags &= ~(GKEYBOARD_FLG_QUICKUPDATE|GKEYBOARD_FLG_REVERTSET);
	gwinRedraw(gh);
	#undef gk
}

/*----------------------------------------------------------
 * Custom Draw Routines
 *----------------------------------------------------------*/

/*
static const GColorSet *getDrawColors(GWidgetObject *gw) {
	if (!(gw->g.flags & GWIN_FLG_SYSENABLED))	return &gw->pstyle->disabled;
	if ((gw->g.flags & GBUTTON_FLG_PRESSED))	return &gw->pstyle->pressed;
	return &gw->pstyle->enabled;
}
*/

void gwinKeyboardDraw_Normal(GWidgetObject *gw, void *param) {
	#define gk ((GKeyboardObject *)gw)

	char cap[5];
	const char *pcap;
	const utf8 *krow;
	gCoord x, y, cx, cy;
	gU8 rows, cols, row, col, kcols;
	ucode key;
	fixed fx, fy;
	const GColorSet *pcol;

	(void) param;

	// Make sure that this is a keyboard widget object
	if (gw->g.vmt != (gwinVMT *)&keyboardVMT)
		return;

	// Get the y parameters
	rows = NumKeyRows(gk->keyset);
	fy = FIXED(gk->w.g.height) / rows;
	for (row = 0; row < rows; row++) {
		y = NONFIXED(fy * row + FIXED0_5);
		cy = NONFIXED(fy * (row+1) + FIXED0_5) - y;

		// Get the current row
		krow = (const utf8 *)gk->keyset[row];

		// Get the x parameters
		cols = UTF8StrLen(krow);
		fx = FIXED(gk->w.g.width) / cols;
		for (col = 0; col < cols; col=kcols) {

			// Get the correct color set
			if (!(gk->w.g.flags & GWIN_FLG_SYSENABLED))
					pcol = &gk->w.pstyle->disabled;
			else 
				pcol = &gk->w.pstyle->enabled;
        	 
			// Get the key
			key = UTF8CharAt(krow, col);
	
			// Fuse identical keys into one big key
			kcols = col+1;
			while (UTF8CharAt(krow, kcols) == key)
				kcols++;
        	 
			// If quick update needed and keyboard already drawn (if not use this flag, then bug when screen touched before keyboard was drawn)
			if ( (gk->w.g.flags & GKEYBOARD_FLG_QUICKUPDATE) && !(gk->w.g.flags & GWIN_FLG_BGREDRAW) )  {

				// If key pressed
				if ( (gk->keyrow != GKEY_BAD_ROWCOL) && (gk->keycol != GKEY_BAD_ROWCOL) ) {

					// And previous key have
					if ( (gk->lastkeyrow != GKEY_BAD_ROWCOL) && (gk->lastkeycol != GKEY_BAD_ROWCOL) ) {
						
						if (gk->lastkeyrow == row && gk->lastkeycol == col) {
							// If keyboard has no "disabled" color
							if (pcol != &gk->w.pstyle->disabled)
								pcol = &gk->w.pstyle->enabled;
							gk->lastkeyrow = gk->lastkeycol = GKEY_BAD_ROWCOL;
						} else {
							continue;
						}
					}

					// If no previous key
					else {

						if (gk->keyrow == row && gk->keycol == col) {
							if (pcol != &gk->w.pstyle->disabled)
								pcol = &gk->w.pstyle->pressed;
							gk->lastkeyrow = row;
							gk->lastkeycol = col;
						}
						else if (gk->lastkeyrow == row && gk->lastkeycol == col)
						{
							if (pcol != &gk->w.pstyle->disabled) pcol = &gk->w.pstyle->enabled;
						}
						else continue;
					}
				}

				// If key up, and need clear the previous key
				else if ( (gk->lastkeyrow != GKEY_BAD_ROWCOL) && (gk->lastkeycol != GKEY_BAD_ROWCOL) )
				{
					if ( (gk->lastkeyrow == row) && (gk->lastkeycol == col) )
					{
						if (pcol != &gk->w.pstyle->disabled) pcol = &gk->w.pstyle->enabled;
					}
					else continue;
				}
			}                  
			else
			{
				gk->lastkeyrow = gk->lastkeycol = GKEY_BAD_ROWCOL;
			}

			x = NONFIXED(fx * col + FIXED0_5);
			cx = NONFIXED(fx * kcols + FIXED0_5) - x;
			
			if (key < 0x20) {
				pcap = gk->keytable->skeys[key-1].keycap;
			} else {
				cap[UCode2UTF8((utf8 *)cap, key)] = 0;
				pcap = cap;
			}
			
			switch(*pcap) {

			case  '\001':	// Shift (up-arrow)
				gdispGFillArea(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcol->fill);

				gdispGDrawLine(gw->g.display, gw->g.x+x    +cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2, gw->g.y+y +cy/4, pcol->text);               /*    / \    */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx -cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2, gw->g.y+y +cy/4, pcol->text); 
				gdispGDrawLine(gw->g.display, gw->g.x+x    +cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy/2, pcol->text);           /*    _ _    */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx -cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy/2, pcol->text);
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy/2, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy -cy/3, pcol->text);      /*    ||     */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy/2, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy -cy/3, pcol->text);
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy -cy/3, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy -cy/3, pcol->text);  /*    _      */

				break;

			case '\002':	// Shift locked (underlined up-arrow)
				gdispGFillArea(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcol->fill);

				gdispGDrawLine(gw->g.display, gw->g.x+x    +cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2, gw->g.y+y +cy/4, pcol->text);               /*   / \     */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx -cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2, gw->g.y+y +cy/4, pcol->text);    
				gdispGDrawLine(gw->g.display, gw->g.x+x    +cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy/2, pcol->text);           /*   _ _     */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx -cx/4, gw->g.y+y+cy/2, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy/2, pcol->text);
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy/2, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy -cy/3, pcol->text);      /*    ||     */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy/2, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy -cy/3, pcol->text);
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2-cx/6, gw->g.y+y+cy -cy/3, gw->g.x+x+cx/2+cx/6, gw->g.y+y+cy -cy/3, pcol->text);  /*     _     */
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx/2-cx/5, gw->g.y+y+cy -cy/4, gw->g.x+x+cx/2+cx/5, gw->g.y+y+cy -cy/4, pcol->text);  /*    ___    */

				break;

			case '\t':	// Tabulator
				gdispGFillArea(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcol->fill);

				gdispGDrawLine(gw->g.display, gw->g.x+x+1, gw->g.y+y+1, gw->g.x+x+cx-1, gw->g.y+y+cy/2, pcol->text);
				gdispGDrawLine(gw->g.display, gw->g.x+x+1, gw->g.y+y+cy-1, gw->g.x+x+cx-1, gw->g.y+y+cy/2, pcol->text);
				gdispGDrawLine(gw->g.display, gw->g.x+x+cx-1, gw->g.y+y+1, gw->g.x+x+cx-1, gw->g.y+y+cy-1, pcol->text);

				break;

			case '\b': // Backspace
				gdispGFillArea(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcol->fill);

				gdispGDrawLine(gw->g.display, gw->g.x+x+ cx/8, gw->g.y+y+cy/2, gw->g.x+x+cx/2, gw->g.y+y    +cy/3, pcol->text);               /* /      */
				gdispGDrawLine(gw->g.display, gw->g.x+x+ cx/8, gw->g.y+y+cy/2, gw->g.x+x+cx-cx/8, gw->g.y+y+cy/2, pcol->text);                /*  --    */
				gdispGDrawLine(gw->g.display, gw->g.x+x+ cx/8, gw->g.y+y+cy/2, gw->g.x+x+cx/2, gw->g.y+y+cy -cy/3, pcol->text);               /* \      */

				break;

			case '\r': // Enter
				gdispGFillArea(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcol->fill);

				gdispGDrawLine(gw->g.display, gw->g.x+x+(cx/3)*2, gw->g.y+y+cy/2, gw->g.x+x+(cx/3)*2, gw->g.y+y+cy/5, pcol->text);            /*      | */
				gdispGDrawLine(gw->g.display, gw->g.x+x+ cx/3, gw->g.y+y+cy/2, gw->g.x+x+cx/3 +cx/8, gw->g.y+y+cy/3, pcol->text);             /* /      */
				gdispGDrawLine(gw->g.display, gw->g.x+x+ cx/3, gw->g.y+y+cy/2, gw->g.x+x+(cx/3)*2, gw->g.y+y+cy/2, pcol->text);               /*  --    */
				gdispGDrawLine(gw->g.display, gw->g.x+x+ cx/3, gw->g.y+y+cy/2, gw->g.x+x+cx/3 +cx/8, gw->g.y+y+cy -cy/3, pcol->text);         /* \      */

				break;

			default:   // Regular character
				gdispGFillStringBox(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcap, gw->g.font, pcol->text, pcol->fill, gJustifyCenter);
				
				break;
			}
			
			// Draw the frame (border around the entire widget)
			gdispGDrawBox(gw->g.display, gw->g.x+x, gw->g.y+y, cx, cy, pcol->edge);
			
			// If key up and we already cleared the previous key
			if ( (gk->keyrow == GKEY_BAD_ROWCOL) && (gk->keycol == GKEY_BAD_ROWCOL) && (gk->lastkeyrow == row) && (gk->lastkeycol == col) ) {
			   gk->lastkeyrow = gk->lastkeycol = GKEY_BAD_ROWCOL;
			   return;
			}

			// Just quit the cycle if we did all the work in order not to waste any CPU time
			if ( (row >= gk->keyrow && col >= gk->keycol) && (row >= gk->lastkeyrow && col >= gk->lastkeycol) ) {
				return;
			}
		}
	}

	#undef gk
}

#if !(GFX_USE_GINPUT && GINPUT_NEED_KEYBOARD)
	GSourceHandle ginputGetKeyboard(unsigned instance) {
		if (instance == GKEYBOARD_ALL_INSTANCES)
			return (GSourceHandle)&AllKeyboards;
		return 0;
	}
#endif

#endif /* GFX_USE_GWIN && GWIN_NEED_KEYBOARD */
