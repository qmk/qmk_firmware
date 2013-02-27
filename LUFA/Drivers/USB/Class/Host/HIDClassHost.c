/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../Core/USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_HID_DRIVER
#define  __INCLUDE_FROM_HID_HOST_C
#include "HIDClassHost.h"

uint8_t HID_Host_ConfigurePipes(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
                                uint16_t ConfigDescriptorSize,
                                void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint  = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint = NULL;
	USB_Descriptor_Interface_t* HIDInterface    = NULL;
	USB_HID_Descriptor_HID_t*   HIDDescriptor   = NULL;

	memset(&HIDInterfaceInfo->State, 0x00, sizeof(HIDInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return HID_ENUMERROR_InvalidConfigDescriptor;

	while (!(DataINEndpoint) || !(DataOUTEndpoint))
	{
		if (!(HIDInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_HID_Host_NextHIDInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (DataINEndpoint)
			  break;

			do
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DCOMP_HID_Host_NextHIDInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return HID_ENUMERROR_NoCompatibleInterfaceFound;
				}

				HIDInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);
			} while (HIDInterfaceInfo->Config.HIDInterfaceProtocol &&
					 (HIDInterface->Protocol != HIDInterfaceInfo->Config.HIDInterfaceProtocol));

			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DCOMP_HID_Host_NextHIDDescriptor) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return HID_ENUMERROR_NoCompatibleInterfaceFound;
			}

			HIDDescriptor = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_HID_Descriptor_HID_t);

			DataINEndpoint  = NULL;
			DataOUTEndpoint = NULL;

			continue;
		}

		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->EndpointAddress & ENDPOINT_DIR_MASK) == ENDPOINT_DIR_IN)
		  DataINEndpoint  = EndpointData;
		else
		  DataOUTEndpoint = EndpointData;
	}

	HIDInterfaceInfo->Config.DataINPipe.Size  = le16_to_cpu(DataINEndpoint->EndpointSize);
	HIDInterfaceInfo->Config.DataINPipe.EndpointAddress = DataINEndpoint->EndpointAddress;
	HIDInterfaceInfo->Config.DataINPipe.Type  = EP_TYPE_INTERRUPT;

	if (!(Pipe_ConfigurePipeTable(&HIDInterfaceInfo->Config.DataINPipe, 1)))
	  return false;

	if (DataOUTEndpoint)
	{
		HIDInterfaceInfo->Config.DataOUTPipe.Size = le16_to_cpu(DataOUTEndpoint->EndpointSize);
		HIDInterfaceInfo->Config.DataOUTPipe.EndpointAddress = DataOUTEndpoint->EndpointAddress;
		HIDInterfaceInfo->Config.DataOUTPipe.Type = EP_TYPE_INTERRUPT;

		if (!(Pipe_ConfigurePipeTable(&HIDInterfaceInfo->Config.DataOUTPipe, 1)))
		  return false;
	}

	HIDInterfaceInfo->State.InterfaceNumber      = HIDInterface->InterfaceNumber;
	HIDInterfaceInfo->State.HIDReportSize        = LE16_TO_CPU(HIDDescriptor->HIDReportLength);
	HIDInterfaceInfo->State.SupportsBootProtocol = (HIDInterface->SubClass != HID_CSCP_NonBootProtocol);
	HIDInterfaceInfo->State.LargestReportSize    = 8;
	HIDInterfaceInfo->State.IsActive             = true;

	return HID_ENUMERROR_NoError;
}

static uint8_t DCOMP_HID_Host_NextHIDInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if (Interface->Class == HID_CSCP_HIDClass)
		  return DESCRIPTOR_SEARCH_Found;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_HID_Host_NextHIDDescriptor(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == HID_DTYPE_HID)
	  return DESCRIPTOR_SEARCH_Found;
	else if (Header->Type == DTYPE_Interface)
	  return DESCRIPTOR_SEARCH_Fail;
	else
	  return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_HID_Host_NextHIDInterfaceEndpoint(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		if (!(Pipe_IsEndpointBound(Endpoint->EndpointAddress)))
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
uint8_t HID_Host_ReceiveReportByID(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
                                   const uint8_t ReportID,
                                   void* Buffer)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
		.bRequest      = HID_REQ_SetReport,
		.wValue        = ((HID_REPORT_ITEM_In + 1) << 8) | ReportID,
		.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
		.wLength       = USB_GetHIDReportSize(HIDInterfaceInfo->Config.HIDParserData, ReportID, HID_REPORT_ITEM_In),
	};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(Buffer);
}
#endif

