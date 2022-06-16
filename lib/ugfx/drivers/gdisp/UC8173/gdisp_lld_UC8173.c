/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_UC8173
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

/*------------------ Load the board file ------------------*/
typedef struct UC8173Lut {
	gU8 const *lutVCOM;				// 32 bytes
	gU8 const *lutFW;				// 512 bytes
	gU8 const *lutFT;				// 128 bytes
	gBool	regal;
	} UC8173Lut;

#include "board_UC8173.h"

/*------------------ Default UC8173 parameters ------------------*/
#ifndef UC8173_REVERSEAXIS_Y
	#define UC8173_REVERSEAXIS_Y	GFXOFF
#endif
#ifndef UC8173_REVERSEAXIS_X
	#define UC8173_REVERSEAXIS_X	GFXOFF
#endif
#ifndef UC8173_DEFAULT_MODE
	#define UC8173_DEFAULT_MODE		0
#endif
#ifndef UC8173_USE_OTP_LUT
	#define UC8173_USE_OTP_LUT		GFXOFF
#endif
#ifndef UC8173_CAN_READ
	#define UC8173_CAN_READ			GFXOFF
#endif
#ifdef UC8173_VCOM_VOLTAGE
	#define UC8173_VCOM_VOLTAGEBYTE	(((UC8173_VCOM_VOLTAGE) + 0.1)/-0.05)
#endif
#ifndef UC8171_BORDER
	#define UC8171_BORDER			0			/* 0 = Hi-Z, 1 = Black, 2 = White */
#endif
#ifndef UC8173_INIT_REAL_LUT
	#define UC8173_INIT_REAL_LUT	GFXON
#endif
#define UC8173_HEIGHT				240
#define UC8173_WIDTH				240

/*------------------ Set FB parameters ------------------*/
#define FB_REVERSEAXIS_Y			UC8173_REVERSEAXIS_Y
#define FB_REVERSEAXIS_X			UC8173_REVERSEAXIS_X
#define FB_WIDTH					UC8173_WIDTH
#define FB_HEIGHT					UC8173_HEIGHT
#define FB_PAGES					1
#define FB_PIXELORDER_MSB			GFXON

/*------------------ Include Generic FB Code ------------------*/
// This FB is for 1,2 or 4 bits per pixel packed along the x-axis
#define FB_TYPE_PIXELS				(LLDCOLOR_TYPE_BITS/LLDCOLOR_BITS)
#define FB_AXIS_MASK				(FB_TYPE_PIXELS-1)
#define FB_LINE_TYPES				((FB_WIDTH+FB_TYPE_PIXELS-1)/FB_TYPE_PIXELS)
#define FB_PAGE_TYPES				(FB_LINE_TYPES*FB_HEIGHT)
#define FB_ADDR(fbp, pg, px, py)	((fbp)->fb + ((px)/FB_TYPE_PIXELS + (py)*FB_LINE_TYPES + (pg)*FB_PAGE_TYPES))
#if FB_PIXELORDER_MSB
	#define FB_COLOR(px, py, c)		((c) << ((LLDCOLOR_TYPE_BITS-LLDCOLOR_BITS)-(((px) & FB_AXIS_MASK)<<(LLDCOLOR_BITS-1))))
#else
	#define FB_COLOR(px, py, c)		((c) << (((px) & FB_AXIS_MASK)<<(LLDCOLOR_BITS-1)))
#endif
#define FB_FLUSH_REQUIRED(fbp)		((fbp)->fa0.x < (fbp)->fa1.x)
#define FB_FLUSH_WIDTH(fbp)			((fbp)->fa1.x - (fbp)->fa0.x + 1)
#define FB_FLUSH_HEIGHT(fbp)		((fbp)->fa1.y - (fbp)->fa0.y + 1)
#define FB_FLUSH_ALL(fbp)			{ (fbp)->fa0.x = (fbp)->fa0.y = 0; (fbp)->fa1.x = FB_WIDTH-1; (fbp)->fa1.y = FB_HEIGHT-1; }
#define FB_FLUSH_NONE(fbp)			{ (fbp)->fa0.x = FB_WIDTH; (fbp)->fa0.y = FB_HEIGHT; (fbp)->fa1.x = (fbp)->fa1.y = -1; }
#define FB_FLUSH_POINT(fbp, px, py)	{											\
			if ((px) < (fbp)->fa0.x) (fbp)->fa0.x = (px) & ~FB_AXIS_MASK;		\
			if ((px) > (fbp)->fa1.x) (fbp)->fa1.x = (px) | FB_AXIS_MASK;		\
			if ((py) < (fbp)->fa0.y) (fbp)->fa0.y = (py);						\
			if ((py) > (fbp)->fa1.y) (fbp)->fa1.y = (py);						\
		}
