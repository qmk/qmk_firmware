/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_FIX_RP2040_USB_DEVICE_ENUMERATION_H
#define _PICO_FIX_RP2040_USB_DEVICE_ENUMERATION_H

/*! \brief Perform a brute force workaround for USB device enumeration issue
 * \ingroup pico_fix
 *
 * This method should be called during the IRQ handler for a bus reset
 */
void rp2040_usb_device_enumeration_fix(void);

#endif