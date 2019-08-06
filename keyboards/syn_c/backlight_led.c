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

static uint32_t backlight_duty;
extern keyboard_config_t keyboard_config;
static void backlight_cb(PWMDriver *pwmp);
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
	backlight_on();
	dprint("[BL] Startup complete.\n");
}

void backlight_level(uint8_t level) {
	backlight_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) keyboard_config.blt_level / BACKLIGHT_LEVELS));
	if (level == 0) {
		backlight_off();
	} else {
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

bool is_breath(void) {
	if(keyboard_config.blt_breath) {
		dprint("[BL] Breathing is on.\n");
		return true;
	} else {
		dprint("[BL] Breathing is off.\n");
		return false;
	}
}

static void backlight_cb(PWMDriver *pwmp) {
	if(is_breath()) {
		dprint("[BL] Callback. (true).\n");
		chSysLockFromISR();
		pwmEnableChannelI(BL_PWMD, BL_TC, PWM_FRACTION_TO_WIDTH(BL_PWMD, 0xFFFF, backlight_duty));
		chSysUnlockFromISR();
	} else {
		// nothing to do
		dprint("[BL] Callback. (false).\n");
		return;
	}
}
