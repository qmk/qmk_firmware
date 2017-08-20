/*
 * Copyright 2012,2013 Jun Wako <wakojun@gmail.com>
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

#ifdef MOUSE_ENABLE
    // Mouse HID Interface
    USB_Descriptor_Interface_t            Mouse_Interface;
    USB_HID_Descriptor_HID_t              Mouse_HID;
    USB_Descriptor_Endpoint_t             Mouse_INEndpoint;
#endif

#ifdef EXTRAKEY_ENABLE
    // Extrakey HID Interface
    USB_Descriptor_Interface_t            Extrakey_Interface;
    USB_HID_Descriptor_HID_t              Extrakey_HID;
    USB_Descriptor_Endpoint_t             Extrakey_INEndpoint;
#endif

#ifdef RAW_ENABLE
    // Raw HID Interface
    USB_Descriptor_Interface_t            Raw_Interface;
    USB_HID_Descriptor_HID_t              Raw_HID;
    USB_Descriptor_Endpoint_t             Raw_INEndpoint;
    USB_Descriptor_Endpoint_t             Raw_OUTEndpoint;
#endif

#ifdef CONSOLE_ENABLE
    // Console HID Interface
    USB_Descriptor_Interface_t            Console_Interface;
    USB_HID_Descriptor_HID_t              Console_HID;
    USB_Descriptor_Endpoint_t             Console_INEndpoint;
    USB_Descriptor_Endpoint_t             Console_OUTEndpoint;
#endif

#ifdef NKRO_ENABLE
    // NKRO HID Interface
    USB_Descriptor_Interface_t            NKRO_Interface;
    USB_HID_Descriptor_HID_t              NKRO_HID;
    USB_Descriptor_Endpoint_t             NKRO_INEndpoint;
#endif

#ifdef MIDI_ENABLE
      // MIDI Audio Control Interface
      USB_Descriptor_Interface_t                Audio_ControlInterface;
      USB_Audio_Descriptor_Interface_AC_t       Audio_ControlInterface_SPC;

      // MIDI Audio Streaming Interface
      USB_Descriptor_Interface_t                Audio_StreamInterface;
      USB_MIDI_Descriptor_AudioInterface_AS_t   Audio_StreamInterface_SPC;
      USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Emb;
      USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Ext;
      USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Emb;
      USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Ext;
      USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_In_Jack_Endpoint;
      USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_In_Jack_Endpoint_SPC;
      USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_Out_Jack_Endpoint;
      USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_Out_Jack_Endpoint_SPC;
#endif

#ifdef VIRTSER_ENABLE
        USB_Descriptor_Interface_Association_t   CDC_Interface_Association;

	// CDC Control Interface
	USB_Descriptor_Interface_t               CDC_CCI_Interface;
	USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
	USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
	USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
	USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

	// CDC Data Interface
	USB_Descriptor_Interface_t               CDC_DCI_Interface;
	USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
	USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
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
#   define EXTRAKEY_INTERFACE       (MOUSE_INTERFACE + 1)
#else
#   define EXTRAKEY_INTERFACE       MOUSE_INTERFACE
#endif

#ifdef RAW_ENABLE
#   define RAW_INTERFACE        	(EXTRAKEY_INTERFACE + 1)
#else
#   define RAW_INTERFACE        	EXTRAKEY_INTERFACE
#endif

#ifdef CONSOLE_ENABLE
#   define CONSOLE_INTERFACE        (RAW_INTERFACE + 1)
#else
#   define CONSOLE_INTERFACE        RAW_INTERFACE
#endif

#ifdef NKRO_ENABLE
#   define NKRO_INTERFACE           (CONSOLE_INTERFACE + 1)
#else
#   define NKRO_INTERFACE           CONSOLE_INTERFACE
#endif

#ifdef MIDI_ENABLE
#   define AC_INTERFACE           (NKRO_INTERFACE + 1)
#   define AS_INTERFACE           (NKRO_INTERFACE + 2)
#else
#   define AS_INTERFACE           NKRO_INTERFACE
#endif

#ifdef VIRTSER_ENABLE
#   define CCI_INTERFACE         (AS_INTERFACE + 1)
#   define CDI_INTERFACE         (AS_INTERFACE + 2)
#else
#   define CDI_INTERFACE         AS_INTERFACE
#endif

/* nubmer of interfaces */
#define TOTAL_INTERFACES            (CDI_INTERFACE + 1)


