// Copyright 2026 doombadroid (@doombadroid)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* EEPROM backing store: 4 APROM pages at 0x30000..0x31FFF (fmc.c). 2 KB logical: VIA's dynamic keymap
   (4 layers x 128 x 2 B) + ~1 KB of macros. */
#define WEAR_LEVELING_BACKING_SIZE 8192
#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define BACKING_STORE_WRITE_SIZE 4

/* NUC126 USBD gives every logical endpoint its own IN and OUT hardware endpoint (hal_usb_lld.c _HW_IN/OUT_EPN),
   so raw HID (VIA) can use one endpoint number for both directions: keeps us within USB_MAX_ENDPOINTS = 3. */
#define USB_ENDPOINTS_ARE_REORDERABLE

/* QMK's default row-select settle time (CPU_CLOCK / 4 MHz); chibios_config.h defines no CPU_CLOCK for NUMICRO. */
#define GPIO_INPUT_PIN_DELAY (NUC126_HCLK / 1000000L / 4)

/* Calibration knobs for the LED driver (see mbi5042.c). */
#ifndef DUCKY_PWM_MAX
#    define DUCKY_PWM_MAX 0xFFFF /* ceiling of the 16-bit MBI5042 PWM word; = stock maximum: defaults routine 0x9614 sets level LUT 0,0x400,0x800,0x1000,0x1A00,0x2400,0x3000,0x4000,0x7000,0x9000,0xFFFF */
#endif
/* Which daisy-chained MBI5042 (0 = last shifted / nearest MCU) drives which colour. Unverified guess. */
#ifndef DUCKY_CHIP_R
#    define DUCKY_CHIP_R 0
#    define DUCKY_CHIP_G 1
#    define DUCKY_CHIP_B 2
#endif
