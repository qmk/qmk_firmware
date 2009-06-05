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

/** \file
 *
 *  Header file for ConfigDescriptor.c.
 */

#ifndef _CONFIGDESCRIPTOR_H_
#define _CONFIGDESCRIPTOR_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		
		#include "MassStorageHost.h"
		
	/* Macros: */
		/** Interface Class value for the Mass Storage Device class */
		#define MASS_STORE_CLASS               0x08

		/** Interface Class value for the Mass Storage Device subclass */
		#define MASS_STORE_SUBCLASS            0x06

		/** Interface Protocol value for the Bulk Only transport protocol */
		#define MASS_STORE_PROTOCOL            0x50
		
		/** Maximum size of a device configuration descriptor which can be processed by the host, in bytes */
		#define MAX_CONFIG_DESCRIPTOR_SIZE     512

	/* Enums: */
		/** Enum for the possible return codes of the ProcessConfigurationDescriptor() function. */
		enum MassStorageHost_GetConfigDescriptorDataCodes_t
		{
			SuccessfulConfigRead            = 0, /**< Configuration Descriptor was processed successfully */
			ControlError                    = 1, /**< A control request to the device failed to complete successfully */
			DescriptorTooLarge              = 2, /**< The device's Configuration Descriptor is too large to process */
			InvalidConfigDataReturned       = 3, /**< The device returned an invalid Configuration Descriptor */
			NoInterfaceFound                = 4, /**< A compatible MSD interface was not found in the device's Configuration Descriptor */
			NoEndpointFound                 = 5, /**< The correct MSD endpoint descriptors were not found in the device's MSD interface */
		};
		
	/* Function Prototypes: */
		uint8_t ProcessConfigurationDescriptor(void);	

		uint8_t DComp_NextMassStorageInterface(void* CurrentDescriptor);
		uint8_t DComp_NextInterfaceBulkDataEndpoint(void* CurrentDescriptor);
		
#endif
