/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gwin/gwin_console.c
 * @brief   GWIN sub-system console code.
 */

#include "../../gfx.h"

#if GFX_USE_GWIN && GWIN_NEED_CONSOLE

#include <string.h>

#include "gwin_class.h"

#define GWIN_CONSOLE_USE_CLEAR_LINES			GFXON			// Clear each line before using it
#define GWIN_CONSOLE_USE_FILLED_CHARS			GFXOFF			// Use filled characters instead of drawn characters
#define GWIN_CONSOLE_BUFFER_SCROLLING			GFXON			// Use the history buffer to scroll when it is available

// Our control flags
#define GCONSOLE_FLG_NOSTORE					(GWIN_FIRST_CONTROL_FLAG<<0)
#define GCONSOLE_FLG_OVERRUN					(GWIN_FIRST_CONTROL_FLAG<<1)

// Meaning of our attribute bits.
#define	ESC_REDBIT		0x01
#define	ESC_GREENBIT	0x02
#define	ESC_BLUEBIT		0x04
#define ESC_USECOLOR	0x08
#define ESC_UNDERLINE	0x10
#define ESC_BOLD		0x20

/*
 * Stream interface implementation. The interface is write only
 */

#if GFX_USE_OS_CHIBIOS && GWIN_CONSOLE_USE_BASESTREAM
	#define Stream2GWindow(ip)		((GHandle)(((char *)(ip)) - (size_t)(&(((GConsoleObject *)0)->stream))))

#if CH_KERNEL_MAJOR == 2
	static size_t GWinStreamWrite(void *ip, const gU8 *bp, size_t n) { gwinPutCharArray(Stream2GWindow(ip), (const char *)bp, n); return RDY_OK; }
	static size_t GWinStreamRead(void *ip, gU8 *bp, size_t n) {	(void)ip; (void)bp; (void)n; return 0; }
	static msg_t GWinStreamPut(void *ip, gU8 b) { gwinPutChar(Stream2GWindow(ip), (char)b); return RDY_OK; }
	static msg_t GWinStreamGet(void *ip) {(void)ip; return RDY_OK; }
	static msg_t GWinStreamPutTimed(void *ip, gU8 b, systime_t time) { (void)time; gwinPutChar(Stream2GWindow(ip), (char)b); return RDY_OK; }
	static msg_t GWinStreamGetTimed(void *ip, systime_t timeout) { (void)ip; (void)timeout; return RDY_OK; }
	static size_t GWinStreamWriteTimed(void *ip, const gU8 *bp, size_t n, systime_t time) { (void)time; gwinPutCharArray(Stream2GWindow(ip), (const char *)bp, n); return RDY_OK; }
	static size_t GWinStreamReadTimed(void *ip, gU8 *bp, size_t n, systime_t time) { (void)ip; (void)bp; (void)n; (void)time; return 0; }
#elif CH_KERNEL_MAJOR == 3
    static size_t GWinStreamWrite(void *ip, const gU8 *bp, size_t n) { gwinPutCharArray(Stream2GWindow(ip), (const char *)bp, n); return MSG_OK; }
    static size_t GWinStreamRead(void *ip, gU8 *bp, size_t n) { (void)ip; (void)bp; (void)n; return 0; }
    static msg_t GWinStreamPut(void *ip, gU8 b) { gwinPutChar(Stream2GWindow(ip), (char)b); return MSG_OK; }
    static msg_t GWinStreamGet(void *ip) {(void)ip; return MSG_OK; }
    static msg_t GWinStreamPutTimed(void *ip, gU8 b, systime_t time) { (void)time; gwinPutChar(Stream2GWindow(ip), (char)b); return MSG_OK; }
    static msg_t GWinStreamGetTimed(void *ip, systime_t timeout) { (void)ip; (void)timeout; return MSG_OK; }
    static size_t GWinStreamWriteTimed(void *ip, const gU8 *bp, size_t n, systime_t time) { (void)time; gwinPutCharArray(Stream2GWindow(ip), (const char *)bp, n); return MSG_OK; }
    static size_t GWinStreamReadTimed(void *ip, gU8 *bp, size_t n, systime_t time) { (void)ip; (void)bp; (void)n; (void)time; return 0; }
