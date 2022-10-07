// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config_common.h"

// Not working correct in json implementation
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

// Not yet supported in json

// Bootmagic Lite key configuration
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

#define SPLIT_HAND_PIN B5
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_OLED_ENABLE
