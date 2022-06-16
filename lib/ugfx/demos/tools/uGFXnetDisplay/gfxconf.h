/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* The operating system to use. One of these must be defined - preferably in your Makefile */
//#define GFX_USE_OS_CHIBIOS	GFXOFF
//#define GFX_USE_OS_WIN32		GFXOFF
//#define GFX_USE_OS_LINUX		GFXOFF
//#define GFX_USE_OS_OSX		GFXOFF

/* GFX sub-systems to turn on */
#define GFX_USE_GDISP				GFXON
#define GFX_USE_GEVENT				GFXON
#define GFX_USE_GTIMER				GFXON
#define GFX_USE_GINPUT				GFXON

/* Features for the GDISP sub-system. */
#define GDISP_NEED_VALIDATION		GFXON
#define GDISP_NEED_TEXT				GFXON
#define GDISP_NEED_CONTROL			GFXON
#define GDISP_NEED_SCROLL			GFXON
#define GDISP_NEED_PIXELREAD		GFXON
#define GDISP_NEED_STREAMING		GFXON

/* Builtin Fonts */
#define GDISP_INCLUDE_FONT_UI2		GFXON

/* Features for the GINPUT sub-system. */
#define GINPUT_NEED_MOUSE			GFXON

/* We need to use this specific pixel format to match the network protocol */
#define GDISP_PIXELFORMAT			GDISP_PIXELFORMAT_RGB565

#endif /* _GFXCONF_H */

