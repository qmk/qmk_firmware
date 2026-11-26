// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

/* The GD32F303CG is a high-density part with 1MB flash / 96KB RAM. The
 * stm32duino board files default to the medium-density STM32F103xB; select the
 * high-density variant so the correct memory map and peripherals are used. */
#undef STM32F103xB
#define STM32F103xE

/* The Model 100 gates its USB D+ pull-up with a GPIO (PA8, active-high,
 * push-pull) rather than a fixed resistor — confirmed from Keyboardio's DAPBoot
 * config (HAVE_USB_PULLUP_CONTROL, USB_PULLUP_GPIO_PIN GPIO8). The stm32duino
 * board default only floats PA12 (assumes a fixed pull-up), so without this the
 * host never sees the device. Drive PA8 to (dis)connect from the bus. */
#undef usb_lld_connect_bus
#define usb_lld_connect_bus(usbp)    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); palSetPad(GPIOA, 8)
#undef usb_lld_disconnect_bus
#define usb_lld_disconnect_bus(usbp) palClearPad(GPIOA, 8)
