/*
 * Created by Oleg Gerasimov <ogerasimov@gmail.com>
 * 10.08.2016
*/

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_HARDWARE_STREAM_WRITE		GFXON
#define GDISP_HARDWARE_CONTROL			GFXON
#define GDISP_HARDWARE_STREAM_POS		GFXON
#define GDISP_HARDWARE_FILLS			GFXON

#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB565

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