#endif

	struct GConsoleWindowVMT_t {
		_base_asynchronous_channel_methods
	};

	static const struct GConsoleWindowVMT_t GWindowConsoleVMT = {
		GWinStreamWrite,
		GWinStreamRead,
		GWinStreamPut,
		GWinStreamGet,
		GWinStreamPutTimed,
		GWinStreamGetTimed,
		GWinStreamWriteTimed,
		GWinStreamReadTimed
	};
#endif

#if GWIN_CONSOLE_ESCSEQ
	// Convert escape sequences to attributes
	static gBool ESCtoAttr(char c, gU8 *pattr) {
		gU8		attr;

		attr = pattr[0];
		switch(c) {
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			attr &= ~(ESC_REDBIT|ESC_GREENBIT|ESC_BLUEBIT);
			attr |= (c - '0') | ESC_USECOLOR;
			break;
		case 'C':
			attr &= ~(ESC_REDBIT|ESC_GREENBIT|ESC_BLUEBIT|ESC_USECOLOR);
			break;
		case 'u':
			attr |= ESC_UNDERLINE;
			break;
		case 'U':
			attr &= ~ESC_UNDERLINE;
			break;
		case 'b':
			attr |= ESC_BOLD;
			break;
		case 'B':
			attr &= ~ESC_BOLD;
			break;
		default:
			return gFalse;
		}
		if (attr == pattr[0])
			return gFalse;
		pattr[0] = attr;
		return gTrue;
	}

	static gColor ESCPrintColor(GConsoleObject *gcw) {
		switch(gcw->currattr & (ESC_REDBIT|ESC_GREENBIT|ESC_BLUEBIT|ESC_USECOLOR)) {
		case (ESC_USECOLOR):
			return GFX_BLACK;
		case (ESC_USECOLOR|ESC_REDBIT):
			return GFX_RED;
		case (ESC_USECOLOR|ESC_GREENBIT):
			return GFX_GREEN;
		case (ESC_USECOLOR|ESC_REDBIT|ESC_GREENBIT):
			return GFX_YELLOW;
		case (ESC_USECOLOR|ESC_BLUEBIT):
			return GFX_BLUE;
		case (ESC_USECOLOR|ESC_REDBIT|ESC_BLUEBIT):
			return GFX_MAGENTA;
		case (ESC_USECOLOR|ESC_GREENBIT|ESC_BLUEBIT):
			return GFX_CYAN;
		case (ESC_USECOLOR|ESC_REDBIT|ESC_GREENBIT|ESC_BLUEBIT):
			return GFX_WHITE;
		default:
			return gcw->g.color;
		}
	}
#else
	#define ESCPrintColor(gcw)		((gcw)->g.color)
#endif

#if GWIN_CONSOLE_USE_HISTORY
	static void HistoryDestroy(GWindowObject *gh) {
		#define gcw		((GConsoleObject *)gh)

		// Deallocate the history buffer if required.
		if (gcw->buffer) {
			gfxFree(gcw->buffer);
			gcw->buffer = 0;
		}

		#undef gcw
	}

	/**
	 * Scroll the history buffer by one line
	 */
	static void scrollBuffer(GConsoleObject *gcw) {
		char	*p, *ep;
		gPtrDiff	dp;

		// Only scroll if we need to
		if (!gcw->buffer || (gcw->g.flags & GCONSOLE_FLG_NOSTORE))
			return;

		// If a buffer overrun has been marked don't scroll as we have already
		if ((gcw->g.flags & GCONSOLE_FLG_OVERRUN)) {
			gcw->g.flags &= ~GCONSOLE_FLG_OVERRUN;
			return;
		}

		// Remove one line from the start
		ep = gcw->buffer+gcw->bufpos;
		for(p = gcw->buffer; p < ep && *p != '\n'; p++) {
			#if GWIN_CONSOLE_ESCSEQ
				if (*p == 27)
					ESCtoAttr(p[1], &gcw->startattr);
			#endif
		}

		// Was there a newline, if not delete everything.
		if (p >= ep) {
			gcw->bufpos = 0;
			return;
		}

		// Delete the data
		dp = ++p - gcw->buffer;						// Calculate the amount to to be removed
		gcw->bufpos -= dp;							// Calculate the new size
		if (gcw->bufpos)
			memcpy(gcw->buffer, p, gcw->bufpos);	// Move the rest of the data
	}

	static void HistoryRedraw(GWindowObject *gh) {
		#define gcw		((GConsoleObject *)gh)
		gCoord fy;

		// No redrawing if there is no history
		if (!gcw->buffer)
			return;

		// Handle vertical size decrease - We have to scroll out first lines of the log 
		fy = gdispGetFontMetric(gh->font, gFontHeight);
		while (gcw->cy > gh->height) {
			scrollBuffer(gcw);
			gcw->cy -= fy;
		}

		// We are printing the buffer - don't store it again
		gh->flags |= GCONSOLE_FLG_NOSTORE;

		#if !GWIN_CONSOLE_USE_CLEAR_LINES
			// Clear the screen
			gdispGFillArea(gh->display, gh->x, gh->y, gh->width, gh->height, gh->bgcolor);
		#endif

		// Reset the cursor
		gcw->cx = 0;
		gcw->cy = 0;

		// Reset the current attributes
		#if GWIN_CONSOLE_ESCSEQ
			gcw->currattr = gcw->startattr;
		#endif

		// Print the buffer
		gwinPutCharArray(gh, gcw->buffer, gcw->bufpos);

		#if GWIN_CONSOLE_USE_CLEAR_LINES
			// Clear the remaining space
			{
				gCoord		y;

				y = gcw->cy;
				if (gcw->cx)
					y += gdispGetFontMetric(gh->font, gFontHeight);
				if (y < gh->height)
					gdispGFillArea(gh->display, gh->x, gh->y+y, gh->width, gh->height-y, gh->bgcolor);
			}
		#endif

		// Turn back on storing of buffer contents
		gh->flags &= ~GCONSOLE_FLG_NOSTORE;

		#undef gcw
	}

	/**
	 * Put a character into our history buffer
	 */
	static void putCharInBuffer(GConsoleObject *gcw, char c) {
		// Only store if we need to
		if (!gcw->buffer || (gcw->g.flags & GCONSOLE_FLG_NOSTORE))
			return;

		// Do we have enough space in the buffer
		if (gcw->bufpos >= gcw->bufsize) {
			char	*p, *ep;
			gPtrDiff	dp;

			/**
			 * This should never really happen except if the user has changed the window
			 * size without turning off and then on the buffer. Even then it is unlikely
			 * because of our conservative allocation strategy.
			 * If it really is needed we scroll one line to make some space. We also mark
			 * it is an overrun so that if asked to really scroll later we know we already have.
			 * Note we only use one bit to indicate an overrun, so an overrun of more
			 * than one line will lead to some interesting scrolling and refreshing
			 * effects.
			 */

			// Remove one line from the start
			ep = gcw->buffer+gcw->bufpos;
			for(p = gcw->buffer; p < ep && *p != '\n'; p++) {
				#if GWIN_CONSOLE_ESCSEQ
					if (*p == 27)
						ESCtoAttr(p[1], &gcw->startattr);
				#endif
			}

			// Was there a newline?
			if (*p != '\n')
				p = gcw->buffer;						// Oops - no newline, just delete one char
			else
				gcw->g.flags |= GCONSOLE_FLG_OVERRUN;	// Mark the overrun

			// Delete the data
			dp = ++p - gcw->buffer;						// Calculate the amount to to be removed
			gcw->bufpos -= dp;							// Calculate the new size
			if (gcw->bufpos)
				memcpy(gcw->buffer, p, gcw->bufpos);	// Move the rest of the data
		}

		// Save the character
		gcw->buffer[gcw->bufpos++] = c;
	}

	/**
	 * Clear the history buffer
	 */
	static void clearBuffer(GConsoleObject *gcw) {

		// Only clear if we need to
		if (!gcw->buffer || (gcw->g.flags & GCONSOLE_FLG_NOSTORE))
			return;

		gcw->bufpos = 0;
	}

