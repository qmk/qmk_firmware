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

static uint8_t CDC_Host_ProcessConfigDescriptor(void)
{
	uint8_t* ConfigDescriptorData;
	uint16_t ConfigDescriptorSize;
	uint8_t  FoundEndpoints = 0;
	
	if (USB_GetDeviceConfigDescriptor(&ConfigDescriptorSize, NULL) != HOST_SENDCONTROL_Successful)
	  return ControlError;
	
	if (ConfigDescriptorSize > MAX_CONFIG_DESCRIPTOR_SIZE)
	  return DescriptorTooLarge;
	  
	ConfigDescriptorData = alloca(ConfigDescriptorSize);

	USB_GetDeviceConfigDescriptor(&ConfigDescriptorSize, ConfigDescriptorData);
	
	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return InvalidConfigDataReturned;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
	                              DComp_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return NoCDCInterfaceFound;
	}

	while (FoundEndpoints != ((1 << CDC_NOTIFICATIONPIPE) | (1 << CDC_DATAPIPE_IN) | (1 << CDC_DATAPIPE_OUT)))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_CDC_Host_NextInterfaceCDCDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			/* Check to see if the control interface's notification pipe has been found, if so search for the data interface */
			if (FoundEndpoints & (1 << CDC_NOTIFICATIONPIPE))
			{
				/* Get the next CDC data interface from the configuration descriptor (CDC class has two CDC interfaces) */
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, 
				                              DComp_CDC_Host_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					/* Descriptor not found, error out */
					return NoCDCInterfaceFound;
				}
			}
			else
			{
				FoundEndpoints = 0;

				Pipe_SelectPipe(CDC_NOTIFICATIONPIPE);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDC_DATAPIPE_IN);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDC_DATAPIPE_OUT);
				Pipe_DisablePipe();
			
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DComp_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return NoCDCInterfaceFound;
				}
			}

			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DComp_CDC_Host_NextInterfaceCDCDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return NoEndpointFound;
			}
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{							   
				Pipe_ConfigurePipe(CDC_NOTIFICATIONPIPE, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);

				Pipe_SetInfiniteINRequests();
				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				FoundEndpoints |= (1 << CDC_NOTIFICATIONPIPE);
			}
		}
		else
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				Pipe_ConfigurePipe(CDC_DATAPIPE_IN, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);

				Pipe_SetInfiniteINRequests();
				Pipe_Unfreeze();
				
				FoundEndpoints |= (1 << CDC_DATAPIPE_IN);
			}
			else
			{
				Pipe_ConfigurePipe(CDC_DATAPIPE_OUT, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
				
				Pipe_Unfreeze();
				
				FoundEndpoints |= (1 << CDC_DATAPIPE_OUT);
			}
		}
	}

	return SuccessfulConfigRead;
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

void CDC_Host_Task(void)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			USB_ControlRequest = (USB_Request_Header_t)
				{
					.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
					.bRequest      = REQ_SetConfiguration,
					.wValue        = 1,
					.wIndex        = 0,
					.wLength       = 0,
				};

			Pipe_SelectPipe(PIPE_CONTROLPIPE);

			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				USB_HostState = HOST_STATE_Unattached;
			}
				
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			if ((ErrorCode = CDC_Host_ProcessConfigDescriptor()) != SuccessfulConfigRead)
			{
				USB_HostState = HOST_STATE_Unattached;
			}
				
			USB_HostState = HOST_STATE_Ready;
			break;
	}
}

#endif
