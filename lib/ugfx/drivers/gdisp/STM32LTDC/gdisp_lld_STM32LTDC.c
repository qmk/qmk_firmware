/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_STM32LTDC
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#if defined(GDISP_SCREEN_HEIGHT) || defined(GDISP_SCREEN_HEIGHT)
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GDISP: This low level driver does not support setting a screen size. It is being ignored.")
	#endif
	#undef GDISP_SCREEN_WIDTH
	#undef GDISP_SCREEN_HEIGHT
#endif

#ifndef LTDC_USE_DMA2D
 	#define LTDC_USE_DMA2D 			GFXOFF
#endif
#ifndef LTDC_NO_CLOCK_INIT
	#define LTDC_NO_CLOCK_INIT		GFXOFF
#endif
#ifndef	LTDC_DMA_CACHE_FLUSH
	#define	LTDC_DMA_CACHE_FLUSH	GFXOFF
#endif

#include "stm32_ltdc.h"

#if LTDC_USE_DMA2D
 	#include "stm32_dma2d.h"

	#if defined(STM32F7) || defined(STM32F746xx)
		#undef 	LTDC_DMA_CACHE_FLUSH
		#define	LTDC_DMA_CACHE_FLUSH	GFXON
	#endif
#endif


typedef struct ltdcLayerConfig {
	// Frame
	LLDCOLOR_TYPE*	frame;			// Frame buffer address
	gCoord			width, height;	// Frame size in pixels
	gCoord			pitch;			// Line pitch, in bytes
	gU16		fmt;			// Pixel format in LTDC format

	// Window
	gCoord			x, y;			// Start pixel position of the virtual layer
	gCoord			cx, cy;			// Size of the virtual layer

	gU32		defcolor;		// Default color, ARGB8888
	gU32		keycolor;		// Color key, RGB888
	gU32		blending;		// Blending factors
	const gU32* palette;		// The palette, RGB888 (can be NULL)
	gU16		palettelen;		// Palette length
	gU8			alpha;			// Constant alpha factor
	gU8			layerflags;		// Layer configuration
} ltdcLayerConfig;

typedef struct ltdcConfig {
	gCoord		width, height;				// Screen size
	gCoord		hsync, vsync;				// Horizontal and Vertical sync pixels
	gCoord		hbackporch, vbackporch;		// Horizontal and Vertical back porch pixels
	gCoord		hfrontporch, vfrontporch;	// Horizontal and Vertical front porch pixels
	gU32	syncflags;					// Sync flags
	gU32	bgcolor;					// Clear screen color RGB888

	ltdcLayerConfig	bglayer;				// Background layer config
	ltdcLayerConfig	fglayer;				// Foreground layer config
} ltdcConfig;

#define LTDC_UNUSED_LAYER_CONFIG	{ 0, 1, 1, 1, LTDC_FMT_L8, 0, 0, 1, 1, 0x000000, 0x000000, LTDC_BLEND_FIX1_FIX2, 0, 0, 0, 0 }

#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB565
	#define LTDC_PIXELFORMAT	LTDC_FMT_RGB565
	#define LTDC_PIXELBYTES		2
	#define LTDC_PIXELBITS		16
#elif GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
	#define LTDC_PIXELFORMAT	LTDC_FMT_ARGB8888
	#define LTDC_PIXELBYTES		4
	#define LTDC_PIXELBITS		32
#else
	#error "GDISP: STM32LTDC - unsupported pixel format"
#endif

#include "board_STM32LTDC.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

/*===========================================================================*/
/* Driver local routines.                                                    */
/*===========================================================================*/

#define PIXIL_POS(g, x, y)		((y) * ((ltdcLayerConfig *)g->priv)->pitch + (x) * LTDC_PIXELBYTES)
#define PIXEL_ADDR(g, pos)		((LLDCOLOR_TYPE *)((gU8 *)((ltdcLayerConfig *)g->priv)->frame+pos))

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

