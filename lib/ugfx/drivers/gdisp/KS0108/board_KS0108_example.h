/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */
/* KS0107/0108 Driver
 * Pinout: There are at least two different Pinouts!
 * Version 1:
 * 1 - CS1       High Active
 * 2 - CS2       High Active
 * 3 - GND
 * 4 - 5V
 * 5 - CONTRAST
 * 6 - RS(=DC)   High = Data, Low = Command
 * 7 - R/W       High = Read, Low = Write
 * 8 - E         Data is KS0108_latched at the falling Edge
 * 9..16 - D0..7
 * Version 2:
 * 1 - GND
 * 2 - 5V
 * 3 - Vo (Operating Voltage for LCD)
 * 4 - RS         High = Data, Low = Command
 * 5 - R/W        High = Read, Low = Write
 * 6 - E          Data is KS0108_latched at the falling Edge
 * 7..14 - D0..7
 * 15 - CS1       High Active
 * 16 - CS2       High Active
 * 17 - /RST      Low Active
 * 18 - Vout (Output voltage for LCD)
 * 19 - LEDA
 * 20 - LEDK
 *
 */
#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

// My Settings
#define GDISP_SCREEN_HEIGHT				64
#define GDISP_SCREEN_WIDTH				128
#define KS0108_NEED_READ                GFXOFF
#define KS0108_HAS_RESET                GFXOFF
#define KS0108_NEED_BACKLIGHT           GFXOFF
#define KS0108_NEED_PWMBACKLIGHT        GFXOFF
#define KS0108_NOP_DLY                  GFXON  //doesn't work for me without!

#define LINE_D0      PAL_LINE(GPIOB, 0U)
#define LINE_D1      PAL_LINE(GPIOB, 1U)
#define LINE_D2      PAL_LINE(GPIOB, 2U)
#define LINE_D3      PAL_LINE(GPIOB, 3U)
#define LINE_D4      PAL_LINE(GPIOB, 4U)
#define LINE_D5      PAL_LINE(GPIOB, 5U)
#define LINE_D6      PAL_LINE(GPIOB, 6U)
#define LINE_D7      PAL_LINE(GPIOB, 7U)
#define LINE_BUSY    PAL_LINE(GPIOB, 7U)
#define LINE_CS1     PAL_LINE(GPIOB, 8U)
#define LINE_CS2     PAL_LINE(GPIOB, 9U)
#define LINE_E       PAL_LINE(GPIOB, 10U)
#define LINE_DC      PAL_LINE(GPIOB, 11U)
#if KS0108_NEED_READ
	#define LINE_RW      PAL_LINE(GPIOB, 12U)
#endif
#if KS0108_NEED_BACKLIGHT
	#define LINE_BL      PAL_LINE(GPIOB, 13U)
#endif
#if KS0108_HAS_RESET
	#define LINE_RESET   PAL_LINE(GPIOB, 13U)
#endif

typedef struct {
	ioline_t CS1;	// Chip Select1 PIN
	ioline_t CS2;	// Chip Select2 PIN
	ioline_t DC;	// Register selector PIN
	ioline_t E;		// Enable PIN
	ioline_t BUSY;	// Busy PIN (Same as D[7])
	#if KS0108_NEED_READ
		ioline_t RW;	// Read/Write PIN
	#endif
	#if KS0108_HAS_RESET
		ioline_t RST;	// Reset PIN
	#endif
	#if KS0108_NEED_BACKLIGHT
		ioline_t BL;	// Backlight PIN
	#endif
	ioline_t	D[8];
	ioline_t	CS[CHIPS];
	} lcd_pins_t;
	
/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/
static const lcd_pins_t lcdpins = {
	LINE_CS1,
	LINE_CS2,
	LINE_DC,
	LINE_E,
	LINE_BUSY,
	#if KS0108_NEED_READ
		LINE_RW,
	#endif
	#if KS0108_HAS_RESET
		LINE_RST,
	#endif
	#if KS0108_NEED_BACKLIGHT
		LINE_BL,
	#endif
	{
		LINE_D0,
		LINE_D1,
		LINE_D2,
		LINE_D3,
		LINE_D4,
		LINE_D5,
		LINE_D6,
		LINE_D7
	},
	{
		LINE_CS1,
		LINE_CS2
	}
};

