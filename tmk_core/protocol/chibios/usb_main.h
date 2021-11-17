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

#ifndef _USB_MAIN_H_
#define _USB_MAIN_H_

// TESTING
// extern uint8_t blinkLed;

#include "ch.h"
#include "hal.h"

/* -------------------------
 * General USB driver header
 * -------------------------
 */

/* The USB driver to use */
#define USB_DRIVER USBD1

/* Initialize the USB driver and bus */
void init_usb_driver(USBDriver *usbp);

/* ---------------
 * Keyboard header
 * ---------------
 */

/* extern report_keyboard_t keyboard_report_sent; */

/* keyboard IN request callback handler */
void kbd_in_cb(USBDriver *usbp, usbep_t ep);

/* start-of-frame handler */
void kbd_sof_cb(USBDriver *usbp);

#ifdef NKRO_ENABLE
/* nkro IN callback hander */
void nkro_in_cb(USBDriver *usbp, usbep_t ep);
#endif /* NKRO_ENABLE */

/* ------------
 * Mouse header
 * ------------
 */

#ifdef MOUSE_ENABLE

/* mouse IN request callback handler */
void mouse_in_cb(USBDriver *usbp, usbep_t ep);
#endif /* MOUSE_ENABLE */

/* ---------------
 * Shared EP header
 * ---------------
 */

/* shared IN request callback handler */
void shared_in_cb(USBDriver *usbp, usbep_t ep);

/* --------------
 * Console header
 * --------------
 */

#ifdef CONSOLE_ENABLE

/* Putchar over the USB console */
int8_t sendchar(uint8_t c);

/* Flush output (send everything immediately) */
void console_flush_output(void);

#endif /* CONSOLE_ENABLE */

void sendchar_pf(void *p, char c);

#endif /* _USB_MAIN_H_ */
