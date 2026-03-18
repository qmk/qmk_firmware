// Copyright 2025 ZSA Technology Labs, Inc <contact@zsa.io>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef NAVIGATOR_SCROLL_DIVIDER
#    define NAVIGATOR_SCROLL_DIVIDER 10
#endif

#ifndef NAVIGATOR_SCROLL_THRESHOLD
#    define NAVIGATOR_SCROLL_THRESHOLD 0f
#endif

#ifndef NAVIGATOR_SCROLL_ACCELERATION
#    define NAVIGATOR_SCROLL_ACCELERATION 1.5f
#endif

#ifndef NAVIGATOR_SCROLL_MAX_SPEED
#    define NAVIGATOR_SCROLL_MAX_SPEED 8.0f
#endif

#ifndef NAVIGATOR_TRACKBALL_ROTATION
#    define NAVIGATOR_TRACKBALL_ROTATION 0
#endif

// Normalize so 360 == 0, 450 == 90, etc.
#define _NAVIGATOR_ROTATION (NAVIGATOR_TRACKBALL_ROTATION % 360)

#ifndef NAVIGATOR_TURBO_MULTIPLIER
#    define NAVIGATOR_TURBO_MULTIPLIER 3
#endif

#ifndef NAVIGATOR_AIM_DIVIDER
#    define NAVIGATOR_AIM_DIVIDER 3
#endif

#ifdef NAVIGATOR_AIM_LAYERS
#    define _NAVIGATOR_AIM_HAS_LAYERS
#endif

#ifdef NAVIGATOR_TURBO_LAYERS
#    define _NAVIGATOR_TURBO_HAS_LAYERS
#endif

extern bool set_scrolling;
extern bool navigator_turbo;
extern bool navigator_aim;
