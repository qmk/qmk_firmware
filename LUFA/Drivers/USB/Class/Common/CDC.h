/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

/** \ingroup Group_USBClassCDC
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

	/* Macros: */
		/** CDC Class specific request to get the current virtual serial port configuration settings. */
		#define REQ_GetLineEncoding              0x21

		/** CDC Class specific request to set the current virtual serial port configuration settings. */
		#define REQ_SetLineEncoding              0x20

		/** CDC Class specific request to set the current virtual serial port handshake line states. */
		#define REQ_SetControlLineState          0x22
		
		/** Notification type constant for a change in the virtual serial port handshake line states, for
		 *  use with a USB_Notification_Header_t notification structure when sent to the host via the CDC 
		 *  notification endpoint.
		 */
		#define NOTIF_SerialState                0x20

		/** Mask for the DTR handshake line for use with the REQ_SetControlLineState class specific request
		 *  from the host, to indicate that the DTR line state should be high.
		 */
		#define CDC_CONTROL_LINE_OUT_DTR         (1 << 0)

		/** Mask for the RTS handshake line for use with the REQ_SetControlLineState class specific request
		 *  from the host, to indicate that theRTS line state should be high.
		 */
		#define CDC_CONTROL_LINE_OUT_RTS         (1 << 1)
		
		/** Mask for the DCD handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the DCD line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_DCD          (1 << 0)

		/** Mask for the DSR handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the DSR line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_DSR          (1 << 1)

		/** Mask for the BREAK handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the BREAK line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_BREAK        (1 << 2)

		/** Mask for the RING handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the RING line state is currently high.
		 */
		#define CDC_CONTROL_LINE_IN_RING         (1 << 3)

		/** Mask for use with the a NOTIF_SerialState class specific notification from the device to the host,
		 *  to indicate that a framing error has occurred on the virtual serial port.
		 */
		#define CDC_CONTROL_LINE_IN_FRAMEERROR   (1 << 4)

		/** Mask for use with the a NOTIF_SerialState class specific notification from the device to the host,
		 *  to indicate that a parity error has occurred on the virtual serial port.
		 */
		#define CDC_CONTROL_LINE_IN_PARITYERROR  (1 << 5)

		/** Mask for use with the a NOTIF_SerialState class specific notification from the device to the host,
		 *  to indicate that a data overrun error has occurred on the virtual serial port.
		 */
		#define CDC_CONTROL_LINE_IN_OVERRUNERROR (1 << 6)
		
		/** Macro to define a CDC class-specific functional descriptor. CDC functional descriptors have a
		 *  uniform structure but variable sized data payloads, thus cannot be represented accurately by
		 *  a single typedef struct. A macro is used instead so that functional descriptors can be created
		 *  easily by specifying the size of the payload. This allows sizeof() to work correctly.
		 *
		 *  \param DataSize  Size in bytes of the CDC functional descriptor's data payload
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
		enum CDCDevice_CDC_LineCodingFormats_t
		{
			CDC_LINEENCODING_OneStopBit          = 0, /**< Each frame contains one stop bit */
			CDC_LINEENCODING_OneAndAHalfStopBits = 1, /**< Each frame contains one and a half stop bits */
			CDC_LINEENCODING_TwoStopBits         = 2, /**< Each frame contains two stop bits */
		};
		
		/** Enum for the possible line encoding parity settings of a virtual serial port. */
		enum CDCDevice_LineCodingParity_t
		{
			CDC_PARITY_None    = 0, /**< No parity bit mode on each frame */
			CDC_PARITY_Odd     = 1, /**< Odd parity bit mode on each frame */
			CDC_PARITY_Even    = 2, /**< Even parity bit mode on each frame */
			CDC_PARITY_Mark    = 3, /**< Mark parity bit mode on each frame */
			CDC_PARITY_Space   = 4, /**< Space parity bit mode on each frame */
		};

	/* Type Defines: */
		/** Class state structure. An instance of this structure should be made for each CDC interface
		 *  within the user application, and passed to each of the CDC class driver functions as the
		 *  CDCInterfaceInfo parameter. The contents of this structure should be set to their correct
		 *  values when used, or ommitted to force the library to use default values.
		 */
		typedef struct
		{
			uint8_t  ControlInterfaceNumber; /**< Interface number of the CDC control interface within the device */

			uint8_t  DataINEndpointNumber; /**< Endpoint number of the CDC interface's IN data endpoint */
			uint16_t DataINEndpointSize; /**< Size in bytes of the CDC interface's IN data endpoint */

			uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the CDC interface's OUT data endpoint */
			uint16_t DataOUTEndpointSize;  /**< Size in bytes of the CDC interface's OUT data endpoint */

			uint8_t  NotificationEndpointNumber; /**< Endpoint number of the CDC interface's IN notification endpoint, if used */
			uint16_t NotificationEndpointSize;  /**< Size in bytes of the CDC interface's IN notification endpoint, if used */

			uint8_t  ControlLineState; /**< Current control line states, as set by the host */

			struct
			{
				uint32_t BaudRateBPS; /**< Baud rate of the virtual serial port, in bits per second */
				uint8_t  CharFormat; /**< Character format of the virtual serial port, a value from the
									  *   CDCDevice_CDC_LineCodingFormats_t enum
									  */
				uint8_t  ParityType; /**< Parity setting of the virtual serial port, a value from the
									  *   CDCDevice_LineCodingParity_t enum
									  */
				uint8_t  DataBits; /**< Bits of data per character of the virtual serial port */
			} LineEncoding;
		} USB_ClassInfo_CDC_t;

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
