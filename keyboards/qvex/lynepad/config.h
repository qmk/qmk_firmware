// Copyright 2023 seflm (@seflm)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

//Digital joystick (4-way switch + encoder)
#define PIN_JU D4
#define PIN_JD B6
#define PIN_JL D7
#define PIN_JR B4
#define PIN_JC C6

//Thumbwheel
#define PIN_TC D2

//Thumbwheel and joystick encoders
#define ENCODERS_PAD_A { D6, D1 }
#define ENCODERS_PAD_B { B5, D0 }
#define ENCODER_RESOLUTIONS { 2, 2 }

//Backlighting
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 8
#define BACKLIGHT_LIMIT_VAL 192
#define BACKLIGHT_BREATHING
#define BACKLIGHT_DEFAULT_LEVEL 5

//RGB ring
#define RGB_DI_PIN D3
#define RGBLED_NUM 5
#define RGBLIGHT_DEFAULT_VAL 64
#define RGBLIGHT_LIMIT_VAL 192
#define RGBLIGHT_SLEEP