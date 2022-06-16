/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT    GDISPVMT_SSD1848
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

typedef struct LCD_Parameters
{
    gU8 curXPtr;
    gU8 startXPtr;       /* The area start bit position in the start column */
    gU8 endXPtr;         /* The area end bit position in the end column */
    gU8 curCol;
    gU8 startCol;        /* The area start column */
    gU8 endCol;          /* The area end column */
    gU8 curYPtr;
} LCD_Parameters;

#include "board_SSD1848.h"
#include <string.h>   /* for memset */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
    #define GDISP_SCREEN_HEIGHT        130
#endif
#ifndef GDISP_SCREEN_WIDTH
    #define GDISP_SCREEN_WIDTH         128
#endif
#ifndef GDISP_INITIAL_CONTRAST
    #define GDISP_INITIAL_CONTRAST     80
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
    #define GDISP_INITIAL_BACKLIGHT    100
#endif
#ifdef SSD1848_PAGE_PREFIX
    #define SSD1848_PAGE_WIDTH         (GDISP_SCREEN_WIDTH + 1)
    #define SSD1848_PAGE_OFFSET        1
#else
    #define SSD1848_PAGE_WIDTH         GDISP_SCREEN_WIDTH
    #define SSD1848_PAGE_OFFSET        0
#endif

#define GDISP_FLG_NEEDFLUSH            (GDISP_FLG_DRIVER << 0)

#include "SSD1848.h"

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/* Some common routines and macros */
#define PRM(g)								((LCD_Parameters *)g->priv)
#define RAM(g)								((gU8 *)(PRM(g)+1))
#define write_cmd2(g, cmd1, cmd2)			{ spi_write_cmd (g, cmd1); spi_write_data (g, cmd2); }
#define write_cmd3(g, cmd1, cmd2, cmd3)		{ spi_write_cmd (g, cmd1); spi_write_data2 (g, cmd2, cmd3); }

#define xyaddr(x, y)                       (SSD1848_PAGE_OFFSET + (x) + ((y) >> 3) * SSD1848_PAGE_WIDTH)
#define xybit(y)                           (1 << ((y) & 7))


static void set_viewport (GDisplay* g)
{
    switch (g->g.Orientation)
    {
    default:
    case gOrientation0:
        spi_write_cmd (g, SSD1848_HV_COLUMN_ADDRESS);
        spi_write_data2 (g, (gU8) (g->p.x / 8), (gU8) ((g->p.x + g->p.cx - 1) / 8));
        spi_write_cmd (g, SSD1848_HV_PAGE_ADDRESS);
        spi_write_data2 (g, g->p.y, g->p.y + g->p.cy - 1);
        spi_write_cmd (g, SSD1848_WRITE_DISP_DATA);
        break;

    case gOrientation90:
        spi_write_cmd (g, SSD1848_HV_COLUMN_ADDRESS);
        spi_write_data2 (g, g->p.y, g->p.y + g->p.cy - 1);
        spi_write_cmd (g, SSD1848_HV_PAGE_ADDRESS);
        spi_write_data2 (g, g->g.Width - g->p.x - g->p.cx, g->g.Width - 1 - g->p.x);
        spi_write_cmd (g, SSD1848_WRITE_DISP_DATA);
        break;

    case gOrientation180:
        spi_write_cmd (g, SSD1848_HV_COLUMN_ADDRESS);
        spi_write_data2 (g, g->g.Width - g->p.x - g->p.cx, g->g.Width - 1 - g->p.x);
        spi_write_cmd (g, SSD1848_HV_PAGE_ADDRESS);
        spi_write_data2 (g, g->g.Height - g->p.y - g->p.cy, g->g.Height - 1 - g->p.y);
        spi_write_cmd (g, SSD1848_WRITE_DISP_DATA);
        break;

    case gOrientation270:
        spi_write_cmd (g, SSD1848_HV_COLUMN_ADDRESS);
        spi_write_data2 (g, g->g.Height - g->p.y - g->p.cy, g->g.Height - 1 - g->p.y);
        spi_write_cmd (g, SSD1848_HV_PAGE_ADDRESS);
        spi_write_data2 (g, g->p.x, g->p.x + g->p.cx - 1);
        spi_write_cmd (g, SSD1848_WRITE_DISP_DATA);
        break;
    }
}


