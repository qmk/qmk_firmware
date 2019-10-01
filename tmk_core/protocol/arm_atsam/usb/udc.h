/**
 * \file
 *
 * \brief Interface of the USB Device Controller (UDC)
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

#ifndef _UDC_H_
#define _UDC_H_

#include "conf_usb.h"
#include "usb_protocol.h"
#include "udc_desc.h"
#include "udd.h"

#if USB_DEVICE_VENDOR_ID == 0
#   error USB_DEVICE_VENDOR_ID cannot be equal to 0
#endif

#if USB_DEVICE_PRODUCT_ID == 0
#   error USB_DEVICE_PRODUCT_ID cannot be equal to 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup usb_device_group
 * \defgroup udc_group USB Device Controller (UDC)
 *
 * The UDC provides a high-level abstraction of the usb device.
 * You can use these functions to control the main device state
 * (start/attach/wakeup).
 *
 * \section USB_DEVICE_CONF USB Device Custom configuration
 * The following USB Device configuration must be included in the conf_usb.h
 * file of the application.
 *
 * USB_DEVICE_VENDOR_ID (Word)<br>
 * Vendor ID provided by USB org (ATMEL 0x03EB).
 *
 * USB_DEVICE_PRODUCT_ID (Word)<br>
 * Product ID (Referenced in usb_atmel.h).
 *
 * USB_DEVICE_MAJOR_VERSION (Byte)<br>
 * Major version of the device
 *
 * USB_DEVICE_MINOR_VERSION (Byte)<br>
 * Minor version of the device
 *
 * USB_DEVICE_MANUFACTURE_NAME (string)<br>
 * ASCII name for the manufacture
 *
 * USB_DEVICE_PRODUCT_NAME (string)<br>
 * ASCII name for the product
 *
 * USB_DEVICE_SERIAL_NAME (string)<br>
 * ASCII name to enable and set a serial number
 *
 * USB_DEVICE_POWER (Numeric)<br>
 * (unit mA) Maximum device power
 *
 * USB_DEVICE_ATTR (Byte)<br>
 * USB attributes available:
 *  - USB_CONFIG_ATTR_SELF_POWERED
 *  - USB_CONFIG_ATTR_REMOTE_WAKEUP
 *  Note: if remote wake enabled then defines remotewakeup callbacks,
 * see Table 5-2. External API from UDC - Callback
 *
 * USB_DEVICE_LOW_SPEED (Only defined)<br>
 * Force the USB Device to run in low speed
 *
 * USB_DEVICE_HS_SUPPORT (Only defined)<br>
 * Authorize the USB Device to run in high speed
 *
 * USB_DEVICE_MAX_EP (Byte)<br>
 * Define the maximum endpoint number used by the USB Device.<br>
 * This one is already defined in UDI default configuration.
 * Ex:
 * - When endpoint control 0x00, endpoint 0x01 and
 *   endpoint 0x82 is used then USB_DEVICE_MAX_EP=2
 * - When only endpoint control 0x00 is used then USB_DEVICE_MAX_EP=0
 * - When endpoint 0x01 and endpoint 0x81 is used then USB_DEVICE_MAX_EP=1<br>
 *   (configuration not possible on USBB interface)
 * @{
 */

/**
 * \brief Authorizes the VBUS event
 *
 * \return true, if the VBUS monitoring is possible.
 *
 * \section udc_vbus_monitoring VBus monitoring used cases
 *
 * The VBus monitoring is used only for USB SELF Power application.
 *
 * - By default the USB device is automatically attached when Vbus is high
 * or when USB is start for devices without internal Vbus monitoring.
 * conf_usb.h file does not contains define USB_DEVICE_ATTACH_AUTO_DISABLE.
 * \code //#define USB_DEVICE_ATTACH_AUTO_DISABLE \endcode
 *
 * - Add custom VBUS monitoring. conf_usb.h file contains define
 * USB_DEVICE_ATTACH_AUTO_DISABLE:
 * \code #define USB_DEVICE_ATTACH_AUTO_DISABLE \endcode
 * User C file contains:
 * \code
    // Authorize VBUS monitoring
    if (!udc_include_vbus_monitoring()) {
      // Implement custom VBUS monitoring via GPIO or other
    }
    Event_VBUS_present() // VBUS interrupt or GPIO interrupt or other
    {
      // Attach USB Device
      udc_attach();
    }
\endcode
 *
 * - Case of battery charging. conf_usb.h file contains define
 * USB_DEVICE_ATTACH_AUTO_DISABLE:
 * \code #define USB_DEVICE_ATTACH_AUTO_DISABLE \endcode
 * User C file contains:
 * \code
    Event VBUS present() // VBUS interrupt or GPIO interrupt or ..
    {
      // Authorize battery charging, but wait key press to start USB.
    }
    Event Key press()
    {
      // Stop batteries charging
      // Start USB
      udc_attach();
    }
\endcode
 */
static inline bool udc_include_vbus_monitoring(void)
{
    return udd_include_vbus_monitoring();
}

/*! \brief Start the USB Device stack
 */
void udc_start(void);

/*! \brief Stop the USB Device stack
 */
void udc_stop(void);

/**
 * \brief Attach device to the bus when possible
 *
 * \warning If a VBus control is included in driver,
 * then it will attach device when an acceptable Vbus
 * level from the host is detected.
 */
static inline void udc_attach(void)
{
    udd_attach();
}

/**
 * \brief Detaches the device from the bus
 *
 * The driver must remove pull-up on USB line D- or D+.
 */
static inline void udc_detach(void)
{
    udd_detach();
}

/*! \brief The USB driver sends a resume signal called \e "Upstream Resume"
 * This is authorized only when the remote wakeup feature is enabled by host.
 */
inline void udc_remotewakeup(void)
{
    udd_send_remotewakeup();
}

/**
 * \brief Returns a pointer on the current interface descriptor
 *
 * \return pointer on the current interface descriptor.
 */
usb_iface_desc_t UDC_DESC_STORAGE *udc_get_interface_desc(void);

//@}

/**
 * \ingroup usb_group
 * \defgroup usb_device_group USB Stack Device
 *
 * This module includes USB Stack Device implementation.
 * The stack is divided in three parts:
 * - USB Device Controller (UDC) provides USB chapter 9 compliance
 * - USB Device Interface (UDI) provides USB Class compliance
 * - USB Device Driver (UDD) provides USB Driver for each Atmel MCU

 * Many USB Device applications can be implemented on Atmel MCU.
 * Atmel provides many application notes for different applications:
 * - AVR4900, provides general information about Device Stack
 * - AVR4901, explains how to create a new class
 * - AVR4902, explains how to create a composite device
 * - AVR49xx, all device classes provided in ASF have an application note
 *
 * A basic USB knowledge is required to understand the USB Device
 * Class application notes (HID,MS,CDC,PHDC,...).
 * Then, to create an USB device with
 * only one class provided by ASF, refer directly to the application note
 * corresponding to this USB class. The USB Device application note for
 * New Class and Composite is dedicated to advanced USB users.
 *
 * @{
 */

//! @}

#ifdef __cplusplus
}
#endif

#endif // _UDC_H_
