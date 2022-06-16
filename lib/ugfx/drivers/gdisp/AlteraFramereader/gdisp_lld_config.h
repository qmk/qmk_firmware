/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP

#define GDISP_HARDWARE_DRAWPIXEL        GFXON
#define GDISP_HARDWARE_PIXELREAD        GFXON
#define GDISP_HARDWARE_CONTROL          GFXON
#define GDISP_HARDWARE_FILLS            GFXON

#define GDISP_LLD_PIXELFORMAT           GDISP_PIXELFORMAT_RGB888

// gdispControl() options
#define GDISP_CONTROL_BUFFERS_SWAP      (GDISP_CONTROL_LLD+0)	// Swap framebuffers (double buffering). Parameter is ignored.
#define GDISP_CONTROL_BUFFERS_ENABLE    (GDISP_CONTROL_LLD+1)   // Enable double buffering. Parameter is ignored.
#define GDISP_CONTROL_BUFFERS_DISABLE   (GDISP_CONTROL_LLD+2)   // Disable double buffering. Parameter is ignored.

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
