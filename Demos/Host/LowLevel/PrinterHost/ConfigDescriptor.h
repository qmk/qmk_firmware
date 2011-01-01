/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#ifndef _CONFIGDESCRIPTOR_H_
#define _CONFIGDESCRIPTOR_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include "PrinterHost.h"
		#include "Lib/PrinterCommands.h"

	/* Macros: */
		/** Pipe number of the Printer data IN pipe. */
		#define PRINTER_DATA_IN_PIPE             1

		/** Pipe number of the Printer data OUT pipe. */
		#define PRINTER_DATA_OUT_PIPE            2

	/* Enums: */
		/** Enum for the possible return codes of the \ref ProcessConfigurationDescriptor() function. */
		enum PrinterHost_GetConfigDescriptorDataCodes_t
		{
			SuccessfulConfigRead            = 0, /**< Configuration Descriptor was processed successfully */
			ControlError                    = 1, /**< A control request to the device failed to complete successfully */
			DescriptorTooLarge              = 2, /**< The device's Configuration Descriptor is too large to process */
			InvalidConfigDataReturned       = 3, /**< The device returned an invalid Configuration Descriptor */
			NoCompatibleInterfaceFound      = 4, /**< A compatible interface with the required endpoints was not found */
		};

	/* External Variables: */
		/** Interface index of the Bidirectional Printer interface within the device, once the Configuration
		 *  Descriptor has been processed.
		 */
		extern uint8_t PrinterInterfaceNumber;

		/** Interface Alternate Setting index of the Bidirectional Printer interface within the device, once
		 *  the Configuration Descriptor has been processed.
		 */
		extern uint8_t PrinterAltSetting;

	/* Function Prototypes: */
		uint8_t ProcessConfigurationDescriptor(void);

		uint8_t DComp_NextBidirectionalPrinterInterface(void* CurrentDescriptor);
		uint8_t DComp_NextPrinterInterfaceBulkDataEndpoint(void* CurrentDescriptor);

#endif

