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

#define  INCLUDE_FROM_CDC_CLASS_HOST_C
#include "CDC.h"

uint8_t CDC_Host_ConfigurePipes(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, uint16_t ConfigDescriptorSize,
                                uint8_t* ConfigDescriptorData)
{
	uint8_t  FoundEndpoints = 0;

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return CDC_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
	                              DComp_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return CDC_ENUMERROR_NoCDCInterfaceFound;
	}

	while (FoundEndpoints != (CDC_FOUND_DATAPIPE_IN | CDC_FOUND_DATAPIPE_OUT | CDC_FOUND_DATAPIPE_NOTIFICATION))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_CDC_Host_NextInterfaceCDCDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (FoundEndpoints & CDC_FOUND_DATAPIPE_NOTIFICATION)
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, 
				                              DComp_CDC_Host_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return CDC_ENUMERROR_NoCDCInterfaceFound;
				}
			}
			else
			{
				FoundEndpoints = 0;

				Pipe_SelectPipe(CDCInterfaceInfo->Config.DataINPipeNumber);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDCInterfaceInfo->Config.DataOUTPipeNumber);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDCInterfaceInfo->Config.NotificationPipeNumber);
				Pipe_DisablePipe();
			
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DComp_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return CDC_ENUMERROR_NoCDCInterfaceFound;
				}
			}

			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DComp_CDC_Host_NextInterfaceCDCDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return CDC_ENUMERROR_EndpointsNotFound;
			}
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{							   
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.NotificationPipeNumber, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.NotificationPipeSize = EndpointData->EndpointSize;

				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				FoundEndpoints |= CDC_FOUND_DATAPIPE_NOTIFICATION;
			}
		}
		else
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

				FoundEndpoints |= CDC_FOUND_DATAPIPE_IN;
			}
			else
			{
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;
				
				FoundEndpoints |= CDC_FOUND_DATAPIPE_OUT;
			}
		}
	}

	return CDC_ENUMERROR_NoError;
}

static uint8_t DComp_CDC_Host_NextCDCControlInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if ((CurrentInterface->Class    == CDC_CONTROL_CLASS)    &&
		    (CurrentInterface->SubClass == CDC_CONTROL_SUBCLASS) &&
			(CurrentInterface->Protocol == CDC_CONTROL_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_CDC_Host_NextCDCDataInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if ((CurrentInterface->Class    == CDC_DATA_CLASS)    &&
		    (CurrentInterface->SubClass == CDC_DATA_SUBCLASS) &&
			(CurrentInterface->Protocol == CDC_DATA_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_CDC_Host_NextInterfaceCDCDataEndpoint(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);
	
		uint8_t EndpointType = (CurrentEndpoint->Attributes & EP_TYPE_MASK);
	
		if (((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT)) &&
		    !(Pipe_IsEndpointBound(CurrentEndpoint->EndpointAddress)))
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

void CDC_Host_USBTask(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo)
{

}

#endif
