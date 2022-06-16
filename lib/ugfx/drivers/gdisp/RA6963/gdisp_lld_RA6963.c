/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */
/* Robert Offner 2017
 * This is a driver for the RA6963 or T6963 Displays.
 * It should work with displays up to 240 pixel in width and 64 pixel in height
 * ATTENTION some newer displays on ebay look like T6963 Type but they're not!
 * They use a new controller: ST7920. These are easy to identify: NO CS pin but
 * a PSB Pin which switches from parallel to serial communication mode.
 * If it cost less than 10.- it is probably a ST7920.
 *
 * Version: 0.1
 *
 * History:
 *
 * v0.1 Initial Release
 * .) tested with readback and without on a 72MHz STM32F103. Display ws a 128x64
 *    type Graphic LCD (Looks like KS0108 Types). STREAM_READ is not implemented.
 */
#include "gfx.h"

#if GFX_USE_GDISP
#define GDISP_DRIVER_VMT			GDISPVMT_RA6963

#include "gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#if defined(GDISP_SCREEN_HEIGHT) || defined(GDISP_SCREEN_HEIGHT)
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GDISP: This low level driver does not support setting a screen size. It is being ignored.")
	#endif
	#undef GDISP_SCREEN_WIDTH
	#undef GDISP_SCREEN_HEIGHT
#endif

#include "board_RA6963.h"

// RA6963 Commands
//Register Setting
#define RA6963_SET_CURSOR_POINTER           0x21
#define RA6963_SET_OFFSET_REGISTER          0x22
#define RA6963_SET_ADDRESS_POINTER          0x24
//Set Control Word
#define RA6963_SET_TEXT_HOME_ADDRESS        0x40
#define RA6963_SET_TEXT_AREA                0x41
#define RA6963_SET_GRAPHIC_HOME_ADDRESS     0x42
#define RA6963_SET_GRAPHIC_AREA             0x43
//Mode Set
#define RA6963_MODE_SET                     0x80
#define RA6963_MODE_OR                      0x00
#define RA6963_MODE_XOR                     0x01
#define RA6963_MODE_AND                     0x03
#define RA6963_MODE_TEXT_ATTRIBUTE          0x04
#define RA6963_MODE_INTERNAL_CGROM          0x00
#define RA6963_MODE_EXTERNAL_CGRAM          0x08
//Display Mode
#define RA6963_DISPLAY_MODE                 0x90
#define RA6963_CURSOR_BLINK_ON              0x01
#define RA6963_CURSOR_DISPLAY_ON            0x02
#define RA6963_TEXT_DISPLAY_ON              0x04
#define RA6963_GRAPHIC_DISPLAY_ON           0x08
//Cursor Pattern Select
#define RA6963_CURSOR_PATTERN_SELECT        0xA0
#define RA6963_CURSOR_1_LINE                0x00
#define RA6963_CURSOR_2_LINE                0x01
#define RA6963_CURSOR_3_LINE                0x02
#define RA6963_CURSOR_4_LINE                0x03
#define RA6963_CURSOR_5_LINE                0x04
#define RA6963_CURSOR_6_LINE                0x05
#define RA6963_CURSOR_7_LINE                0x06
#define RA6963_CURSOR_8_LINE                0x07
//Data Read/Write
#define RA6963_DATA_WRITE_AND_INCREMENT     0xC0
#define RA6963_DATA_READ_AND_INCREMENT      0xC1
#define RA6963_DATA_WRITE_AND_DECREMENT     0xC2
#define RA6963_DATA_READ_AND_DECREMENT      0xC3
#define RA6963_DATA_WRITE_AND_NONVARIALBE   0xC4
#define RA6963_DATA_READ_AND_NONVARIABLE    0xC5
//Data auto Read/Write
#define RA6963_SET_DATA_AUTO_WRITE          0xB0
#define RA6963_SET_DATA_AUTO_READ           0xB1
#define RA6963_AUTO_RESET                   0xB2
//Screen Peek
#define RA6963_SCREEN_PEEK                  0xE0
//Screen copy
#define RA6963_SCREEN_COPY                  0xE8
// Status Register Bits
#define RA6963_STATUS_BUSY1    0x01
#define RA6963_STATUS_BUSY2    0x02
#define RA6963_STATUS_DARRDY   0x04
#define RA6963_STATUS_DAWRDY   0x08

#ifndef GDISP_SCREEN_HEIGHT
  #define GDISP_SCREEN_HEIGHT		  64
#endif
#ifndef GDISP_SCREEN_WIDTH
  #define GDISP_SCREEN_WIDTH		  128
#endif

#define RA6963_FONT_WIDTH         8