/**
 * As this controller can't update on a pixel boundary we need to maintain the
 * the entire display surface in memory so that we can do the necessary bit
 * operations. Fortunately it is a small display in monochrome.
 * 128 * 128 / 8 = 2048 bytes.
 */

LLDSPEC gBool gdisp_lld_init (GDisplay *g)
{
    gU8 temp [5] = { 0 };

    /* The private area is the display surface. */
    g->priv = gfxAlloc (sizeof(DisplayData) + GDISP_SCREEN_WIDTH / 8 * GDISP_SCREEN_HEIGHT);
	if (!g->priv)
		return gFalse;
    memset (g->priv, 0, sizeof(DisplayData) + GDISP_SCREEN_WIDTH / 8 * GDISP_SCREEN_HEIGHT);

    /* Initialise the board interface */
    init_board (g);

    /* Init LCD */
    /* Hardware reset */
    setpin_reset (g, gFalse);
    gfxSleepMilliseconds (50);
    setpin_reset (g, gTrue);
    gfxSleepMilliseconds (50);
    setpin_reset (g, gFalse);


    acquire_bus (g);
    gfxSleepMilliseconds (50);
    spi_write_cmd (g, SSD1848_ENABLE_INTERNAL_CLOCK); /* 0xD1 */
    spi_write_cmd (g, SSD1848_EXITSLEEP);             /* 0x94 */
    gfxSleepMilliseconds (20);

    spi_write_cmd (g, SSD1848_SET_FRAME_FREQ_LINEINVE);
    spi_write_data2 (g, 0x00, 0x00);

    temp [0] = 0x00;
    temp [1] = 0x0e;
    temp [2] = 0x41;
    spi_write_cmd (g, SSD1848_SET_BLACK_WHITE);
    spi_write_data_array (g, temp, 3);

    temp [0] = 0x00;
    temp [1] = 0x00;
    temp [2] = 0x00;
    spi_write_cmd (g, SSD1848_DATA_OUTPUT_SCAN_DIR);
    spi_write_data_array (g, temp, 3);

    spi_write_cmd (g, SSD1848_SETSTARTLINE);
    spi_write_data (g, 0x00);

    spi_write_cmd (g, SSD1848_COM_OUTPUT_SCAN_DIR);
    spi_write_data (g, 0x01);

    spi_write_cmd (g, SSD1848_SETDISP_CTRL); /* 0xCA */
    temp [0] = 0x00;
    temp [1] = 0x20;                         /* 0x1F */
    temp [2] = 0x00;
    spi_write_data_array (g, temp, 3);


    spi_write_cmd (g, SSD1848_SETPOWER_CTRL); /* 0x20 */
    spi_write_data (g, 0x0F);

    gfxSleepMilliseconds (150);

    spi_write_cmd (g, SSD1848_SETCONTRAST);  /* 0x81 */
    spi_write_data2 (g, 0x28, 0x06);

    spi_write_cmd (g, SSD1848_TEMP_COMPENSATION);
    spi_write_data (g, 0x01);

    spi_write_cmd (g, SSD1848_SET_BIASING_LOCK);  /* 0xFB */
    spi_write_data (g, 0x02);

    spi_write_cmd (g, 0xF3); 
    temp [0] = 0xc4;
    temp [1] = 0x15;
    temp [2] = 0x00;
    temp [3] = 0x80;
    spi_write_data_array (g, temp, 4);

    spi_write_cmd (g, SSD1848_SET_FRAME_FREQ_LINEINVE);
    temp [0] = 0x40;
    temp [1] = 0x04;
    temp [2] = 0x10;
    temp [3] = 0x01;
    spi_write_data_array (g, temp, 4);

    spi_write_cmd (g, SSD1848_DISPLAYON);

    spi_write_cmd (g, SSD1848_DUAL_OPT_SET);
    spi_write_data2 (g, 0x1F, 0x06);

    release_bus (g);

    /* Finish Init */
    post_init_board (g);

    /* Initialise the GDISP structure */
    g->g.Width       = GDISP_SCREEN_WIDTH;
    g->g.Height      = GDISP_SCREEN_HEIGHT;
    g->g.Orientation = gOrientation0;
    g->g.Powermode   = gPowerOn;
    g->g.Backlight   = GDISP_INITIAL_BACKLIGHT;
    g->g.Contrast    = GDISP_INITIAL_CONTRAST;
    return gTrue;
}

