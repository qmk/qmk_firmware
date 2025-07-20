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

#pragma once

#include <LUFA/Drivers/USB/USB.h>

#ifdef PROTOCOL_CHIBIOS
#    include <hal.h>
#    if STM32_USB_USE_OTG1 == TRUE
#        define USB_ENDPOINTS_ARE_REORDERABLE
#    endif
#endif

/*
 * USB descriptor structure
 */
typedef struct {
    USB_Descriptor_Configuration_Header_t Config;

#ifndef KEYBOARD_SHARED_EP
    // Keyboard HID Interface
    USB_Descriptor_Interface_t Keyboard_Interface;
    USB_HID_Descriptor_HID_t   Keyboard_HID;
    USB_Descriptor_Endpoint_t  Keyboard_INEndpoint;
#else
    // Shared Interface
    USB_Descriptor_Interface_t Shared_Interface;
    USB_HID_Descriptor_HID_t   Shared_HID;
    USB_Descriptor_Endpoint_t  Shared_INEndpoint;
#endif

#ifdef RAW_ENABLE
    // Raw HID Interface
    USB_Descriptor_Interface_t Raw_Interface;
    USB_HID_Descriptor_HID_t   Raw_HID;
    USB_Descriptor_Endpoint_t  Raw_INEndpoint;
    USB_Descriptor_Endpoint_t  Raw_OUTEndpoint;
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
    // Mouse HID Interface
    USB_Descriptor_Interface_t Mouse_Interface;
    USB_HID_Descriptor_HID_t   Mouse_HID;
    USB_Descriptor_Endpoint_t  Mouse_INEndpoint;
#endif

#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
    // Shared Interface
    USB_Descriptor_Interface_t Shared_Interface;
    USB_HID_Descriptor_HID_t   Shared_HID;
    USB_Descriptor_Endpoint_t  Shared_INEndpoint;
#endif

#ifdef CONSOLE_ENABLE
    // Console HID Interface
    USB_Descriptor_Interface_t Console_Interface;
    USB_HID_Descriptor_HID_t   Console_HID;
    USB_Descriptor_Endpoint_t  Console_INEndpoint;
#endif

#ifdef MIDI_ENABLE
    USB_Descriptor_Interface_Association_t Audio_Interface_Association;
    // MIDI Audio Control Interface
    USB_Descriptor_Interface_t          Audio_ControlInterface;
    USB_Audio_Descriptor_Interface_AC_t Audio_ControlInterface_SPC;
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
    USB_Descriptor_Interface_Association_t CDC_Interface_Association;
    // CDC Control Interface
    USB_Descriptor_Interface_t            CDC_CCI_Interface;
    USB_CDC_Descriptor_FunctionalHeader_t CDC_Functional_Header;
    USB_CDC_Descriptor_FunctionalACM_t    CDC_Functional_ACM;
    USB_CDC_Descriptor_FunctionalUnion_t  CDC_Functional_Union;
    USB_Descriptor_Endpoint_t             CDC_NotificationEndpoint;
    // CDC Data Interface
    USB_Descriptor_Interface_t CDC_DCI_Interface;
    USB_Descriptor_Endpoint_t  CDC_DataOutEndpoint;
    USB_Descriptor_Endpoint_t  CDC_DataInEndpoint;
#endif

#if defined(JOYSTICK_ENABLE) && !defined(JOYSTICK_SHARED_EP)
    // Joystick HID Interface
    USB_Descriptor_Interface_t Joystick_Interface;
    USB_HID_Descriptor_HID_t   Joystick_HID;
    USB_Descriptor_Endpoint_t  Joystick_INEndpoint;
#endif

#if defined(DIGITIZER_ENABLE) && !defined(DIGITIZER_SHARED_EP)
    // Digitizer HID Interface
    USB_Descriptor_Interface_t Digitizer_Interface;
    USB_HID_Descriptor_HID_t   Digitizer_HID;
    USB_Descriptor_Endpoint_t  Digitizer_INEndpoint;
#endif
} USB_Descriptor_Configuration_t;

/*
 * Interface indexes
 */
enum usb_interfaces {
#ifndef KEYBOARD_SHARED_EP
    KEYBOARD_INTERFACE,
#else
    SHARED_INTERFACE,
#    define KEYBOARD_INTERFACE SHARED_INTERFACE
#endif

// It is important that the Raw HID interface is at a constant
// interface number, to support Linux/OSX platforms and chrome.hid
// If Raw HID is enabled, let it be always 1.
#ifdef RAW_ENABLE
    RAW_INTERFACE,
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
    MOUSE_INTERFACE,
#endif

#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
    SHARED_INTERFACE,
#endif

#ifdef CONSOLE_ENABLE
    CONSOLE_INTERFACE,
#endif

#ifdef MIDI_ENABLE
    AC_INTERFACE,
    AS_INTERFACE,
#endif

#ifdef VIRTSER_ENABLE
    CCI_INTERFACE,
    CDI_INTERFACE,
#endif

#if defined(JOYSTICK_ENABLE) && !defined(JOYSTICK_SHARED_EP)
    JOYSTICK_INTERFACE,
#endif

#if defined(DIGITIZER_ENABLE) && !defined(DIGITIZER_SHARED_EP)
    DIGITIZER_INTERFACE,
#endif
    TOTAL_INTERFACES
};

#define IS_VALID_INTERFACE(i) ((i) >= 0 && (i) < TOTAL_INTERFACES)

#define NEXT_EPNUM __COUNTER__

/*
 * Endpoint numbers
 */
enum usb_endpoints {
    __unused_epnum__ = NEXT_EPNUM, // Endpoint numbering starts at 1

#ifndef KEYBOARD_SHARED_EP
    KEYBOARD_IN_EPNUM = NEXT_EPNUM,
#else
#    define KEYBOARD_IN_EPNUM SHARED_IN_EPNUM
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
    MOUSE_IN_EPNUM = NEXT_EPNUM,
#else
#    define MOUSE_IN_EPNUM SHARED_IN_EPNUM
#endif

#ifdef RAW_ENABLE
    RAW_IN_EPNUM = NEXT_EPNUM,
#    ifdef USB_ENDPOINTS_ARE_REORDERABLE
#        define RAW_OUT_EPNUM RAW_IN_EPNUM
#    else
    RAW_OUT_EPNUM         = NEXT_EPNUM,
#    endif
#endif

#ifdef SHARED_EP_ENABLE
    SHARED_IN_EPNUM = NEXT_EPNUM,
#endif

#ifdef CONSOLE_ENABLE
    CONSOLE_IN_EPNUM = NEXT_EPNUM,
#endif

#ifdef MIDI_ENABLE
    MIDI_STREAM_IN_EPNUM = NEXT_EPNUM,
#    ifdef USB_ENDPOINTS_ARE_REORDERABLE
#        define MIDI_STREAM_OUT_EPNUM MIDI_STREAM_IN_EPNUM
#    else
    MIDI_STREAM_OUT_EPNUM = NEXT_EPNUM,
#    endif
#endif

#ifdef VIRTSER_ENABLE
    CDC_NOTIFICATION_EPNUM = NEXT_EPNUM,
    CDC_IN_EPNUM           = NEXT_EPNUM,
#    ifdef USB_ENDPOINTS_ARE_REORDERABLE
#        define CDC_OUT_EPNUM CDC_IN_EPNUM
#    else
    CDC_OUT_EPNUM         = NEXT_EPNUM,
#    endif
#endif

#ifdef JOYSTICK_ENABLE
#    if !defined(JOYSTICK_SHARED_EP)
    JOYSTICK_IN_EPNUM = NEXT_EPNUM,
#    else
#        define JOYSTICK_IN_EPNUM SHARED_IN_EPNUM
#    endif
#endif

#ifdef DIGITIZER_ENABLE
#    if !defined(DIGITIZER_SHARED_EP)
    DIGITIZER_IN_EPNUM = NEXT_EPNUM,
#    else
#        define DIGITIZER_IN_EPNUM SHARED_IN_EPNUM
#    endif
#endif
};

#ifdef PROTOCOL_LUFA
// LUFA tells us total endpoints including control
#    define MAX_ENDPOINTS (ENDPOINT_TOTAL_ENDPOINTS - 1)
#elif defined(PROTOCOL_CHIBIOS)
// ChibiOS gives us number of available user endpoints, not control
#    define MAX_ENDPOINTS USB_MAX_ENDPOINTS
#endif

#if (NEXT_EPNUM - 1) > MAX_ENDPOINTS
#    error There are not enough available endpoints to support all functions. Please disable one or more of the following: Mouse Keys, Extra Keys, Console, NKRO, MIDI, Serial, Steno
#endif

#define KEYBOARD_EPSIZE 8
#define SHARED_EPSIZE 32
#define MOUSE_EPSIZE 16
#define RAW_EPSIZE 32
#define CONSOLE_EPSIZE 32
#define MIDI_STREAM_EPSIZE 64
#define CDC_NOTIFICATION_EPSIZE 8
#define CDC_EPSIZE 16
#define JOYSTICK_EPSIZE 8
#define DIGITIZER_EPSIZE 8

uint16_t get_usb_descriptor(const uint16_t wValue, const uint16_t wIndex, const uint16_t wLength, const void** const DescriptorAddress);