#define RA6963_GRAPHIC_AREA     (GDISP_SCREEN_WIDTH / RA6963_FONT_WIDTH)   //16
#define RA6963_TEXT_AREA        (GDISP_SCREEN_WIDTH / RA6963_FONT_WIDTH)   //16
#define RA6963_GRAPHIC_SIZE     (RA6963_GRAPHIC_AREA * GDISP_SCREEN_HEIGHT) //1024
#define RA6963_TEXT_SIZE        (RA6963_TEXT_AREA * (GDISP_SCREEN_HEIGHT/8))//128
//#define RA6963_TEXT_HOME         0
//#define RA6963_GRAPHIC_HOME     (RA6963_TEXT_HOME + RA6963_TEXT_SIZE)          //128
#define RA6963_GRAPHIC_HOME      0
#define RA6963_TEXT_HOME       (RA6963_GRAPHIC_HOME + RA6963_GRAPHIC_SIZE)
//#define RA6963_OFFSET_REGISTER   2

#if !RA6963_NEED_READ
	#define BUFFSZ (RA6963_GRAPHIC_SIZE)
	#define RAM(g) ((gU8 *)g->priv)
	#define POS (((g->p.x) / RA6963_FONT_WIDTH) + ((g->p.y) * RA6963_GRAPHIC_AREA))
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif


/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
#ifndef write_data_repeat
#define write_data_repeat(g, data, count) { int i; for (i = 0; i < count; ++i) write_data (g, data); }
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
#if RA6963_NEED_READ
  g->priv = 0;
#else
  // The private area is the display surface.
  g->priv = gfxAlloc(BUFFSZ);
#endif
  // Initialise the board interface
  init_board(g);

#if RA6963_HAS_RESET  //Make Hardware Reset
  setpin_reset(g, gTrue);
  gfxSleepMilliseconds(100);
  setpin_reset(g, gFalse);
#endif
  gfxSleepMilliseconds(50);
  //RA6963 needs Data first THEN command!

  write_data(g, (gU8)RA6963_GRAPHIC_HOME);             //0
  write_data(g, (gU8)(RA6963_GRAPHIC_HOME>>8));        //0
  write_cmd(g, RA6963_SET_GRAPHIC_HOME_ADDRESS);           //0x42

  write_data(g, (gU8)RA6963_GRAPHIC_AREA);             //16
  write_data(g, 0);                                        //0
  write_cmd(g, RA6963_SET_GRAPHIC_AREA);                   //0x43

  write_data(g, (gU8)RA6963_TEXT_HOME);                //0x00
  write_data(g, (gU8)(RA6963_TEXT_HOME>>8));           //0x04 = 0x400
  write_cmd(g, RA6963_SET_TEXT_HOME_ADDRESS);              //0x40

  write_data(g, (gU8)RA6963_TEXT_AREA);                //16
  write_data(g, (gU8)(RA6963_TEXT_AREA>>8));           //0
  write_cmd(g, RA6963_SET_TEXT_AREA);                      //0x41

/*  write_data(g, (gU8)RA6963_OFFSET_REGISTER);
  write_data(g, 0);
  write_cmd(g, RA6963_SET_OFFSET_REGISTER);*/

  write_data(g, 0x00);
  write_data(g, 0x00);
  write_cmd(g, RA6963_SET_ADDRESS_POINTER);

  write_data(g, 0x00);
  write_data(g, 0x00);
  write_cmd(g, RA6963_SET_CURSOR_POINTER);


  //write_cmd(g, RA6963_CURSOR_PATTERN_SELECT | RA6963_CURSOR_1_LINE);
  write_cmd(g, RA6963_MODE_SET | RA6963_MODE_OR);
  //write_cmd(g, RA6963_DISPLAY_MODE | RA6963_TEXT_DISPLAY_ON | RA6963_GRAPHIC_DISPLAY_ON);
  write_cmd(g, RA6963_DISPLAY_MODE | RA6963_GRAPHIC_DISPLAY_ON);

  // Finish Init
  post_init_board(g);
#if RA6963_NEED_BACKLIGHT
  // Turn on the back-light
  set_backlight(g, GDISP_INITIAL_BACKLIGHT);
#endif
  // Initialise the GDISP structure
  g->g.Width = GDISP_SCREEN_WIDTH;
  g->g.Height = GDISP_SCREEN_HEIGHT;
  g->g.Orientation = gOrientation0;
  g->g.Powermode = gPowerOn;
  g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
  g->g.Contrast = GDISP_INITIAL_CONTRAST;

  return gTrue;
}

static void set_viewport(GDisplay *g) {
  if ((g->p.x >= GDISP_SCREEN_WIDTH) || (g->p.y >= GDISP_SCREEN_HEIGHT))
    return;         //     0           + (  x      /         8        ) + (  y      *        16           )
  //gU16 addr = (RA6963_GRAPHIC_HOME + ((g->p.x) / RA6963_FONT_WIDTH) + ((g->p.y) * RA6963_GRAPHIC_AREA));
  gU16 addr = (RA6963_GRAPHIC_HOME + ((g->p.x >> 3) + (g->p.y << 4)));
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "check function set_viewport about the shift operations if you change the resolution!"
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("check function set_viewport about the shift operations if you change the resolution!")
	#endif
  write_data(g, (gU8)addr);
  write_data(g, (gU8)(addr>>8));
  write_cmd(g, RA6963_SET_ADDRESS_POINTER);
}

