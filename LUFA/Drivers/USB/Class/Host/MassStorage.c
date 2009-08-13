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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define INCLUDE_FROM_MS_CLASS_HOST_C
#include "MassStorage.h"

#warning The Mass Storage Host mode Class driver is currently incomplete and is for preview purposes only.

uint8_t MS_Host_ConfigurePipes(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint16_t ConfigDescriptorLength,
							   uint8_t* DeviceConfigDescriptor)
{
	uint8_t FoundEndpoints = 0;
	
	memset(&MSInterfaceInfo->State, 0x00, sizeof(MSInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(DeviceConfigDescriptor) != DTYPE_Configuration)
	  return MS_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorLength, &DeviceConfigDescriptor,
	                              DComp_NextMassStorageInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return MS_ENUMERROR_NoMSInterfaceFound;
	}

	MSInterfaceInfo->State.InterfaceNumber	     =
	#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES)
	                     DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Interface_t)->InterfaceNumber;
	#else
	                     DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Interface_t)->bInterfaceNumber;
	#endif
	
	while (FoundEndpoints != (MS_FOUND_DATAPIPE_IN | MS_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorLength, &DeviceConfigDescriptor,
		                              DComp_NextInterfaceBulkDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return MS_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			Pipe_ConfigurePipe(MSInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
			                   EndpointData->EndpointAddress, EndpointData->EndpointSize,
			                   PIPE_BANK_DOUBLE);
			MSInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= MS_FOUND_DATAPIPE_IN;
		}
		else
		{
			Pipe_ConfigurePipe(MSInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
			                   EndpointData->EndpointAddress, EndpointData->EndpointSize,
			                   PIPE_BANK_DOUBLE);
			MSInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= MS_FOUND_DATAPIPE_OUT;
		}		
	}

	MSInterfaceInfo->State.Active = true;
	return MS_ENUMERROR_NoError;
}

static uint8_t DComp_NextMassStorageInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == MASS_STORE_CLASS)    &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).SubClass == MASS_STORE_SUBCLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == MASS_STORE_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_NextInterfaceBulkDataEndpoint(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		uint8_t EndpointType = (DESCRIPTOR_CAST(CurrentDescriptor,
		                                        USB_Descriptor_Endpoint_t).Attributes & EP_TYPE_MASK);

		if (EndpointType == EP_TYPE_BULK)
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void MS_Host_USBTask(USB_ClassInfo_MS_Host_t* MSInterfaceInfo)
{
	
}

#endif