static const ltdcLayerConfig layerOff = LTDC_UNUSED_LAYER_CONFIG;

static void _ltdc_reload(void) {
	LTDC->SRCR |= LTDC_SRCR_IMR;
	while (LTDC->SRCR & (LTDC_SRCR_IMR | LTDC_SRCR_VBR))
		gfxYield();
}

static void _ltdc_layer_init(LTDC_Layer_TypeDef* pLayReg, const ltdcLayerConfig* pCfg) {
	static const gU8 fmt2Bpp[] = {
		4, /* LTDC_FMT_ARGB8888 */
		3, /* LTDC_FMT_RGB888 */
		2, /* LTDC_FMT_RGB565 */
		2, /* LTDC_FMT_ARGB1555 */
		2, /* LTDC_FMT_ARGB4444 */
		1, /* LTDC_FMT_L8 */
		1, /* LTDC_FMT_AL44 */
		2  /* LTDC_FMT_AL88 */
	};
	gU32 start, stop;

	// Set the framebuffer dimensions and format
	pLayReg->PFCR = (pLayReg->PFCR & ~LTDC_LxPFCR_PF) | ((gU32)pCfg->fmt & LTDC_LxPFCR_PF);
	pLayReg->CFBAR = (gU32)pCfg->frame & LTDC_LxCFBAR_CFBADD;
	pLayReg->CFBLR = ((((gU32)pCfg->pitch << 16) & LTDC_LxCFBLR_CFBP) | (((gU32)fmt2Bpp[pCfg->fmt] * pCfg->width + 3) & LTDC_LxCFBLR_CFBLL));
	pLayReg->CFBLNR = (gU32)pCfg->height & LTDC_LxCFBLNR_CFBLNBR;

	// Set the display window boundaries
	start = (gU32)pCfg->x + driverCfg.hsync + driverCfg.hbackporch;
	stop  = start + pCfg->cx - 1;
	pLayReg->WHPCR = ((start <<  0) & LTDC_LxWHPCR_WHSTPOS) | ((stop  << 16) & LTDC_LxWHPCR_WHSPPOS);
	start = (gU32)pCfg->y + driverCfg.vsync + driverCfg.vbackporch;
	stop  = start + pCfg->cy - 1;
	pLayReg->WVPCR = ((start <<  0) & LTDC_LxWVPCR_WVSTPOS) | ((stop  << 16) & LTDC_LxWVPCR_WVSPPOS);

	// Set colors
	pLayReg->DCCR = pCfg->defcolor;
	pLayReg->CKCR = (pLayReg->CKCR & ~0x00FFFFFF) | (pCfg->keycolor & 0x00FFFFFF);
	pLayReg->CACR = (pLayReg->CACR & ~LTDC_LxCACR_CONSTA) | ((gU32)pCfg->alpha & LTDC_LxCACR_CONSTA);
	pLayReg->BFCR = (pLayReg->BFCR & ~(LTDC_LxBFCR_BF1 | LTDC_LxBFCR_BF2)) | ((gU32)pCfg->blending & (LTDC_LxBFCR_BF1 | LTDC_LxBFCR_BF2));
	for (start = 0; start < pCfg->palettelen; start++)
		pLayReg->CLUTWR = ((gU32)start << 24) | (pCfg->palette[start] & 0x00FFFFFF);

	// Final flags
	pLayReg->CR = (pLayReg->CR & ~LTDC_LEF_MASK) | ((gU32)pCfg->layerflags & LTDC_LEF_MASK);
}

