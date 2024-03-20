// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WPM_ENABLE
#ifdef SPLIT_OLED_ENABLE
#    undef SPLIT_OLED_ENABLE
#endif
#if defined(__AVR__) && !defined(SELECT_SOFT_SERIAL_SPEED)
#    define SELECT_SOFT_SERIAL_SPEED 1
#endif
#ifdef CUSTOM_SPLIT_TRANSPORT_SYNC
#    define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_STATE_SYNC, RPC_ID_USER_KEYMAP_SYNC, RPC_ID_USER_CONFIG_SYNC, RPC_ID_USER_PLACEHOLDER, RPC_ID_USER_KEYLOG_STR
#endif
