/*
 * This file has a different license to the rest of the GFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* The operating system to use. One of these must be defined - preferably in your Makefile */
//#define GFX_USE_OS_CHIBIOS	GFXOFF
//#define GFX_USE_OS_WIN32		GFXOFF
//#define GFX_USE_OS_LINUX		GFXOFF
//#define GFX_USE_OS_OSX		GFXOFF

/* GFX sub-systems to turn on */
#define GFX_USE_GDISP			GFXON
#define GFX_USE_GWIN			GFXON
#define GFX_USE_GEVENT			GFXON
#define GFX_USE_GTIMER			GFXON
#define GFX_USE_GINPUT			GFXON

/* Features for the GDISP sub-system. */
#define GDISP_NEED_VALIDATION		GFXON
#define GDISP_NEED_CLIP				GFXON
#define GDISP_NEED_TEXT				GFXON
#define GDISP_NEED_CIRCLE			GFXON
#define GDISP_NEED_ELLIPSE			GFXOFF
#define GDISP_NEED_ARC				GFXOFF
#define GDISP_NEED_CONVEX_POLYGON	GFXOFF
#define GDISP_NEED_SCROLL			GFXOFF
#define GDISP_NEED_PIXELREAD		GFXOFF
#define GDISP_NEED_CONTROL			GFXON
#define GDISP_NEED_IMAGE			GFXON
#define GDISP_NEED_MULTITHREAD		GFXON
#define GDISP_NEED_ASYNC			GFXOFF
#define GDISP_NEED_MSGAPI			GFXOFF

/* Builtin Fonts */
#define GDISP_INCLUDE_FONT_SMALL		GFXOFF
#define GDISP_INCLUDE_FONT_LARGER		GFXOFF
#define GDISP_INCLUDE_FONT_UI1			GFXOFF
#define GDISP_INCLUDE_FONT_UI2			GFXON
#define GDISP_INCLUDE_FONT_LARGENUMBERS	GFXOFF

/* GDISP image decoders */
#define GDISP_NEED_IMAGE_NATIVE		GFXOFF
#define GDISP_NEED_IMAGE_GIF		GFXON
#define GDISP_NEED_IMAGE_BMP		GFXOFF
#define GDISP_NEED_IMAGE_JPG		GFXOFF
#define GDISP_NEED_IMAGE_PNG		GFXOFF

/* Features for the GWIN sub-system. */
#define GWIN_NEED_BUTTON		GFXON
#define GWIN_NEED_CONSOLE		GFXON
#define GWIN_NEED_SLIDER		GFXON

/* Features for the GINPUT sub-system. */
#define GINPUT_NEED_MOUSE		GFXON
#define GINPUT_NEED_DIAL		GFXOFF

#endif /* _GFXCONF_H */
