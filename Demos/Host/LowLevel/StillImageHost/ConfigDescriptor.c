/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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
 *  \return An error code from the \ref StillImageHost_GetConfigDescriptorDataCodes_t enum.
 */
uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t  ConfigDescriptorData[512];
	void*    CurrConfigLocation = ConfigDescriptorData;
	uint16_t CurrConfigBytesRem;

	USB_Descriptor_Interface_t* StillImageInterface = NULL;
	USB_Descriptor_Endpoint_t*  DataINEndpoint      = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint     = NULL;
	USB_Descriptor_Endpoint_t*  EventsEndpoint      = NULL;

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

	while (!(DataINEndpoint) || !(DataOUTEndpoint))
	{
		/* See if we've found a likely compatible interface, and if there is an endpoint within that interface */
		if (!(StillImageInterface) ||
		    USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              DComp_NextStillImageInterfaceDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			/* Get the next Still Image interface from the configuration descriptor */
			if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
										  DComp_NextStillImageInterface) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				/* Descriptor not found, error out */
				return NoCompatibleInterfaceFound;
			}

			/* Save the interface in case we need to refer back to it later */
			StillImageInterface = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Interface_t);

			/* Clear any found endpoints */
			DataINEndpoint  = NULL;
			DataOUTEndpoint = NULL;
			EventsEndpoint  = NULL;

			/* Skip the remainder of the loop as we have not found an endpoint yet */
			continue;
		}

		/* Retrieve the endpoint address from the endpoint descriptor */
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

		/* If the endpoint is a IN type endpoint */
		if ((EndpointData->EndpointAddress & ENDPOINT_DIR_MASK) == ENDPOINT_DIR_IN)
		{
			/* Check if the found endpoint is a interrupt or bulk type descriptor */
			if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
			  EventsEndpoint = EndpointData;
			else
			  DataINEndpoint = EndpointData;
		}
		else
		{
			DataOUTEndpoint = EndpointData;
		}
	}

	/* Configure the Still Image data IN pipe */
	Pipe_ConfigurePipe(SIMAGE_DATA_IN_PIPE, EP_TYPE_BULK, DataINEndpoint->EndpointAddress, DataINEndpoint->EndpointSize, 1);

	/* Configure the Still Image data OUT pipe */
	Pipe_ConfigurePipe(SIMAGE_DATA_OUT_PIPE, EP_TYPE_BULK, DataOUTEndpoint->EndpointAddress, DataOUTEndpoint->EndpointSize, 1);

	/* Configure the Still Image events pipe */
	Pipe_ConfigurePipe(SIMAGE_EVENTS_PIPE, EP_TYPE_INTERRUPT, EventsEndpoint->EndpointAddress, EventsEndpoint->EndpointSize, 1);
	Pipe_SetInterruptPeriod(EventsEndpoint->PollingIntervalMS);

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
uint8_t DComp_NextStillImageInterface(void* CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		/* Check the descriptor class, subclass and protocol, break out if correct interface found */
		if ((Interface->Class    == SI_CSCP_StillImageClass)    &&
		    (Interface->SubClass == SI_CSCP_StillImageSubclass) &&
		    (Interface->Protocol == SI_CSCP_BulkOnlyProtocol))
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
uint8_t DComp_NextStillImageInterfaceDataEndpoint(void* CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		/* Check the endpoint type, break out if correct BULK or INTERRUPT type endpoint found */
		if (((Endpoint->Attributes & EP_TYPE_MASK) == EP_TYPE_BULK) ||
		    ((Endpoint->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

