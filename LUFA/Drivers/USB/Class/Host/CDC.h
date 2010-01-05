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

/** \ingroup Group_USBClassCDC
 *  @defgroup Group_USBClassCDCHost CDC Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/CDC.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the CDC USB Class driver.
 *
 *  @{
 */

#ifndef __CDC_CLASS_HOST_H__
#define __CDC_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/CDC.h"

		#include <stdio.h>
		#include <string.h>
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the CDC class driver functions as the CDCInterfaceInfo parameter. This
			 *  stores each CDC interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the CDC interface's IN data pipe */
					bool     DataINPipeDoubleBank; /** Indicates if the CDC interface's IN data pipe should use double banking */

					uint8_t  DataOUTPipeNumber; /**< Pipe number of the CDC interface's OUT data pipe */
					bool     DataOUTPipeDoubleBank; /** Indicates if the CDC interface's OUT data pipe should use double banking */

					uint8_t  NotificationPipeNumber; /**< Pipe number of the CDC interface's IN notification endpoint, if used */			
					bool     NotificationPipeDoubleBank; /** Indicates if the CDC interface's notification pipe should use double banking */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref CDC_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state
					                */
					uint8_t ControlInterfaceNumber; /**< Interface index of the CDC-ACM control interface within the attached device */
				
					uint16_t DataINPipeSize; /**< Size in bytes of the CDC interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the CDC interface's OUT data pipe */
					uint16_t NotificationPipeSize;  /**< Size in bytes of the CDC interface's IN notification pipe, if used */
					
					bool BidirectionalDataEndpoints; /**< Indicates if the attached CDC interface uses bidirectional data endpoints,
					                                  *   and this has only the IN pipe configured (with \ref Pipe_SetPipeToken()
					                                  *   used to switch the pipe's direction)
					                                  */

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
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_CDC_Host_t;
			
		/* Enums: */
			/** Enum for the possible error codes returned by the \ref CDC_Host_ConfigurePipes() function. */
			enum CDCHost_EnumerationFailure_ErrorCodes_t
			{
				CDC_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				CDC_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				CDC_ENUMERROR_NoCDCInterfaceFound        = 2, /**< A compatible CDC interface was not found in the device's Configuration Descriptor */
				CDC_ENUMERROR_EndpointsNotFound          = 3, /**< Compatible CDC endpoints were not found in the device's CDC interface */
			};
	
		/* Function Prototypes: */
			/** General management task for a given CDC host class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing an CDC Class host configuration and state
			 */
			void CDC_Host_USBTask(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Host interface configuration routine, to configure a given CDC host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given CDC Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the device.
			 *  This should be called once after the stack has enumerated the attached device, while the host state machine is in
			 *  the Addressed state.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing an CDC Class host configuration and state
			 *  \param[in] ConfigDescriptorSize  Length of the attached device's Configuration Descriptor
			 *  \param[in] DeviceConfigDescriptor  Pointer to a buffer containing the attached device's Configuration Descriptor
			 *
			 *  \return A value from the \ref CDCHost_EnumerationFailure_ErrorCodes_t enum
			 */
			uint8_t CDC_Host_ConfigurePipes(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo, uint16_t ConfigDescriptorSize,
			                                void* DeviceConfigDescriptor) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);
			
			/** Sets the line encoding for the attached device's virtual serial port. This should be called when the LineEncoding
			 *  values of the interface have been changed to push the new settings to the USB device.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t CDC_Host_SetLineEncoding(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a Serial Control Line State Change notification to the device. This should be called when the virtual serial
			 *  control lines (DTR, RTS, etc.) have changed states. Line states persist until they are cleared via a second
			 *  notification. This should be called each time the CDC class driver's ControlLineStates.HostToDevice value is updated
			 *  to push the new states to the USB device.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t CDC_Host_SendControlLineStateChange(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Sends a given string to the attached USB device, if connected. If a device is not connected when the function is called, the
			 *  string is discarded. Bytes will be queued for transmission to the device until either the pipe bank becomes full, or the
			 *  \ref CDC_Host_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be 
			 *  packed into a single pipe packet, increasing data throughput.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *  \param[in] Data  Pointer to the string to send to the device
			 *  \param[in] Length  Size in bytes of the string to send to the device
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t CDC_Host_SendString(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo, char* Data, const uint16_t Length)
			                            ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);
			
			/** Sends a given byte to the attached USB device, if connected. If a device is not connected when the function is called, the
			 *  byte is discarded. Bytes will be queued for transmission to the device until either the pipe bank becomes full, or the
			 *  \ref CDC_Host_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be 
			 *  packed into a single pipe packet, increasing data throughput.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *  \param[in] Data  Byte of data to send to the device
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum
			 */
			uint8_t CDC_Host_SendByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo, const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines the number of bytes received by the CDC interface from the device, waiting to be read.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *
			 *  \return Total number of buffered bytes received from the device
			 */
			uint16_t CDC_Host_BytesReceived(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads a byte of data from the device. If no data is waiting to be read of if a USB device is not connected, the function
			 *  returns 0. The \ref CDC_Host_BytesReceived() function should be queried before data is received to ensure that no data
			 *  underflow occurs.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *
			 *  \return Next received byte from the device, or 0 if no data received
			 */
			uint8_t CDC_Host_ReceiveByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum
			 */
			uint8_t CDC_Host_Flush(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Creates a standard characer stream for the given CDC Device instance so that it can be used with all the regular
			 *  functions in the avr-libc <stdio.h> library that accept a FILE stream as a destination (e.g. fprintf). The created
			 *  stream is bidirectional and can be used for both input and output functions.
			 *
			 *  \note The created stream can be given as stdout if desired to direct the standard output from all <stdio.h> functions
			 *        to the given CDC interface.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *  \param[in,out] Stream  Pointer to a FILE structure where the created stream should be placed
			 */
			void CDC_Host_CreateStream(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, FILE* Stream);

			/** Identical to CDC_Host_CreateStream(), except that reads are blocking until the calling stream function terminates
			 *  the transfer. While blocking, the USB and CDC service tasks are called repeatedly to maintain USB communications.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state
			 *  \param[in,out] Stream  Pointer to a FILE structure where the created stream should be placed
			 */
			void CDC_Host_CreateBlockingStream(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, FILE* Stream);

			/** CDC class driver event for a control line state change on a CDC host interface. This event fires each time the device notifies
			 *  the host of a control line state change (containing the virtual serial control line states, such as DCD) and may be hooked in the
			 *  user program by declaring a handler function with the same name and parameters listed here. The new control line states
			 *  are available in the ControlLineStates.DeviceToHost value inside the CDC host interface structure passed as a parameter, set as
			 *  a mask of CDC_CONTROL_LINE_IN_* masks.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state
			 */
			void EVENT_CDC_Host_ControLineStateChanged(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define CDC_CONTROL_CLASS               0x02
			#define CDC_CONTROL_SUBCLASS            0x02
			#define CDC_CONTROL_PROTOCOL            0x01
			#define CDC_DATA_CLASS                  0x0A
			#define CDC_DATA_SUBCLASS               0x00
			#define CDC_DATA_PROTOCOL               0x00
			
			#define CDC_FOUND_DATAPIPE_IN           (1 << 0)
			#define CDC_FOUND_DATAPIPE_OUT          (1 << 1)
			#define CDC_FOUND_NOTIFICATION_IN       (1 << 2)

		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_CDC_CLASS_HOST_C)
				static int CDC_Host_putchar(char c, FILE* Stream);
				static int CDC_Host_getchar(FILE* Stream);
				static int CDC_Host_getchar_Blocking(FILE* Stream);

				void CDC_Host_Event_Stub(void);
				void EVENT_CDC_Host_ControLineStateChanged(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
				                                           ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(CDC_Host_Event_Stub);
				static uint8_t DComp_CDC_Host_NextCDCControlInterface(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DComp_CDC_Host_NextCDCDataInterface(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DComp_CDC_Host_NextCDCInterfaceEndpoint(void* const CurrentDescriptor);
			#endif	
	#endif
				
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
