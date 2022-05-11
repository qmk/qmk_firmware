// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Leader key customizations
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 1000
#define LEADER_KEY_STRICT_KEY_PROCESSING

#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2 // For TT swap hands SH_TT keycode

// Enabling IGNORE_MOD_TAP_INTERRUPT is recommended when using Mod-Tap on alphanumeric keys to avoid hold function taking precendence when the next key is pressed quickly. https://docs.qmk.fm/#/tap_hold?id=ignore-mod-tap-interrupt
#define IGNORE_MOD_TAP_INTERRUPT

#define MK_KINETIC_SPEED // Mouse key cursor motion customization

// Redefine Product and Vendor IDs for Apple Fn Key patch to work
// Anything from this list should work: https://usb-ids.gowdy.us/read/UD/05ac
#undef VENDOR_ID
#define VENDOR_ID 0x05AC
#undef PRODUCT_ID
#define PRODUCT_ID 0x0267

// Activate Command Mode (for flashing keyboard) with Left Ctrl + Right Ctrl (then, tap B key) because the default setting (both shift keys plus B) is intercepted by the CAPSWORD module.
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL)