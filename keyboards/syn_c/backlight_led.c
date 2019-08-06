/* Copyright 2019 kratsyn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hal.h"
#include "debug.h"
#include "eeconfig.h"
#include "backlight_led.h"
#include "syn_c.h"

#define BL_PIN		B0
#define BL_PWMD		&PWMD3
#define BL_TC		2

extern keyboard_config_t keyboard_config;

static void backlight_cb(PWMDriver *pwmp);
static uint32_t backlight_duty;
static uint16_t breath_counter = 0;

static PWMConfig pwmCfg = {
	0xFFFF,
	256,
	backlight_cb,
	{
		{ PWM_OUTPUT_DISABLED, NULL },
		{ PWM_OUTPUT_DISABLED, NULL },
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL }, // GPIOB,0 (TIM3_CH3)
		{ PWM_OUTPUT_DISABLED, NULL }
	},
	0,
	0
};

static const uint8_t breathing_table[BACKLIGHT_BREATHING_STEPS] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10,
	12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76,
	83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178,
	185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247,
	250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240,
	235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162,
	154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63,
	57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5,
	4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
  if (v <= 5243) // if below 8% of max
    return v / 9; // same as dividing by 900%
  else {
    uint32_t y = (((uint32_t) v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
    // to get a useful result with integer division, we shift left in the expression above
    // and revert what we've done again after squaring.
    y = y * y * y >> 8;
    if (y > 0xFFFFUL) // prevent overflow
      return 0xFFFFU;
    else
      return (uint16_t) y;
  }
}

void backlight_init(void) {
	palSetLineMode(BL_PIN, PAL_MODE_ALTERNATE(2));
	pwmStart(BL_PWMD, &pwmCfg);
	backlight_enable_cb();
	backlight_on();
	dprint("[BL] Startup complete.\n");
}

void backlight_enable_cb(void) {
	//chSysLockFromISR();
	pwmEnablePeriodicNotification(BL_PWMD);
	//chSysUnlockFromISR();
}

void backlight_disable_cb(void) {
	//chSysLockFromISR();
    pwmDisablePeriodicNotification(BL_PWMD);
    //chSysUnlockFromISR();
}

void backlight_level(uint8_t level) {
	backlight_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) keyboard_config.blt_level / BACKLIGHT_LEVELS));
	if (level == 0) {
		backlight_off();
	} else {
		if(!is_breathing())
			pwmEnableChannel(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD,0xFFFF,backlight_duty));
	}
	dprintf("[BL] Backlight set. (L:%d) (D:%d)\n", keyboard_config.blt_level, backlight_duty);
}

void backlight_on(void) {
	pwmEnableChannel(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD, 0xFFFF,cie_lightness(0xFFFF)));
	dprint("[BL] Backlight turned on.\n");
}

void backlight_off(void) {
	pwmDisableChannel(BL_PWMD, BL_TC);
	dprint("[BL] Backlight turned off.\n");
}

bool is_breathing(void) {
	if(keyboard_config.blt_breath) {
		dprint("[BL] Breathing is on.\n");
		return true;
	} else {
		dprint("[BL] Breathing is off.\n");
		return false;
	}
}

void backlight_breathing_on(void) {
	keyboard_config.blt_breath = 1;
	eeconfig_update_kb(keyboard_config.raw);

	/*
	chSysLockFromISR();
	pwmEnablePeriodicNotification(BL_PWMD);
	chSysUnlockFromISR();
	*/

	dprint("[BL] Breathing enabled.\n");
}

void backlight_breathing_off(void) {
	keyboard_config.blt_breath = 0;
	eeconfig_update_kb(keyboard_config.raw);

	/*
	chSysLockFromISR();
	pwmDisablePeriodicNotification(BL_PWMD);
	chSysUnlockFromISR();
	*/

	dprint("[BL] Breathing disabled.\n");
}

static inline uint16_t backlight_scale(uint16_t value) {
	return value / BACKLIGHT_LEVELS * keyboard_config.blt_level;
}

static void backlight_cb(PWMDriver *pwmp) {
	if(is_breathing()) {
		dprint("[BL] Callback. (true).\n");

		//(void) pwmp; // ??

		uint16_t intval = (uint16_t) BREATHING_PERIOD * 256 / BACKLIGHT_BREATHING_STEPS;
		breath_counter = (breath_counter + 1) % (BREATHING_PERIOD * 256);
		uint8_t index = breath_counter / intval % BACKLIGHT_BREATHING_STEPS;

		uint32_t breath_duty = cie_lightness(backlight_scale(breathing_table[index] * 256));

		chSysLockFromISR();
		pwmEnableChannelI(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD, 0xFFFF, breath_duty));
		chSysUnlockFromISR();
	} else {
		// nothing to do
		dprint("[BL] Callback. (false).\n");
	}
	return;
}
