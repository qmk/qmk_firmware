// Copyright 2023 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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
#define WS2812_PIO_USE_PIO1
#define WS2812_DI_PIN GP4
#define RGBLED_NUM 4
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF 
//The label on PCB v0.02 for the analog thumbstick should be interchanged.
#define ANALOG_JOYSTICK_X_AXIS_PIN GP28
#define ANALOG_JOYSTICK_Y_AXIS_PIN GP29
#define ANALOG_JOYSTICK_AXIS_MIN 255
#define ANALOG_JOYSTICK_AXIS_MAX 765
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define POINTING_DEVICE_INVERT_X