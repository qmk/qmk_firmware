// Copyright 2022 Selene ToyKeeper
// SPDX-License-Identifier: GPL-2.0-or-later
// config.h for ToyKeeper's NK65 layout
// (most of the config is in users/toykeeper/config.h)
#pragma once

#define KEYMAP_URL "http://toykeeper.net/keyboard/qmk/tk-nk65.png"

///// personal config stuff /////

//#define HAS_RGB  // uses wilba_tech RGB, not RGB Matrix
#define USE_NUMPAD
//#define HAS_DIPSWITCH
//#define HAS_F_ROW
//#define USE_RGUI_2TAP_MOUSELOCK


///// Wilba Tech stuff... /////

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#undef  RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED
#define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 1

// disable backlight after timeout in minutes, 0 = no timeout
#undef  RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 5
#define RGB_MATRIX_TIMEOUT (1000*60*5)  // 5 minutes