uint8_t HID_Host_ReceiveReport(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
                               void* Buffer)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(HIDInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(HIDInterfaceInfo->Config.DataINPipe.Address);
	Pipe_Unfreeze();

	uint16_t ReportSize;
	uint8_t* BufferPos = Buffer;

#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
	if (!(HIDInterfaceInfo->State.UsingBootProtocol))
	{
		uint8_t ReportID = 0;

		if (HIDInterfaceInfo->Config.HIDParserData->UsingReportIDs)
		{
			ReportID = Pipe_Read_8();
			*(BufferPos++) = ReportID;
		}

		ReportSize = USB_GetHIDReportSize(HIDInterfaceInfo->Config.HIDParserData, ReportID, HID_REPORT_ITEM_In);
	}
	else
#endif
	{
		ReportSize = Pipe_BytesInPipe();
	}

	if ((ErrorCode = Pipe_Read_Stream_LE(BufferPos, ReportSize, NULL)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearIN();
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

uint8_t HID_Host_SendReportByID(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
                                const uint8_t ReportID,
#endif
                                const uint8_t ReportType,
                                void* Buffer,
                                const uint16_t ReportSize)
{
#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
	if ((USB_HostState != HOST_STATE_Configured) || !(HIDInterfaceInfo->State.IsActive))
	  return false;

	if (HIDInterfaceInfo->State.DeviceUsesOUTPipe && (ReportType == HID_REPORT_ITEM_Out))
	{
		uint8_t ErrorCode;

		Pipe_SelectPipe(HIDInterfaceInfo->Config.DataOUTPipe.Address);
		Pipe_Unfreeze();

		if (ReportID)
		  Pipe_Write_Stream_LE(&ReportID, sizeof(ReportID), NULL);

		if ((ErrorCode = Pipe_Write_Stream_LE(Buffer, ReportSize, NULL)) != PIPE_RWSTREAM_NoError)
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
			.bRequest      = HID_REQ_SetReport,
#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
			.wValue        = ((ReportType + 1) << 8) | ReportID,
#else
			.wValue        = ((ReportType + 1) << 8),
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

	Pipe_SelectPipe(HIDInterfaceInfo->Config.DataINPipe.Address);
	Pipe_Unfreeze();

	ReportReceived = Pipe_IsINReceived();

	Pipe_Freeze();

	return ReportReceived;
}

uint8_t HID_Host_SetBootProtocol(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo)
{
	uint8_t ErrorCode;

	if (!(HIDInterfaceInfo->State.SupportsBootProtocol))
	  return HID_ERROR_LOGICAL;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = HID_REQ_SetProtocol,
			.wValue        = 0,
			.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	HIDInterfaceInfo->State.LargestReportSize = 8;
	HIDInterfaceInfo->State.UsingBootProtocol = true;

	return HOST_SENDCONTROL_Successful;
}

uint8_t HID_Host_SetIdlePeriod(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
                               const uint16_t MS)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = HID_REQ_SetIdle,
			.wValue        = ((MS << 6) & 0xFF00),
			.wIndex        = HIDInterfaceInfo->State.InterfaceNumber,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
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
			.wValue        = (HID_DTYPE_Report << 8),
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
				.bRequest      = HID_REQ_SetProtocol,
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

	uint16_t LargestReportSizeBits = HIDInterfaceInfo->Config.HIDParserData->LargestReportSizeBits;
	HIDInterfaceInfo->State.LargestReportSize = (LargestReportSizeBits >> 3) + ((LargestReportSizeBits & 0x07) != 0);

	return 0;
}
#endif

#endif

