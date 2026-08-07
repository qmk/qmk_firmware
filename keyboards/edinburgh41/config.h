// Copyright 2022 L. Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Thumbstick settings
#define ANALOG_JOYSTICK_X_AXIS_PIN B5
#define ANALOG_JOYSTICK_Y_AXIS_PIN B6

// Thumbstick defaults

#ifndef SCROLLING_LAYER
    #define SCROLLING_LAYER 1
#endif
#ifndef TAPPING_LAYER
    #define TAPPING_LAYER 2
#endif
#ifndef CURSOR_SPEED
    #define CURSOR_SPEED 70
#endif
#ifndef SCROLL_SPEED
    #define SCROLL_SPEED 25
#endif
#ifndef SCROLL_DELAY_MS
    #define SCROLL_DELAY_MS 70
#endif
