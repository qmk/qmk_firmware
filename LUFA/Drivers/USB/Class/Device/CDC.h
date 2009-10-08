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
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/CDC.c
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

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made for each CDC interface
			 *  within the user application, and passed to each of the CDC class driver functions as the
			 *  CDCInterfaceInfo parameter. This stores each CDC interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  ControlInterfaceNumber; /**< Interface number of the CDC control interface within the device */

					uint8_t  DataINEndpointNumber; /**< Endpoint number of the CDC interface's IN data endpoint */
					uint16_t DataINEndpointSize; /**< Size in bytes of the CDC interface's IN data endpoint */

					uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the CDC interface's OUT data endpoint */
					uint16_t DataOUTEndpointSize;  /**< Size in bytes of the CDC interface's OUT data endpoint */

					uint8_t  NotificationEndpointNumber; /**< Endpoint number of the CDC interface's IN notification endpoint, if used */
					uint16_t NotificationEndpointSize;  /**< Size in bytes of the CDC interface's IN notification endpoint, if used */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					struct
					{
						uint8_t HostToDevice; /**< Control line states from the host to device, as a set of CDC_CONTROL_LINE_OUT_*
											   *   masks.
											   */
						uint8_t DeviceToHost; /**< Control line states from the device to host, as a set of CDC_CONTROL_LINE_IN_*
											   *   masks.
											   */
					} ControlLineStates;

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
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_CDC_Device_t;
		
		/* Function Prototypes: */		
			/** Configures the endpoints of a given CDC interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration containing
			 *  the given CDC interface is selected.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool CDC_Device_ConfigureEndpoints(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Processes incomming control requests from the host, that are directed to the given CDC class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_UnhandledControlRequest() event.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 */
			void CDC_Device_ProcessControlRequest(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given CDC class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 */
			void CDC_Device_USBTask(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** CDC class driver event for a line encoding change on a CDC interface. This event fires each time the host requests a
			 *  line encoding change (containing the serial parity, baud and other configuration information) and may be hooked in the
			 *  user program by declaring a handler function with the same name and parameters listed here. The new line encoding
			 *  settings are available in the LineEncoding structure inside the CDC interface structure passed as a parameter.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 */
			void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** CDC class driver event for a control line state change on a CDC interface. This event fires each time the host requests a
			 *  control line state change (containing the virtual serial control line states, such as DTR) and may be hooked in the
			 *  user program by declaring a handler function with the same name and parameters listed here. The new control line states
			 *  are available in the ControlLineStates.HostToDevice value inside the CDC interface structure passed as a parameter, set as
			 *  a mask of CDC_CONTROL_LINE_OUT_* masks.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 */
			void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given string to the attached USB host, if connected. If a host is not connected when the function is called, the
			 *  string is discarded.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *  \param[in] Data  Pointer to the string to send to the host
			 *  \param[in] Length  Size in bytes of the string to send to the host
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t CDC_Device_SendString(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo, char* const Data, const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1, 2);
			
			/** Sends a given byte to the attached USB host, if connected. If a host is not connected when the function is called, the
			 *  byte is discarded.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *  \param[in] Data  Byte of data to send to the host
			 *
			 *  \return A value from the \ref Endpoint_WaitUntilReady_ErrorCodes_t enum
			 */
			uint8_t CDC_Device_SendByte(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo, const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Determines the number of bytes received by the CDC interface from the host, waiting to be read.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *
			 *  \return Total number of buffered bytes received from the host
			 */
			uint16_t CDC_Device_BytesReceived(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Reads a byte of data from the host. If no data is waiting to be read of if a USB host is not connected, the function
			 *  returns 0. The \ref CDC_Device_BytesReceived() function should be queried before data is received to ensure that no data
			 *  underflow occurs.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *
			 *  \return Next received byte from the host, or 0 if no data received
			 */
			uint8_t CDC_Device_ReceiveByte(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *
			 *  \return A value from the \ref Endpoint_WaitUntilReady_ErrorCodes_t enum
			 */
			uint8_t CDC_Device_Flush(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Sends a Serial Control Line State Change notification to the host. This should be called when the virtual serial
			 *  control lines (DCD, DSR, etc.) have changed states, or to give BREAK notfications to the host. Line states persist
			 *  until they are cleared via a second notification. This should be called each time the CDC class driver's 
			 *  ControlLineStates.DeviceToHost value is updated to push the new states to the USB host.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 */
			void CDC_Device_SendControlLineStateChange(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_CDC_CLASS_DEVICE_C)
				void CDC_Device_Event_Stub(void);
				void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
														  ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(CDC_Device_Event_Stub);
				void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
															 ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(CDC_Device_Event_Stub);
			#endif

	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
