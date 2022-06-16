/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* RA6963 Driver
 * Pinout:
 * Version 1:
 * 1 - Vee       Negative Voltage Output
 * 2 - GND       GND
 * 3 - +5V
 * 4 - Vo        LCD Driver Supply (10-20k Pot between +5V and Vee)
 * 5 - /WR       Write (Low active)
 * 6 - /RD       Read  (Low active)
 * 7 - /CE       Chip Enable  (Low active)
 * 8 - C/D       Command or Data
 * 9 - /RST      Reset (Low active)
 * 10..17 - D0..7
 * 18 - FS       Font Select
 * 19 - A        Backlight Anode (~4.3V)
 * 20 - K        Backlight Cathode (GND)
 */
#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

// My Settings
#define RA6963_NEED_READ                GFXOFF //works, but is very slow!
#define RA6963_HAS_RESET                GFXOFF
#define RA6963_NEED_FONT_SELECT         GFXOFF
#define RA6963_NEED_BACKLIGHT           GFXOFF
#define RA6963_NEED_PWMBACKLIGHT        GFXOFF
#define GDISP_SCREEN_HEIGHT             64
#define GDISP_SCREEN_WIDTH              128
#define GDISP_INITIAL_CONTRAST          50
#define GDISP_INITIAL_BACKLIGHT         100

#define RA6963_delay(n) {asm("nop");asm("nop");asm("nop");asm("nop");}

#define LINE_WR       PAL_LINE(GPIOB, 8U)
#if RA6963_NEED_READ
#define LINE_RD       PAL_LINE(GPIOB, 9U)
#endif
#define LINE_CE       PAL_LINE(GPIOB, 10U)
#define LINE_CD       PAL_LINE(GPIOB, 11U)
#if RA6963_HAS_RESET
#define LINE_RST      PAL_LINE(GPIOB, 12U)
#endif
#define LINE_D0       PAL_LINE(GPIOB, 0U)
#define LINE_D1       PAL_LINE(GPIOB, 1U)
#define LINE_D2       PAL_LINE(GPIOB, 2U)
#define LINE_D3       PAL_LINE(GPIOB, 3U)
#define LINE_D4       PAL_LINE(GPIOB, 4U)
#define LINE_D5       PAL_LINE(GPIOB, 5U)
#define LINE_D6       PAL_LINE(GPIOB, 6U)
#define LINE_D7       PAL_LINE(GPIOB, 7U)
#if RA6963_NEED_FONT_SELECT
#define LINE_FS      PAL_LINE(GPIOA, 13U)
#endif
#if RA6963_NEED_BACKLIGHT
#define LINE_BL       PAL_LINE(GPIOA, 14U)
#endif

typedef struct {
  ioline_t WR;           //Write PIN
#if RA6963_NEED_READ
  ioline_t RD;           //Read PIN  (tie to +5V if not needed)
#endif
  ioline_t CE;           //Chip Enable PIN
  ioline_t CD;           //Command/Data Select PIN
#if RA6963_HAS_RESET
  ioline_t RST;          //Reset PIN (tie to +5V if not needed)
#endif
  ioline_t D[8];         //Data PINs
#if RA6963_NEED_BACKLIGHT
  ioline_t BL;           //Backlight PIN
#endif
#if RA6963_NEED_FONT_SELECT
  ioline_t FS;          //Font Select PIN (tie to GND if not needed)
#endif
} lcd_pins_t;

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/
static const lcd_pins_t lcdpins = {
  LINE_WR,
#if RA6963_NEED_READ
  LINE_RD,
#endif
  LINE_CE,
  LINE_CD,
#if RA6963_HAS_RESET
  LINE_RST,
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
#if RA6963_NEED_BACKLIGHT
  LINE_BL,
#endif
#if RA6963_NEED_FONT_SELECT
  LINE_FS,
#endif
};

