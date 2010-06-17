/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common definitions and declarations for the library USB CDC Class driver.
 *
 *  Common definitions and declarations for the library USB CDC Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the class driver
 *        dispatch header located in LUFA/Drivers/USB/Class/CDC.h.
 */

/** \ingroup Group_USBClassCDC
 *  @defgroup Group_USBClassCDCCommon  Common Class Definitions
 *
 *  \section Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  CDC Class.
 *
 *  @{
 */
 
#ifndef _CDC_CLASS_COMMON_H_
#define _CDC_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_CDC_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/Class/CDC.h instead.
		#endif
		
	/* Macros: */
		/** CDC class-specific request to get the current virtual serial port configuration settings. */
		#define REQ_GetLineEncoding              0x21

		/** CDC class-specific request to set the current virtual serial port configuration settings. */
		#define REQ_SetLineEncoding              0x20

		/** CDC class-specific request to set the current virtual serial port handshake line states. */
		#define REQ_SetControlLineState          0x22

		/** CDC class-specific request to send a break to the receiver via the carrier channel. */
		#define REQ_SendBreak                    0x23

		/** CDC class-specific request to send an encapsulated command to the device. */
		#define REQ_SendEncapsulatedCommand      0x00

		/** CDC class-specific request to retrieve an encapsulated command response from the device. */
		#define REQ_GetEncapsulatedResponse      0x01
		
		/** Notification type constant for a change in the virtual serial port handshake line states, for
		 *  use with a USB_Notification_Header_t notification structure when sent to the host via the CDC 
		 *  notification endpoint.
		 */
		#define NOTIF_SerialState                0x20

		/** Mask for the DTR handshake line for use with the REQ_SetControlLineState class-specific request
		 *  from the host, to indicate that the DTR line state should be high.
		 */
		#define CDC_CONTROL_LINE_OUT_DTR         (1 << 0)

		/** Mask for the RTS handshake line for use with the REQ_SetControlLineState class-specific request
		 *  from the host, to indicate that theRTS line state should be high.
		 */
		#define CDC_CONTROL_LINE_OUT_RTS         (1 << 1)
		
		/** Mask for the DCD handshake line for use with the a NOTIF_SerialState class-specific notification
		 *  from the device to the host, to indicate that the DCD line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_DCD          (1 << 0)

		/** Mask for the DSR handshake line for use with the a NOTIF_SerialState class-specific notification
		 *  from the device to the host, to indicate that the DSR line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_DSR          (1 << 1)

		/** Mask for the BREAK handshake line for use with the a NOTIF_SerialState class-specific notification
		 *  from the device to the host, to indicate that the BREAK line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_BREAK        (1 << 2)

		/** Mask for the RING handshake line for use with the a NOTIF_SerialState class-specific notification
		 *  from the device to the host, to indicate that the RING line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_RING         (1 << 3)

		/** Mask for use with the a NOTIF_SerialState class-specific notification from the device to the host,
		 *  to indicate that a framing error has occurred on the virtual serial port.
		 */
		#define CDC_CONTROL_LINE_IN_FRAMEERROR   (1 << 4)

		/** Mask for use with the a NOTIF_SerialState class-specific notification from the device to the host,
		 *  to indicate that a parity error has occurred on the virtual serial port.
		 */
		#define CDC_CONTROL_LINE_IN_PARITYERROR  (1 << 5)

		/** Mask for use with the a NOTIF_SerialState class-specific notification from the device to the host,
		 *  to indicate that a data overrun error has occurred on the virtual serial port.
		 */
		#define CDC_CONTROL_LINE_IN_OVERRUNERROR (1 << 6)
		
		/** Macro to define a CDC class-specific functional descriptor. CDC functional descriptors have a
		 *  uniform structure but variable sized data payloads, thus cannot be represented accurately by
		 *  a single typedef struct. A macro is used instead so that functional descriptors can be created
		 *  easily by specifying the size of the payload. This allows sizeof() to work correctly.
		 *
		 *  \param[in] DataSize  Size in bytes of the CDC functional descriptor's data payload.
		 */
		#define CDC_FUNCTIONAL_DESCRIPTOR(DataSize)        \
		     struct                                        \
		     {                                             \
		          USB_Descriptor_Header_t Header;          \
			      uint8_t                 SubType;         \
		          uint8_t                 Data[DataSize];  \
		     }

	/* Enums: */
		/** Enum for the possible line encoding formats of a virtual serial port. */
		enum CDC_LineEncodingFormats_t
		{
			CDC_LINEENCODING_OneStopBit          = 0, /**< Each frame contains one stop bit. */
			CDC_LINEENCODING_OneAndAHalfStopBits = 1, /**< Each frame contains one and a half stop bits. */
			CDC_LINEENCODING_TwoStopBits         = 2, /**< Each frame contains two stop bits. */
		};
		
		/** Enum for the possible line encoding parity settings of a virtual serial port. */
		enum CDC_LineEncodingParity_t
		{
			CDC_PARITY_None    = 0, /**< No parity bit mode on each frame. */
			CDC_PARITY_Odd     = 1, /**< Odd parity bit mode on each frame. */
			CDC_PARITY_Even    = 2, /**< Even parity bit mode on each frame. */
			CDC_PARITY_Mark    = 3, /**< Mark parity bit mode on each frame. */
			CDC_PARITY_Space   = 4, /**< Space parity bit mode on each frame. */
		};

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
