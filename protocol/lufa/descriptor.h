/* 
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 * This file is based on:
 *     LUFA-120219/Demos/Device/Lowlevel/KeyboardMouse
 *     LUFA-120219/Demos/Device/Lowlevel/GenericHID
 */

/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

#include <LUFA/Drivers/USB/USB.h>
#include <avr/pgmspace.h>


typedef struct
{
    USB_Descriptor_Configuration_Header_t Config;

    // Keyboard HID Interface
    USB_Descriptor_Interface_t            Keyboard_Interface;
    USB_HID_Descriptor_HID_t              Keyboard_HID;
    USB_Descriptor_Endpoint_t             Keyboard_INEndpoint;

    // Mouse HID Interface
#ifdef MOUSE_ENABLE
    USB_Descriptor_Interface_t            Mouse_Interface;
    USB_HID_Descriptor_HID_t              Mouse_HID;
    USB_Descriptor_Endpoint_t             Mouse_INEndpoint;
#endif

    // Console HID Interface
    USB_Descriptor_Interface_t            Console_Interface;
    USB_HID_Descriptor_HID_t              Console_HID;
    USB_Descriptor_Endpoint_t             Console_INEndpoint;
    USB_Descriptor_Endpoint_t             Console_OUTEndpoint;

    // Extra HID Interface
#ifdef EXTRAKEY_ENABLE
    USB_Descriptor_Interface_t            Extra_Interface;
    USB_HID_Descriptor_HID_t              Extra_HID;
    USB_Descriptor_Endpoint_t             Extra_INEndpoint;
#endif
} USB_Descriptor_Configuration_t;


/* index of interface */
#define KEYBOARD_INTERFACE          0

#ifdef MOUSE_ENABLE
#   define MOUSE_INTERFACE          (KEYBOARD_INTERFACE + 1)
#else
#   define MOUSE_INTERFACE          KEYBOARD_INTERFACE
#endif 

#ifdef EXTRAKEY_ENABLE
#   define EXTRA_INTERFACE          (MOUSE_INTERFACE + 1)
#else
#   define EXTRA_INTERFACE          MOUSE_INTERFACE
#endif 

#define CONSOLE_INTERFACE           (EXTRA_INTERFACE + 1)


/* nubmer of interfaces */
#define TOTAL_INTERFACES            (CONSOLE_INTERFACE + 1)


// Endopoint number and size
#define KEYBOARD_IN_EPNUM           1
#define MOUSE_IN_EPNUM              2
#define CONSOLE_IN_EPNUM            3
#define CONSOLE_OUT_EPNUM           4
#define EXTRA_IN_EPNUM              5

#define KEYBOARD_EPSIZE             8
#define MOUSE_EPSIZE                8
#define CONSOLE_EPSIZE              32
#define EXTRA_EPSIZE                8


uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
