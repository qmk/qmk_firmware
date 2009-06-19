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

static uint8_t CDC_Host_ProcessConfigDescriptor(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo)
{
	uint8_t* ConfigDescriptorData;
	uint16_t ConfigDescriptorSize;
	uint8_t  FoundEndpoints = 0;
	
	if (USB_GetDeviceConfigDescriptor(&ConfigDescriptorSize, NULL) != HOST_SENDCONTROL_Successful)
	  return CDC_ENUMERROR_ControlError;
	
	if (ConfigDescriptorSize > 512)
	  return CDC_ENUMERROR_DescriptorTooLarge;
	  
	ConfigDescriptorData = alloca(ConfigDescriptorSize);

	USB_GetDeviceConfigDescriptor(&ConfigDescriptorSize, ConfigDescriptorData);
	
	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return CDC_ENUMERROR_InvalidConfigDataReturned;
	
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
			/* Check to see if the control interface's notification pipe has been found, if so search for the data interface */
			if (FoundEndpoints & CDC_FOUND_DATAPIPE_NOTIFICATION)
			{
				/* Get the next CDC data interface from the configuration descriptor (CDC class has two CDC interfaces) */
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, 
				                              DComp_CDC_Host_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					/* Descriptor not found, error out */
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
				return CDC_ENUMERROR_NoEndpointFound;
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

				Pipe_SetInfiniteINRequests();
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

				Pipe_SetInfiniteINRequests();
				Pipe_Unfreeze();
				
				FoundEndpoints |= CDC_FOUND_DATAPIPE_IN;
			}
			else
			{
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;
				
				Pipe_Unfreeze();
				
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

static uint8_t DComp_CDC_Host_NextCDCDataInterface(void* CurrentDescriptor)
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

static uint8_t DComp_CDC_Host_NextInterfaceCDCDataEndpoint(void* CurrentDescriptor)
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

void CDC_Host_USBTask(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			if ((ErrorCode = CDC_Host_ProcessConfigDescriptor(CDCInterfaceInfo)) != CDC_ENUMERROR_NoError)
			{
				USB_HostState = HOST_STATE_Unattached;
			}

			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
			{
				USB_HostState = HOST_STATE_Unattached;
			}
				
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
				
			USB_HostState = HOST_STATE_Ready;
			break;
	}
}

#endif
