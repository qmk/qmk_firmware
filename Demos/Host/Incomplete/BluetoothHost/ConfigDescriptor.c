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

	USB_Descriptor_Endpoint_t* DataINEndpoint  = NULL;
	USB_Descriptor_Endpoint_t* DataOUTEndpoint = NULL;
	USB_Descriptor_Endpoint_t* EventsEndpoint  = NULL;

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
			return DevControlError;
	}

	/* The Bluetooth USB transport addendum mandates that the data (not streaming voice) endpoints
	   be in the first interface descriptor (interface 0) */
	USB_GetNextDescriptorOfType(&CurrConfigBytesRem, &CurrConfigLocation, DTYPE_Interface);

	/* Ensure that an interface was found, and the end of the descriptor was not reached */
	if (!(CurrConfigBytesRem))
	  return NoCompatibleInterfaceFound;

	while (!(DataINEndpoint) || !(DataOUTEndpoint))
	{
		/* Get the next Still Image interface's data endpoint descriptor */
		if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
		                              DComp_NextInterfaceBluetoothDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			/* Data endpoints not found within the first bluetooth device interface, error out */
			return NoCompatibleInterfaceFound;
		}

		/* Retrieve the endpoint address from the endpoint descriptor */
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

		/* If the endpoint is a IN type endpoint */
		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
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

	/* Configure the Bluetooth data IN pipe */
	Pipe_ConfigurePipe(BLUETOOTH_DATA_IN_PIPE, EP_TYPE_BULK, PIPE_TOKEN_IN,
	                   DataINEndpoint->EndpointAddress, DataINEndpoint->EndpointSize, PIPE_BANK_SINGLE);

	/* Configure the Bluetooth data OUT pipe */
	Pipe_ConfigurePipe(BLUETOOTH_DATA_OUT_PIPE, EP_TYPE_BULK, PIPE_TOKEN_OUT,
					   DataOUTEndpoint->EndpointAddress, DataOUTEndpoint->EndpointSize, PIPE_BANK_SINGLE);

	/* Configure the Bluetooth events pipe */
	Pipe_ConfigurePipe(BLUETOOTH_EVENTS_PIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
					   EventsEndpoint->EndpointAddress, EventsEndpoint->EndpointSize, PIPE_BANK_SINGLE);
	Pipe_SetInterruptPeriod(EventsEndpoint->PollingIntervalMS);

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
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	/* Determine the type of the current descriptor */
	if (Header->Type == DTYPE_Endpoint)
	  return DESCRIPTOR_SEARCH_Found;
	else if (Header->Type == DTYPE_Interface)
	  return DESCRIPTOR_SEARCH_Fail;
	else
	  return DESCRIPTOR_SEARCH_NotFound;
}