LLDSPEC void gdisp_lld_write_color(GDisplay *g) {
  gU8 temp;

#if RA6963_NEED_READ
  temp = read_data(g);
#else
  temp = RAM(g)[POS];
#endif

  if (g->p.color != GFX_WHITE) {
    temp |= (1 << (RA6963_FONT_WIDTH - 1 - ((g->p.x) % RA6963_FONT_WIDTH)));
  }
  else {
    temp &= ~(1 << (RA6963_FONT_WIDTH - 1 - ((g->p.x) % RA6963_FONT_WIDTH)));
  }

  write_data(g, temp);
#if !RA6963_NEED_READ
  RAM(g)[POS] = temp;
#endif
  //write_cmd(g, RA6963_DATA_WRITE_AND_INCREMENT);
  write_cmd(g, RA6963_DATA_WRITE_AND_NONVARIALBE);

}

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
  set_viewport(g);
  gdisp_lld_write_color(g);
}

#if GDISP_HARDWARE_STREAM_WRITE
LLDSPEC void gdisp_lld_write_start(GDisplay *g) {
  //acquire_bus(g);
  set_viewport(g);
}

LLDSPEC void gdisp_lld_write_stop(GDisplay *g) {
  //release_bus(g);
}
#endif

#if GDISP_HARDWARE_STREAM_READ
LLDSPEC void gdisp_lld_read_start(GDisplay *g) {
  acquire_bus(g);
  set_viewport(g);
  setreadmode(g);
  dummy_read(g);
}

LLDSPEC gColor gdisp_lld_read_color(GDisplay *g) {
  gU16 data;

  data = read_data(g);
  return gdispNative2Color(data);
}

LLDSPEC void gdisp_lld_read_stop(GDisplay *g) {
  setwritemode(g);
  release_bus(g);
}
#endif

#if GDISP_HARDWARE_FILLS
LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
  gU8 data, j;
  set_viewport(g);

  if (g->p.color != GFX_WHITE) {
    data = 0xFF;              // set dot
  }
  else {
    data = 0;              // clr dot
  }
  for (j=0; j < (g->p.cy)/8; j++) {
    write_data_repeat(g, data, (g->p.cx));
    (g->p.cy) +=8;
    set_viewport(g);
  }

}
#endif // GDISP_HARDWARE_FILLS

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
LLDSPEC void gdisp_lld_control(GDisplay *g) {
  switch(g->p.x) {
    case GDISP_CONTROL_POWER:
    if (g->g.Powermode == (gPowermode)g->p.ptr)
    return;

    switch((gPowermode)g->p.ptr) {
      case gPowerOff:
      acquire_bus(g);
      write_index(g, 0x28);
      gfxSleepMilliseconds(10);
      write_index(g, 0x10);
      release_bus(g);
      break;

      case gPowerOn:
      acquire_bus(g);
      write_index(g, 0x11);
      gfxSleepMilliseconds(120);
      write_index(g, 0x29);
      release_bus(g);
      if (g->g.Powermode != gPowerSleep)
      gdisp_lld_init(g);
      break;

      case gPowerSleep:
      acquire_bus(g);
      write_index(g, 0x28);
      gfxSleepMilliseconds(10);
      write_index(g, 0x10);
      release_bus(g);
      break;

      default:
      return;
    }

    g->g.Powermode = (gPowermode)g->p.ptr;
    return;

    case GDISP_CONTROL_ORIENTATION:
    if (g->g.Orientation == (gOrientation)g->p.ptr)
    return;

    switch((gOrientation)g->p.ptr) {
      case gOrientation0:
      acquire_bus(g);

      write_index(g, 0x36);
      write_data(g, 0x08);

      release_bus(g);
      g->g.Height = GDISP_SCREEN_HEIGHT;
      g->g.Width = GDISP_SCREEN_WIDTH;
      break;

      case gOrientation90:
      acquire_bus(g);

      write_index(g, 0x36);
      write_data(g, 0x68);

      release_bus(g);
      g->g.Height = GDISP_SCREEN_WIDTH;
      g->g.Width = GDISP_SCREEN_HEIGHT;
      break;

      case gOrientation180:
      acquire_bus(g);

      write_index(g, 0x36);
      write_data(g, 0xC8);

      release_bus(g);
      g->g.Height = GDISP_SCREEN_HEIGHT;
      g->g.Width = GDISP_SCREEN_WIDTH;
      break;

      case gOrientation270:
      acquire_bus(g);

      write_index(g, 0x36);
      write_data(g, 0xA8);

      release_bus(g);
      g->g.Height = GDISP_SCREEN_WIDTH;
      g->g.Width = GDISP_SCREEN_HEIGHT;
      break;

      default:
      return;
    }

    g->g.Orientation = (gOrientation)g->p.ptr;
    return;

    default:
    return;
  }
}
#endif

#endif /* GFX_USE_GDISP */
