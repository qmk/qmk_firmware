/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef GAUDIO_PLAY_BOARD_H
#define GAUDIO_PLAY_BOARD_H

/*
 * This routine is defined in the driver - the timer interrupt should call this routine.
 *
 * static void gaudio_play_pwm_timer_callbackI(void);
 *
 */

static gBool gaudio_play_pwm_setup(gU32 frequency, ArrayDataFormat format) {
	/* Initialise the PWM - use a midpoint value for the initial PWM value */
	/* Initialise the timer interrupt @ frequency */
	/* Return gFalse if any parameter invalid */
}

static void gaudio_play_pwm_start(void) {
	/* Start the PWM  */
	/* Start the timer interrupt */
}

static void gaudio_play_pwm_stop(void) {
	/* Stop the timer interrupt */
	/* Stop the PWM */
}

static void gaudio_play_pwm_setI(gU16 value) {
	/* Set the PWM value */
}

#endif	/* GAUDIO_PLAY_BOARD_H */