static void _ltdc_init(void) {
	// Set up the display scanning
	gU32 hacc, vacc;

	// Reset the LTDC peripheral
	RCC->APB2RSTR |= RCC_APB2RSTR_LTDCRST;
	RCC->APB2RSTR = 0;

	// Enable the LTDC clock
	#if !LTDC_NO_CLOCK_INIT
		#if defined(STM32F469xx)
			RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR);
		#elif defined(STM32F4) || defined(STM32F429_439xx) || defined(STM32F429xx)
			RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | (1 << 16);
		#elif defined(STM32F7) || defined(STM32F746xx)
			RCC->DCKCFGR1 = (RCC->DCKCFGR1 & ~RCC_DCKCFGR1_PLLSAIDIVR) | (1 << 16);
		#else
			#error STM32LTDC driver not implemented for your platform
		#endif
	#endif

	// Enable the peripheral
	RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;

	// Turn off the controller and its interrupts
	LTDC->GCR = 0;
	LTDC->IER = 0;
	_ltdc_reload();

	// Set synchronization params
	hacc = driverCfg.hsync - 1;
	vacc = driverCfg.vsync - 1;
	LTDC->SSCR = ((hacc << 16) & LTDC_SSCR_HSW) | ((vacc <<  0) & LTDC_SSCR_VSH);

	// Set accumulated back porch params
	hacc += driverCfg.hbackporch;
	vacc += driverCfg.vbackporch;
	LTDC->BPCR = ((hacc << 16) & LTDC_BPCR_AHBP) | ((vacc <<  0) & LTDC_BPCR_AVBP);

	// Set accumulated active params
	hacc += driverCfg.width;
	vacc += driverCfg.height;
	LTDC->AWCR = ((hacc << 16) & LTDC_AWCR_AAW) | ((vacc <<  0) & LTDC_AWCR_AAH);

	// Set accumulated total params
	hacc += driverCfg.hfrontporch;
	vacc += driverCfg.vfrontporch;
	LTDC->TWCR = ((hacc << 16) & LTDC_TWCR_TOTALW) | ((vacc <<  0) & LTDC_TWCR_TOTALH);

	// Set signal polarities and other flags
	LTDC->GCR = driverCfg.syncflags & (LTDC_EF_MASK & ~LTDC_EF_ENABLE);

	// Set background color
	LTDC->BCCR = (LTDC->BCCR & ~0x00FFFFFF) | (driverCfg.bgcolor & 0x00FFFFFF);

	// Load the background layer
	_ltdc_layer_init(LTDC_Layer1, &driverCfg.bglayer);

	// Load the foreground layer
	_ltdc_layer_init(LTDC_Layer2, &layerOff);

	// Interrupt handling
	// Possible flags - LTDC_IER_RRIE, LTDC_IER_LIE, LTDC_IER_FUIE, LTDC_IER_TERRIE etc
	LTDC->IER = 0;

	// Set everything going
	_ltdc_reload();
	LTDC->GCR |= LTDC_GCR_LTDCEN;
	_ltdc_reload();
}

LLDSPEC gBool gdisp_lld_init(GDisplay* g) {
	// Initialize the private structure
	g->priv = 0;
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:			// Display 0 is the background layer
		// Init the board
		init_board(g);

		// Initialise the LTDC controller
		_ltdc_init();

		// Initialise DMA2D
		#if LTDC_USE_DMA2D
			dma2d_init();
		#endif

		if (!(driverCfg.bglayer.layerflags & LTDC_LEF_ENABLE))
			return gFalse;

		g->priv = (void *)&driverCfg.bglayer;

	    // Finish Init the board
	    post_init_board(g);

		// Turn on the back-light
		set_backlight(g, GDISP_INITIAL_BACKLIGHT);

		break;

	case 1:			// Display 1 is the foreground layer

		if (!(driverCfg.fglayer.layerflags & LTDC_LEF_ENABLE))
			return gFalse;

		// Load the foreground layer
		_ltdc_layer_init(LTDC_Layer2, &driverCfg.fglayer);
		_ltdc_reload();

		g->priv = (void *)&driverCfg.fglayer;

	    // Finish Init the board
	    post_init_board(g);

		break;

	default:		// There is only 1 LTDC in the CPU and only the 2 layers in the LTDC.
		return gFalse;
	}

	// Initialise the GDISP structure
	g->g.Width = ((ltdcLayerConfig *)g->priv)->width;
	g->g.Height = ((ltdcLayerConfig *)g->priv)->height;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;

	return gTrue;
}

