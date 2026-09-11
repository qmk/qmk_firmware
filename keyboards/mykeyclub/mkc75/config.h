// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Caps-lock indicator: PA2, driven LOW when caps is active.
 * Recovered from led_set() at 0x08001FF4 in the stock firmware -- it tests
 * bit 1 of the USB LED report (caps lock) and resets PA2 when set.
 * Declared here rather than via keyboard.json "indicators" because this QMK
 * tree does not wire indicators.on_state into LED_PIN_ON_STATE. */
#define LED_CAPS_LOCK_PIN A2
#define LED_PIN_ON_STATE 0
