// Copyright 2024 mukil (@bukil)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define ENCODERS 1
#define ENCODERS_PAD_A { GP0 }
#define ENCODERS_PAD_B { GP1 }
/*#define JOYSTICK_AXES_COUNT 2
#define JOYSTICK_BUTTON_COUNT 1
#define JOYSTICK_AXIS_RESOLUTION 10 */
#define BACKLIGHT_PIN GP22
#define OLED_DISPLAY_128X64
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5
#define OLED_BRIGHTNESS 200
/*#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 2*/
/*#define OLED_SCROLL_TIMEOUT 30000*/
/*#define OLED_FONT_H "nes.c"*/
/*#define OLED_FONT_WIDTH 8
#define OLED_FONT_HEIGHT 10*/
/*#define I2C0_SDA_PIN GP6
#define I2C0_SCL_PIN GP7*/

/*#define ANALOG_JOYSTICK_X_AXIS_PIN GP26
* #define ANALOG_JOYSTICK_X_AXIS_PIN GP27
*/
#ifdef POINTING_DEVICE_ENABLE
    #define ANALOG_JOYSTICK_X_AXIS_PIN GP27
    #define ANALOG_JOYSTICK_Y_AXIS_PIN GP26
    #define ANALOG_JOYSTICK_AXIS_MIN 0
    #define ANALOG_JOYSTICK_AXIS_MAX 1023
    #define ANALOG_JOYSTICK_SPEED_REGULATOR 40
    #define ANALOG_JOYSTICK_READ_INTERVAL 10
    #define ANALOG_JOYSTICK_SPEED_MAX 2
#endif
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
