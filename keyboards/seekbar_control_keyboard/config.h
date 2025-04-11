// Copyright 2024 sotarokashiuchi (@sotarokashiuchi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* tap dance */
#define TAPPING_TERM 275

/* encoders */
#define ENCODER_A_PINS { F7 }
#define ENCODER_B_PINS { B1 }

/* rgb-led */
#define WS2812_DI_PIN D7
#define RGBLIGHT_LED_COUNT 5


/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
