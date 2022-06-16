/*
 * Created by Oleg Gerasimov <ogerasimov@gmail.com>
 * 10.08.2016
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

#define GDISP_DRIVER_VMT			GDISPVMT_ILI9225
#include "gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"

#include "board_ILI9225.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		220
#endif
#ifndef GDISP_SCREEN_WIDTH
    #define GDISP_SCREEN_WIDTH		176
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	100
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

#include "drivers/gdisp/ILI9225/ili9225.h"

// Some common routines and macros
#define dummy_read(g)				{ volatile gU16 dummy; dummy = read_data(g); (void) dummy; }
#define write_reg(g, reg, data)		{ write_cmd(g, reg); write_data(g, data); }

// Serial write data for fast fill.
#ifndef write_data_repeat
#define write_data_repeat(g, data, count) { int i; for (i = 0; i < count; ++i) write_data (g, data) }
#endif

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

	write_reg(g, ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
	write_reg(g, ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
	write_reg(g, ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
	write_reg(g, ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
	write_reg(g, ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
	gfxSleepMilliseconds(40);
	// Power-on sequence
	write_reg(g, ILI9225_POWER_CTRL2, 0x0018); // Set APON,PON,AON,VCI1EN,VC
	write_reg(g, ILI9225_POWER_CTRL3, 0x6121); // Set BT,DC1,DC2,DC3
	write_reg(g, ILI9225_POWER_CTRL4, 0x006F); // Set GVDD   /*007F 0088 */
	write_reg(g, ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
	write_reg(g, ILI9225_POWER_CTRL1, 0x0F00); // Set SAP,DSTB,STB
	gfxSleepMilliseconds(10);
	write_reg(g, ILI9225_POWER_CTRL2, 0x103B); // Set APON,PON,AON,VCI1EN,VC
	gfxSleepMilliseconds(50);
	write_reg(g, ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
	write_reg(g, ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
	write_reg(g, ILI9225_ENTRY_MODE, 0x1030); // set GRAM write direction and BGR=1.
	write_reg(g, ILI9225_DISP_CTRL1, 0x0000); // Display off
	write_reg(g, ILI9225_BLANK_PERIOD_CTRL1, 0x0808); // set the back porch and front porch
	write_reg(g, ILI9225_FRAME_CYCLE_CTRL, 0x1100); // set the clocks number per line
	write_reg(g, ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
	write_reg(g, ILI9225_OSC_CTRL, 0x0D01); // Set Osc  /*0e01*/
	write_reg(g, ILI9225_VCI_RECYCLING, 0x0020); // Set VCI recycling
	write_reg(g, ILI9225_RAM_ADDR_SET1, 0x0000); // RAM Address
	write_reg(g, ILI9225_RAM_ADDR_SET2, 0x0000); // RAM Address
	// Set GRAM area
	write_reg(g, ILI9225_GATE_SCAN_CTRL, 0x0000);
	write_reg(g, ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB);
	write_reg(g, ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000);
	write_reg(g, ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000);
	write_reg(g, ILI9225_PARTIAL_DRIVING_POS1, 0x00DB);
	write_reg(g, ILI9225_PARTIAL_DRIVING_POS2, 0x0000);
	write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF);
	write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000);
	write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB);
	write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000);

	// Set GAMMA curve
	write_reg(g, ILI9225_GAMMA_CTRL1, 0x0000);
	write_reg(g, ILI9225_GAMMA_CTRL2, 0x0808);
	write_reg(g, ILI9225_GAMMA_CTRL3, 0x080A);
	write_reg(g, ILI9225_GAMMA_CTRL4, 0x000A);
	write_reg(g, ILI9225_GAMMA_CTRL5, 0x0A08);
	write_reg(g, ILI9225_GAMMA_CTRL6, 0x0808);
	write_reg(g, ILI9225_GAMMA_CTRL7, 0x0000);
	write_reg(g, ILI9225_GAMMA_CTRL8, 0x0A00);
	write_reg(g, ILI9225_GAMMA_CTRL9, 0x0710);
	write_reg(g, ILI9225_GAMMA_CTRL10, 0x0710);

	write_reg(g, ILI9225_DISP_CTRL1, 0x0012);
	gfxSleepMilliseconds(50);
	write_reg(g, ILI9225_DISP_CTRL1, 0x1017);

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