#if GDISP_HARDWARE_STREAM_WRITE
LLDSPEC void gdisp_lld_write_start (GDisplay *g)
{
    acquire_bus (g);
    set_viewport (g);

    PRM(g)->curCol  = PRM(g)->startCol = (gU8) (g->p.x / 8);
    PRM(g)->endCol  = (gU8) ((g->p.x + g->p.cx - 1) / 8);
    PRM(g)->curXPtr = PRM(g)->startXPtr = (gU8) (g->p.x % 8);
    PRM(g)->endXPtr = (gU8) ((g->p.x + g->p.cx - 1) % 8);
    PRM(g)->curYPtr = g->p.y;
}
LLDSPEC void gdisp_lld_write_color (GDisplay *g)
{
    gU8  temp;
    gU8  a;
    gU16 y = PRM(g)->curYPtr;
    gU16 c = PRM(g)->curCol;

    temp = RAM (g)[y * 16 + c];
    if (gdispColor2Native (g->p.color))
    {
        temp |= 0x80 >> PRM(g)->curXPtr;
    }
    else
    {
        temp &= ~(0x80 >> PRM(g)->curXPtr);
    }
    RAM (g)[y * 16 + c] = temp;

	PRM(g)->curXPtr++;
    if (PRM(g)->curXPtr == 8)
    {
        spi_write_data (g, temp);
        if (PRM(g)->curCol == PRM(g)->endCol)
        {
            PRM(g)->curYPtr++;
            PRM(g)->curCol  = PRM(g)->startCol;
            PRM(g)->curXPtr = PRM(g)->startXPtr;
        }
        else
        {
            PRM(g)->curCol++;
            PRM(g)->curXPtr = 0;
        }
    }

    /* If hit the boundary, flush the byte */
    else if ((PRM(g)->curCol == PRM(g)->endCol) &&
             (PRM(g)->curXPtr == PRM(g)->endXPtr + 1))
    {
        spi_write_data (g, temp);
        PRM(g)->curXPtr = PRM(g)->startXPtr;
        PRM(g)->curCol  = PRM(g)->startCol;
        PRM(g)->curYPtr++;
    }
}
LLDSPEC void gdisp_lld_write_stop (GDisplay *g)
{
    release_bus (g);
}
#endif

#if GDISP_HARDWARE_FLUSH
LLDSPEC void gdisp_lld_flush (GDisplay *g)
{
    gU8  * ram;
    unsigned pages;

    /* Don't flush if we don't need it. */
    if (!(g->flags & GDISP_FLG_NEEDFLUSH))
        return;
    ram   = RAM (g);
    pages = GDISP_SCREEN_WIDTH / 8;

    acquire_bus (g);
    spi_write_cmd (g, SSD1848_SETSTARTLINE | 0);

    while (pages--)
    {
        spi_write_data_array (g, ram, SSD1848_PAGE_WIDTH);
        ram += SSD1848_PAGE_WIDTH;
    }
    release_bus (g);

    g->flags &= ~GDISP_FLG_NEEDFLUSH;
}
#endif

#if GDISP_HARDWARE_CLEARS
LLDSPEC void gdisp_lld_clear (GDisplay *g)
{
    gU16 area = GDISP_SCREEN_WIDTH / 8 * GDISP_SCREEN_HEIGHT;

	if (gdispColor2Native (g->p.color))
	{
		memset (RAM (g), 0xFF, GDISP_SCREEN_WIDTH / 8 * GDISP_SCREEN_HEIGHT);
	}
	else
	{
		memset (RAM (g), 0, GDISP_SCREEN_WIDTH / 8 * GDISP_SCREEN_HEIGHT);
	}

    acquire_bus (g);
    spi_write_cmd (g, SSD1848_HV_COLUMN_ADDRESS);
    spi_write_data2 (g, 0, 15);
    spi_write_cmd (g, SSD1848_HV_PAGE_ADDRESS);
    spi_write_data2 (g, 0, 129);
    spi_write_cmd (g, SSD1848_WRITE_DISP_DATA);

    for (; area; area--)
    {
        spi_write_data (g, 0);
    }
    release_bus (g);
}
#endif