LLDSPEC void gdisp_lld_draw_pixel(GDisplay* g) {
	unsigned	pos;

	#if GDISP_NEED_CONTROL
		switch(g->g.Orientation) {
		case gOrientation0:
		default:
			pos = PIXIL_POS(g, g->p.x, g->p.y);
			break;
		case gOrientation90:
			pos = PIXIL_POS(g, g->p.y, g->g.Width-g->p.x-1);
			break;
		case gOrientation180:
			pos = PIXIL_POS(g, g->g.Width-g->p.x-1, g->g.Height-g->p.y-1);
			break;
		case gOrientation270:
			pos = PIXIL_POS(g, g->g.Height-g->p.y-1, g->p.x);
			break;
		}
	#else
		pos = PIXIL_POS(g, g->p.x, g->p.y);
	#endif

	#if LTDC_USE_DMA2D
		while(DMA2D->CR & DMA2D_CR_START);
	#endif

	#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
		// As we don't support ARGB pixel types in uGFX yet we will
		// use RGB with an inverted alpha value for compatibility
		// ie. 0x00FFFFFF is fully opaque white, 0xFFFFFFFF is fully transparent white
		PIXEL_ADDR(g, pos)[0] = gdispColor2Native(g->p.color) ^ 0xFF000000;
	#else
		PIXEL_ADDR(g, pos)[0] = gdispColor2Native(g->p.color);
	#endif
}

LLDSPEC	gColor gdisp_lld_get_pixel_color(GDisplay* g) {
	unsigned		pos;
	LLDCOLOR_TYPE	color;

	#if GDISP_NEED_CONTROL
		switch(g->g.Orientation) {
		case gOrientation0:
		default:
			pos = PIXIL_POS(g, g->p.x, g->p.y);
			break;
		case gOrientation90:
			pos = PIXIL_POS(g, g->p.y, g->g.Width-g->p.x-1);
			break;
		case gOrientation180:
			pos = PIXIL_POS(g, g->g.Width-g->p.x-1, g->g.Height-g->p.y-1);
			break;
		case gOrientation270:
			pos = PIXIL_POS(g, g->g.Height-g->p.y-1, g->p.x);
			break;
		}
	#else
		pos = PIXIL_POS(g, g->p.x, g->p.y);
	#endif

	#if LTDC_USE_DMA2D
		while(DMA2D->CR & DMA2D_CR_START);
	#endif

	#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
		// As we don't support ARGB pixel types in uGFX yet we will
		// use RGB with an inverted alpha value for compatibility
		// ie. 0x00FFFFFF is fully opaque white, 0xFFFFFFFF is fully transparent white
		color = PIXEL_ADDR(g, pos)[0] ^ 0xFF000000;
	#else
		color = PIXEL_ADDR(g, pos)[0];
	#endif

	return gdispNative2Color(color);
}

#if GDISP_NEED_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay* g) {
		switch(g->p.x) {
		case GDISP_CONTROL_ORIENTATION:
			if (g->g.Orientation == (gOrientation)g->p.ptr)
				return;
			switch((gOrientation)g->p.ptr) {
				case gOrientation0:
				case gOrientation180:
					if (g->g.Orientation == gOrientation90 || g->g.Orientation == gOrientation270) {
						gCoord		tmp;

						tmp = g->g.Width;
						g->g.Width = g->g.Height;
						g->g.Height = tmp;
					}
					break;
				case gOrientation90:
				case gOrientation270:
					if (g->g.Orientation == gOrientation0 || g->g.Orientation == gOrientation180) {
						gCoord		tmp;

						tmp = g->g.Width;
						g->g.Width = g->g.Height;
						g->g.Height = tmp;
					}
					break;
				default:
					return;
			}
			g->g.Orientation = (gOrientation)g->p.ptr;
			return;

		case GDISP_CONTROL_BACKLIGHT:
			if ((unsigned)g->p.ptr > 100) g->p.ptr = (void *)100;
			set_backlight(g, (unsigned)g->p.ptr);
			g->g.Backlight = (unsigned)g->p.ptr;
			return;
		}
	}