static void set_cursor(GDisplay *g) {
	switch(g->g.Orientation) {
		default:
		case gOrientation0:
		case gOrientation180:
			write_reg(g, ILI9225_RAM_ADDR_SET1, g->p.x);
			write_reg(g, ILI9225_RAM_ADDR_SET2, g->p.y);
			break;

		case gOrientation90:
		case gOrientation270:
			write_reg(g, ILI9225_RAM_ADDR_SET1, g->p.y);
			write_reg(g, ILI9225_RAM_ADDR_SET2, g->p.x);
			break;
	}
	write_cmd (g, ILI9225_GRAM_DATA_REG);
}

static void set_viewport(GDisplay *g) {
	switch(g->g.Orientation) {
		default:
		case gOrientation0:
		case gOrientation180:
			write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR2, g->p.x);
			write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR1, g->p.x + g->p.cx - 1);
			write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR2, g->p.y);
			write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR1, g->p.y + g->p.cy - 1);
			break;

		case gOrientation90:
		case gOrientation270:
			write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR2, g->p.y);
			write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR1, g->p.y + g->p.cy - 1);
			write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR2, g->p.x);
			write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR1, g->p.x + g->p.cx - 1);
		break;
	}
}


// temporary variables for saving viewport
static int svx,svy,svcx,svcy,ws;

#if GDISP_HARDWARE_STREAM_WRITE
LLDSPEC	void gdisp_lld_write_start(GDisplay *g) {
	acquire_bus(g);
	set_viewport(g);

	// save viewport
	switch(g->g.Orientation) {
		default:
		case gOrientation0:
		case gOrientation180:
			svx = g->p.x; svy = g->p.y; svcx = g->p.cx; svcy = g->p.cy;
			break;
		case gOrientation90:
		case gOrientation270:
			svx = g->p.y; svy = g->p.x; svcx = g->p.cy; svcy = g->p.cx;
			break;
	}
	ws++;
}

LLDSPEC	void gdisp_lld_write_color(GDisplay *g) {
	LLDCOLOR_TYPE	c;
	c = gdispColor2Native(g->p.color);
	write_data(g, c );
}

LLDSPEC	void gdisp_lld_write_stop(GDisplay *g) {
	release_bus(g);
	if (ws)
		ws--;
}

LLDSPEC void gdisp_lld_write_pos(GDisplay *g) {
	set_cursor(g);
}
#endif

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
	set_cursor(g);
	gdisp_lld_write_color (g);

}

