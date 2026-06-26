// Copyright 2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only
#pragma once

// The dev unit had a different pixel order
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

// The dev unit used a smaller display
#define OLED_DISPLAY_128X64
// Needs to be shifted over
#define OLED_COLUMN_OFFSET 2
