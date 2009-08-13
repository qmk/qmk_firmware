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

/** \ingroup Group_USBClassMS
 *  @defgroup Group_USBClassMassStorageHost Mass Storage Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/MassStorage.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the Mass Storage USB Class driver.
 *
 *  @{
 */

#ifndef __MS_CLASS_HOST_H__
#define __MS_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/MassStorage.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the HID class driver functions as the HIDInterfaceInfo parameter. This
			 *  stores each HID interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the MS interface's IN data pipe */
					uint8_t  DataOUTPipeNumber; /**< Pipe number of the MS interface's OUT data pipe */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool Active; /**< Indicates if the current interface instance is connected to an attached device, valid
					              *   after \ref HID_Host_ConfigurePipes() is called and the Host state machine is in the
					              *   Configured state
					              */
					uint8_t InterfaceNumber; /**< Interface index of the HID interface within the attached device */

					uint16_t DataINPipeSize; /**< Size in bytes of the MS interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the MS interface's OUT data pipe */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_MS_Host_t;

		/* Enums: */
			enum
			{
				MS_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				MS_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				MS_ENUMERROR_NoMSInterfaceFound        = 2, /**< A compatible Mass Storage interface was not found in the device's Configuration Descriptor */
				MS_ENUMERROR_EndpointsNotFound          = 3, /**< Compatible Mass Storage endpoints were not found in the device's interfaces */
			} MSHost_EnumerationFailure_ErrorCodes_t;
	
		/* Function Prototypes: */
			void MS_Host_USBTask(USB_ClassInfo_MS_Host_t* MSInterfaceInfo);
			uint8_t MS_Host_ConfigurePipes(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint16_t ConfigDescriptorLength,
			                               uint8_t* DeviceConfigDescriptor);
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define MASS_STORE_CLASS               0x08
			#define MASS_STORE_SUBCLASS            0x06
			#define MASS_STORE_PROTOCOL            0x50

			#define MS_FOUND_DATAPIPE_IN           (1 << 0)
			#define MS_FOUND_DATAPIPE_OUT          (1 << 1)
			
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_MS_CLASS_HOST_C)		
				static uint8_t DComp_NextMassStorageInterface(void* CurrentDescriptor);
				static uint8_t DComp_NextInterfaceBulkDataEndpoint(void* CurrentDescriptor);
			#endif
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
