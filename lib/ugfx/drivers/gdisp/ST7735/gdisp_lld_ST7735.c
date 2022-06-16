/*
 * Created by Oleg Gerasimov <ogerasimov@gmail.com>
 * 14.08.2016
 */
 
#include "gfx.h"

#if GFX_USE_GDISP

#if defined(GDISP_SCREEN_HEIGHT) || defined(GDISP_SCREEN_HEIGHT)
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GDISP: This low level driver does not support setting a screen size. It is being ignored.")
	#endif
	#undef GDISP_SCREEN_WIDTH
	#undef GDISP_SCREEN_HEIGHT
#endif

#define GDISP_DRIVER_VMT			GDISPVMT_ST7735
#include "gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"

#define BOARD_TYPE_B      1
#define BOARD_TYPE_R      2
#define BOARD_TYPE_R144   3
                
#include "board_ST7735.h"

#if !defined(ST7735_TYPE)
// Backward compatibility:
  #if defined(ST7735_TYPE_R)
    #define ST7735_TYPE BOARD_TYPE_R
  #elif defined(ST7735_TYPE_B)
    #define ST7735_TYPE BOARD_TYPE_B
  #endif
#endif

#if !defined(ST7735_TYPE)
  // It seems all modern boards is 7735R
  #define ST7735_TYPE BOARD_TYPE_R
#endif

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
  #if ST7735_TYPE == BOARD_TYPE_R144
    #define GDISP_SCREEN_HEIGHT		128
  #else
    #define GDISP_SCREEN_HEIGHT		160
  #endif
#endif
#ifndef GDISP_SCREEN_WIDTH
    #define GDISP_SCREEN_WIDTH		128
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	100
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

// Define one of supported color packing, if not defined yet
#if !defined(ST7735_COLOR_RGB) && !defined(ST7735_COLOR_BRG)
	// It seems most modern boards are RGB
#if ST7735_TYPE == BOARD_TYPE_R144
	#define ST7735_COLOR_RGB GFXOFF
#else
	#define ST7735_COLOR_RGB GFXON
#endif
#endif


#if ST7735_COLOR_RGB
	#define ST7735_MADCTRL_COLOR 0x00
#else
	#define ST7735_MADCTRL_COLOR 0x08
#endif

#if ST7735_TYPE == BOARD_TYPE_R144
	#define ST7735_COL_SHIFT 2
	#define ST7735_ROW_SHIFT 3
#elif defined(ST7735_SHIFTED_COORDS) && ST7735_SHIFTED_COORDS
	#define ST7735_COL_SHIFT 2
	#define ST7735_ROW_SHIFT 1
#else
	#define ST7735_COL_SHIFT 0
	#define ST7735_ROW_SHIFT 0
#endif


#include "drivers/gdisp/ST7735/st7735.h"

// Some common routines and macros
#define dummy_read(g)				{ volatile gU16 dummy; dummy = read_data(g); (void) dummy; }
#define write_reg(g, reg, data)		{ write_cmd(g, reg); write_data(g, data); }

// Serial write data for fast fill.
#ifndef write_data_repeat
#define write_data_repeat(g, data, count) { int i; for (i = 0; i < count; ++i) write_data (g, data); }
#endif

// Commands list copied from https://github.com/adafruit/Adafruit-ST7735-Library
#define DELAY 0x80

#if ST7735_TYPE == BOARD_TYPE_B
static const unsigned char  
	init_cmds[] = {                  // Initialization commands for 7735B screens
    16,                       // 16 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
      50,                     //     50 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
      255,                    //     255 = 500 ms delay
    ST7735_COLMOD , 1+DELAY,  //  3: Set color mode, 1 arg + delay:
      0x05,                   //     16-bit color
      10,                     //     10 ms delay
    ST7735_FRMCTR1, 3+DELAY,  //  4: Frame rate control, 3 args + delay:
      0x00,                   //     fastest refresh
      0x06,                   //     6 lines front porch
      0x03,                   //     3 lines back porch
      10,                     //     10 ms delay
    ST7735_MADCTL , 1      ,  //  5: Memory access ctrl (directions), 1 arg:
    ST7735_MADCTRL_COLOR,     //     Row addr/col addr, bottom to top refresh
    ST7735_DISSET5, 2      ,  //  6: Display settings #5, 2 args, no delay:
      0x15,                   //     1 clk cycle nonoverlap, 2 cycle gate
                              //     rise, 3 cycle osc equalize
      0x02,                   //     Fix on VTL
    ST7735_INVCTR , 1      ,  //  7: Display inversion control, 1 arg:
      0x0,                    //     Line inversion
    ST7735_PWCTR1 , 2+DELAY,  //  8: Power control, 2 args + delay:
      0x02,                   //     GVDD = 4.7V
      0x70,                   //     1.0uA
      10,                     //     10 ms delay
    ST7735_PWCTR2 , 1      ,  //  9: Power control, 1 arg, no delay:
      0x05,                   //     VGH = 14.7V, VGL = -7.35V
    ST7735_PWCTR3 , 2      ,  // 10: Power control, 2 args, no delay:
      0x01,                   //     Opamp current small
      0x02,                   //     Boost frequency
    ST7735_VMCTR1 , 2+DELAY,  // 11: Power control, 2 args + delay:
      0x3C,                   //     VCOMH = 4V
      0x38,                   //     VCOML = -1.1V
      10,                     //     10 ms delay
    ST7735_PWCTR6 , 2      ,  // 12: Power control, 2 args, no delay:
      0x11, 0x15,
    ST7735_GMCTRP1,16      ,  // 13: Magical unicorn dust, 16 args, no delay:
      0x09, 0x16, 0x09, 0x20, //     (seriously though, not sure what
      0x21, 0x1B, 0x13, 0x19, //      these config values represent)
      0x17, 0x15, 0x1E, 0x2B,
      0x04, 0x05, 0x02, 0x0E,
    ST7735_GMCTRN1,16+DELAY,  // 14: Sparkles and rainbows, 16 args + delay:
      0x0B, 0x14, 0x08, 0x1E, //     (ditto)
      0x22, 0x1D, 0x18, 0x1E,
      0x1B, 0x1A, 0x24, 0x2B,
      0x06, 0x06, 0x02, 0x0F,
      10,                     //     10 ms delay
    ST7735_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
      255 };                  //     255 = 500 ms delay
