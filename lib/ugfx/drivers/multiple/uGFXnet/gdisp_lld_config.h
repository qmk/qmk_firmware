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

// Calling gdispGFlush() is optional for this driver but can be used by the
//	application to force a display update. eg after streaming.

#define GDISP_HARDWARE_FLUSH			GFXON
#define GDISP_HARDWARE_DRAWPIXEL		GFXON
#define GDISP_HARDWARE_FILLS			GFXON
#define GDISP_HARDWARE_BITFILLS			GFXON
#define GDISP_HARDWARE_PIXELREAD		GFXON
#define GDISP_HARDWARE_SCROLL			GFXON
#define GDISP_HARDWARE_CONTROL			GFXON

#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB565

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
