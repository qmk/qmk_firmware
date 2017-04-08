/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_ST7565_ERGODOX
#include "drivers/gdisp/st7565ergodox/gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"

#include "board_ST7565.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
#define GDISP_SCREEN_HEIGHT		32
#endif
#ifndef GDISP_SCREEN_WIDTH
#define GDISP_SCREEN_WIDTH		128
#endif
#ifndef GDISP_INITIAL_CONTRAST
#define GDISP_INITIAL_CONTRAST	35
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
#define GDISP_INITIAL_BACKLIGHT	100
#endif

#define GDISP_FLG_NEEDFLUSH			(GDISP_FLG_DRIVER<<0)

#include "drivers/gdisp/st7565ergodox/st7565.h"

/*===========================================================================*/
/* Driver config defaults for backward compatibility.               	     */
/*===========================================================================*/
#ifndef ST7565_LCD_BIAS
#define ST7565_LCD_BIAS         ST7565_LCD_BIAS_7
#endif
#ifndef ST7565_ADC
#define ST7565_ADC              ST7565_ADC_NORMAL
#endif
#ifndef ST7565_COM_SCAN
#define ST7565_COM_SCAN         ST7565_COM_SCAN_INC
#endif
#ifndef ST7565_PAGE_ORDER
#define ST7565_PAGE_ORDER       0,1,2,3
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

typedef struct{
    bool_t buffer2;
    uint8_t data_pos;
    uint8_t data[16];
    uint8_t ram[GDISP_SCREEN_HEIGHT * GDISP_SCREEN_WIDTH / 8];
}PrivData;

// Some common routines and macros
#define PRIV(g)                         ((PrivData*)g->priv)
#define RAM(g)							(PRIV(g)->ram)

static GFXINLINE void write_cmd(GDisplay* g, uint8_t cmd) {
    PRIV(g)->data[PRIV(g)->data_pos++] = cmd;
}

static GFXINLINE void flush_cmd(GDisplay* g) {
    write_data(g, PRIV(g)->data, PRIV(g)->data_pos);
    PRIV(g)->data_pos = 0;
}

#define write_cmd2(g, cmd1, cmd2)		{ write_cmd(g, cmd1); write_cmd(g, cmd2); }
#define write_cmd3(g, cmd1, cmd2, cmd3)	{ write_cmd(g, cmd1); write_cmd(g, cmd2); write_cmd(g, cmd3); }

// Some common routines and macros
#define delay(us)			gfxSleepMicroseconds(us)
#define delay_ms(ms)		gfxSleepMilliseconds(ms)

#define xyaddr(x, y)		((x) + ((y)>>3)*GDISP_SCREEN_WIDTH)
#define xybit(y)			(1<<((y)&7))

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/*
 * As this controller can't update on a pixel boundary we need to maintain the
 * the entire display surface in memory so that we can do the necessary bit
 * operations. Fortunately it is a small display in monochrome.
 * 64 * 128 / 8 = 1024 bytes.
 */

LLDSPEC bool_t gdisp_lld_init(GDisplay *g) {
    // The private area is the display surface.
    g->priv = gfxAlloc(sizeof(PrivData));
    PRIV(g)->buffer2 = false;
    PRIV(g)->data_pos = 0;

    // Initialise the board interface
    init_board(g);

    // Hardware reset
    setpin_reset(g, TRUE);
    gfxSleepMilliseconds(20);
    setpin_reset(g, FALSE);
    gfxSleepMilliseconds(20);
    acquire_bus(g);
    enter_cmd_mode(g);

    write_cmd(g, ST7565_RESET);
    write_cmd(g, ST7565_LCD_BIAS);
    write_cmd(g, ST7565_ADC);
    write_cmd(g, ST7565_COM_SCAN);

    write_cmd(g, ST7565_RESISTOR_RATIO | 0x1);
    write_cmd2(g, ST7565_CONTRAST, GDISP_INITIAL_CONTRAST);

    // turn on internal power supply (VC=1, VR=1, VF=1)
    write_cmd(g, ST7565_POWER_CONTROL | 0x07);

    write_cmd(g, ST7565_INVERT_DISPLAY);
    write_cmd(g, ST7565_ALLON_NORMAL);

    write_cmd(g, ST7565_START_LINE | 0);
    write_cmd(g, ST7565_RMW);
    flush_cmd(g);

    // Finish Init
    post_init_board(g);

    // Release the bus
    release_bus(g);

    /* Initialise the GDISP structure */
    g->g.Width = GDISP_SCREEN_WIDTH;
    g->g.Height = GDISP_SCREEN_HEIGHT;
    g->g.Orientation = GDISP_ROTATE_0;
    g->g.Powermode = powerOff;
    g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
    g->g.Contrast = GDISP_INITIAL_CONTRAST;
    return TRUE;
}

