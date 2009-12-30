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
 *  This routine searches for a CDC interface descriptor containing bulk data IN and OUT endpoints, and an interrupt event endpoint.
 *
 *  \return An error code from the \ref CDCHost_GetConfigDescriptorDataCodes_t enum.
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
	
	/* Get the CDC control interface from the configuration descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoCDCInterfaceFound;
	}

	/* Get the IN and OUT data and IN notification endpoints for the CDC interface */
	while (FoundEndpoints != ((1 << CDC_NOTIFICATIONPIPE) | (1 << CDC_DATAPIPE_IN) | (1 << CDC_DATAPIPE_OUT)))
	{
		/* Fetch the next bulk or interrupt endpoint from the current CDC interface */
		if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              DComp_NextCDCDataInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			/* Check to see if the control interface's notification pipe has been found, if so search for the data interface */
			if (FoundEndpoints & (1 << CDC_NOTIFICATIONPIPE))
			{
				/* Get the next CDC data interface from the configuration descriptor (CDC class has two CDC interfaces) */
				if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation, 
				                              DComp_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					/* Descriptor not found, error out */
					return NoCDCInterfaceFound;
				}
			}
			else
			{
				/* Clear the found endpoints mask, since any already processed endpoints aren't in the CDC interface we need */
				FoundEndpoints = 0;

				/* Disable any already configured pipes from the invalid CDC interfaces */
				Pipe_SelectPipe(CDC_NOTIFICATIONPIPE);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDC_DATAPIPE_IN);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDC_DATAPIPE_OUT);
				Pipe_DisablePipe();
			
				/* Get the next CDC control interface from the configuration descriptor (CDC class has two CDC interfaces) */
				if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
				                              DComp_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					/* Descriptor not found, error out */
					return NoCDCInterfaceFound;
				}
			}

			/* Fetch the next bulk or interrupt endpoint from the current CDC interface */
			if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
			                              DComp_NextCDCDataInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				/* Descriptor not found, error out */
				return NoEndpointFound;
			}
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

		/* Check if the found endpoint is a interrupt or bulk type descriptor */
		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			/* If the endpoint is a IN type interrupt endpoint */
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{							   
				/* Configure the notification pipe */
				Pipe_ConfigurePipe(CDC_NOTIFICATIONPIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);

				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				/* Set the flag indicating that the notification pipe has been found */
				FoundEndpoints |= (1 << CDC_NOTIFICATIONPIPE);
			}
		}
		else
		{
			/* Check if the endpoint is a bulk IN or bulk OUT endpoint */
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				/* Kill the configured OUT pipe if the data endpoints are bidirectional */
				if (Pipe_IsEndpointBound(EndpointData->EndpointAddress))
				  Pipe_DisablePipe();

				/* Configure the data IN pipe */
				Pipe_ConfigurePipe(CDC_DATAPIPE_IN, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				
				/* Set the flag indicating that the data IN pipe has been found */
				FoundEndpoints |= (1 << CDC_DATAPIPE_IN);
			}
			else
			{
				/* Only configure the OUT data pipe if the data endpoints haev not shown to be bidirectional */
				if (!(Pipe_IsEndpointBound(EndpointData->EndpointAddress)))
				{
					/* Configure the data OUT pipe */
					Pipe_ConfigurePipe(CDC_DATAPIPE_OUT, EP_TYPE_BULK, PIPE_TOKEN_OUT,
									   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				}
				
				/* Set the flag indicating that the data OUT pipe has been found */
				FoundEndpoints |= (1 << CDC_DATAPIPE_OUT);
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
 *  This comparator searches for the next Interface descriptor of the correct CDC control Class, Subclass and Protocol values.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextCDCControlInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Check the CDC descriptor class, subclass and protocol, break out if correct control interface found */
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == CDC_CONTROL_CLASS)    &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).SubClass == CDC_CONTROL_SUBCLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == CDC_CONTROL_PROTOCOL))
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
 *  This comparator searches for the next Interface descriptor of the correct CDC data Class, Subclass and Protocol values.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextCDCDataInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Check the CDC descriptor class, subclass and protocol, break out if correct data interface found */
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == CDC_DATA_CLASS)    &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).SubClass == CDC_DATA_SUBCLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == CDC_DATA_PROTOCOL))
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
 *  This comparator searches for the next bulk IN or OUT endpoint, or interrupt IN endpoint within the current interface,
 *  aborting the search if another interface descriptor is found before the required endpoint (so that it may be compared
 *  using a different comparator to determine if it is another CDC class interface).
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextCDCDataInterfaceEndpoint(void* CurrentDescriptor)
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
