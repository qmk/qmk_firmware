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
					uint8_t  DataOUTPipeNumber; /**< Pipe number of the CDC interface's OUT data pipe */
					uint8_t  NotificationPipeNumber; /**< Pipe number of the CDC interface's IN notification endpoint, if used */			
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					uint16_t DataINPipeSize; /**< Size in bytes of the CDC interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the CDC interface's OUT data pipe */
					uint16_t NotificationPipeSize;  /**< Size in bytes of the CDC interface's IN notification endpoint, if used */

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
						bool Active; /**< Indicates if the interface is currently active, i.e. attached to the connected device */
					
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
			enum
			{
				CDC_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				CDC_ENUMERROR_ControlError               = 1, /**< A control request to the device failed to complete successfully */
				CDC_ENUMERROR_DescriptorTooLarge         = 2, /**< The device's Configuration Descriptor is too large to process */
				CDC_ENUMERROR_InvalidConfigDataReturned  = 3, /**< The device returned an invalid Configuration Descriptor */
				CDC_ENUMERROR_NoCDCInterfaceFound        = 4, /**< A compatible CDC interface was not found in the device's Configuration Descriptor */
				CDC_ENUMERROR_EndpointsNotFound          = 5, /**< Compatible CDC endpoints were not found in the device's CDC interface */
			} CDCHost_EnumerationFailure_ErrorCodes_t;
	
		/* Function Prototypes: */
			void CDC_Host_USBTask(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo);
			uint8_t CDC_Host_ConfigurePipes(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, uint16_t MaxConfigBufferSize);

			void EVENT_CDC_Host_ControLineStateChanged(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo);
			
			uint8_t CDC_Host_SetLineEncoding(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo);
			uint8_t CDC_Host_SendControlLineStateChange(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo);
			
			void CDC_Host_SendString(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, char* Data, uint16_t Length);
			void CDC_Host_SendByte(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, uint8_t Data);
			uint16_t CDC_Host_BytesReceived(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo);
			uint8_t CDC_Host_ReceiveByte(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo);

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
			#define CDC_FOUND_DATAPIPE_NOTIFICATION (1 << 2)

		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_CDC_CLASS_HOST_C)
				static uint8_t DComp_CDC_Host_NextCDCControlInterface(void* CurrentDescriptor);
				static uint8_t DComp_CDC_Host_NextCDCDataInterface(void* CurrentDescriptor);
				static uint8_t DComp_CDC_Host_NextInterfaceCDCDataEndpoint(void* CurrentDescriptor);
			#endif	
	#endif
				
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
