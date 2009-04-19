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
 *  USB Device Configuration Descriptor processing routines, to determine the correct pipe configurations
 *  needed to communication with an attached USB device. Descriptors are special  computer-readable structures
 *  which the host requests upon device enumeration, to determine the device's capabilities and functions.
 */

#include "ConfigDescriptor.h"

/** Reads and processes an attached device's descriptors, to determine compatibility and pipe configurations. This
 *  routine will read in the entire configuration descriptor, and configure the hosts pipes to correctly communicate
 *  with compatible devices.
 *
 *  This routine searches for a SI interface descriptor containing bulk IN and OUT data endpoints.
 *
 *  \return An error code from the StillImageHost_GetConfigDescriptorDataCodes_t enum.
 */
uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t* ConfigDescriptorData;
	uint16_t ConfigDescriptorSize;
	uint8_t  FoundEndpoints = 0;
	
	/* Get Configuration Descriptor size from the device */
	if (USB_GetDeviceConfigDescriptor(&ConfigDescriptorSize, NULL) != HOST_SENDCONTROL_Successful)
	  return ControlError;
	
	/* Ensure that the Configuration Descriptor isn't too large */
	if (ConfigDescriptorSize > MAX_CONFIG_DESCRIPTOR_SIZE)
	  return DescriptorTooLarge;
	  
	/* Allocate enough memory for the entire config descriptor */
	ConfigDescriptorData = alloca(ConfigDescriptorSize);

	/* Retrieve the entire configuration descriptor into the allocated buffer */
	USB_GetDeviceConfigDescriptor(&ConfigDescriptorSize, ConfigDescriptorData);
	
	/* Validate returned data - ensure first entry is a configuration header descriptor */
	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return InvalidConfigDataReturned;
	
	/* Get the Still Image interface from the configuration descriptor */
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, NextStillImageInterface))
	{
		/* Descriptor not found, error out */
		return NoInterfaceFound;
	}

	/* Get the IN and OUT data and event endpoints for the Still Image interface */
	while (FoundEndpoints != ((1 << SIMAGE_EVENTS_PIPE) | (1 << SIMAGE_DATA_IN_PIPE) | (1 << SIMAGE_DATA_OUT_PIPE)))
	{
		/* Fetch the next endpoint from the current Still Image interface */
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                                   NextSImageInterfaceDataEndpoint))
		{
			/* Descriptor not found, error out */
			return NoEndpointFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		/* Check if the found endpoint is a interrupt or bulk type descriptor */
		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			/* If the endpoint is a IN type interrupt endpoint */
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				/* Configure the events pipe */
				Pipe_ConfigurePipe(SIMAGE_EVENTS_PIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_DOUBLE);			

				Pipe_SetInfiniteINRequests();
				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				/* Set the flag indicating that the events pipe has been found */
				FoundEndpoints |= (1 << SIMAGE_EVENTS_PIPE);
			}
		}
		else
		{
			/* Check if the endpoint is a bulk IN or bulk OUT endpoint */
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				/* Configure the data IN pipe */
				Pipe_ConfigurePipe(SIMAGE_DATA_IN_PIPE, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_DOUBLE);

				Pipe_SetInfiniteINRequests();

				/* Set the flag indicating that the data IN pipe has been found */
				FoundEndpoints |= (1 << SIMAGE_DATA_IN_PIPE);
			}
			else
			{
				/* Configure the data OUT pipe */
				Pipe_ConfigurePipe(SIMAGE_DATA_OUT_PIPE, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_DOUBLE);

				/* Set the flag indicating that the data OUT pipe has been found */
				FoundEndpoints |= (1 << SIMAGE_DATA_OUT_PIPE);
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
 *  This comparator searches for the next Interface descriptor of the correct Still Image Class, Subclass and Protocol values.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
DESCRIPTOR_COMPARATOR(NextStillImageInterface)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Check the descriptor class and protocol, break out if correct class/protocol interface found */
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == SIMAGE_CLASS)    &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).SubClass == SIMAGE_SUBCLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == SIMAGE_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next Interrupt or Bulk Endpoint descriptor of the current SI interface, aborting the
 *  search if another interface descriptor is found before the next endpoint.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
DESCRIPTOR_COMPARATOR(NextSImageInterfaceDataEndpoint)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		uint8_t EndpointType = (DESCRIPTOR_CAST(CurrentDescriptor,
		                                        USB_Descriptor_Endpoint_t).Attributes & EP_TYPE_MASK);
	
		if ((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT))
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}
