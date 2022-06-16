/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GAUDIO && GAUDIO_NEED_PLAY

/* Include the driver defines */
#include "../../../src/gaudio/gaudio_driver_play.h"

/* Forward definition */
static void gaudio_play_pwm_timer_callbackI(void);

/* Include the board interface */
#include "gaudio_play_board.h"

static GDataBuffer		*pplay;
static ArrayDataFormat	playfmt;
static gMemSize			playlen;
static gU8			*pdata;

static void gaudio_play_pwm_timer_callbackI(void) {
	if (pplay) {

		// Get the next value from the current data buffer
		if (gfxSampleFormatBits(playfmt) > 8) {
			gaudio_play_pwm_setI(*(gU16 *)pdata);
			pdata += 2;
		} else {
			gaudio_play_pwm_setI(*pdata);
			pdata++;
		}

		// Are we done yet
		if (--playlen)
			return;
		gaudioPlayReleaseDataBlockI(pplay);

		// Get a new data buffer
		if (!(pplay = gaudioPlayGetDataBlockI())) {
			// All is done
			gaudioPlayDoneI();
			return;
		}

	} else {
		// Get a new data buffer
		if (!(pplay = gaudioPlayGetDataBlockI()))
			return;
	}

	// Set up ready for the new buffer
	playlen = pplay->len;
	if (gfxSampleFormatBits(playfmt) > 8)
		playlen >>= 1;
	pdata = (gU8 *)(pplay+1);
}


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

gBool gaudio_play_lld_init(gU16 channel, gU32 frequency, ArrayDataFormat format) {
	(void) channel;

	if (format != ARRAY_DATA_8BITUNSIGNED && format != ARRAY_DATA_10BITUNSIGNED)
		return gFalse;

	playfmt = format;
	return gaudio_play_pwm_setup(frequency, format);
}

gBool gaudio_play_lld_set_volume(gU8 vol) {
	(void) vol;
	return gFalse;
}

void gaudio_play_lld_start(void) {

	gfxSystemLock();
	// Get a new data buffer
	if (pplay || !(pplay = gaudioPlayGetDataBlockI())) {
		gfxSystemUnlock();			// Nothing to do
		return;
	}

	// Set up ready for the new buffer
	playlen = pplay->len;
	if (gfxSampleFormatBits(playfmt) > 8)
		playlen >>= 1;
	pdata = (gU8 *)(pplay+1);
	gfxSystemUnlock();

	// Start the playing
	gaudio_play_pwm_start();
}

void gaudio_play_lld_stop(void) {
	// Stop everything
	gaudio_play_pwm_stop();

	// We may need to clean up the remaining buffer.
	gfxSystemLock();
	if (pplay) {
		gaudioPlayReleaseDataBlockI(pplay);
		pplay = 0;
		gaudioPlayDoneI();
	}
	gfxSystemUnlock();
}

#endif /* GFX_USE_GAUDIO && GAUDIO_NEED_PLAY */
