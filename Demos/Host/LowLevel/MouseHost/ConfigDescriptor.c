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
 *  \return An error code from the \ref MouseHost_GetConfigDescriptorDataCodes_t enum.
 */
uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t  ConfigDescriptorData[512];
	uint8_t* CurrConfigLocation = ConfigDescriptorData;
	uint16_t CurrConfigBytesRem;

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
	
	/* Get the mouse interface from the configuration descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextMouseInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoHIDInterfaceFound;
	}

	/* Get the mouse interface's data endpoint descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextMouseInterfaceDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoEndpointFound;
	}
	
	/* Retrieve the endpoint address from the endpoint descriptor */
	USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

	/* Configure the mouse data pipe */
	Pipe_ConfigurePipe(MOUSE_DATAPIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
	                   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);

	/* Valid data found, return success */
	return SuccessfulConfigRead;
}

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next Interface descriptor of the correct Mouse HID Class and Protocol values.
 *
 *  \return A value from the \ref DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextMouseInterface(void* CurrentDescriptor)
{
	/* Determine if the current descriptor is an interface descriptor */
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Check the HID descriptor class and protocol, break out if correct class/protocol interface found */
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == MOUSE_CLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == MOUSE_PROTOCOL))
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
 *  This comparator searches for the next IN Endpoint descriptor inside the current interface descriptor,
 *  aborting the search if another interface descriptor is found before the required endpoint.
 *
 *  \return A value from the \ref DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextMouseInterfaceDataEndpoint(void* CurrentDescriptor)
{
	/* Determine the type of the current descriptor */
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		/* Check if the current Endpoint descriptor is of type IN */
		if (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Endpoint_t).EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			/* Indicate that the descriptor being searched for has been found */
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Indicate that the search has failed prematurely and should be aborted */
		return DESCRIPTOR_SEARCH_Fail;
	}

	/* Current descriptor does not match what this comparator is looking for */
	return DESCRIPTOR_SEARCH_NotFound;
}
