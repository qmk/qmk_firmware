// Copyright 2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

// The dev unit had a different pixel order
#undef WS2812_BYTE_ORDER
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

// The dev unit used a smaller display
#undef OLED_DISPLAY_128X128
#define OLED_DISPLAY_128X64