#endif

#if LTDC_USE_DMA2D
	#if LTDC_DMA_CACHE_FLUSH
		#if defined(__CC_ARM)
			#define __ugfxDSB()		__dsb(0xF)
		#else		// GCC like
			#define __ugfxDSB()		__ASM volatile ("dsb 0xF":::"memory")
		#endif
	#endif


	static void dma2d_init(void) {
		// Enable DMA2D clock
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;

		// Output color format
		#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB565
			DMA2D->OPFCCR = OPFCCR_RGB565;
		#elif GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
			DMA2D->OPFCCR = OPFCCR_ARGB8888;
		#endif

		// Foreground color format
		#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB565
			DMA2D->FGPFCCR = FGPFCCR_CM_RGB565;
		#elif GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
			DMA2D->FGPFCCR = FGPFCCR_CM_ARGB8888;
		#endif
	}

	// Uses p.x,p.y  p.cx,p.cy  p.color
	LLDSPEC void gdisp_lld_fill_area(GDisplay* g)
	{
		gU32 pos;
		gU32 lineadd;
		gU32 shape;

		#if GDISP_NEED_CONTROL
			switch(g->g.Orientation) {
			case gOrientation0:
			default:
				pos = PIXIL_POS(g, g->p.x, g->p.y);
				lineadd = g->g.Width - g->p.cx;
				shape = (g->p.cx << 16) | (g->p.cy);
				break;
			case gOrientation90:
				pos = PIXIL_POS(g, g->p.y, g->g.Width-g->p.x-g->p.cx);
				lineadd = g->g.Height - g->p.cy;
				shape = (g->p.cy << 16) | (g->p.cx);
				break;
			case gOrientation180:
				pos = PIXIL_POS(g, g->g.Width-g->p.x-g->p.cx, g->g.Height-g->p.y-g->p.cy);
				lineadd = g->g.Width - g->p.cx;
				shape = (g->p.cx << 16) | (g->p.cy);
				break;
			case gOrientation270:
				pos = PIXIL_POS(g, g->g.Height-g->p.y-g->p.cy, g->p.x);
				lineadd = g->g.Height - g->p.cy;
				shape = (g->p.cy << 16) | (g->p.cx);
				break;
			}
		#else
			pos = PIXIL_POS(g, g->p.x, g->p.y);
			lineadd = g->g.Width - g->p.cx;
			shape = (g->p.cx << 16) | (g->p.cy);
		#endif

		#if LTDC_DMA_CACHE_FLUSH
		{
			// This is slightly less than optimal as we flush the whole line in the source and destination image
			// instead of just the cx portion but this saves us having to iterate over each line.
			gU32	f, e;

			// Data memory barrier
			__ugfxDSB();

			// Flush then invalidate the destination area
			e = pos + (g->p.cy > 1 ? ((gU32)((ltdcLayerConfig *)g->priv)->pitch*(shape & 0xFFFF)) : ((shape>>16)*LTDC_PIXELBYTES));
			for(f=(pos & ~31); f < e; f += 32) {
			    SCB->DCCIMVAC = f;
			    SCB->DCIMVAC = f;
			}

			// Data memory barrier
			__ugfxDSB();
		}
		#endif

		// Wait until DMA2D is ready
		while(DMA2D->CR & DMA2D_CR_START);

		// Start the DMA2D
		DMA2D->OMAR = (gU32)PIXEL_ADDR(g, pos);
		DMA2D->OOR = lineadd;
		DMA2D->NLR = shape;
		#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_RGB888
			// As we don't support ARGB pixel types in uGFX yet we will
			// use RGB with an inverted alpha value for compatibility
			// ie. 0x00FFFFFF is fully opaque white, 0xFFFFFFFF is fully transparent white
			DMA2D->OCOLR = (gU32)(gdispColor2Native(g->p.color)) ^ 0xFF000000;
		#else
			DMA2D->OCOLR = (gU32)(gdispColor2Native(g->p.color));
		#endif
		;
		DMA2D->CR = DMA2D_CR_MODE_R2M | DMA2D_CR_START;
	}

	/* Oops - the DMA2D only supports gOrientation0.
	 *
	 * Where the width is 1 we can trick it for other orientations.
	 * That is worthwhile as a width of 1 is common. For other
	 * situations we need to fall back to pixel pushing.
	 *
	 * Additionally, although DMA2D can translate color formats
	 * it can only do it for a small range of formats. For any
	 * other formats we also need to fall back to pixel pushing.
	 *
	 * As the code to actually do all that for other than the
	 * simplest case (orientation == gOrientation0 and
	 * GDISP_PIXELFORMAT == GDISP_LLD_PIXELFORMAT) is very complex
	 * we will always pixel push for now. In practice that is OK as
	 * access to the framebuffer is fast - probably faster than DMA2D.
	 * It just uses more CPU.
	 */
	#if GDISP_HARDWARE_BITFILLS
		// Uses p.x,p.y  p.cx,p.cy  p.x1,p.y1 (=srcx,srcy)  p.x2 (=srccx), p.ptr (=buffer)
		LLDSPEC void gdisp_lld_blit_area(GDisplay* g) {
			gU32	srcstart, dststart;

			srcstart = LTDC_PIXELBYTES * ((gU32)g->p.x2 * g->p.y1 * + g->p.x1) + (gU32)g->p.ptr;
			dststart = (gU32)PIXEL_ADDR(g, PIXIL_POS(g, g->p.x, g->p.y));

			#if LTDC_DMA_CACHE_FLUSH
			{
				// This is slightly less than optimal as we flush the whole line in the source and destination image
				// instead of just the cx portion but this saves us having to iterate over each line.
				gU32	f, e;

				// Data memory barrier
				__ugfxDSB();

				// Flush the source area
				e = srcstart + (g->p.cy > 1 ? ((gU32)g->p.x2*g->p.cy) : (gU32)g->p.cx)*LTDC_PIXELBYTES;
				for(f=(srcstart & ~31); f < e; f += 32)
				    SCB->DCCIMVAC = f;

				// Flush then invalidate the destination area
				e = dststart + (g->p.cy > 1 ? ((gU32)((ltdcLayerConfig *)g->priv)->pitch*g->p.cy) : ((gU32)g->p.cx*LTDC_PIXELBYTES));
				for(f=(dststart & ~31); f < e; f += 32) {
				    SCB->DCCIMVAC = f;
				    SCB->DCIMVAC = f;
				}

				// Data memory barrier
				__ugfxDSB();
			}
			#endif

			// Wait until DMA2D is ready
			while(DMA2D->CR & DMA2D_CR_START);

			// Source setup
			DMA2D->FGMAR = srcstart;
			DMA2D->FGOR = g->p.x2 - g->p.cx;

			// Output setup
			DMA2D->OMAR = dststart;
			DMA2D->OOR = g->g.Width - g->p.cx;
			DMA2D->NLR = (g->p.cx << 16) | (g->p.cy);

			// Set MODE to M2M and Start the process
			DMA2D->CR = DMA2D_CR_MODE_M2M | DMA2D_CR_START;
		}
	#endif

#endif /* LTDC_USE_DMA2D */

#endif /* GFX_USE_GDISP */
