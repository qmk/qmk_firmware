// Copyright 2026 Anefecious
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define OLED_TIMEOUT 60000
// Verified 128x32: rotated 270 => ~5 chars wide (KeyCraft was clipped as KeyCr on 128x64).
#define OLED_DISPLAY_128X32

// Encoder push-buttons are direct to GND (not in the key matrix).
#define ENC_L_BTN_PIN B4
#define ENC_R_BTN_PIN B5
