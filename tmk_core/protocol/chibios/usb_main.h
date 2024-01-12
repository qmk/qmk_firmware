/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

#pragma once

#include <ch.h>
#include <hal.h>

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
