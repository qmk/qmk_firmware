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
 *  This routine searches for a HID interface descriptor containing at least one Interrupt type IN endpoint.
 *
 *  \return An error code from the \ref GenericHIDHost_GetConfigDescriptorDataCodes_t enum.
 */
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
			return ControlError;
	}
	
	/* Get the HID interface from the configuration descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextHIDInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoHIDInterfaceFound;
	}

	while (FoundEndpoints != ((1 << HID_DATA_IN_PIPE) | (1 << HID_DATA_OUT_PIPE)))
	{
		/* Get the next HID interface's data endpoint descriptor */
		if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              DComp_NextHIDInterfaceDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			/* Not all HID devices have an OUT endpoint - if we've reached the end of the HID descriptor
			 * but only found the mandatory IN endpoint, it's safe to continue with the device enumeration */
			if (FoundEndpoints == (1 << HID_DATA_IN_PIPE))
			  break;
				
			/* Descriptor not found, error out */
			return NoEndpointFound;
		}
		
		/* Retrieve the endpoint address from the endpoint descriptor */
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

		/* If the endpoint is a IN type endpoint */
		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			/* Configure the HID data IN pipe */
			Pipe_ConfigurePipe(HID_DATA_IN_PIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
							   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
			
			FoundEndpoints |= (1 << HID_DATA_IN_PIPE);
		}
		else
		{
			/* Configure the HID data OUT pipe */
			Pipe_ConfigurePipe(HID_DATA_OUT_PIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_OUT,
							   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
			
			FoundEndpoints |= (1 << HID_DATA_OUT_PIPE);		
		}
	}
			
	/* Valid data found, return success */
	return SuccessfulConfigRead;
}

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next Interface descriptor of the correct HID Class value.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextHIDInterface(void* CurrentDescriptor)
{
	/* Determine if the current descriptor is an interface descriptor */
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Check the HID descriptor class, break out if correct class/protocol interface found */
		if (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class == HID_CLASS)
		{
			/* Indicate that the descriptor being searched for has been found */
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	/* Current descriptor does not match what this comparator is looking for */
	return DESCRIPTOR_SEARCH_NotFound;
}

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next Endpoint descriptor inside the current interface descriptor,
 *  aborting the search if another interface descriptor is found before the required endpoint.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextHIDInterfaceDataEndpoint(void* CurrentDescriptor)
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
