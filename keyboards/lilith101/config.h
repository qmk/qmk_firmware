/*#ifndef KEYBOARDS_lilith101_CONFIG_H_
#define KEYBOARDS_lilith101_CONFIG_H_
*/
/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#define FORCE_NKRO //for test only


#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2427
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
#define MANUFACTURER TechnoRage Developments
#define PRODUCT Lilith101
#define DESCRIPTION Lilith101 Keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19
#define DIODE_DIRECTION COL2ROW





#define MATRIX_COL_PINS { B16, B17, D0, A12, A13, D7, D4, D2, D3, C3, C4, C6, C7, D1, C0, B0, B1, B3, B2 }
#define MATRIX_ROW_PINS { D5, D6, C1, C2, A5, B19 }
//#define UNUSED_PINS


#ifndef B16
  #define B16 PAL_LINE(GPIOB, 16)
#else
  #pragma message("workaround not required anymore")
#endif

#ifndef B17
  #define B17 PAL_LINE(GPIOB, 17)
#else
  #pragma message("workaround not required anymore")
#endif

#ifndef B19
  #define B19 PAL_LINE(GPIOB, 19)
#else
  #pragma message("workaround not required anymore")
#endif

#ifndef B18
  #define B18 PAL_LINE(GPIOB, 18)
#else
  #pragma message("workaround not required anymore")
#endif

//#ifndef C8
//  #define C8 PAL_LINE(GPIOC, 8)
//#else
//  #pragma message("workaround not required anymore")
//#endif

//#ifndef C9
//  #define C9 PAL_LINE(GPIOC, 9)
//#else
//  #pragma message("workaround not required anymore")
//#endif

//#ifndef E0
//  #define E0 PAL_LINE(GPIOE, 0)
//#else
//  #pragma message("workaround not required anymore")
//#endif

// The pin connected to the data pin of the LEDs
//#define RGB_DI_PIN E1
// The number of LEDs connected
//#define DRIVER_LED_TOTAL 101
#define ENCODERS_PAD_B { B18 }
//#define ENCODERS_PAD_B { A4 }
#define ENCODERS_PAD_A { C5 }
#define ENCODER_RESOLUTION 4

/*
#define USE_I2CV1
#define I2C1_OPMODE 1
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE 1

#define I2C1_SCL_BANK GPIOC
#define I2C1_SDA_BANK GPIOC
#define I2C1_SCL 10
#define I2C1_SDA 11
*/

#define USE_I2CV1
#define I2C_DRIVER I2CD1

#define I2C1_OPMODE 1
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE 1

#define I2C1_SCL_BANK GPIOC
#define I2C1_SDA_BANK GPIOC
#define I2C1_SCL 10
#define I2C1_SDA 11



// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN E1
// The number of LEDs connected
#define DRIVER_LED_TOTAL 101
//#define CYCLES_PER_SEC (KINETIS_SYSCLK_FREQUENCY / NUMBER_NOPS * NOP_FUDGE)
#define STM32_SYSCLK KINETIS_SYSCLK_FREQUENCY
#define NOP_FUDGE 0.4



#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_BAND_PINWHEEL_VAL // Sets the default mode, if none has been set
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
//#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif


/* 
#endif 
*/
/* KEYBOARDS_lilith101_CONFIG_H_ */

