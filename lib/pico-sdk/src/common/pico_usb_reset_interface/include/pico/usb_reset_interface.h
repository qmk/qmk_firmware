/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_USB_RESET_INTERFACE_H
#define _PICO_USB_RESET_INTERFACE_H

/** \file usb_reset_interface.h
 *  \defgroup pico_usb_reset_interface pico_usb_reset_interface
 *
 * Definition for the reset interface that may be exposed by the pico_stdio_usb library
 */

// VENDOR sub-class for the reset interface
#define RESET_INTERFACE_SUBCLASS 0x00
// VENDOR protocol for the reset interface
#define RESET_INTERFACE_PROTOCOL 0x01

// CONTROL requests:

// reset to BOOTSEL
#define RESET_REQUEST_BOOTSEL 0x01
// regular flash boot
#define RESET_REQUEST_FLASH 0x02

#endif