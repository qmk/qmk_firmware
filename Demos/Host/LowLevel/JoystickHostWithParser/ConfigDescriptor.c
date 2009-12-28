/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  This routine searches for a HID interface descriptor containing at least one Interrupt type IN endpoint and HID descriptor.
 *
 *  \return An error code from the \ref JoystickHostWithParser_GetConfigDescriptorDataCodes_t enum.
 */
uint8_t ProcessConfigurationDescriptor(void)
{
	uint8_t  ConfigDescriptorData[512];
	void*    CurrConfigLocation = ConfigDescriptorData;
	uint16_t CurrConfigBytesRem;

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

	/* Get the joystick interface from the configuration descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextJoystickInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoHIDInterfaceFound;
	}
	
	/* Get the joystick interface's HID descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextHID) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoHIDDescriptorFound;
	}

	/* Save the HID report size for later use */
	HIDReportSize = DESCRIPTOR_CAST(CurrConfigLocation, USB_Descriptor_HID_t).HIDReportLength;
	
	/* Get the joystick interface's data endpoint descriptor */
	if (USB_GetNextDescriptorComp(&CurrConfigBytesRem, &CurrConfigLocation,
	                              DComp_NextJoystickInterfaceDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		/* Descriptor not found, error out */
		return NoEndpointFound;
	}
	
	/* Retrieve the endpoint address from the endpoint descriptor */
	USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(CurrConfigLocation, USB_Descriptor_Endpoint_t);

	/* Configure the joystick data pipe */
	Pipe_ConfigurePipe(JOYSTICK_DATAPIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
	                   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);

	/* Valid data found, return success */
	return SuccessfulConfigRead;
}

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next Interface descriptor of the correct Joystick HID Class and Protocol values.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextJoystickInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		/* Check the HID descriptor class and protocol, break out if correct class/protocol interface found */
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == JOYSTICK_CLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == JOYSTICK_PROTOCOL))
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
 *  This comparator searches for the next IN Endpoint descriptor inside the current interface descriptor,
 *  aborting the search if another interface descriptor is found before the required endpoint.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextJoystickInterfaceDataEndpoint(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		if (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Endpoint_t).EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

/** Descriptor comparator function. This comparator function is can be called while processing an attached USB device's
 *  configuration descriptor, to search for a specific sub descriptor. It can also be used to abort the configuration
 *  descriptor processing if an incompatible descriptor configuration is found.
 *
 *  This comparator searches for the next HID descriptor within the current HID interface descriptor.
 *
 *  \return A value from the DSEARCH_Return_ErrorCodes_t enum
 */
uint8_t DComp_NextHID(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_HID)
	  return DESCRIPTOR_SEARCH_Found;
	else
	  return DESCRIPTOR_SEARCH_NotFound;	  
}
