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
#include "proton_c.h"

#define BL_PIN		B0		// B0 ALT_MODE(2) (TIM3_3)
#define BL_PWMD		&PWMD3	// PWM Driver
#define BL_TC		2		// Timing Channel (MCU specific value - 1)

backlight_config_t backlight_config;

static uint32_t backlight_duty = 0;
static uint16_t breath_intval = 0;
static uint32_t breath_duty = 0;
static uint8_t breath_index = 0;
static uint16_t breath_count = 0;

static void _bl_cb(PWMDriver *pwmp);
static PWMConfig pwmCfg = {
	0xFFFF,
	256,
	_bl_cb,
	{
#if BL_TC == 0
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
#else
		{ PWM_OUTPUT_DISABLED, NULL },
#endif
#if BL_TC == 1
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
#else
		{ PWM_OUTPUT_DISABLED, NULL },
#endif
#if BL_TC == 2
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
#else
		{ PWM_OUTPUT_DISABLED, NULL },
#endif
#if BL_TC == 3
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL }
#else
		{ PWM_OUTPUT_DISABLED, NULL }
#endif
	},
	0,
	0
};

static const uint8_t breathing_table[BACKLIGHT_BREATHING_STEPS] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
	backlight_config.raw = eeconfig_read_backlight();
	palSetLineMode(BL_PIN, PAL_MODE_ALTERNATE(2));
	pwmStart(BL_PWMD, &pwmCfg);
	_set_cb(true);
	backlight_level(backlight_config.level);
	dprint("[BL] Startup complete.\n");
}

void backlight_reset_callback(void) {
	_set_cb(false);
	_set_cb(true);
}

void backlight_level(uint8_t level) {
	backlight_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) backlight_config.level / BACKLIGHT_LEVELS));
	if (level == 0) {
		backlight_off();
	} else {
		if(!backlight_is_breathing()) {
			pwmEnableChannel(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD,0xFFFF,backlight_duty));
		} else {
			backlight_config.level = level;
		}
	}
	dprintf("[BL] Backlight level set. (L:%d) (D:%d)\n", backlight_config.level, backlight_duty);
}

// forward if true, backwards if false
void backlight_step(bool forward) {
	if(!backlight_is_enabled())
		backlight_config.enable = 1;

	if(forward)
		++backlight_config.level;
	else
		backlight_config.level--;
	
	if (backlight_config.level == (BACKLIGHT_LEVELS+1)) {
		backlight_config.level =  0;
	} else if ((backlight_config.level > BACKLIGHT_LEVELS)) {
		backlight_config.level = BACKLIGHT_LEVELS;
	} 
	
	if (!backlight_is_breathing()) {
		backlight_level((uint8_t)backlight_config.level * 255 / BACKLIGHT_LEVELS);
	} else {
		dprintf("[BL] Breathing level set. (L:%d)\n", backlight_config.level);
	}
	eeconfig_update_backlight(backlight_config.raw);
	backlight_reset_callback();
}

bool backlight_is_enabled(void) {
	if(backlight_config.enable)
		return true;
	else
		return false;
}

void backlight_enable(void) {
	backlight_config.enable = 1;
	backlight_config.level = BACKLIGHT_LEVELS;
	backlight_config.breathing = 0;
	eeconfig_update_backlight(backlight_config.raw);
	_set_cb(true);
}

void backlight_disable(void) {
	backlight_config.enable = 0;
	backlight_config.level = 0;
	backlight_config.breathing = 0;
	eeconfig_update_backlight(backlight_config.raw);
	_set_cb(false);
}

void backlight_on(void) {
	backlight_enable();
	pwmEnableChannel(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD, 0xFFFF,cie_lightness(0xFFFF)));
	dprint("[BL] Backlight turned on.\n");
}

void backlight_off(void) {
	backlight_disable();
	pwmDisableChannel(BL_PWMD, BL_TC);
	dprint("[BL] Backlight turned off.\n");
}

void backlight_toggle(void) {
	if(backlight_config.enable)
		backlight_off();
	else
		backlight_on();
}

bool backlight_is_breathing(void) {
	if(backlight_config.breathing)
		return true;
	else 
		return false;
}

void backlight_breathing_on(void) {
	if(backlight_is_enabled()) {
		backlight_config.breathing = 1;
		eeconfig_update_backlight(backlight_config.raw);
		dprint("[BL] Breathing enabled.\n");
	}
}

void backlight_breathing_off(void) {
	if(backlight_is_enabled()) {
		backlight_config.breathing = 0;
		eeconfig_update_backlight(backlight_config.raw);
		dprint("[BL] Breathing disabled.\n");
	}
}

void backlight_breathing_toggle(void) {
	if(backlight_config.breathing)
		backlight_breathing_off();
	else
		backlight_breathing_on();
}

static inline uint16_t backlight_scale(uint16_t value) {
	return (value / BACKLIGHT_LEVELS * backlight_config.level);
}

static void _bl_cb(PWMDriver *pwmp) {
	if(backlight_is_breathing()) {
		breath_intval = (uint16_t) BREATHING_PERIOD * 256 / BACKLIGHT_BREATHING_STEPS;
		breath_count = (breath_count + 1) % (BREATHING_PERIOD * 256);
		breath_index = breath_count / breath_intval % BACKLIGHT_BREATHING_STEPS;

		breath_duty = cie_lightness(backlight_scale(breathing_table[breath_index] * 256));
	
		// lock, set new val, unlock
		chSysLockFromISR();
		pwmEnableChannelI(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD, 0xFFFF, breath_duty));
		chSysUnlockFromISR();
	}
}

/* pwm callback toggle */
void _set_cb(bool on) {
	chSysLockFromISR();
	if (on) {
		pwmEnablePeriodicNotificationI(BL_PWMD);
	} else {
	    pwmDisablePeriodicNotificationI(BL_PWMD);
	}
	chSysUnlockFromISR();
}