static GFXINLINE void init_board(GDisplay* g){
	(void) g;
	g->board = 0;
	int ii;

	for (ii = 0; ii < CHIPS; ii++){
		palSetLineMode(lcdpins.CS[ii], PAL_MODE_OUTPUT_PUSHPULL);
		palClearLine(lcdpins.CS[ii]);
	}
	palSetLineMode(lcdpins.DC,  PAL_MODE_OUTPUT_PUSHPULL);
	palClearLine(lcdpins.DC);
	palSetLineMode(lcdpins.E,   PAL_MODE_OUTPUT_PUSHPULL);
	palSetLine(lcdpins.E);
	#if KS0108_NEED_READ
		palSetLineMode(lcdpins.RW,  PAL_MODE_OUTPUT_PUSHPULL);
		palClearLine(lcdpins.RW);
	#endif
	#if KS0108_HAS_RESET
		palSetLineMode(lcdpins.RST, PAL_MODE_OUTPUT_PUSHPULL);
		palSetLine(lcdpins.RST);
	#endif
	for(ii = 0; ii < 8; ii++) {
		palSetLineMode(lcdpins.D[ii],  PAL_MODE_OUTPUT_PUSHPULL);
		palClearLine(lcdpins.D[ii]);
	}
	#if KS0108_NEED_BACKLIGHT
		#if KS0108_NEED_PWMBACKLIGHT
			palSetLineMode(lcdpins.BL,   PAL_MODE_ALTERNATE(1));
		#else
			palSetLineMode(lcdpins.BL,   PAL_MODE_OUTPUT_PUSHPULL);
		#endif
	#endif
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;
	(void) state;
	
	#if KS0108_HAS_RESET  //Make Hardware Reset
		if (state)
		  palClearLine(lcdpins.RST);
		else
		  palSetLine(lcdpins.RST);
	#endif
}

static GFXINLINE void set_backlight(GDisplay *g, gU8 percent) {
  (void) g;
  (void) percent;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}

void KS0108_delay(gU16 microsec){
	#if KS0108_NOP_DLY
		gU16 cn;
		for (cn=0;cn< microsec;cn++){

			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");

			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");

			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");

			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");asm("nop");

			//asm("nop");asm("nop");asm("nop");asm("nop");
			//asm("nop");asm("nop");asm("nop");asm("nop");
			//1us
		}
	#else
		gfxSleepMicroseconds(microsec);
	#endif
}

static GFXINLINE void KS0108_latch(void){
	palClearLine(lcdpins.E);
	KS0108_delay(1);
	palSetLine(lcdpins.E);
}

static GFXINLINE void KS0108_write(gU8 value){
	int ii;

	for(ii = 0; ii < 8; ii++){
		if(value & (1 << ii))
			palSetLine(lcdpins.D[ii]);
		else
			palClearLine(lcdpins.D[ii]);
	}
	KS0108_delay(1);
}

static GFXINLINE void KS0108_select(gU8 chip){
	gU8 ii;
	KS0108_delay(1);
	for (ii = 0; ii < CHIPS; ii++){
		if (ii == chip)
			palSetLine(lcdpins.CS[ii]);
	}
	KS0108_delay(1);
}

static GFXINLINE void KS0108_unselect(void){
	gU8 ii;
	
	KS0108_delay(1);
	for (ii = 0; ii < CHIPS; ii++){
		palClearLine(lcdpins.CS[ii]);
	}
}