#else
	#define putCharInBuffer(gcw, c)
	#define scrollBuffer(gcw)
	#define clearBuffer(gcw)
#endif

static void AfterClear(GWindowObject *gh) {
	#define gcw		((GConsoleObject *)gh)
	gcw->cx = 0;
	gcw->cy = 0;
	clearBuffer(gcw);
	#if GWIN_CONSOLE_ESCSEQ
		gcw->startattr = gcw->currattr;
	#endif
	#undef gcw		
}

static const gwinVMT consoleVMT = {
	"Console",				// The classname
	sizeof(GConsoleObject),	// The object size
	#if GWIN_CONSOLE_USE_HISTORY
		HistoryDestroy,		// The destroy routine (custom)
		HistoryRedraw,		// The redraw routine (custom)
	#else
		0,					// The destroy routine
		0,					// The redraw routine (default)
	#endif
	AfterClear,				// The after-clear routine
};

GHandle gwinGConsoleCreate(GDisplay *g, GConsoleObject *gc, const GWindowInit *pInit) {
	if (!(gc = (GConsoleObject *)_gwindowCreate(g, &gc->g, pInit, &consoleVMT, 0)))
		return 0;

	#if GFX_USE_OS_CHIBIOS && GWIN_CONSOLE_USE_BASESTREAM
		gc->stream.vmt = &GWindowConsoleVMT;
	#endif

	#if GWIN_CONSOLE_USE_HISTORY
		gc->buffer = 0;
		#if GWIN_CONSOLE_HISTORY_ATCREATE
			gwinConsoleSetBuffer(&gc->g, gTrue);
		#endif
	#endif

	gc->cx = 0;
	gc->cy = 0;

	#if GWIN_CONSOLE_ESCSEQ
		gc->startattr = gc->currattr = 0;
		gc->escstate = 0;
	#endif

	gwinSetVisible((GHandle)gc, pInit->show);
	_gwinFlushRedraws(REDRAW_WAIT);

	return (GHandle)gc;
}

#if GFX_USE_OS_CHIBIOS && GWIN_CONSOLE_USE_BASESTREAM
	BaseSequentialStream *gwinConsoleGetStream(GHandle gh) {
		if (gh->vmt != &consoleVMT)
			return 0;

		return (BaseSequentialStream *)&(((GConsoleObject *)(gh))->stream);
	}
#endif

#if GWIN_CONSOLE_USE_HISTORY
	gBool gwinConsoleSetBuffer(GHandle gh, gBool onoff) {
		#define gcw		((GConsoleObject *)gh)

		if (gh->vmt != &consoleVMT)
			return gFalse;

		// Do we want the buffer turned off?
		if (!onoff) {
			if (gcw->buffer) {
				gfxFree(gcw->buffer);
				gcw->buffer = 0;
			}
			return gFalse;
		}

		// Is the buffer already on?
		if (gcw->buffer)
			return gTrue;

		// Get the number of characters that fit in the x direction
		#if GWIN_CONSOLE_HISTORY_AVERAGING
			gcw->bufsize = gh->width / ((2*gdispGetFontMetric(gh->font, gFontMinWidth)+gdispGetFontMetric(gh->font, gFontMaxWidth))/3);
		#else
			gcw->bufsize = gh->width / gdispGetFontMetric(gh->font, gFontMinWidth);
		#endif
		gcw->bufsize++;				// Allow space for a newline on each line.

		// Multiply by the number of lines
		gcw->bufsize *= gh->height / gdispGetFontMetric(gh->font, gFontHeight);

		// Allocate the buffer
		if (!(gcw->buffer = gfxAlloc(gcw->bufsize)))
			return gFalse;

		// All good!
		gh->flags &= ~GCONSOLE_FLG_OVERRUN;
		gcw->bufpos = 0;
		return gTrue;
		
		#undef gcw
	}
#endif

/*
 *  We can get into gwinPutChar() 2 ways -
 *  	1. when the user calls us, and
 *  	2. when the redraw uses us to redraw the display.
 *  When called by option 2 we MUST not try to obtain a draw session
 *  as we already have one.
 *
 *  We use these macro's below to make sure we do that safely
 */
