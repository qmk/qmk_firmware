/*
Copyright 2019 kratsyn

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0xBEEF
#define DEVICE_VER      0x8008
#define MANUFACTURER    Keebio
#define PRODUCT         BDN9 (Proton-C)
#define DESCRIPTION     3x3 Macropad with Rotary Encoders

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

#define DIRECT_PINS { \
	{ A10, B5, A2 }, \
	{ B3, B13, B14 }, \
	{ B2, B1, B15 } \
}

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define ENCODERS_PAD_A { B6, A0 }
#define ENCODERS_PAD_B { B7, A1 }
#define ENCODER_RESOLUTION 4


// STM32F303vc variants can be found @ https://www.st.com/resource/en/datasheet/stm32f303vc.pdf
// Others may be identified by via ST @ https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html

#define	BACKLIGHT_ARM_PIN		B0			// temporary until PR#6487 is included with support for custom drivers
#define BACKLIGHT_PWM_DRIVER	&PWMD3		// PWM Driver Channel (TIMX), must be enabled in mcuconf.h)
#define BACKLIGHT_PWM_CHANEL	2			// PWM Timing Channel (TIMX_CHN, where N is the timing channel)

#define BACKLIGHT_LEVELS 5 
#define BACKLIGHT_BREATHING
#define BACKLIGHT_BREATHING_STEPS 128
#define BREATHING_PERIOD 6 

/* Pending DI implementation in PR#6301 */
//#define RGB_DI_PIN A9
//#ifdef RGB_DI_PIN
//  #define RGBLED_NUM 4
//  #define RGBLIGHT_HUE_STEP 8
//  #define RGBLIGHT_SAT_STEP 8
//  #define RGBLIGHT_VAL_STEP 8
//  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
//  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
//  /*== all animations enable ==*/
//  #define RGBLIGHT_ANIMATIONS
//#endif
