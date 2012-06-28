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
    USB_Descriptor_Interface_t            HID0_KeyboardInterface;
    USB_HID_Descriptor_HID_t              HID0_KeyboardHID;
    USB_Descriptor_Endpoint_t             HID0_ReportINEndpoint;

    // Mouse HID Interface
    USB_Descriptor_Interface_t            HID1_MouseInterface;
    USB_HID_Descriptor_HID_t              HID1_MouseHID;
    USB_Descriptor_Endpoint_t             HID1_ReportINEndpoint;

    // Generic HID Interface
    USB_Descriptor_Interface_t            HID2_GenericInterface;
    USB_HID_Descriptor_HID_t              HID2_GenericHID;
    USB_Descriptor_Endpoint_t             HID2_ReportINEndpoint;
    USB_Descriptor_Endpoint_t             HID2_ReportOUTEndpoint;
} USB_Descriptor_Configuration_t;


#define KEYBOARD_INTERFACE          0
#define MOUSE_INTERFACE             1
#define GENERIC_INTERFACE           2

// Endopoint number/size
#define KEYBOARD_IN_EPNUM           1
#define MOUSE_IN_EPNUM              2
#define GENERIC_IN_EPNUM            3
#define GENERIC_OUT_EPNUM           4

#define HID_EPSIZE                  8
#define GENERIC_EPSIZE              8
#define GENERIC_REPORT_SIZE         8


uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