#define DrawStart(gh)		((gh->flags & GCONSOLE_FLG_NOSTORE) || _gwinDrawStart(gh))
#define DrawEnd(gh)			{ if (!(gh->flags & GCONSOLE_FLG_NOSTORE)) _gwinDrawEnd(gh); }

void gwinPutChar(GHandle gh, char c) {
	#define gcw		((GConsoleObject *)gh)
	gU8			width, fy;

	if (gh->vmt != &consoleVMT || !gh->font)
		return;

	fy = gdispGetFontMetric(gh->font, gFontHeight);

	#if GWIN_CONSOLE_ESCSEQ
		/**
		 * Handle escape sequences
		 * 			ESC color		Change subsequent text color
		 * 							color:	"0" = black, "1" = red, "2" = green, "3" = yellow, "4" = blue,
		 * 									"5" = magenta, "6" = cyan, "7" = white
		 * 			ESC C			Revert subsequent text color to the window default
		 * 			ESC u			Turn on underline
		 * 			ESC U			Turn off underline
		 * 			ESC b			Turn on bold
		 * 			ESC B			Turn off bold
		 * 			ESC J			Clear the window
		 */
		switch (gcw->escstate) {
		case 1:
			gcw->escstate = 0;
			if (ESCtoAttr(c, &gcw->currattr)) {
				if (gcw->cx == 0 && gcw->cy == 0)
					gcw->startattr = gcw->currattr;
				else {
					putCharInBuffer(gcw, 27);
					putCharInBuffer(gcw, c);
				}
			} else {
				switch(c) {
				case 'J':
					// Clear the console and reset the cursor
					clearBuffer(gcw);
					if (DrawStart(gh)) {
						gdispGFillArea(gh->display, gh->x, gh->y, gh->width, gh->height, gh->bgcolor);
						DrawEnd(gh);
					}
					gcw->cx = 0;
					gcw->cy = 0;
					gcw->startattr = gcw->currattr;
					break;
				}
			}
			return;
		}
	#endif

	/**
	 * Special Characters:
	 *
	 * Carriage returns and line feeds (\r & \n) are handled in unix terminal cooked mode; that is,
	 * line feeds perform both actions and carriage-returns are ignored.
	 *
	 * if GWIN_CONSOLE_ESCSEQ is turned on then ESC is trapped ready for the escape command.
	 *
	 * All other characters are treated as printable.
	 */
	switch (c) {
	case '\n':
		// clear to the end of the line
		#if GWIN_CONSOLE_USE_CLEAR_LINES
			if (gcw->cx == 0 && gcw->cy+fy < gh->height && DrawStart(gh)) {
				gdispGFillArea(gh->display, gh->x, gh->y + gcw->cy, gh->width, fy, gh->bgcolor);
				DrawEnd(gh);
			}
		#endif
		// update the cursor
		gcw->cx = 0;
		gcw->cy += fy;
		putCharInBuffer(gcw, '\n');
		// We use lazy scrolling here and only scroll when the next char arrives
		return;

	case '\r':
		// gcw->cx = 0;
		return;

	#if GWIN_CONSOLE_ESCSEQ
		case 27:		// ESC
			gcw->escstate = 1;
			return;
	#endif
	}

	// Characters with no width are ignored
	if (!(width = gdispGetCharWidth(c, gh->font)))
		return;

	// Allow space for (very crude) bold
	#if GWIN_CONSOLE_ESCSEQ
		if ((gcw->currattr & ESC_BOLD))
			width++;
	#endif

	// Do we need to go to the next line to fit this character?
	if (gcw->cx + width >= gh->width) {
		gcw->cx = 0;
		gcw->cy += fy;
		putCharInBuffer(gcw, '\n');
	}

	// Do we need to scroll to fit this character?
	if (gcw->cy + fy > gh->height) {
		#if GWIN_CONSOLE_USE_HISTORY && GWIN_CONSOLE_BUFFER_SCROLLING
			if (gcw->buffer) {
				// If flag GCONSOLE_FLG_NOSTORE is set, then do not recursivly call HistoryRedraw - just drop the buffer
				if (gh->flags & GCONSOLE_FLG_NOSTORE)
					gcw->bufpos = 0;
					
				// Scroll the buffer and then redraw using the buffer
				scrollBuffer(gcw);
				if (DrawStart(gh)) {
					HistoryRedraw(gh);
					DrawEnd(gh);
				}
			} else
		#endif
		#if GDISP_NEED_SCROLL
			{
				// Scroll the console using hardware
				scrollBuffer(gcw);
				if (DrawStart(gh)) {
					gdispGVerticalScroll(gh->display, gh->x, gh->y, gh->width, gh->height, fy, gh->bgcolor);
					DrawEnd(gh);
				}

				// Set the cursor to the start of the last line
				gcw->cx = 0;
				gcw->cy = (((gCoord)(gh->height/fy))-1)*fy;
			}
		#else
			{
				// Clear the console and reset the cursor
				clearBuffer(gcw);
				if (DrawStart(gh)) {
					gdispGFillArea(gh->display, gh->x, gh->y, gh->width, gh->height, gh->bgcolor);
					DrawEnd(gh);
				}
				gcw->cx = 0;
				gcw->cy = 0;
				#if GWIN_CONSOLE_ESCSEQ
					gcw->startattr = gcw->currattr;
				#endif
			}
		#endif
	}

	// Save the char
	putCharInBuffer(gcw, c);

	// Draw the character
	if (DrawStart(gh)) {

		// If we are at the beginning of a new line clear the line
		#if GWIN_CONSOLE_USE_CLEAR_LINES
			if (gcw->cx == 0)
				gdispGFillArea(gh->display, gh->x, gh->y + gcw->cy, gh->width, fy, gh->bgcolor);
		#endif

		#if GWIN_CONSOLE_USE_FILLED_CHARS
			gdispGFillChar(gh->display, gh->x + gcw->cx, gh->y + gcw->cy, c, gh->font, ESCPrintColor(gcw), gh->bgcolor);
		#else
			gdispGDrawChar(gh->display, gh->x + gcw->cx, gh->y + gcw->cy, c, gh->font, ESCPrintColor(gcw));
		#endif

		#if GWIN_CONSOLE_ESCSEQ
			// Draw the underline
			if ((gcw->currattr & ESC_UNDERLINE))
				gdispGDrawLine(gh->display, gh->x + gcw->cx, gh->y + gcw->cy + fy - gdispGetFontMetric(gh->font, gFontDescendersHeight),
											gh->x + gcw->cx + width + gdispGetFontMetric(gh->font, gFontCharPadding), gh->y + gcw->cy + fy - gdispGetFontMetric(gh->font, gFontDescendersHeight),
											ESCPrintColor(gcw));
			// Bold (very crude)
			if ((gcw->currattr & ESC_BOLD))
				gdispGDrawChar(gh->display, gh->x + gcw->cx + 1, gh->y + gcw->cy, c, gh->font, ESCPrintColor(gcw));
		#endif

		DrawEnd(gh);
	}

	// Update the cursor
	gcw->cx += width + gdispGetFontMetric(gh->font, gFontCharPadding);

	#undef gcw
}

