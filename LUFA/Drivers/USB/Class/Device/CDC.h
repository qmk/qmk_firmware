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
 *  @defgroup Group_USBClassCDCDevice CDC Class Device Mode Driver
 *
 *  \section Module Description
 *  Device Mode USB Class driver framework interface, for the CDC USB Class driver.
 *
 *  @{
 */
 
#ifndef _CDC_CLASS_DEVICE_H_
#define _CDC_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/CDC.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_CDC_CLASS_DEVICE_C)
			void CDC_Device_Event_Stub(void);
			void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
												      ATTR_WEAK ATTR_ALIAS(CDC_Device_Event_Stub);
			void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
			                                             ATTR_WEAK ATTR_ALIAS(CDC_Device_Event_Stub);
		#endif
	
		/** Configures the endpoints of a given CDC interface, ready for use. This should be linked to the library
		 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration containing the
		 *  given CDC interface is selected.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 *
		 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
		 */
		bool CDC_Device_ConfigureEndpoints(USB_ClassInfo_CDC_t* CDCInterfaceInfo);

		/** Processes incomming control requests from the host, that are directed to the given CDC class interface. This should be
		 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 */
		void CDC_Device_ProcessControlPacket(USB_ClassInfo_CDC_t* CDCInterfaceInfo);

		/** General management task for a given CDC class interface, required for the correct operation of the interface. This should
		 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 */
		void CDC_Device_USBTask(USB_ClassInfo_CDC_t* CDCInterfaceInfo);

		/** CDC class driver event for a line encoding change on a CDC interface. This event fires each time the host requests a
		 *  line encoding change (containing the serial parity, baud and other configuration information) and may be hooked in the
		 *  user program by declaring a handler function with the same name and parameters listed here. The new line encoding
		 *  settings are available in the LineEncoding structure inside the CDC interface structure passed as a parameter.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 */
		void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_t* CDCInterfaceInfo);
		
		/** CDC class driver event for a control line state change on a CDC interface. This event fires each time the host requests a
		 *  control line state change (containing the virtual serial control line states, such as DTR) and may be hooked in the
		 *  user program by declaring a handler function with the same name and parameters listed here. The new control line states
		 *  are available in the ControlLineState value inside the CDC interface structure passed as a parameter, set as a mask of
		 *  CDC_CONTROL_LINE_OUT_* masks.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 */		
		void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_t* CDCInterfaceInfo);

		/** Sends a given string to the attached USB host, if connected. If a host is not connected when the function is called, the
		 *  string is discarded.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 *  \param Data  Pointer to the string to send to the host
		 *  \param Length  Size in bytes of the string to send to the host
		 */
		void CDC_Device_SendString(USB_ClassInfo_CDC_t* CDCInterfaceInfo, char* Data, uint16_t Length);
		
		/** Sends a given byte to the attached USB host, if connected. If a host is not connected when the function is called, the
		 *  byte is discarded.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 *  \param Data  Byte of data to send to the host
		 */
		void CDC_Device_SendByte(USB_ClassInfo_CDC_t* CDCInterfaceInfo, uint8_t Data);
		
		/** Determines the number of bytes received by the CDC interface from the host, waiting to be read.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 *
		 *  \return Total number of buffered bytes received from the host
		 */
		uint16_t CDC_Device_BytesReceived(USB_ClassInfo_CDC_t* CDCInterfaceInfo);
		
		/** Reads a byte of data from the host. If no data is waiting to be read of if a USB host is not connected, the function
		 *  returns 0. The USB_CDC_BytesReceived() function should be queried before data is recieved to ensure that no data
		 *  underflow occurs.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 *
		 *  \return Next received byte from the host, or 0 if no data received
		 */
		uint8_t CDC_Device_ReceiveByte(USB_ClassInfo_CDC_t* CDCInterfaceInfo);
		
		/** Sends a Serial Control Line State Change notification to the host. This should be called when the virtual serial control
		 *  lines (DCD, DSR, etc.) have changed states, or to give BREAK notfications to the host. Line states persist until they are
		 *  cleared via a second notification.
		 *
		 *  \param CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
		 *  \param LineStateMask  Mask of CDC_CONTROL_LINE_IN_* masks giving the current control line states
		 */
		void CDC_Device_SendControlLineStateChange(USB_ClassInfo_CDC_t* CDCInterfaceInfo, uint16_t LineStateMask);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
