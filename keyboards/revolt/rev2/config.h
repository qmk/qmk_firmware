// Copyright 2025 Jacek Królikowski (@nietaki)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define LED_CAPS_LOCK_PIN GP25

#define BACKLIGHT_PWM_DRIVER PWMD6
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A

#define ANALOG_JOYSTICK_READ_INTERVAL 2
#define ANALOG_JOYSTICK_X_AXIS_PIN GP26
#define ANALOG_JOYSTICK_Y_AXIS_PIN GP27
#define ANALOG_JOYSTICK_AUTO_AXIS

// Lower Values Create Faster Movement
#define ANALOG_JOYSTICK_SPEED_REGULATOR 10

// Weights topping out at 100 early to account for the circular gate of the PSP joystick
//    JSON.stringify(Array.from(Array(101).keys()).map(x =>Math.min(Math.round( x / 4 + Math.pow(Math.max(x - 20, 0), 3)/2000), 100)))
#define ANALOG_JOYSTICK_WEIGHTS {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 26, 28, 29, 31, 33, 35, 37, 40, 42, 44, 47, 50, 53, 56, 59, 62, 65, 69, 72, 76, 80, 84, 88, 93, 97, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}

#define MIDI_ADVANCED
