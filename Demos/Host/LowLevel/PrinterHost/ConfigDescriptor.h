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

#ifndef _CONFIGDESCRIPTOR_H_
#define _CONFIGDESCRIPTOR_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		
		#include "PrinterHost.h"
		#include "Lib/PrinterCommands.h"
		
	/* Macros: */
		/** Interface Class value for the Printer Device class */
		#define PRINTER_CLASS                    0x07

		/** Interface Subclass value for the Printer Device class */
		#define PRINTER_SUBCLASS                 0x01

		/** Interface Protocol value for a Bidirectional communication encapsulation */
		#define PRINTER_PROTOCOL                 0x02
		
		/** Maximum size of a device configuration descriptor which can be processed by the host, in bytes */
		#define MAX_CONFIG_DESCRIPTOR_SIZE       512

	/* Enums: */
		/** Enum for the possible return codes of the ProcessConfigurationDescriptor() function. */
		enum PrinterHost_GetConfigDescriptorDataCodes_t
		{
			SuccessfulConfigRead            = 0, /**< Configuration Descriptor was processed successfully */
			ControlError                    = 1, /**< A control request to the device failed to complete successfully */
			DescriptorTooLarge              = 2, /**< The device's Configuration Descriptor is too large to process */
			InvalidConfigDataReturned       = 3, /**< The device returned an invalid Configuration Descriptor */
			NoInterfaceFound                = 4, /**< A compatible printer interface was not found in the device's Configuration Descriptor */
			NoEndpointFound                 = 5, /**< The printer data endpoints were not found in the device's Configuration Descriptor */
		};
	
	/* External Variables: */
		/** Interface index of the Bidirectional Printer interface within the device, once the Configuration
		 *  Descriptor has been processed.
		 */
		uint8_t PrinterInterfaceNumber;
		
		/** Interface Alternate Setting index of the Bidirectional Printer interface within the device, once
		 *  the Configuration Descriptor has been processed.
		 */
		uint8_t PrinterAltSetting;

	/* Function Prototypes: */
		uint8_t ProcessConfigurationDescriptor(void);	

		uint8_t DComp_NextBidirectionalPrinterInterface(void* CurrentDescriptor);
		uint8_t DComp_NextPrinterInterfaceBulkDataEndpoint(void* CurrentDescriptor);

#endif
