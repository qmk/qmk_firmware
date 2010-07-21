/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_PRINTER_CLASS_HOST_C
#define  __INCLUDE_FROM_PRINTER_DRIVER
#include "Printer.h"

uint8_t PRNT_Host_ConfigurePipes(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                                 uint16_t ConfigDescriptorSize,
							     void* DeviceConfigDescriptor)
{
	uint8_t FoundEndpoints = 0;
	
	memset(&PRNTInterfaceInfo->State, 0x00, sizeof(PRNTInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(DeviceConfigDescriptor) != DTYPE_Configuration)
	  return PRNT_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &DeviceConfigDescriptor,
	                              DCOMP_PRNT_NextPRNTInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return PRNT_ENUMERROR_NoPrinterInterfaceFound;
	}

	USB_Descriptor_Interface_t* PrinterInterface = DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Interface_t);

	PRNTInterfaceInfo->State.InterfaceNumber  = PrinterInterface->InterfaceNumber;
	PRNTInterfaceInfo->State.AlternateSetting = PrinterInterface->AlternateSetting;
	
	while (FoundEndpoints != (PRNT_FOUND_DATAPIPE_IN | PRNT_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &DeviceConfigDescriptor,
		                              DCOMP_PRNT_NextPRNTInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return PRNT_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			Pipe_ConfigurePipe(PRNTInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
			                   EndpointData->EndpointAddress, EndpointData->EndpointSize,
			                   PRNTInterfaceInfo->Config.DataINPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			PRNTInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= PRNT_FOUND_DATAPIPE_IN;
		}
		else
		{
			Pipe_ConfigurePipe(PRNTInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
			                   EndpointData->EndpointAddress, EndpointData->EndpointSize,
			                   PRNTInterfaceInfo->Config.DataOUTPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			PRNTInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= PRNT_FOUND_DATAPIPE_OUT;
		}		
	}

	PRNTInterfaceInfo->State.IsActive = true;
	return PRNT_ENUMERROR_NoError;
}

static uint8_t DCOMP_PRNT_NextPRNTInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		if ((DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Class    == PRINTER_CLASS)    &&
		    (DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).SubClass == PRINTER_SUBCLASS) &&
			(DESCRIPTOR_CAST(CurrentDescriptor, USB_Descriptor_Interface_t).Protocol == PRINTER_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_PRNT_NextPRNTInterfaceEndpoint(void* CurrentDescriptor)
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

uint8_t PRNT_Host_SetBidirectionalMode(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	if (PRNTInterfaceInfo->State.AlternateSetting)
	{
		uint8_t ErrorCode;
	
		USB_ControlRequest = (USB_Request_Header_t)
			{
				.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE),
				.bRequest      = REQ_SetInterface,
				.wValue        = PRNTInterfaceInfo->State.AlternateSetting,
				.wIndex        = PRNTInterfaceInfo->State.InterfaceNumber,
				.wLength       = 0,
			};
		
		Pipe_SelectPipe(PIPE_CONTROLPIPE);
		
		if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
		  return ErrorCode;
	}
	
	return HOST_SENDCONTROL_Successful;
}

uint8_t PRNT_Host_GetPortStatus(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                                uint8_t* const PortStatus)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_GetPortStatus,
			.wValue        = 0,
			.wIndex        = PRNTInterfaceInfo->State.InterfaceNumber,
			.wLength       = sizeof(uint8_t),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(PortStatus);
}

uint8_t PRNT_Host_SoftReset(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest     = REQ_SoftReset,
			.wValue       = 0,
			.wIndex       = PRNTInterfaceInfo->State.InterfaceNumber,
			.wLength      = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t PRNT_Host_SendData(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                           void* PrinterCommands,
                           const uint16_t CommandSize)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();
	
	if ((ErrorCode = Pipe_Write_Stream_LE(PrinterCommands, CommandSize, NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearOUT();
	while (!(Pipe_IsOUTReady()))
	{
		if (USB_HostState == HOST_STATE_Unattached)
		  return PIPE_RWSTREAM_DeviceDisconnected;
	}
	
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

uint8_t PRNT_Host_GetDeviceID(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                              char* const DeviceIDString,
                              const uint16_t BufferSize)
{
	uint8_t  ErrorCode = HOST_SENDCONTROL_Successful;
	uint16_t DeviceIDStringLength = 0;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      =  REQ_GetDeviceID,
			.wValue        = 0,
			.wIndex        = PRNTInterfaceInfo->State.InterfaceNumber,
			.wLength       = sizeof(DeviceIDStringLength),
		};
		
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(&DeviceIDStringLength)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	  
	if (!(DeviceIDStringLength))
	{
		DeviceIDString[0] = 0x00;
		return HOST_SENDCONTROL_Successful;
	}
	
	DeviceIDStringLength = SwapEndian_16(DeviceIDStringLength);

	if (DeviceIDStringLength > BufferSize)
	  DeviceIDStringLength = BufferSize;

	USB_ControlRequest.wLength = DeviceIDStringLength;
	
	if ((ErrorCode = USB_Host_SendControlRequest(DeviceIDString)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	  
	memmove(&DeviceIDString[0], &DeviceIDString[2], DeviceIDStringLength - 2);

	DeviceIDString[DeviceIDStringLength - 2] = 0x00;
	
	return HOST_SENDCONTROL_Successful;
}

#endif
