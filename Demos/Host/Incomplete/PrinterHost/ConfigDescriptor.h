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
		
	/* Macros: */
		#define PRINTER_CLASS                    0x07
		#define PRINTER_SUBCLASS                 0x01
		
		#define PRINTER_DATA_OUT_PIPE            1
		#define PRINTER_DATA_IN_PIPE             2
		
		#define MAX_CONFIG_DESCRIPTOR_SIZE       512

	/* Enums: */
		enum PrinterHost_GetConfigDescriptorDataCodes_t
		{
			SuccessfulConfigRead                 = 0,
			ControlError                         = 1,
			DescriptorTooLarge                   = 2,
			InvalidConfigDataReturned            = 3,
			NoInterfaceFound                     = 4,
			NoEndpointFound                      = 5,
		};
	
	/* External Variables: */
		uint8_t PrinterInterfaceNumber;
		uint8_t PrinterAltSetting;

	/* Function Prototypes: */
		uint8_t ProcessConfigurationDescriptor(void);	

		uint8_t NextBidirectionalPrinterInterface(void* CurrentDescriptor);
		uint8_t NextInterfaceBulkDataEndpoint(void* CurrentDescriptor);

#endif