#define FB_SETPIXEL(fbp, pg, px, py, c)	{										\
			LLDCOLOR_TYPE	*p, oc;												\
			p = FB_ADDR((fbp), (pg), (px), (py));								\
			oc = (*p & ~FB_COLOR((px), (py), LLDCOLOR_MASK())) | FB_COLOR((px), (py), (c));	\
			if (oc != *p) { *p = oc; FB_FLUSH_POINT((fbp), (px), (py)); }		\
		}

typedef struct FBpriv {
	gPoint			fa0, fa1;
	LLDCOLOR_TYPE	fb[FB_PAGE_TYPES * FB_PAGES];
	} FBpriv;

/*------------------ UC8173 Driver Code ------------------*/

#include "UC8173.h"

// UC8173 Inernal Macros & types
typedef struct UC8173_Private {
	UC8173Lut	*lut;
	FBpriv		fb;
} UC8173_Private;

#if !UC8173_INIT_REAL_LUT
	static gU8 const UC8173_LUT_None[] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00 
	};	
#endif
	
LLDSPEC gBool gdisp_lld_init(GDisplay* g)
{
	UC8173_Private	*priv;
	
	// Allocate the private area
	g->priv = gfxAlloc(sizeof(UC8173_Private));
	if (!g->priv)
		return gFalse;
	priv = (UC8173_Private *)g->priv;

	// Initialize the private area
	// As the display is non-volatile we need to ensure a full flush on the first draw
	priv->lut = &UC8173_ModeTable[UC8173_DEFAULT_MODE];
	FB_FLUSH_ALL(&priv->fb);

	// Initialise the board interface
	if (!init_board(g))
		return gFalse;

	// Hardware reset
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(100);
	setpin_reset(g, gFalse);
	gfxSleepMilliseconds(300);

	// Acquire the bus
	acquire_bus(g);

	// Booster soft-start		- Values from example code
	write_cmd(g, BTST);
	write_data(g, 0x17);		// data: PhaseA: Bits76=StartupTime [10ms+n*10ms def=0x00], Bits543=Strength, Bits210=MinGDROffTime
	write_data(g, 0x97);		// data: PhaseB: Bits76=StartupTime [10ms+n*10ms def=0x00], Bits543=Strength, Bits210=MinGDROffTime
	write_data(g, 0x20);		// data: PhaseC:                                            Bits543=Strength, Bits210=MinGDROffTime [def=0x07]
  
	// Power settings			- Values from datasheet default values
	write_cmd(g, PWR);
	write_data(g, 0x03);		// data: 0x02=Internal VDH/VDL, 0x01=Internal VGH/VGL
	write_data(g, 0x00);		// data: Always 0x00
	write_data(g, 0x26);		// data: 0x00->0x3F VSH Voltage 2.4V -> 11.0V step 0.2V - default=10V (0x26)
	write_data(g, 0x26);		// data: 0x00->0x3F VSL Voltage 2.4V -> 11.0V step 0.2V - default=10V (0x26)
	write_data(g, 0x03);		// data: 0x00->0x3F Red Voltage 2.4V -> 11.0V step 0.2V - default= 3V (0x03)

	// Power-on
	write_cmd(g, PON);
	while (!getpin_busy(g));

	// Panel setting register	- Values from datasheet (OTP untested)
	write_cmd(g, PSR);			// data: 0x08 + ..., 0x04=Shift Right, 0x02=Booster On, 0x01=Reset Off
	write_data(g, 0x0F);
	#if UC8173_USE_OTP_LUT
		write_cmd(g, 0x86);		// data: Always 0x86, write_data=Register LUT, write_cmd=OTP LUT
	#else
		write_data(g, 0x86);
	#endif

	// Power-off sequence		- Values from example code
	write_cmd(g, PFS);			// data: Shutdown frames - 0x00=1, 0x10=2, 0x20=3, 0x30=4
	write_data(g, 0x00);

	// PLL control				- Values from example code
	write_cmd(g, LPRD);			// data: PLL Clock Freq = 1MHz/(n+1) Min=0x04 (=200kHz)
	write_data(g, 0x25);

	// Internal temperature sensor enable	- Values from example code
	write_cmd(g, TSE);			// data: 0x00=Use internal temperature sensor, 0x80=external, Bits0-4=signed degrees to add eg 0x0F = -1
	write_data(g, 0x00);

	// VCOM settings 			- Values from datasheet
	write_cmd(g, CDI);			// data: 0x80=Border Hi-Z, 0x40=Border Output DC enabled, 0x30=BorderColor, 0x01=Normal/Inverted
	#if UC8171_BORDER == 0
		write_data(g, 0x81); 
	#elif UC8171_BORDER == 1
		write_data(g, 0x41);
	#elif UC8171_BORDER == 2
		write_data(g, 0x71);
	#else
		#error "UC8173: UC8173_BORDER must be 0..2"
	#endif
	
	// More VCOM data			- Values from example code
	write_data(g, 0x20);		// data: 0xX0=Src->VCOM interval (n+1 HSync, Def=0011), 0b0000-00XX=VCOM->Src interval (top 2 bits)
	write_data(g, 0x10);		// data: 0xXX=VCOM->Src interval (bottom 8 bits) Def=0x18
  
	// Set display panel resolution - from datasheet: should always be 240x240 for this chip
	write_cmd(g, TRES);
	write_data(g, (UC8173_WIDTH-1));
	write_data(g, ((UC8173_HEIGHT-1)>>8));
	write_data(g, ((UC8173_HEIGHT-1) & 0xFF));

	// Undocumented register	- Values from example code
	write_cmd(g, GDS);
	write_data(g, 0xA9);
	write_data(g, 0xA9);
	write_data(g, 0xEB);
	write_data(g, 0xEB);
	write_data(g, 0x02);

	// Auto measure VCOM		- Values from example code		
	write_cmd(g, AMV);
	write_data(g, 0x11);
	while (!getpin_busy(g));

	// Get current VCOM value and write it
	#if defined(UC8173_VCOM_VOLTAGEBYTE)
		// VCM_DC setting
		write_cmd(g, VDCS);
		write_data(g, UC8173_VCOM_VOLTAGEBYTE);			// was 0x12 in example code = -1.0V
	#elif UC8173_CAN_READ
		{
			gU8	vc;
				
			write_cmd(g, VV);
			vc = read_data(g);
			write_cmd(g, VDCS);
			write_data(g, vc);
		}
	#else
		#error "UC8173: Either UC8173_VCOM_VOLTAGE or UC8173_VCOM_VOLTAGEBYTE must be defined or UC8173_CAN_READ must be GFXON"
	#endif
  
	// Undocumented register	- Values from example code
	write_cmd(g, VBDS);
	write_data(g, 0x22);
  
	// Undocumented register	- Values from example code
	write_cmd(g, LVSEL);
	write_data(g, 0x02);
  
	// Undocumented register	- Values from example code
	write_cmd(g, GBS);
	write_data(g, 0x02);
	write_data(g, 0x02);
  
	// Undocumented register	- Values from example code
	write_cmd(g, GSS);
	write_data(g, 0x02);
	write_data(g, 0x02);
  
	// Undocumented register	- Values from example code
	write_cmd(g, DF);			// For REGAL (???)
	write_data(g, 0x1F);
	
	write_cmd(g, PON);
	while (!getpin_busy(g));
	
	#if UC8173_INIT_REAL_LUT
		// Load the real LUT's
		write_cmd(g, LUT_KWVCOM);
		write_data_burst(g, priv->lut->lutVCOM, 32);
		write_cmd(g, LUT_KW);
		write_data_burst(g, priv->lut->lutFW, 512);
		write_cmd(g, LUT_FT);
		write_data_burst(g, priv->lut->lutFT, 128);
	#else
		// Clear the LUT's		- Values from example code
		write_cmd(g, LUT_KW);
		write_data_burst(g, UC8173_LUT_None, sizeof(UC8173_LUT_None));
		write_cmd(g, LUT_KWVCOM);
		write_data_burst(g, UC8173_LUT_None, sizeof(UC8173_LUT_None));
	#endif
	
    write_cmd(g, POF); 
    while (getpin_busy(g));
	
	// Finish Init
	post_init_board(g);

 	// Release the bus
	release_bus(g);

	// Initialise the GDISP structure
	g->g.Width = UC8173_WIDTH;
	g->g.Height = UC8173_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = 0;
	g->g.Contrast = 0;

	return gTrue;
}

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay* g)
	{
		gCoord 		cy, cx, dx, dy;
		LLDCOLOR_TYPE	*fb;
		UC8173_Private	*priv;

		priv = (UC8173_Private *)g->priv;

		if (!FB_FLUSH_REQUIRED(&priv->fb))
			return;

		#if 0
			FB_FLUSH_ALL(&priv->fb);
		#endif
		
		// Acquire the bus to communicate with the display controller
		acquire_bus(g);
		
		// Upload the new temperature LUT
		write_cmd(g, LUT_KWVCOM);
		write_data_burst(g, priv->lut->lutVCOM, 32);
		write_cmd(g, LUT_KW);
		write_data_burst(g, priv->lut->lutFW, 512);
		write_cmd(g, LUT_FT);
		write_data_burst(g, priv->lut->lutFT, 128);

		// Calculate the width, height
		cx = FB_FLUSH_WIDTH(&priv->fb);
		cy = FB_FLUSH_HEIGHT(&priv->fb);

		// Setup the window
		// Datasheet says x,y,w,h but in practice it needs to be x,y,w-1,h-1
		write_cmd(g, DTMW);
		write_data(g, (gU8)((priv->fb.fa0.x >> 0) & 0xFF));
		write_data(g, (gU8)((priv->fb.fa0.y >> 8) & 0x03));
		write_data(g, (gU8)((priv->fb.fa0.y >> 0) & 0xFF));
		write_data(g, (gU8)(((cx-1) >> 0) & 0xFF));
		write_data(g, (gU8)(((cy-1) >> 8) & 0x03));
		write_data(g, (gU8)(((cy-1) >> 0) & 0xFF));

		// Transfer the buffer
		#if GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_MONO
			write_cmd(g, DTM4);
		#elif  GDISP_LLD_PIXELFORMAT == GDISP_PIXELFORMAT_GRAY4
			write_cmd(g, DTM2);
		#else
			#error "UC8173: Unsupported driver color format"
		#endif
		dx = (cx+FB_TYPE_PIXELS-1)/FB_TYPE_PIXELS * (LLDCOLOR_TYPE_BITS/8);
		for (fb = FB_ADDR(&priv->fb, 0, priv->fb.fa0.x, priv->fb.fa0.y), dy = cy; dy; dy--, fb += FB_LINE_TYPES)
			write_data_burst(g, (gU8 *)fb, dx);

		// Power-up the DC/DC converter to update the display panel
		write_cmd(g, PON);
		while (!getpin_busy(g));

		// Refresh the panel contents
		// Datasheet says x,y,w,h but in practice it needs to be x,y,w-1,h-1
		write_cmd(g, DRF);		// data: Partial Scan = 0x10, REGAL = 0x08, VCOM_DoNothing = 0x04 (GC4/A2 = 0x00, GU4 = 0x08)
		write_data(g, (priv->lut->regal ? 0x08 : 0x00));
		write_data(g, (gU8)((priv->fb.fa0.x >> 0) & 0xFF));
		write_data(g, (gU8)((priv->fb.fa0.y >> 8) & 0x03));
		write_data(g, (gU8)((priv->fb.fa0.y >> 0) & 0xFF));
		write_data(g, (gU8)(((cx-1) >> 0) & 0xFF));
		write_data(g, (gU8)(((cy-1) >> 8) & 0x03));
		write_data(g, (gU8)(((cy-1) >> 0) & 0xFF));
		while (!getpin_busy(g));

		// Power-down the DC/DC converter
		write_cmd(g, POF);
		while (getpin_busy(g));

		// Release the bus
		release_bus(g);

		// Mark as flushed
		FB_FLUSH_NONE(&priv->fb);
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay* g)
	{
		gCoord			x, y;
		UC8173_Private	*priv;

		priv = (UC8173_Private *)g->priv;

		// Handle the different possible orientations
		#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
			switch(g->g.Orientation) {
			default:
			case gOrientation0:
				#if FB_REVERSEAXIS_X
					x = FB_WIDTH-1 - g->p.x;
				#else
					x = g->p.x;
				#endif
				#if FB_REVERSEAXIS_Y
					y = FB_HEIGHT-1 - g->p.y;
				#else
					y = g->p.y;
				#endif
				break;
			case gOrientation90:
				#if FB_REVERSEAXIS_X
					x = FB_WIDTH-1 - g->p.y;
				#else
					x = g->p.y;
				#endif
				#if FB_REVERSEAXIS_Y
					y = g->p.x;
				#else
					y = FB_HEIGHT-1 - g->p.x;
				#endif
				break;
			case gOrientation180:
				#if FB_REVERSEAXIS_X
					x = g->p.x;
				#else
					x = FB_WIDTH-1 - g->p.x;
				#endif
				#if FB_REVERSEAXIS_Y
					y = g->p.y;
				#else
					y = FB_HEIGHT-1 - g->p.y;
				#endif
				break;
			case gOrientation270:
				#if FB_REVERSEAXIS_X
					x = g->p.y;
				#else
					x = FB_WIDTH-1 - g->p.y;
				#endif
				#if FB_REVERSEAXIS_Y
					y = FB_HEIGHT-1 - g->p.x;
				#else
					y = g->p.x;
				#endif
				break;
			}
		#else
			#if FB_REVERSEAXIS_X
				x = FB_WIDTH-1 - g->p.x;
			#else
				x = g->p.x;
			#endif
			#if FB_REVERSEAXIS_Y
				y = FB_HEIGHT-1 - g->p.y;
			#else
				y = g->p.y;
			#endif
		#endif
		
		// Modify the framebuffer content
		FB_SETPIXEL(&priv->fb, 0, x, y, gdispColor2Native(g->p.color));
	}
