// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_CAPS_LOCK_PIN C15
#define LED_SCROLL_LOCK_PIN C14
#define MAC_PIN C13
#define LED_PIN_ON_STATE 0

#define BACKLIGHT_DEFAULT_ON 1

#ifdef ENCODER_ENABLE
#    define ENCODER_MAP_KEY_DELAY 20
#endif
