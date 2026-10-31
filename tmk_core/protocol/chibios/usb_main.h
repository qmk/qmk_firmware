// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2020 Ryan (@fauxpark)
// Copyright 2020 Joel Challis (@zvecr)
// Copyright 2018 James Laird-Wah
// Copyright 2016 Fredizzimo
// Copyright 2016 Giovanni Di Sirio
// SPDX-License-Identifier: GPL-3.0-or-later OR Apache-2.0

#pragma once

#include <ch.h>
#include <hal.h>

#include "usb_device_state.h"
#include "usb_descriptor.h"
#include "usb_driver.h"
#include "usb_endpoints.h"

/* -------------------------
 * General USB driver header
 * -------------------------
 */

/* The USB driver to use */
#ifndef USB_DRIVER
#    define USB_DRIVER USBD1
#endif // USB_DRIVER

/* Initialize the USB driver and bus */
void init_usb_driver(USBDriver *usbp);

/* Restart the USB driver and bus */
void restart_usb_driver(USBDriver *usbp);

/* Change the USB interfaces a host sees (see docs/custom_quantum_functions.md) */
bool usb_get_descriptor_kb(uint16_t wValue, uint16_t wIndex, const void **address, uint16_t *size);
bool usb_get_descriptor_user(uint16_t wValue, uint16_t wIndex, const void **address, uint16_t *size);
bool usb_interface_from_host_kb(uint8_t *interface);
bool usb_interface_from_host_user(uint8_t *interface);

bool send_report(usb_endpoint_in_lut_t endpoint, void *report, size_t size);

/* ---------------
 * USB Event queue
 * ---------------
 */

/* Initialisation of the FIFO */
void usb_event_queue_init(void);

/* Task to dequeue and execute any handlers for the USB events on the main thread */
void usb_event_queue_task(void);

/* --------------
 * Console header
 * --------------
 */

#ifdef CONSOLE_ENABLE

/* Putchar over the USB console */
int8_t sendchar(uint8_t c);

#endif /* CONSOLE_ENABLE */

/* --------------
 * Virtser header
 * --------------
 */

#if defined(VIRTSER_ENABLE)

bool virtser_usb_request_cb(USBDriver *usbp);

#endif
