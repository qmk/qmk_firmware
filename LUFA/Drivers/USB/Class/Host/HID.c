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

#define INCLUDE_FROM_HID_CLASS_HOST_C
#include "HID.h"

uint8_t HID_Host_ConfigurePipes(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo, uint16_t ConfigDescriptorSize,
                                void* ConfigDescriptorData)
{
	uint8_t FoundEndpoints = 0;

	memset(&HIDInterfaceInfo->State, 0x00, sizeof(HIDInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return HID_ENUMERROR_InvalidConfigDescriptor;
	
	USB_Descriptor_Interface_t* CurrentHIDInterface;
	
	do
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
									  DComp_HID_Host_NextHIDInterface) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return HID_ENUMERROR_NoHIDInterfaceFound;
		}
		
		CurrentHIDInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);
	} while (HIDInterfaceInfo->Config.HIDInterfaceProtocol &&
	         (CurrentHIDInterface->Protocol != HIDInterfaceInfo->Config.HIDInterfaceProtocol));

	HIDInterfaceInfo->State.InterfaceNumber      = CurrentHIDInterface->InterfaceNumber;
	HIDInterfaceInfo->State.SupportsBootProtocol = (CurrentHIDInterface->SubClass != HID_NON_BOOT_PROTOCOL);

	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, DComp_NextHID) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return HID_ENUMERROR_NoHIDDescriptorFound;
	}

	HIDInterfaceInfo->State.HIDReportSize = DESCRIPTOR_CAST(ConfigDescriptorData, USB_HID_Descriptor_t).HIDReportLength;

	while (FoundEndpoints != (HID_FOUND_DATAPIPE_IN | HID_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_HID_Host_NextHIDInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (FoundEndpoints & HID_FOUND_DATAPIPE_IN)
			  break;
				
			return HID_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			Pipe_ConfigurePipe(HIDInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
							   EndpointData->EndpointAddress, EndpointData->EndpointSize,
							   HIDInterfaceInfo->Config.DataINPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			HIDInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;
			
			FoundEndpoints |= HID_FOUND_DATAPIPE_IN;
		}
		else
		{
			Pipe_ConfigurePipe(HIDInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_INTERRUPT, PIPE_TOKEN_OUT,
							   EndpointData->EndpointAddress, EndpointData->EndpointSize,
							   HIDInterfaceInfo->Config.DataOUTPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			HIDInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;
			
			HIDInterfaceInfo->State.DeviceUsesOUTPipe = true;
			
			FoundEndpoints |= HID_FOUND_DATAPIPE_OUT;		
		}
	}

	HIDInterfaceInfo->State.LargestReportSize = 8;
	HIDInterfaceInfo->State.IsActive = true;
	return HID_ENUMERROR_NoError;
}

static uint8_t DComp_HID_Host_NextHIDInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if (CurrentInterface->Class == HID_INTERFACE_CLASS)
		  return DESCRIPTOR_SEARCH_Found;
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_NextHID(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_HID)
	  return DESCRIPTOR_SEARCH_Found;
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	  return DESCRIPTOR_SEARCH_Fail;
	else
	  return DESCRIPTOR_SEARCH_NotFound;	  
}

static uint8_t DComp_HID_Host_NextHIDInterfaceEndpoint(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);	

		if (!(Pipe_IsEndpointBound(CurrentEndpoint->EndpointAddress)))
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void HID_Host_USBTask(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo)
{

}

#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
uint8_t HID_Host_ReceiveReportByID(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo, const uint8_t ReportID, void* Buffer)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
		.bRequest      = REQ_SetReport,
		.wValue        = (REPORT_ITEM_TYPE_In << 8) | ReportID,
		.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
		.wLength       = USB_GetHIDReportSize(HIDInterfaceInfo->Config.HIDParserData, ReportID, REPORT_ITEM_TYPE_In),
	};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	
	return USB_Host_SendControlRequest(Buffer);
}											   
#endif
										   
