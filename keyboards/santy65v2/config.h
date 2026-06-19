// Copyright 2023-2026 Santiago Garcia (@santy81855)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
/* optical sensor settings */
// define which side the pointing device is on
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_LEFT
// SS Pin on the Trackball sensor 
#define PMW33XX_CS_PIN B0
// the sensitivity between 100 and 12000
#define PMW33XX_CPI 1200
#define POINTING_DEVICE_INVERT_Y