#if GDISP_HARDWARE_FILLS
LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
	LLDCOLOR_TYPE c = gdispColor2Native(g->p.color);

	acquire_bus(g);

	// Set view port if drawing more than 1 line, or write not started
	if (g->p.cy != 1 || !ws)
		set_viewport(g);

	set_cursor(g);
	write_data_repeat (g,c,g->p.cx*g->p.cy);

	// Restore view port if write started and drawed more than 1 line
	if (g->p.cy != 1 && ws)
	{
		write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR2, svx);
		write_reg(g, ILI9225_HORIZONTAL_WINDOW_ADDR1, svx + svcx - 1);
		write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR2, svy);
		write_reg(g, ILI9225_VERTICAL_WINDOW_ADDR1, svy + svcy - 1);
	}
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
				write_reg(g, ILI9225_DISP_CTRL1, 0x0000); // Display off
				write_reg(g, ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
				write_reg(g, ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
				write_reg(g, ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
				write_reg(g, ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
				write_reg(g, ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
				release_bus();
				set_backlight(g, 0);
				break;
			case gPowerSleep:
			case gPowerDeepSleep:
				acquire_bus(g);
				write_reg(g, ILI9225_DISP_CTRL1, 0x0000); // Display off
				write_reg(g, ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
				write_reg(g, ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
				write_reg(g, ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
				write_reg(g, ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
				gfxSleepMilliseconds(40);
				write_reg(g, ILI9225_POWER_CTRL1, 0x0004); // Set SAP,DSTB,STB
				release_bus(g);
				set_backlight(g, 0);
				break;
			case gPowerOn:
				acquire_bus(g);
				write_reg(g, ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
				write_reg(g, ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
				write_reg(g, ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
				write_reg(g, ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
				write_reg(g, ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
				gfxSleepMilliseconds(40);
				// Power-on sequence
				write_reg(g, ILI9225_POWER_CTRL2, 0x0018); // Set APON,PON,AON,VCI1EN,VC
				write_reg(g, ILI9225_POWER_CTRL3, 0x6121); // Set BT,DC1,DC2,DC3
				write_reg(g, ILI9225_POWER_CTRL4, 0x006F); // Set GVDD   /*007F 0088 */
				write_reg(g, ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
				write_reg(g, ILI9225_POWER_CTRL1, 0x0F00); // Set SAP,DSTB,STB
				gfxSleepMilliseconds(10);
				write_reg(g, ILI9225_POWER_CTRL2, 0x103B); // Set APON,PON,AON,VCI1EN,VC
				gfxSleepMilliseconds(50);
				write_reg(g, ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
				write_reg(g, ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
				write_reg(g, ILI9225_ENTRY_MODE, 0x1030); // set GRAM write direction and BGR=1.
				write_reg(g, ILI9225_DISP_CTRL1, 0x0000); // Display off
				write_reg(g, ILI9225_BLANK_PERIOD_CTRL1, 0x0808); // set the back porch and front porch
				write_reg(g, ILI9225_FRAME_CYCLE_CTRL, 0x1100); // set the clocks number per line
				write_reg(g, ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
				write_reg(g, ILI9225_OSC_CTRL, 0x0D01); // Set Osc  /*0e01*/
				write_reg(g, ILI9225_VCI_RECYCLING, 0x0020); // Set VCI recycling
				// Set GRAM area
				write_reg(g, ILI9225_GATE_SCAN_CTRL, 0x0000);
				write_reg(g, ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB);
				write_reg(g, ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000);
				write_reg(g, ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000);
				write_reg(g, ILI9225_PARTIAL_DRIVING_POS1, 0x00DB);
				write_reg(g, ILI9225_PARTIAL_DRIVING_POS2, 0x0000);
				write_reg(g, ILI9225_DISP_CTRL1, 0x0012);
				gfxSleepMilliseconds(50);
				write_reg(g, ILI9225_DISP_CTRL1, 0x1017);
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
			case gOrientation0: // correct
				acquire_bus(g);
				write_reg(g, ILI9225_DRIVER_OUTPUT_CTRL, 0x011C);
				write_reg(g, ILI9225_ENTRY_MODE, 0x1030);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				release_bus(g);
				break;
			case gOrientation90:
				acquire_bus(g);
				write_reg(g, ILI9225_DRIVER_OUTPUT_CTRL, 0x031C);
				write_reg(g, ILI9225_ENTRY_MODE, 0x1038);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				release_bus(g);
				break;
			case gOrientation180:
				acquire_bus(g);
				write_reg(g, ILI9225_DRIVER_OUTPUT_CTRL, 0x021C);
				write_reg(g, ILI9225_ENTRY_MODE, 0x1030);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				release_bus(g);
				break;
			case gOrientation270:
				acquire_bus(g);
				write_reg(g, ILI9225_DRIVER_OUTPUT_CTRL, 0x001C);
				write_reg(g, ILI9225_ENTRY_MODE, 0x1038);
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