void gwinPutString(GHandle gh, const char *str) {
	while(*str)
		gwinPutChar(gh, *str++);
}

void gwinPutCharArray(GHandle gh, const char *str, gMemSize n) {
	while(n--)
		gwinPutChar(gh, *str++);
}

#include <stdarg.h>

#define MAX_FILLER 11
#define FLOAT_PRECISION 100000

static char *consltoa_wd(char *p, long num, unsigned radix, long divisor) {
	int i;
	char *q;

	if (!divisor) divisor = num;

	q = p + MAX_FILLER;
	do {
		i = (int)(num % radix);
		i += '0';
		if (i > '9')
		  i += 'A' - '0' - 10;
		*--q = i;
		num /= radix;
	} while ((divisor /= radix) != 0);

	i = (int)(p + MAX_FILLER - q);
	do {
		*p++ = *q++;
	} while (--i);

	return p;
}

#if GWIN_CONSOLE_USE_FLOAT
	static char *ftoa(char *p, double num) {
		long l;
		unsigned long precision = FLOAT_PRECISION;

		l = num;
		p = consltoa_wd(p, l, 10, 0);
		*p++ = '.';
		l = (num - l) * precision;
		return consltoa_wd(p, l, 10, precision / 10);
	}
#endif

void gwinPrintf(GHandle gh, const char *fmt, ...) {
	va_list ap;
	char *p, *s, c, filler;
	int i, precision, width;
	gBool is_long, left_align;
	long l;
	#if GWIN_CONSOLE_USE_FLOAT
		float f;
		char tmpbuf[2*MAX_FILLER + 1];
	#else
		char tmpbuf[MAX_FILLER + 1];
	#endif

	if (gh->vmt != &consoleVMT || !gh->font)
		return;

	va_start(ap, fmt);
	while (gTrue) {
		c = *fmt++;
		if (c == 0) {
			va_end(ap);
			return;
		}
		if (c != '%') {
			gwinPutChar(gh, c);
			continue;
		}

		p = tmpbuf;
		s = tmpbuf;
		left_align = gFalse;
		if (*fmt == '-') {
			fmt++;
			left_align = gTrue;
		}
		filler = ' ';
		if (*fmt == '0') {
			fmt++;
			filler = '0';
		}
		width = 0;

		while (gTrue) {
			c = *fmt++;
			if (c >= '0' && c <= '9')
				c -= '0';
			else if (c == '*')
				c = va_arg(ap, int);
			else
				break;
			width = width * 10 + c;
		}
		precision = 0;
		if (c == '.') {
			while (gTrue) {
				c = *fmt++;
				if (c >= '0' && c <= '9')
					c -= '0';
				else if (c == '*')
					c = va_arg(ap, int);
				else
					break;
				precision = precision * 10 + c;
			}
		}
		/* Long modifier.*/
		if (c == 'l' || c == 'L') {
			is_long = gTrue;
			if (*fmt)
				c = *fmt++;
		}
		else
			is_long = (c >= 'A') && (c <= 'Z');

		/* Command decoding.*/
		switch (c) {
		case 'c':
			filler = ' ';
			*p++ = va_arg(ap, int);
			break;
		case 's':
			filler = ' ';
			if ((s = va_arg(ap, char *)) == 0)
				s = "(null)";
			if (precision == 0)
				precision = 32767;
			for (p = s; *p && (--precision >= 0); p++);
			break;
		case 'D':
		case 'd':
			if (is_long)
				l = va_arg(ap, long);
			else
				l = va_arg(ap, int);
			if (l < 0) {
				*p++ = '-';
				l = -l;
			}
			p = consltoa_wd(p, l, 10, 0);
			break;
		#if GWIN_CONSOLE_USE_FLOAT
			case 'f':
				f = (float) va_arg(ap, double);
				if (f < 0) {
					*p++ = '-';
					f = -f;
				}
				p = ftoa(p, f);
				break;
		#endif
		case 'X':
		case 'x':
			c = 16;
			goto unsigned_common;
		case 'U':
		case 'u':
			c = 10;
			goto unsigned_common;
		case 'O':
		case 'o':
			c = 8;
		unsigned_common:
			if (is_long)
				l = va_arg(ap, long);
			else
				l = va_arg(ap, int);
			p = consltoa_wd(p, l, c, 0);
			break;
		default:
			*p++ = c;
			break;
		}

		i = (int)(p - s);
		if ((width -= i) < 0)
			width = 0;
		if (!left_align)
			width = -width;
		if (width < 0) {
			if (*s == '-' && filler == '0') {
				gwinPutChar(gh, *s++);
				i--;
			}
			do {
				gwinPutChar(gh, filler);
			} while (++width != 0);
		}
		while (--i >= 0)
			gwinPutChar(gh, *s++);
		while (width) {
			gwinPutChar(gh, filler);
			width--;
		}
	}
}

#endif /* GFX_USE_GWIN && GWIN_NEED_CONSOLE */