/*
#if KS0108_NEED_READ  //Hardware Read ##############  WORKS more or less
static GFXINLINE gU8 read_KS0108(void) {
  gU8 ii, data=0;

  for(ii = 0; ii < 8; ii++)
    palSetLineMode(lcdpins.D[ii], PAL_MODE_INPUT);  //Set pads to input
  palSetLine(lcdpins.RW);
  KS0108_delay(1);
  palClearLine(lcdpins.E);
  KS0108_delay(1);
  palSetLine(lcdpins.E);
  KS0108_delay(1);
//  palClearLine(lcdpins.RW);
//  KS0108_delay(1);
//  palSetLine(lcdpins.RW);
//  KS0108_delay(1);
  for(ii = 0; ii < 8; ii++){
    if (palReadLine(lcdpins.D[ii]) == PAL_HIGH){ //Read output
      data |= (1<<ii);
    }
  }
//  palClearLine(lcdpins.E);
  palClearLine(lcdpins.RW);                //Write again
  for(ii = 0; ii < 8; ii++) {
    palSetLineMode(lcdpins.D[ii],  PAL_MODE_OUTPUT_PUSHPULL);  //Set pads to output
  }
  return data;
}
#endif
*/
#if KS0108_NEED_READ  //Hardware Read ########### needs more testing but my display is broken
static GFXINLINE gU8 read_KS0108(void) {
	gU8 ii, data=0;

	for(ii = 0; ii < 8; ii++)
		palSetLineMode(lcdpins.D[ii], PAL_MODE_INPUT);  //Set pads to input
	palSetLine(lcdpins.RW);
	KS0108_delay(1);

	palClearLine(lcdpins.DC);
	KS0108_delay(1);


	while (palReadLine(lcdpins.BUSY)); //Wait for busy flag
	palSetLine(lcdpins.DC);
	/*
	KS0108_delay(2);
	KS0108_latch();
	KS0108_delay(2);
	//KS0108_latch();
	//KS0108_delay(1);
	*/
	palClearLine(lcdpins.RW);
	KS0108_delay(2);
	palSetLine(lcdpins.RW);
	KS0108_delay(1);
	palClearLine(lcdpins.DC);
	KS0108_delay(1);
	while (palReadLine(lcdpins.BUSY)); //Wait for busy flag
	//KS0108_delay(7);
	palSetLine(lcdpins.DC);

	//KS0108_delay(1);
	//KS0108_latch();
	//KS0108_delay(3);

	KS0108_delay(1);
	for(ii = 0; ii < 8; ii++){
		if (palReadLine(lcdpins.D[ii]) == PAL_HIGH) //Read output
			data |= (1<<ii);
	}
	//  palClearLine(lcdpins.E);
	palSetLine(lcdpins.DC);
	palClearLine(lcdpins.RW);                //Write again
	for(ii = 0; ii < 8; ii++) {
		palSetLineMode(lcdpins.D[ii],  PAL_MODE_OUTPUT_PUSHPULL);  //Set pads to output
	}
	return data;
}
#endif

static GFXINLINE void write_data(GDisplay* g, gU16 data){
	(void)g;
	gU8 bit, displayData;
	#if !KS0108_NEED_READ
		gU8	*p;
	#endif
	
	palSetLine(lcdpins.DC);
	KS0108_select((gU8)(data>>8));
	#if KS0108_NEED_READ
		displayData=read_KS0108();
	#else
		p = RAM(g) + (GDISP_SCREEN_WIDTH*(g->p.y >> 3)) + g->p.x;
		displayData = *p;
	#endif
	bit = 1 << (g->p.y & 7);			//Get Page bit

	if ((gU8)data){              //set bit
		KS0108_write(displayData | bit);
		#if !KS0108_NEED_READ
			*p = (displayData | bit);
		#endif
		KS0108_latch();
	} else {
		KS0108_write(displayData & ~bit);
		#if !KS0108_NEED_READ
			*p = (displayData & ~bit);
		#endif
		KS0108_latch();
	}
	KS0108_delay(2);          //one is too short!
	KS0108_unselect();        //Important
}

static GFXINLINE void write_cmd(GDisplay* g, gU16 cmd){
	(void)g;
	palClearLine(lcdpins.DC);
	KS0108_select((gU8)(cmd>>8));
	KS0108_write((gU8)cmd);
	KS0108_latch();
	KS0108_unselect();         //Important
}

static GFXINLINE void setreadmode(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g) {
	(void) g;
}

static GFXINLINE gU16 read_data(GDisplay *g) {
	(void) g;
	return 0;
}
#endif /* _GDISP_LLD_BOARD_H */
