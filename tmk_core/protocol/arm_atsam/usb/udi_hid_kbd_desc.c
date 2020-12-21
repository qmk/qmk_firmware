/**
 * \file
 *
 * \brief Default descriptors for a USB Device
 * with a single interface HID keyboard
 *
 * Copyright (c) 2009-2016 Atmel Corporation. All rights reserved.
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

#include "conf_usb.h"
#include "usb_protocol.h"
#include "udc_desc.h"
#include "udi_device_conf.h"
#include "udi_hid_kbd.h"
#include "udi_cdc.h"

/**
 * \ingroup udi_hid_keyboard_group
 * \defgroup udi_hid_keyboard_group_single_desc USB device descriptors for a single interface
 *
 * The following structures provide the USB device descriptors required
 * for USB Device with a single interface HID keyboard.
 *
 * It is ready to use and do not require more definition.
 * @{
 */

//! USB Device Descriptor
COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE usb_dev_desc_t udc_device_desc = {.bLength         = sizeof(usb_dev_desc_t),
                                                   .bDescriptorType = USB_DT_DEVICE,
                                                   .bcdUSB          = LE16(USB_V2_0),
                                                   .bDeviceClass    = DEVICE_CLASS,
                                                   .bDeviceSubClass = DEVICE_SUBCLASS,
                                                   .bDeviceProtocol = DEVICE_PROTOCOL,
                                                   .bMaxPacketSize0 = USB_DEVICE_EP_CTRL_SIZE,
                                                   .idVendor        = LE16(USB_DEVICE_VENDOR_ID),
                                                   .idProduct       = LE16(USB_DEVICE_PRODUCT_ID),
                                                   .bcdDevice       = LE16(USB_DEVICE_VERSION),
#ifdef USB_DEVICE_MANUFACTURE_NAME
                                                   .iManufacturer = 1,
#else
                                                   .iManufacturer = 0,  // No manufacture string
#endif
#ifdef USB_DEVICE_PRODUCT_NAME
                                                   .iProduct = 2,
#else
                                                   .iProduct = 0,  // No product string
#endif
#if (defined USB_DEVICE_SERIAL_NAME || defined USB_DEVICE_GET_SERIAL_NAME_POINTER)
                                                   .iSerialNumber = 3,
#else
                                                   .iSerialNumber = 0,  // No serial string
#endif
                                                   .bNumConfigurations = 1};

#if 0
#    ifdef USB_DEVICE_HS_SUPPORT
//! USB Device Qualifier Descriptor for HS
COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE usb_dev_qual_desc_t udc_device_qual = {
    .bLength                   = sizeof(usb_dev_qual_desc_t),
    .bDescriptorType           = USB_DT_DEVICE_QUALIFIER,
    .bcdUSB                    = LE16(USB_V2_0),
    .bDeviceClass              = 0,
    .bDeviceSubClass           = 0,
    .bDeviceProtocol           = 0,
    .bMaxPacketSize0           = USB_DEVICE_EP_CTRL_SIZE,
    .bNumConfigurations        = 1
};
#    endif
#endif

//! USB Device Configuration Descriptor filled for FS and HS
COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udc_desc_t udc_desc = {
    .conf.bLength             = sizeof(usb_conf_desc_t),
    .conf.bDescriptorType     = USB_DT_CONFIGURATION,
    .conf.wTotalLength        = LE16(sizeof(udc_desc_t)),
    .conf.bNumInterfaces      = USB_DEVICE_NB_INTERFACE,
    .conf.bConfigurationValue = 1,
    .conf.iConfiguration      = 0,
    .conf.bmAttributes        = /* USB_CONFIG_ATTR_MUST_SET | */ USB_DEVICE_ATTR,
    .conf.bMaxPower           = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER),
    .hid_kbd                  = UDI_HID_KBD_DESC,
#ifdef RAW_ENABLE
    .hid_raw = UDI_HID_RAW_DESC,
#endif
#ifdef MOUSE_ENABLE
    .hid_mou = UDI_HID_MOU_DESC,
#endif
#ifdef EXTRAKEY_ENABLE
    .hid_exk = UDI_HID_EXK_DESC,
#endif
#ifdef CONSOLE_ENABLE
    .hid_con = UDI_HID_CON_DESC,
#endif
#ifdef NKRO_ENABLE
    .hid_nkro = UDI_HID_NKRO_DESC,
#endif
#ifdef VIRTSER_ENABLE
    .cdc_serial = CDC_DESCRIPTOR,
#endif
};

UDC_DESC_STORAGE udi_api_t *udi_apis[USB_DEVICE_NB_INTERFACE] = {
    &udi_api_hid_kbd,
#ifdef RAW_ENABLE
    &udi_api_hid_raw,
#endif
#ifdef MOUSE_ENABLE
    &udi_api_hid_mou,
#endif
#ifdef EXTRAKEY_ENABLE
    &udi_api_hid_exk,
#endif
#ifdef CONSOLE_ENABLE
    &udi_api_hid_con,
#endif
#ifdef NKRO_ENABLE
    &udi_api_hid_nkro,
#endif
#ifdef VIRTSER_ENABLE
    &udi_api_cdc_comm, &udi_api_cdc_data,
#endif
};

//! Add UDI with USB Descriptors FS & HS
UDC_DESC_STORAGE udc_config_speed_t udc_config_fshs[1] = {{
    .desc     = (usb_conf_desc_t UDC_DESC_STORAGE *)&udc_desc,
    .udi_apis = udi_apis,
}};

//! Add all information about USB Device in global structure for UDC
UDC_DESC_STORAGE udc_config_t udc_config = {
    .confdev_lsfs = &udc_device_desc,
    .conf_lsfs    = udc_config_fshs,
};

//@}
//@}
