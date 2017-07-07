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
 *  This routine searches for a CDC interface descriptor containing bulk data IN and OUT endpoints, and an interrupt event endpoint.
 *
 *  \return An error code from the \ref CDCHost_GetConfigDescriptorDataCodes_t enum.
 */
uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t  ConfigDescriptorData[512];
	void*    CurrConfigLocation = ConfigDescriptorData;
	uint16_t CurrConfigBytesRem;

	USB_Descriptor_Interface_t* CDCControlInterface  = NULL;
	USB_Descriptor_Endpoint_t*  DataINEndpoint       = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint      = NULL;
	USB_Descriptor_Endpoint_t*  NotificationEndpoint = NULL;

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

	while (!(DataINEndpoint) || !(DataOUTEndpoint) || !(NotificationEndpoint))
	{
		/* See if we've found a likely compatible interface, and if there is an endpoint within that interface */
		if (!(CDCControlInterface) ||
		    USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              DComp_NextCDCDataInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			/* Check if we have already found the control interface's notification endpoint or not */
			if (NotificationEndpoint)
			{
				/* Get the next CDC data interface from the configuration descriptor */
				if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
											  DComp_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					/* Descriptor not found, error out */
					return NoCompatibleInterfaceFound;
				}

				/* Clear any found endpoints */
				DataINEndpoint       = NULL;
				DataOUTEndpoint      = NULL;
			}
			else
			{
				/* Get the next CDC control interface from the configuration descriptor */
				if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
											  DComp_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					/* Descriptor not found, error out */
					return NoCompatibleInterfaceFound;
				}

				/* Save the interface in case we need to refer back to it later */
				CDCControlInterface = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Interface_t);

				/* Clear any found endpoints */
				NotificationEndpoint = NULL;
			}

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
			  NotificationEndpoint = EndpointData;
			else
			  DataINEndpoint = EndpointData;
		}
		else
		{
			DataOUTEndpoint = EndpointData;
		}
	}

	/* Configure the CDC data IN pipe */
	Pipe_ConfigurePipe(CDC_DATA_IN_PIPE, EP_TYPE_BULK, DataINEndpoint->EndpointAddress, DataINEndpoint->EndpointSize, 1);

	/* Configure the CDC data OUT pipe */
	Pipe_ConfigurePipe(CDC_DATA_OUT_PIPE, EP_TYPE_BULK, DataOUTEndpoint->EndpointAddress, DataOUTEndpoint->EndpointSize, 1);

	/* Configure the CDC notification pipe */
	Pipe_ConfigurePipe(CDC_NOTIFICATION_PIPE, EP_TYPE_INTERRUPT, NotificationEndpoint->EndpointAddress, NotificationEndpoint->EndpointSize, 1);
	Pipe_SetInterruptPeriod(NotificationEndpoint->PollingIntervalMS);

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
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		/* Check the CDC descriptor class, subclass and protocol, break out if correct control interface found */
		if ((Interface->Class    == CDC_CSCP_CDCClass)    &&
		    (Interface->SubClass == CDC_CSCP_ACMSubclass) &&
		    (Interface->Protocol == CDC_CSCP_ATCommandProtocol))
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
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		/* Check the CDC descriptor class, subclass and protocol, break out if correct data interface found */
		if ((Interface->Class    == CDC_CSCP_CDCDataClass)   &&
		    (Interface->SubClass == CDC_CSCP_NoDataSubclass) &&
		    (Interface->Protocol == CDC_CSCP_NoDataProtocol))
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
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

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