#if GDISP_HARDWARE_FILLS
LLDSPEC void gdisp_lld_fill_area (GDisplay *g)
{
    gCoord  scol, ecol, sx, ex;
    gCoord  y, col, x;
    gU16 area = (gU16) g->p.cx * g->p.cy;
    gU8  temp;

    col  = scol = (gU8) (g->p.x / 8);
    ecol = (gU8) ((g->p.x + g->p.cx - 1) / 8);
    x    = sx = (gU8) (g->p.x % 8);
    ex   = (gU8) ((g->p.x + g->p.cx - 1) % 8);
    y    = g->p.y;


    acquire_bus (g);
    set_viewport (g);
    for (; area; area--)
    {
        temp = RAM (g)[y * 16 + col];
        if (gdispColor2Native (g->p.color))
        {
            temp |= (0x80 >> x);
        }
        else
        {
            temp &= ~(0x80 >> x);
        }
        RAM (g)[y * 16 + col] = temp;

        if (++x == 8)
        {
            spi_write_data (g, temp);
            if (col == ecol)
            {
                y++;
                col = scol;
                x   = sx;
            }
            else
            {
                col++;
                x = 0;
            }
        }

        /* If hit the boundary, flush the byte */
        else if ((col == ecol) && (x == ex + 1))
        {
            spi_write_data (g, temp);
            x   = sx;
            col = scol;
            y++;
        }
    }
    release_bus (g);
}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
LLDSPEC void gdisp_lld_draw_pixel (GDisplay *g)
{
    gCoord x, y;

    switch (g->g.Orientation)
    {
    default:
    case gOrientation0:
        x = g->p.x;
        y = g->p.y;
        break;

    case gOrientation90:
        x = g->p.y;
        y = GDISP_SCREEN_HEIGHT - 1 - g->p.x;
        break;

    case gOrientation180:
        x = GDISP_SCREEN_WIDTH - 1 - g->p.x;
        y = GDISP_SCREEN_HEIGHT - 1 - g->p.y;
        break;

    case gOrientation270:
        x = GDISP_SCREEN_WIDTH - 1 - g->p.y;
        y = g->p.x;
        break;
    }
    if (gdispColor2Native (g->p.color) != gdispColor2Native (GFX_BLACK))
        RAM (g)[xyaddr (x, y)] |= xybit (y);
    else
        RAM (g)[xyaddr (x, y)] &= ~xybit(y);
    g->flags |= GDISP_FLG_NEEDFLUSH;
}
#endif

