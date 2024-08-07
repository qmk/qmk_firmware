// Copyright 2024 Bernd Lehmann (@der-b)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "quantum.h"

// pins for USB port selection
#define USB_SEL_0 E6
#define USB_SEL_1 B0

// USB active port indicator
#define USB_LED1 F6
#define USB_LED2 F4
#define USB_LED3 C7

// pins for USB port sensing
#define USB_SENSE_P1 F7
#define USB_SENSE_P2 F5
#define USB_SENSE_P3 B2

enum keyboard_keycodes {
  USB1 = QK_KB,
  USB2,
  USB3,
};
