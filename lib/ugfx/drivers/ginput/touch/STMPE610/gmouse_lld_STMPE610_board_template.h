/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_STMPE610_PEN_CALIBRATE_ERROR		8
#define GMOUSE_STMPE610_PEN_CLICK_ERROR			6
#define GMOUSE_STMPE610_PEN_MOVE_ERROR			4
#define GMOUSE_STMPE610_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_STMPE610_FINGER_CLICK_ERROR		18
#define GMOUSE_STMPE610_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_STMPE610_BOARD_DATA_SIZE			0

// Options - Leave these commented to make it user configurable in the gfxconf.h
//#define GMOUSE_STMPE610_READ_PRESSURE		GFXOFF
//#define GMOUSE_STMPE610_SELF_CALIBRATE	GFXOFF
//#define GMOUSE_STMPE610_TEST_MODE			GFXOFF

// If GFXON this board has the STMPE610 IRQ pin connected to a GPIO.
// Note: For tested hardware this is unreliable and should be set to GFXOFF until tested.
//			Symptoms are that mouse readings just appear to stop for a bit. Lifting the touch
//			and re-applying the touch cause readings to start again.
#define GMOUSE_STMPE610_GPIO_IRQPIN				GFXOFF

// If GFXON this is a really slow CPU and we should always clear the FIFO between reads.
#define GMOUSE_STMPE610_SLOW_CPU				GFXOFF

static gBool init_board(GMouse* m, unsigned driverinstance) {
}

#if GMOUSE_STMPE610_GPIO_IRQPIN
	static gBool getpin_irq(GMouse* m) {

	}
#endif

static GFXINLINE void aquire_bus(GMouse* m) {
}

static GFXINLINE void release_bus(GMouse* m) {
}

static void write_reg(GMouse* m, gU8 reg, gU8 val) {
}

static gU8 read_byte(GMouse* m, gU8 reg) {
}

static gU16 read_word(GMouse* m, gU8 reg) {
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
