/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#pragma once

#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_HARDWARE_DRAWPIXEL		GFXON
#define GDISP_HARDWARE_PIXELREAD		GFXON

#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB888

#endif	/* GFX_USE_GDISP */
