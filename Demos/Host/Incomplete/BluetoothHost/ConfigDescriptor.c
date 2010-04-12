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

/** \file
 *
 *  USB Device Configuration Descriptor processing routines, to determine the correct pipe configurations
 *  needed to communication with an attached USB device. Descriptors are special  computer-readable structures
 *  which the host requests upon device enumeration, to determine the device's capabilities and functions.
 */

#include "ConfigDescriptor.h"

/** Reads and processes an attached device's descriptors, to determine compatibility and pipe configurations. This
 *  routine will read in the entire configuration descriptor, and configure the hosts pipes to correctly communicate
 *  with compatible devices.
 *
 *  This routine searches for a BT interface descriptor containing bulk IN and OUT data endpoints.
 *
 *  \return An error code from the \ref BluetoothHost_GetConfigDescriptorDataCodes_t enum.
 */
uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t  ConfigDescriptorData[512];
	void*    CurrConfigLocation = ConfigDescriptorData;
	uint16_t CurrConfigBytesRem;
	uint8_t  FoundEndpoints = 0;

	/* Retrieve the entire configuration descriptor into the allocated buffer */
	switch (USB_Host_GetDeviceConfigDescriptor(1, &CurrConfigBytesRem, ConfigDescriptorData, sizeof(ConfigDescriptorData)))
	{
		case HOST_GETCONFIG_Successful:
			break;
		case HOST_GETCONFIG_InvalidData:
			return InvalidConfigDataReturned;
		case HOST_GETCONFIG_BuffOverflow:
			return DescriptorTooLarge;
		default:
			return ControlError;
	}
	
	/* The bluetooth USB transport addendum mandates that the data (not streaming voice) endpoints
	   be in the first interface descriptor (interface 0) */
	USB_GetNextDescriptorOfType(&CurrConfigBytesRem, &CurrConfigLocation, DTYPE_Interface);
	
	/* Ensure that an interface was found, and the end of the descriptor was not reached */
	if (!(CurrConfigBytesRem))
	  return NoBTInterfaceFound;

	/* Get the data IN, data OUT and event notification endpoints for the bluetooth interface */
	while (FoundEndpoints != ((1 << BLUETOOTH_DATA_IN_PIPE) | (1 << BLUETOOTH_DATA_OUT_PIPE) |
	                          (1 << BLUETOOTH_EVENTS_PIPE)))
	{
		/* Fetch the next endpoint from the current bluetooth interface */
		if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              DComp_NextInterfaceBluetoothDataEndpoint))
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

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next Endpoint descriptor inside the current interface descriptor, aborting the 
 *  search if another interface descriptor is found before the required endpoint.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextInterfaceBluetoothDataEndpoint(void* CurrentDescriptor)
{
	/* Determine the type of the current descriptor */
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		/* Indicate that the descriptor being searched for has been found */
		return DESCRIPTOR_SEARCH_Found;
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Indicate that the search has failed prematurely and should be aborted */
		return DESCRIPTOR_SEARCH_Fail;
	}

	/* Current descriptor does not match what this comparator is looking for */
	return DESCRIPTOR_SEARCH_NotFound;
}

