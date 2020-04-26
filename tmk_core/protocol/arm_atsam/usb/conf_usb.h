/**
 * \file
 *
 * \brief USB configuration file
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"
#include "udi_device_conf.h"

#define UDI_CDC_DEFAULT_RATE 115200
#define UDI_CDC_DEFAULT_STOPBITS CDC_STOP_BITS_1
#define UDI_CDC_DEFAULT_PARITY CDC_PAR_NONE
#define UDI_CDC_DEFAULT_DATABITS 8

//! Device definition (mandatory)
#define USB_DEVICE_VENDOR_ID VENDOR_ID
#define USB_DEVICE_PRODUCT_ID PRODUCT_ID
#define USB_DEVICE_VERSION DEVICE_VER
#define USB_DEVICE_POWER 500  // Consumption on Vbus line (mA)
#define USB_DEVICE_ATTR (USB_CONFIG_ATTR_REMOTE_WAKEUP | USB_CONFIG_ATTR_BUS_POWERED)
//                                      (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)
//                                      (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
//                                      (USB_CONFIG_ATTR_SELF_POWERED)
//                                      (USB_CONFIG_ATTR_BUS_POWERED)

//! USB Device string definitions (Optional)
#define USB_DEVICE_MANUFACTURE_NAME MANUFACTURER
#define USB_DEVICE_PRODUCT_NAME PRODUCT
#define USB_DEVICE_SERIAL_NAME SERIAL_NUM

// Comment out USB_DEVICE_SERIAL_USE_BOOTLOADER_SERIAL to prevent ROM lookup of factory programmed serial number
#define USB_DEVICE_SERIAL_USE_BOOTLOADER_SERIAL

/**
 * Device speeds support
 * @{
 */
//! To define a Low speed device
//#define  USB_DEVICE_LOW_SPEED

//! To authorize the High speed
#if (UC3A3 || UC3A4)
//#define  USB_DEVICE_HS_SUPPORT
#elif (SAM3XA || SAM3U)
//#define  USB_DEVICE_HS_SUPPORT
#endif
//@}

/**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
#define UDC_VBUS_EVENT(b_vbus_high)
#define UDC_SOF_EVENT() main_sof_action()
#define UDC_SUSPEND_EVENT() main_suspend_action()
#define UDC_RESUME_EVENT() main_resume_action()
//! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature
#define UDC_REMOTEWAKEUP_ENABLE() main_remotewakeup_enable()
#define UDC_REMOTEWAKEUP_DISABLE() main_remotewakeup_disable()
//! When a extra string descriptor must be supported
//! other than manufacturer, product and serial string
// #define  UDC_GET_EXTRA_STRING()
//@}

//@}

/**
 * USB Interface Configuration
 * @{
 */
/**
 * Configuration of HID Keyboard interface
 * @{
 */
//! Interface callback definition
#define UDI_HID_KBD_ENABLE_EXT() main_kbd_enable()
#define UDI_HID_KBD_DISABLE_EXT() main_kbd_disable()
//#define UDI_HID_KBD_CHANGE_LED(value) ui_kbd_led(value)

#ifdef NKRO_ENABLE
#    define UDI_HID_NKRO_ENABLE_EXT() main_nkro_enable()
#    define UDI_HID_NKRO_DISABLE_EXT() main_nkro_disable()
//#define UDI_HID_NKRO_CHANGE_LED(value) ui_kbd_led(value)
#endif

#ifdef EXTRAKEY_ENABLE
#    define UDI_HID_EXK_ENABLE_EXT() main_exk_enable()
#    define UDI_HID_EXK_DISABLE_EXT() main_exk_disable()
#endif

#ifdef CONSOLE_ENABLE
#    define UDI_HID_CON_ENABLE_EXT() main_con_enable()
#    define UDI_HID_CON_DISABLE_EXT() main_con_disable()
#endif

#ifdef MOUSE_ENABLE
#    define UDI_HID_MOU_ENABLE_EXT() main_mou_enable()
#    define UDI_HID_MOU_DISABLE_EXT() main_mou_disable()
#endif

#ifdef RAW_ENABLE
#    define UDI_HID_RAW_ENABLE_EXT() main_raw_enable()
#    define UDI_HID_RAW_DISABLE_EXT() main_raw_disable()
#    define UDI_HID_RAW_RECEIVE(buffer, len) main_raw_receive(buffer, len)
#endif

//@}
//@}

/**
 * USB Device Driver Configuration
 * @{
 */
//@}

//! The includes of classes and other headers must be done at the end of this file to avoid compile error
#include "udi_hid_kbd_conf.h"
#include "usb_main.h"
#include "ui.h"

#endif  // _CONF_USB_H_