uint8_t HID_Host_ReceiveReport(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo, void* Buffer)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(HIDInterfaceInfo->State.IsActive))
	  return false;

	uint8_t ErrorCode;

	Pipe_SelectPipe(HIDInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();
	
	uint16_t ReportSize;

#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
	if (!(HIDInterfaceInfo->State.UsingBootProtocol))
	{
		uint8_t ReportID = 0;
	
		if (HIDInterfaceInfo->Config.HIDParserData->UsingReportIDs)
		{
			ReportID = Pipe_Read_Byte();
			*((uint8_t*)Buffer++) = ReportID;
		}
		
		ReportSize = USB_GetHIDReportSize(HIDInterfaceInfo->Config.HIDParserData, ReportID, REPORT_ITEM_TYPE_In);
	}
	else
#endif
	{
		ReportSize = Pipe_BytesInPipe();
	}

	if ((ErrorCode = Pipe_Read_Stream_LE(Buffer, ReportSize, NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	 
	Pipe_ClearIN();		
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

uint8_t HID_Host_SendReportByID(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
                                const uint8_t ReportID,
#endif
                                void* Buffer, const uint16_t ReportSize)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(HIDInterfaceInfo->State.IsActive))
	  return false;

#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
	if (HIDInterfaceInfo->State.DeviceUsesOUTPipe)
	{
		uint8_t ErrorCode;
	
		Pipe_SelectPipe(HIDInterfaceInfo->Config.DataOUTPipeNumber);
		Pipe_Unfreeze();
		
		if (ReportID)
		  Pipe_Write_Stream_LE(&ReportID, sizeof(ReportID), NO_STREAM_CALLBACK);
		
		if ((ErrorCode = Pipe_Write_Stream_LE(Buffer, ReportSize, NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;
		
		Pipe_ClearOUT();
		Pipe_Freeze();
		
		return PIPE_RWSTREAM_NoError;
	}
	else
#endif
	{
		USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_SetReport,
#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
			.wValue        = (REPORT_ITEM_TYPE_Out << 8) | ReportID,
#else
			.wValue        = 0,
#endif
			.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
			.wLength       = ReportSize,
		};

		Pipe_SelectPipe(PIPE_CONTROLPIPE);
		
		return USB_Host_SendControlRequest(Buffer);
	}
}

bool HID_Host_IsReportReceived(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(HIDInterfaceInfo->State.IsActive))
	  return false;

	bool ReportReceived;

	Pipe_SelectPipe(HIDInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();
	
	ReportReceived = Pipe_IsINReceived();
	
	Pipe_Freeze();
	
	return ReportReceived;
}

uint8_t HID_Host_SetBootProtocol(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo)
{
	if (HIDInterfaceInfo->State.UsingBootProtocol)
	  return HOST_SENDCONTROL_Successful;

	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_SetProtocol,
			.wValue        = 0,
			.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	
	if (!(HIDInterfaceInfo->State.SupportsBootProtocol))
	  return HID_ERROR_LOGICAL;

	if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	HIDInterfaceInfo->State.LargestReportSize = 8;
	HIDInterfaceInfo->State.UsingBootProtocol = true;
	
	return HOST_SENDCONTROL_Successful;
}

#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
uint8_t HID_Host_SetReportProtocol(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo)
{
	uint8_t ErrorCode;

	uint8_t HIDReportData[HIDInterfaceInfo->State.HIDReportSize];
	
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_GetDescriptor,
			.wValue        = (DTYPE_Report << 8),
			.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
			.wLength       = HIDInterfaceInfo->State.HIDReportSize,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(HIDReportData)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	  
	if (HIDInterfaceInfo->State.UsingBootProtocol)
	{
		USB_ControlRequest = (USB_Request_Header_t)
			{
				.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
				.bRequest      = REQ_SetProtocol,
				.wValue        = 1,
				.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
				.wLength       = 0,
			};

		if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
		  return ErrorCode;

		HIDInterfaceInfo->State.UsingBootProtocol = false;
	}
	
	if (HIDInterfaceInfo->Config.HIDParserData == NULL)
	  return HID_ERROR_LOGICAL;
		
	if ((ErrorCode = USB_ProcessHIDReport(HIDReportData, HIDInterfaceInfo->State.HIDReportSize,
	                                      HIDInterfaceInfo->Config.HIDParserData)) != HID_PARSE_Successful)
	{
		return HID_ERROR_LOGICAL | ErrorCode;
	}

	uint8_t LargestReportSizeBits = HIDInterfaceInfo->Config.HIDParserData->LargestReportSizeBits;
	HIDInterfaceInfo->State.LargestReportSize = (LargestReportSizeBits >> 3) + ((LargestReportSizeBits & 0x07) != 0);

	return 0;
}
#endif

#endif
