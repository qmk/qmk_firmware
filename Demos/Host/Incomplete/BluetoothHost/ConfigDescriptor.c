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

#include "ConfigDescriptor.h"

uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t  ConfigDescriptorData[512];
	uint8_t* CurrConfigLocation = ConfigDescriptorData;
	uint16_t CurrConfigBytesRem;
	uint8_t  FoundEndpoints = 0;

	/* Retrieve the entire configuration descriptor into the allocated buffer */
	switch (USB_GetDeviceConfigDescriptor(1, &CurrConfigBytesRem, ConfigDescriptorData, sizeof(ConfigDescriptorData)))
	{
		case HOST_GETCONFIG_Successful:
			break;
		case HOST_GETCONFIG_InvalidData:
			return InvalidConfigDataReturned;
		case HOST_GETCONFIG_BuffOverflow:
			return DescriptorTooLarge;
		default:
			return ControlErrorDuringConfigRead;
	}
	
	/* The bluetooth USB transport addendium mandates that the data (not streaming voice) endpoints
	   be in the first interface descriptor (interface 0) */
	USB_GetNextDescriptorOfType(&CurrConfigBytesRem, &CurrConfigLocation, DTYPE_Interface);
	
	/* Ensure that an interface was found, and the end of the descriptor was not reached */
	if (!(CurrConfigBytesRem))
	  return NoInterfaceFound;

	/* Get the data IN, data OUT and event notification endpoints for the bluetooth interface */
	while (FoundEndpoints != ((1 << BLUETOOTH_DATA_IN_PIPE) | (1 << BLUETOOTH_DATA_OUT_PIPE) |
	                          (1 << BLUETOOTH_EVENTS_PIPE)))
	{
		/* Fetch the next endpoint from the current bluetooth interface */
		if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              NextInterfaceBluetoothDataEndpoint))
		{
			/* Descriptor not found, error out */
			return NoEndpointFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

		/* Check if the endpoint is a bulk or interrupt type endpoint */
		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				/* Configure the events IN pipe */
				Pipe_ConfigurePipe(BLUETOOTH_EVENTS_PIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_SINGLE);

				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				/* Set the flag indicating that the events notification pipe has been found */
				FoundEndpoints |= (1 << BLUETOOTH_EVENTS_PIPE);	
			}
		}
		else
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				/* Configure the data IN pipe */
				Pipe_ConfigurePipe(BLUETOOTH_DATA_IN_PIPE, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_SINGLE);

				/* Set the flag indicating that the data IN pipe has been found */
				FoundEndpoints |= (1 << BLUETOOTH_DATA_IN_PIPE);
			}
			else
			{
				/* Configure the data OUT pipe */
				Pipe_ConfigurePipe(BLUETOOTH_DATA_OUT_PIPE, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_SINGLE);

				/* Set the flag indicating that the data OUT pipe has been found */
				FoundEndpoints |= (1 << BLUETOOTH_DATA_OUT_PIPE);
			}		
		}

	}

	/* Valid data found, return success */
	return SuccessfulConfigRead;
}

uint8_t NextInterfaceBluetoothDataEndpoint(void* CurrentDescriptor)
{
	/* PURPOSE: Find next interface endpoint descriptor before next interface descriptor */

	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	  return DESCRIPTOR_SEARCH_Found;
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	  return DESCRIPTOR_SEARCH_Fail;

	return DESCRIPTOR_SEARCH_NotFound;
}