#if GDISP_HARDWARE_FLUSH
LLDSPEC void gdisp_lld_flush(GDisplay *g) {
    unsigned	p;

    // Don't flush if we don't need it.
    if (!(g->flags & GDISP_FLG_NEEDFLUSH))
        return;

    acquire_bus(g);
    enter_cmd_mode(g);
    unsigned dstOffset = (PRIV(g)->buffer2 ? 4 : 0);
    for (p = 0; p < 4; p++) {
        write_cmd(g, ST7565_PAGE | (p + dstOffset));
        write_cmd(g, ST7565_COLUMN_MSB | 0);
        write_cmd(g, ST7565_COLUMN_LSB | 0);
        write_cmd(g, ST7565_RMW);
        flush_cmd(g);
        enter_data_mode(g);
        write_data(g, RAM(g) + (p*GDISP_SCREEN_WIDTH), GDISP_SCREEN_WIDTH);
        enter_cmd_mode(g);
    }
    unsigned line = (PRIV(g)->buffer2 ? 32 : 0);
    write_cmd(g, ST7565_START_LINE | line);
    flush_cmd(g);
    PRIV(g)->buffer2 = !PRIV(g)->buffer2;
    release_bus(g);

    g->flags &= ~GDISP_FLG_NEEDFLUSH;
}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
    coord_t		x, y;

    switch(g->g.Orientation) {
    default:
    case GDISP_ROTATE_0:
        x = g->p.x;
        y = g->p.y;
        break;
    case GDISP_ROTATE_90:
        x = g->p.y;
        y = GDISP_SCREEN_HEIGHT-1 - g->p.x;
        break;
    case GDISP_ROTATE_180:
        x = GDISP_SCREEN_WIDTH-1 - g->p.x;
        y = GDISP_SCREEN_HEIGHT-1 - g->p.y;
        break;
    case GDISP_ROTATE_270:
        x = GDISP_SCREEN_HEIGHT-1 - g->p.y;
        y = g->p.x;
        break;
    }
    if (gdispColor2Native(g->p.color) != Black)
        RAM(g)[xyaddr(x, y)] |= xybit(y);
    else
        RAM(g)[xyaddr(x, y)] &= ~xybit(y);
    g->flags |= GDISP_FLG_NEEDFLUSH;
}
#endif

#if GDISP_HARDWARE_PIXELREAD
LLDSPEC color_t gdisp_lld_get_pixel_color(GDisplay *g) {
    coord_t		x, y;

    switch(g->g.Orientation) {
    default:
    case GDISP_ROTATE_0:
        x = g->p.x;
        y = g->p.y;
        break;
    case GDISP_ROTATE_90:
        x = g->p.y;
        y = GDISP_SCREEN_HEIGHT-1 - g->p.x;
        break;
    case GDISP_ROTATE_180:
        x = GDISP_SCREEN_WIDTH-1 - g->p.x;
        y = GDISP_SCREEN_HEIGHT-1 - g->p.y;
        break;
    case GDISP_ROTATE_270:
        x = GDISP_SCREEN_HEIGHT-1 - g->p.y;
        y = g->p.x;
        break;
    }
    return (RAM(g)[xyaddr(x, y)] & xybit(y)) ? White : Black;
}
#endif

LLDSPEC void gdisp_lld_blit_area(GDisplay *g) {
    uint8_t* buffer = (uint8_t*)g->p.ptr;
    int linelength = g->p.cx;
    for (int i = 0; i < g->p.cy; i++) {
        unsigned dstx = g->p.x;
        unsigned dsty = g->p.y + i;
        unsigned srcx = g->p.x1;
        unsigned srcy = g->p.y1 + i;
        unsigned srcbit = srcy * g->p.x2 + srcx;
        for(int j=0; j < linelength; j++) {
            uint8_t src = buffer[srcbit / 8];
            uint8_t bit = 7-(srcbit % 8);
            uint8_t bitset = (src >> bit) & 1;
            uint8_t* dst = &(RAM(g)[xyaddr(dstx, dsty)]);
            if (bitset) {
                *dst |= xybit(dsty);
            }
            else {
                *dst &= ~xybit(dsty);
            }
			dstx++;
            srcbit++;
        }
    }
    g->flags |= GDISP_FLG_NEEDFLUSH;
}

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
LLDSPEC void gdisp_lld_control(GDisplay *g) {
    switch(g->p.x) {
    case GDISP_CONTROL_POWER:
        if (g->g.Powermode == (powermode_t)g->p.ptr)
            return;
        switch((powermode_t)g->p.ptr) {
        case powerOff:
        case powerSleep:
        case powerDeepSleep:
            acquire_bus(g);
            enter_cmd_mode(g);
            write_cmd(g, ST7565_DISPLAY_OFF);
            flush_cmd(g);
            release_bus(g);
            break;
        case powerOn:
            acquire_bus(g);
            enter_cmd_mode(g);
            write_cmd(g, ST7565_DISPLAY_ON);
            flush_cmd(g);
            release_bus(g);
            break;
        default:
            return;
        }
        g->g.Powermode = (powermode_t)g->p.ptr;
        return;

        case GDISP_CONTROL_ORIENTATION:
            if (g->g.Orientation == (orientation_t)g->p.ptr)
                return;
            switch((orientation_t)g->p.ptr) {
            /* Rotation is handled by the drawing routines */
            case GDISP_ROTATE_0:
            case GDISP_ROTATE_180:
                g->g.Height = GDISP_SCREEN_HEIGHT;
                g->g.Width = GDISP_SCREEN_WIDTH;
                break;
            case GDISP_ROTATE_90:
            case GDISP_ROTATE_270:
                g->g.Height = GDISP_SCREEN_WIDTH;
                g->g.Width = GDISP_SCREEN_HEIGHT;
                break;
            default:
                return;
            }
            g->g.Orientation = (orientation_t)g->p.ptr;
            return;

            case GDISP_CONTROL_CONTRAST:
                g->g.Contrast = (unsigned)g->p.ptr & 63;
                acquire_bus(g);
                enter_cmd_mode(g);
                write_cmd2(g, ST7565_CONTRAST, g->g.Contrast);
                flush_cmd(g);
                release_bus(g);
                return;
    }
}
#endif // GDISP_NEED_CONTROL

#endif // GFX_USE_GDISP
