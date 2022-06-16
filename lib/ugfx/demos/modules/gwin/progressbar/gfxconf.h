/*
 * Copyright (c) 2012, 2013, Joel Bodenmann aka Tectu <joel@unormal.org>
 * Copyright (c) 2012, 2013, Andrew Hannam aka inmarket
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

//#define GFX_USE_OS_CHIBIOS		GFXON
//#define GFX_USE_OS_WIN32		GFXON
//#define GFX_USE_OS_LINUX		GFXON

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
#define GDISP_NEED_CONVEX_POLYGON	GFXON
#define GDISP_NEED_SCROLL			GFXON
#define GDISP_NEED_PIXELREAD		GFXOFF
#define GDISP_NEED_CONTROL			GFXOFF
#define GDISP_NEED_IMAGE			GFXON
#define GDISP_NEED_MULTITHREAD		GFXON
#define GDISP_NEED_ASYNC			GFXOFF
#define GDISP_NEED_MSGAPI			GFXOFF

/* Builtin Fonts */
#define GDISP_INCLUDE_FONT_UI2		GFXON
#define GDISP_NEED_ANTIALIAS		GFXOFF

/* GDISP image decoders */
#define GDISP_NEED_IMAGE_NATIVE		GFXOFF
#define GDISP_NEED_IMAGE_GIF		GFXON
#define GDISP_NEED_IMAGE_BMP		GFXOFF
#define GDISP_NEED_IMAGE_JPG		GFXOFF
#define GDISP_NEED_IMAGE_PNG		GFXOFF

/* Features for the GWIN sub-system. */
#define GWIN_NEED_WINDOWMANAGER	GFXON
#define GWIN_NEED_CONSOLE		GFXOFF
#define GWIN_NEED_GRAPH			GFXOFF
#define GWIN_NEED_WIDGET		GFXON
#define GWIN_NEED_BUTTON		GFXOFF
#define GWIN_NEED_SLIDER		GFXOFF
#define GWIN_NEED_CHECKBOX		GFXOFF
#define GWIN_NEED_LABEL			GFXOFF
#define GWIN_NEED_IMAGE			GFXOFF
#define GWIN_NEED_RADIO			GFXOFF
#define GWIN_NEED_LIST			GFXOFF
#define GWIN_NEED_IMAGE_ANIMATION	GFXOFF
#define GWIN_NEED_LIST_IMAGES		GFXOFF
#define GWIN_NEED_PROGRESSBAR	GFXON
#define GWIN_PROGRESSBAR_AUTO    GFXON

/* Features for the GINPUT sub-system. */
#define GINPUT_NEED_MOUSE		GFXON
#define GINPUT_NEED_TOGGLE		GFXOFF
#define GINPUT_NEED_DIAL		GFXOFF

#endif /* _GFXCONF_H */
