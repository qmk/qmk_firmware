/*b
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../../gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_QImage
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"
#include "gdisp_lld_qimage.h"

#ifndef GDISP_SCREEN_HEIGHT
    #define GDISP_SCREEN_HEIGHT		512
#endif
#ifndef GDISP_SCREEN_WIDTH
    #define GDISP_SCREEN_WIDTH		512
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

LLDSPEC gBool gdisp_lld_init(GDisplay *g)
{
	/* No board interface and no private driver area */
    g->priv = g->board = 0;

    if (!qimage_init(g, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT)) {
        return gFalse;
    }

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;

	return gTrue;
}

#if GDISP_HARDWARE_DRAWPIXEL
    void gdisp_lld_draw_pixel(GDisplay *g)
    {
        qimage_setPixel(g);
	}
#endif

#if GDISP_HARDWARE_PIXELREAD
    gColor gdisp_lld_get_pixel_color(GDisplay *g)
    {
        return qimage_getPixel(g);
	}
#endif

#endif /* GFX_USE_GDISP */