// Endopoint number and size
#define KEYBOARD_IN_EPNUM           1

#ifdef MOUSE_ENABLE
#   define MOUSE_IN_EPNUM           (KEYBOARD_IN_EPNUM + 1)
#else
#   define MOUSE_IN_EPNUM           KEYBOARD_IN_EPNUM
#endif

#ifdef EXTRAKEY_ENABLE
#   define EXTRAKEY_IN_EPNUM        (MOUSE_IN_EPNUM + 1)
#else
#   define EXTRAKEY_IN_EPNUM        MOUSE_IN_EPNUM
#endif

#ifdef RAW_ENABLE
#   define RAW_IN_EPNUM         (EXTRAKEY_IN_EPNUM + 1)
#   define RAW_OUT_EPNUM        (EXTRAKEY_IN_EPNUM + 2)
#else
#   define RAW_OUT_EPNUM        EXTRAKEY_IN_EPNUM
#endif

#ifdef CONSOLE_ENABLE
#   define CONSOLE_IN_EPNUM         (RAW_OUT_EPNUM + 1)
//#   define CONSOLE_OUT_EPNUM        (RAW_OUT_EPNUM + 2)
#   define CONSOLE_OUT_EPNUM        (RAW_OUT_EPNUM + 1)
#else
#   define CONSOLE_OUT_EPNUM        RAW_OUT_EPNUM
#endif

#ifdef NKRO_ENABLE
#   define NKRO_IN_EPNUM            (CONSOLE_OUT_EPNUM + 1)
#else
#   define NKRO_IN_EPNUM            CONSOLE_OUT_EPNUM
#endif

#ifdef MIDI_ENABLE
#   define MIDI_STREAM_IN_EPNUM     (NKRO_IN_EPNUM + 1)
// #   define MIDI_STREAM_OUT_EPNUM    (NKRO_IN_EPNUM + 1)
#   define MIDI_STREAM_OUT_EPNUM    (NKRO_IN_EPNUM + 2)
#   define MIDI_STREAM_IN_EPADDR    (ENDPOINT_DIR_IN | MIDI_STREAM_IN_EPNUM)
#   define MIDI_STREAM_OUT_EPADDR   (ENDPOINT_DIR_OUT | MIDI_STREAM_OUT_EPNUM)
#else
#   define MIDI_STREAM_OUT_EPNUM     NKRO_IN_EPNUM
#endif

#ifdef VIRTSER_ENABLE
#   define CDC_NOTIFICATION_EPNUM   (MIDI_STREAM_OUT_EPNUM + 1)
#   define CDC_IN_EPNUM		    (MIDI_STREAM_OUT_EPNUM + 2)
#   define CDC_OUT_EPNUM		    (MIDI_STREAM_OUT_EPNUM + 3)
#   define CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN | CDC_NOTIFICATION_EPNUM)
#   define CDC_IN_EPADDR                  (ENDPOINT_DIR_IN | CDC_IN_EPNUM)
#   define CDC_OUT_EPADDR                  (ENDPOINT_DIR_OUT | CDC_OUT_EPNUM)
#else
#   define CDC_OUT_EPNUM	MIDI_STREAM_OUT_EPNUM
#endif

#if (defined(__AVR_ATmega32U2__) && CDC_OUT_EPNUM > 4) || \
    (defined(__AVR_ATmega32U4__) && CDC_OUT_EPNUM > 6)
# error "Endpoints are not available enough to support all functions. Remove some in Makefile.(MOUSEKEY, EXTRAKEY, CONSOLE, NKRO, MIDI, SERIAL)"
#endif

#define KEYBOARD_EPSIZE             8
#define MOUSE_EPSIZE                8
#define EXTRAKEY_EPSIZE             8
#define RAW_EPSIZE              	32
#define CONSOLE_EPSIZE              32
#define NKRO_EPSIZE                 32
#define MIDI_STREAM_EPSIZE          64
#define CDC_NOTIFICATION_EPSIZE     8
#define CDC_EPSIZE                  16


uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);


/* new API */
#if LUFA_VERSION_INTEGER < 0x140302
    #undef VERSION_BCD
    #define VERSION_BCD(Major, Minor, Revision) \
                                              CPU_TO_LE16( ((Major & 0xFF) << 8) | \
                                                           ((Minor & 0x0F) << 4) | \
                                                           (Revision & 0x0F) )
#endif

#endif
