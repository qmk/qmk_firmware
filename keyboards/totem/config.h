// Copyright 2022 GEIST <@geigigeist>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN GP0
//#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_USB_DETECT
#define SERIAL_USE_MULTI_TRANSACTION
/* communication between sides */
#define SERIAL_PIO_USE_PIO1


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
