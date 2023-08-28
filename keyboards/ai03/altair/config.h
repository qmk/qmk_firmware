/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once


/* Split hand pin for handedness detection */
#define SPLIT_HAND_PIN GP8

/* VBUS-routed pin for upstream detection */
#define USB_VBUS_PIN GP0

/* RP2040- and hardware-specific config */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

#define DYNAMIC_KEYMAP_LAYER_COUNT 6


