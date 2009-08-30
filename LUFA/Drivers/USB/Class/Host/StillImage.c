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

#define INCLUDE_FROM_SI_CLASS_HOST_C
#include "StillImage.h"

#warning The Still Image Host mode Class driver is currently incomplete and is for preview purposes only.

uint8_t SI_Host_ConfigurePipes(USB_ClassInfo_SI_Host_t* SIInterfaceInfo, uint16_t ConfigDescriptorSize,
                              uint8_t* ConfigDescriptorData)
{
	uint8_t  FoundEndpoints = 0;
	
	memset(&SIInterfaceInfo->State, 0x00, sizeof(SIInterfaceInfo->State));
	
	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return SI_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
	                              DComp_SI_Host_NextSIInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return SI_ENUMERROR_NoSIInterfaceFound;
	}

	while (FoundEndpoints != (SI_FOUND_EVENTS_IN | SI_FOUND_DATAPIPE_IN | SI_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_SI_Host_NextSIInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return SI_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				Pipe_ConfigurePipe(SIInterfaceInfo->Config.EventsPipeNumber, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_DOUBLE);			
				SIInterfaceInfo->State.EventsPipeSize = EndpointData->EndpointSize;

				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				FoundEndpoints |= SI_FOUND_EVENTS_IN;
			}
		}
		else
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				Pipe_ConfigurePipe(SIInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_DOUBLE);
				SIInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

				FoundEndpoints |= SI_FOUND_DATAPIPE_IN;
			}
			else
			{
				Pipe_ConfigurePipe(SIInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   PIPE_BANK_DOUBLE);
				SIInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;

				FoundEndpoints |= SI_FOUND_DATAPIPE_OUT;
			}
		}
	}

	return SI_ENUMERROR_NoError;
}

uint8_t DComp_SI_Host_NextSIInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == STILL_IMAGE_CLASS)    &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).SubClass == STILL_IMAGE_SUBCLASS) &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == STILL_IMAGE_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

uint8_t DComp_SI_Host_NextSIInterfaceEndpoint(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);
	
		uint8_t EndpointType = (CurrentEndpoint->Attributes & EP_TYPE_MASK);

		if (((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT)) &&
		    (!(Pipe_IsEndpointBound(CurrentEndpoint->EndpointAddress))))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void SI_Host_USBTask(USB_ClassInfo_SI_Host_t* SIInterfaceInfo)
{

}

#endif