#if GDISP_HARDWARE_PIXELREAD
LLDSPEC gColor gdisp_lld_get_pixel_color (GDisplay *g)
{
    gCoord x, y;

    switch (g->g.Orientation)
    {
    default:
    case gOrientation0:
        x = g->p.x;
        y = g->p.y;
        break;

    case gOrientation90:
        x = g->p.y;
        y = GDISP_SCREEN_HEIGHT - 1 - g->p.x;
        break;

    case gOrientation180:
        x = GDISP_SCREEN_WIDTH - 1 - g->p.x;
        y = GDISP_SCREEN_HEIGHT - 1 - g->p.y;
        break;

    case gOrientation270:
        x = GDISP_SCREEN_WIDTH - 1 - g->p.y;
        y = g->p.x;
        break;
    }
    return (RAM (g)[xyaddr (x, y)] & xybit (y)) ? GFX_WHITE : GFX_BLACK;
}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
LLDSPEC void gdisp_lld_control (GDisplay *g)
{
    switch (g->p.x)
    {
    case GDISP_CONTROL_POWER:
        if (g->g.Powermode == (gPowermode) g->p.ptr)
            return;
        switch ((gPowermode) g->p.ptr)
        {
        case gPowerOff:
            acquire_bus (g);
            spi_write_cmd (g, SSD1848_SETCONTRAST);
            spi_write_data2 (g, 0x00, 0x00);    /* Drop the contrast & gain */
            spi_write_cmd (g, SSD1848_DISPLAYOFF);
            spi_write_cmd (g, SSD1848_ENTERSLEEP);
            release_bus (g);
            break;

        case gPowerSleep:
        case gPowerDeepSleep:
            acquire_bus (g);
            spi_write_cmd (g, SSD1848_ENTERSLEEP);
            release_bus (g);
            break;

        case gPowerOn:
            acquire_bus (g);
            spi_write_cmd (g, SSD1848_EXITSLEEP);       /* need this in case we were in 'normal' sleep mode */
            gfxSleepMilliseconds (5);
            spi_write_cmd (g, SSD1848_DISPLAYON);
            release_bus (g);
            break;

        default:
            return;
        }
        g->g.Powermode = (gPowermode) g->p.ptr;
        return;

    case GDISP_CONTROL_ORIENTATION:
        if (g->g.Orientation == (gOrientation) g->p.ptr)
            return;
        switch ((gOrientation) g->p.ptr)
        {
        /* Rotation is handled by the drawing routines */
        case gOrientation0:
        case gOrientation180:
            g->g.Height = GDISP_SCREEN_HEIGHT;
            g->g.Width  = GDISP_SCREEN_WIDTH;
            break;

        case gOrientation90:
        case gOrientation270:
            g->g.Height = GDISP_SCREEN_WIDTH;
            g->g.Width  = GDISP_SCREEN_HEIGHT;
            break;

        default:
            return;
        }
        g->g.Orientation = (gOrientation) g->p.ptr;
        return;

    case GDISP_CONTROL_CONTRAST:
        if ((unsigned) g->p.ptr > 100)
            g->p.ptr = (void *) 100;
        acquire_bus (g);
        spi_write_cmd (g, SSD1848_SETCONTRAST);
        spi_write_data (g, (((gU16) g->p.ptr) << 8) / 101);
        release_bus (g);
        g->g.Contrast = (gU8) g->p.ptr;
        return;

    /* Our own special controller code to inverse the display */
    /* 0 = normal, 1 = inverse */
    case GDISP_CONTROL_INVERSE:
        acquire_bus (g);
        spi_write_cmd (g, g->p.ptr ? SSD1848_INVERTDISPLAY : SSD1848_NORMALDISPLAY);
        release_bus (g);
        return;
    }
}
#endif /* GDISP_NEED_CONTROL */


#if GDISP_HARDWARE_BITFILLS
LLDSPEC void gdisp_lld_blit_area (GDisplay *g)
{
    gCoord  scol, ecol, sx;
    gCoord  y, col;
    gU16 area;
    gU8  temp, temp2, i;

    col  = scol = (gU8) (g->p.x / 8);
    ecol = (gU8) ((g->p.x + g->p.cx - 1) / 8);
    sx   = (gU8) (g->p.x % 8);
    y    = g->p.y;
    area = (ecol - scol + 1) * (g->p.cy);


    acquire_bus (g);
    set_viewport (g);

    /* Bitfill align with Column */
    if (sx == 0)
    {
        for (; area; area--)
        {
            temp = RAM (g)[y * 16 + col] = *((gU8 *) g->p.ptr)++;
            spi_write_data (g, temp);
            if (col == ecol)
            {
                y++;
                col = scol;
            }
            else
            {
                col++;
            }
        }
    }
    else
    {
        /* Bitfil doesn't align with column */
        for (; area; area--)
        {
            temp = RAM (g)[y * 16 + col];
            if (col != ecol)
            {
                temp |= (*((gU8 *) g->p.ptr) >> sx);
                RAM (g)[y * 16 + col] = temp;

                temp2  = RAM (g)[y * 16 + col + 1];
                temp2 |= (*((gU8 *) g->p.ptr) << (8-sx));
                RAM (g)[y * 16 + col + 1] = temp2;
				((gU8 *) g->p.ptr)++;
            }

            spi_write_data (g, temp);
            if (col == ecol)
            {
                y++;
                col = scol;
            }
            else
            {
                col++;
            }
        }
    }
    release_bus (g);
}
#endif

#endif /* GFX_USE_GDISP */