#elif (ST7735_TYPE == BOARD_TYPE_R) || (ST7735_TYPE == BOARD_TYPE_R144)
static const unsigned char
  init_cmds[] = {                 // Init for 7735R, part 1 (red or green tab)
    19,                       // 19 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x00, 0x0, 0x0,       //     Rate = fosc/(0+40) * (LINE+0+0)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x44,                   //     mode 3
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,  
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      0xC0|ST7735_MADCTRL_COLOR, //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05,                   //     16-bit color
    ST7735_GMCTRP1, 16      , //  1: Gamma + Correction, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Gamma - Correction, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100
      };                  //     100 ms delay
#endif


static void execute_cmds(GDisplay *g, const gU8 *addr) {

	unsigned int cmds = *addr++;
	while (cmds--) {
		write_cmd (g, *addr++);
		unsigned int args = *addr++;
		unsigned int ms = args & DELAY;
		args &= ~DELAY;
		while(args--)
			write_data_byte (g,*addr++);
		if (ms) {
			ms = *addr++;
			gfxSleepMilliseconds(ms==255?500:ms);
		}
	}
}


LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	// No private area for this controller
	g->priv = 0;

	// Initialise the board interface
	init_board(g);

	// Hardware reset
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(20);
	setpin_reset(g, gFalse);
	gfxSleepMilliseconds(20);

	// Get the bus for the following initialisation commands
	acquire_bus(g);
	execute_cmds(g, init_cmds);
	release_bus(g);

	// Finish Init
	post_init_board(g);

	/* Turn on the back-light */
	set_backlight(g, GDISP_INITIAL_BACKLIGHT);

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;
	return gTrue;
}

static void set_viewport(GDisplay *g) {
	write_cmd (g, ST7735_CASET);
	write_data (g, g->p.x+ST7735_COL_SHIFT);
	write_data (g, g->p.x+g->p.cx-1+ST7735_COL_SHIFT);
	write_cmd (g, ST7735_RASET);
	write_data (g, g->p.y+ST7735_ROW_SHIFT);
	write_data (g, g->p.y+g->p.cy-1+ST7735_ROW_SHIFT);
	write_cmd (g, ST7735_RAMWR);
}

#if GDISP_HARDWARE_STREAM_WRITE
LLDSPEC	void gdisp_lld_write_start(GDisplay *g) {
	acquire_bus(g);
	set_viewport(g);
}

LLDSPEC	void gdisp_lld_write_color(GDisplay *g) {
	LLDCOLOR_TYPE	c;
	c = gdispColor2Native(g->p.color);
	write_data(g, c );
}

LLDSPEC	void gdisp_lld_write_stop(GDisplay *g) {
	release_bus(g);
}

#endif

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
	set_viewport(g);
	gdisp_lld_write_color (g);
}

#if GDISP_HARDWARE_FILLS
LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
	LLDCOLOR_TYPE c = gdispColor2Native(g->p.color);

	acquire_bus(g);
	set_viewport (g);
	write_data_repeat (g,c,g->p.cx*g->p.cy);
	release_bus(g);
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
				// not implemented
				release_bus(g);
				set_backlight(g, 0);
				break;
			case gPowerSleep:
			case gPowerDeepSleep:
				// not implemented
				acquire_bus(g);
				release_bus(g);
				set_backlight(g, 0);
				break;
			case gPowerOn:
				acquire_bus(g);
				// not implemented
				release_bus(g);
				set_backlight(g, g->g.Backlight);
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
				write_cmd(g, ST7735_MADCTL);
				write_data_byte(g, 0xC0|ST7735_MADCTRL_COLOR);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				release_bus(g);
				break;
			case gOrientation90:
				acquire_bus(g);
				write_cmd(g, ST7735_MADCTL);
				write_data_byte(g, 0xA0|ST7735_MADCTRL_COLOR);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				release_bus(g);
				break;
			case gOrientation180:
				acquire_bus(g);
				write_cmd(g, ST7735_MADCTL);
				write_data_byte(g, 0x00|ST7735_MADCTRL_COLOR);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				release_bus(g);
				break;
			case gOrientation270:
				acquire_bus(g);
				write_cmd(g, ST7735_MADCTL);
				write_data_byte(g, 0x60|ST7735_MADCTRL_COLOR);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				release_bus(g);
				break;
			default:
				return;
		}
		g->g.Orientation = (gOrientation)g->p.ptr;
		return;
	case GDISP_CONTROL_BACKLIGHT:
		if ((unsigned)g->p.ptr > 100)
			g->p.ptr = (void *)100;
		set_backlight(g, (unsigned)g->p.ptr);
		g->g.Backlight = (unsigned)g->p.ptr;
		return;
	default:
		return;
	}
}
#endif

#endif /* GFX_USE_GDISP */
