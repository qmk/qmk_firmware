/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_HARDWARE_DRAWPIXEL		GFXON
#define GDISP_HARDWARE_PIXELREAD		GFXON
#define GDISP_HARDWARE_CONTROL			GFXON

// Any other support comes from the board file
#include "board_fb24bpp.h"

// This driver supports a packed 24bit per pixel framebuffer
#ifndef GDISP_LLD_PIXELFORMAT
	#error "GDISP Fb24bpp: You must specify a GDISP_LLD_PIXELFORMAT in your board_fb24bpp.h or your makefile"
#endif

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