static GFXINLINE void init_board(GDisplay* g){
  (void) g;
  g->board = 0;
  int ii;
//################################DEBUG#######################################
#define DEB13_ON palClearLine(PAL_LINE(GPIOB, 13U))
#define DEB13_OFF palSetLine(PAL_LINE(GPIOB, 13U))
#define DEB14_ON palClearLine(PAL_LINE(GPIOB, 14U))
#define DEB14_OFF palSetLine(PAL_LINE(GPIOB, 14U))

  palSetLineMode(PAL_LINE(GPIOB, 13U),  PAL_MODE_OUTPUT_PUSHPULL);
  DEB13_OFF;
  palSetLineMode(PAL_LINE(GPIOB, 14U),  PAL_MODE_OUTPUT_PUSHPULL);
  DEB14_OFF;

  //################################DEBUG#######################################

  palSetLineMode(lcdpins.WR,  PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(lcdpins.WR);
#if RA6963_NEED_READ
  palSetLineMode(lcdpins.RD,  PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(lcdpins.RD);
#endif
  palSetLineMode(lcdpins.CE,   PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(lcdpins.CE);
  palSetLineMode(lcdpins.CD,   PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(lcdpins.CD);
#if RA6963_HAS_RESET
  palSetLine(lcdpins.RST);
  palSetLineMode(lcdpins.RST, PAL_MODE_OUTPUT_PUSHPULL);

#endif
  for(ii = 0; ii < 8; ii++) {
    palSetLineMode(lcdpins.D[ii],  PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(lcdpins.D[ii]);
  }
#if RA6963_NEED_BACKLIGHT
#if RA6963_NEED_PWMBACKLIGHT
  palSetLineMode(lcdpins.BL,   PAL_MODE_ALTERNATE(1));
#else
  palSetLineMode(lcdpins.BL,   PAL_MODE_OUTPUT_PUSHPULL);
#endif
#endif
#if RA6963_NEED_FONT_SELECT
  palSetLineMode(lcdpins.FS,  PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(lcdpins.FS);
#endif
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;
#if RA6963_HAS_RESET  //Make Hardware Reset
	if (state)
	  palClearLine(lcdpins.RST);
	else
	  palSetLine(lcdpins.RST);
#else
	(void) state;
#endif
}

static GFXINLINE void set_backlight(GDisplay *g, gU8 percent) {
  (void) g;
  (void) percent;
#if RA6963_NEED_BACKLIGHT
#if RA6963_NEED_PWMBACKLIGHT

#else

#endif
#endif
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}


#if RA6963_NEED_READ
static GFXINLINE gU8 RA6963_busy_wait(gU8 pattern, gBool lh){

  gU8 data;
  int ii;

  for(ii = 0; ii < 2; ii++) //Only interested in Bit 0 and 1
    palSetLineMode(lcdpins.D[ii], PAL_MODE_INPUT);  //Set pads to input

  palClearLine(lcdpins.CE);
  palClearLine(lcdpins.RD);
  do{
    data = 0;

    for(ii = 0; ii < 2; ii++){
      if (palReadLine(lcdpins.D[ii]) == PAL_HIGH){ //Read output
        data |= (1<<ii);
      }
    }
  } while ((data & pattern) == lh);

  palSetLine(lcdpins.CE);
  palSetLine(lcdpins.RD);
   for(ii = 0; ii < 2; ii++) {
     palSetLineMode(lcdpins.D[ii],  PAL_MODE_OUTPUT_PUSHPULL);  //Set pads to output
   }

  return data;
}
#endif

static GFXINLINE void RA6963_write(gU8 value){
  int ii;
  for(ii = 0; ii < 8; ii++){
      if(value & (1 << ii))
        palSetLine(lcdpins.D[ii]);
      else
        palClearLine(lcdpins.D[ii]);
  }
}

static GFXINLINE void write_data(GDisplay* g, gU8 data){
  (void)g;
#if RA6963_NEED_READ
  RA6963_busy_wait(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2, ~(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2));
#endif
  RA6963_write(data);
  palClearLine(lcdpins.CD);
  palClearLine(lcdpins.CE);
  palClearLine(lcdpins.WR);
  RA6963_delay(1);
  palSetLine(lcdpins.WR);
  palSetLine(lcdpins.CE);
  palSetLine(lcdpins.CD);
}

static GFXINLINE void write_cmd(GDisplay* g, gU8 data){
  (void)g;
#if RA6963_NEED_READ
  RA6963_busy_wait(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2, ~(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2));
#endif
  RA6963_write(data);
  palClearLine(lcdpins.CE);
  palClearLine(lcdpins.WR);
  RA6963_delay(1);
  palSetLine(lcdpins.WR);
  palSetLine(lcdpins.CE);
}

static GFXINLINE void setreadmode(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g) {
	(void) g;
}

static GFXINLINE gU8 read_data(GDisplay *g) {
  (void) g;
#if RA6963_NEED_READ
  int ii;
  gU8 data;
  write_cmd(g, RA6963_DATA_READ_AND_NONVARIABLE);
  //RA6963_busy_wait(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2, ~(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2));

  for(ii = 0; ii < 8; ii++)
    palSetLineMode(lcdpins.D[ii], PAL_MODE_INPUT);  //Set pads to input

  palClearLine(lcdpins.CE);
  palClearLine(lcdpins.RD);
  do{
    data = 0;

    for(ii = 0; ii < 2; ii++){
      if (palReadLine(lcdpins.D[ii]) == PAL_HIGH){ //Read output
        data |= (1<<ii);
      }
    }
  } while ((data & (RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2)) == ~(RA6963_STATUS_BUSY1 | RA6963_STATUS_BUSY2));

  palClearLine(lcdpins.CD);
//  RA6963_delay(1);
  data = 0;
  for(ii = 0; ii < 8; ii++){
    if (palReadLine(lcdpins.D[ii]) == PAL_HIGH){ //Read output
      data |= (1<<ii);
    }
  }
  palSetLine(lcdpins.CE);
  palSetLine(lcdpins.RD);
  palSetLine(lcdpins.CD);
  for(ii = 0; ii < 8; ii++) {
     palSetLineMode(lcdpins.D[ii],  PAL_MODE_OUTPUT_PUSHPULL);  //Set pads to output
   }
  return data;
#else
  return 0;
#endif
}
#endif /* _GDISP_LLD_BOARD_H */