#endif
	
#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay* g) {
		UC8173_Private	*priv;
	
		priv = (UC8173_Private *)g->priv;
		
		switch(g->p.x) {
			
		// Custom gdispControl() to invert the framebuffer
		case GDISP_CONTROL_INVERT:
			{
				unsigned		i;
				LLDCOLOR_TYPE	*fb;

				// Invert the framebuffer
				for (fb = priv->fb.fb, i = FB_PAGE_TYPES; i ; i--, fb++)
					fb[0] = ~fb[0];
				
				// We should flush these changes to the display controller framebuffer at some point
				FB_FLUSH_ALL(&priv->fb);
			}
			break;
		
		// Custom gdispControl() to set which EINK Mode (waveform) to use
		case GDISP_CONTROL_SETMODE:
			if ((unsigned)g->p.ptr < sizeof(UC8173_ModeTable)/sizeof(UC8173_ModeTable[0]))
				priv->lut = &UC8173_ModeTable[(unsigned)g->p.ptr];
			break;

		// Custom gdispControl() to set the EINK border
		case GDISP_CONTROL_SETBORDER:
			if ((unsigned)g->p.ptr > 2)
				break;
			acquire_bus(g);
			write_cmd(g, PON);
			while (!getpin_busy(g));
			write_cmd(g, CDI);
			switch((unsigned)g->p.ptr) {
			case 0:
				write_data(g, 0x81);	// Border Hi-Z
				break;
			case 1:
				write_data(g, 0x41);	// Border Black
				break;
			case 2:
				write_data(g, 0x71);	// Border White
				break;
			}
			write_cmd(g, POF); 
			while (getpin_busy(g));
			release_bus(g);
			break;
			
		default:
			break;
		}
	}
#endif

#endif // GFX_USE_GDISP
