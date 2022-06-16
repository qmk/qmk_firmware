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

#define	LTDC_USE_DMA2D						GFXON
#define GDISP_HARDWARE_DRAWPIXEL			GFXON
#define GDISP_HARDWARE_PIXELREAD			GFXON
#define GDISP_HARDWARE_CONTROL				GFXON

// Both these pixel formats are supported - pick one.
// RGB565 obviously is faster and uses less RAM but with lower color resolution than RGB888

#if defined(GDISP_LTDC_USE_RGB565) && GDISP_LTDC_USE_RGB565
	#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB565
	#if GDISP_TOTAL_DISPLAYS > 1
		#error "LTDC: You must use RGB888 pixel format with LTDC when using dual layers as only RGB888 currently supports using alpha"
	#endif
#else
	#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB888
#endif


/*===========================================================================*/
/* Don't change stuff below this line. Please.                               */
/*===========================================================================*/

#if LTDC_USE_DMA2D
	// DMA2D supports accelerated fills
 	#define GDISP_HARDWARE_FILLS		GFXON

	// Accelerated bitfills are also possible but only for gOrientation0
	//	and if no color translation is required (for now)
	#if !GDISP_NEED_CONTROL && !defined(GDISP_PIXELFORMAT)
 		#define GDISP_HARDWARE_BITFILLS	GFXON
	#endif
#endif /* GDISP_USE_DMA2D */

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
