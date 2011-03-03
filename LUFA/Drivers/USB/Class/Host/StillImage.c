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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../Core/USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_SI_DRIVER
#define  __INCLUDE_FROM_STILLIMAGE_HOST_C
#include "StillImage.h"

uint8_t SI_Host_ConfigurePipes(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                               uint16_t ConfigDescriptorSize,
                               void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint      = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint     = NULL;
	USB_Descriptor_Endpoint_t*  EventsEndpoint      = NULL;
	USB_Descriptor_Interface_t* StillImageInterface = NULL;

	memset(&SIInterfaceInfo->State, 0x00, sizeof(SIInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return SI_ENUMERROR_InvalidConfigDescriptor;

	while (!(DataINEndpoint) || !(DataOUTEndpoint) || !(EventsEndpoint))
	{
		if (!(StillImageInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_SI_Host_NextSIInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DCOMP_SI_Host_NextSIInterface) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return SI_ENUMERROR_NoCompatibleInterfaceFound;
			}

			StillImageInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

			DataINEndpoint  = NULL;
			DataOUTEndpoint = NULL;
			EventsEndpoint  = NULL;

			continue;
		}

		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
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

	for (uint8_t PipeNum = 1; PipeNum < PIPE_TOTAL_PIPES; PipeNum++)
	{
		uint16_t Size;
		uint8_t  Type;
		uint8_t  Token;
		uint8_t  EndpointAddress;
		uint8_t  InterruptPeriod;
		bool     DoubleBanked;

		if (PipeNum == SIInterfaceInfo->Config.DataINPipeNumber)
		{
			Size            = DataINEndpoint->EndpointSize;
			EndpointAddress = DataINEndpoint->EndpointAddress;
			Token           = PIPE_TOKEN_IN;
			Type            = EP_TYPE_BULK;
			DoubleBanked    = SIInterfaceInfo->Config.DataINPipeDoubleBank;
			InterruptPeriod = 0;

			SIInterfaceInfo->State.DataINPipeSize = DataINEndpoint->EndpointSize;
		}
		else if (PipeNum == SIInterfaceInfo->Config.DataOUTPipeNumber)
		{
			Size            = DataOUTEndpoint->EndpointSize;
			EndpointAddress = DataOUTEndpoint->EndpointAddress;
			Token           = PIPE_TOKEN_OUT;
			Type            = EP_TYPE_BULK;
			DoubleBanked    = SIInterfaceInfo->Config.DataOUTPipeDoubleBank;
			InterruptPeriod = 0;

			SIInterfaceInfo->State.DataOUTPipeSize = DataOUTEndpoint->EndpointSize;
		}
		else if (PipeNum == SIInterfaceInfo->Config.EventsPipeNumber)
		{
			Size            = EventsEndpoint->EndpointSize;
			EndpointAddress = EventsEndpoint->EndpointAddress;
			Token           = PIPE_TOKEN_IN;
			Type            = EP_TYPE_INTERRUPT;
			DoubleBanked    = SIInterfaceInfo->Config.EventsPipeDoubleBank;
			InterruptPeriod = EventsEndpoint->PollingIntervalMS;

			SIInterfaceInfo->State.EventsPipeSize = EventsEndpoint->EndpointSize;
		}
		else
		{
			continue;
		}
		
		if (!(Pipe_ConfigurePipe(PipeNum, Type, Token, EndpointAddress, Size,
		                         DoubleBanked ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE)))
		{
			return SI_ENUMERROR_PipeConfigurationFailed;
		}
		
		if (InterruptPeriod)
		  Pipe_SetInterruptPeriod(InterruptPeriod);
	}

	SIInterfaceInfo->State.InterfaceNumber = StillImageInterface->InterfaceNumber;
	SIInterfaceInfo->State.IsActive = true;

	return SI_ENUMERROR_NoError;
}

uint8_t DCOMP_SI_Host_NextSIInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == SI_CSCP_StillImageClass)    &&
		    (Interface->SubClass == SI_CSCP_StillImageSubclass) &&
		    (Interface->Protocol == SI_CSCP_BulkOnlyProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

uint8_t DCOMP_SI_Host_NextSIInterfaceEndpoint(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		uint8_t EndpointType = (Endpoint->Attributes & EP_TYPE_MASK);

		if (((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT)) &&
		    (!(Pipe_IsEndpointBound(Endpoint->EndpointAddress))))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

uint8_t SI_Host_SendBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                                PIMA_Container_t* const PIMAHeader)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	if (SIInterfaceInfo->State.IsSessionOpen)
	  PIMAHeader->TransactionID = SIInterfaceInfo->State.TransactionID++;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(PIMAHeader, PIMA_COMMAND_SIZE(0), NULL)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	uint8_t ParamBytes = (PIMAHeader->DataLength - PIMA_COMMAND_SIZE(0));

	if (ParamBytes)
	{
		if ((ErrorCode = Pipe_Write_Stream_LE(&PIMAHeader->Params, ParamBytes, NULL)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;
	}

	Pipe_ClearOUT();
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

uint8_t SI_Host_ReceiveBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                                   PIMA_Container_t* const PIMAHeader)
{
	uint16_t TimeoutMSRem        = SI_COMMAND_DATA_TIMEOUT_MS;
	uint16_t PreviousFrameNumber = USB_Host_GetFrameNumber();

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();

	while (!(Pipe_IsINReceived()))
	{
		uint16_t CurrentFrameNumber = USB_Host_GetFrameNumber();

		if (CurrentFrameNumber != PreviousFrameNumber)
		{
			PreviousFrameNumber = CurrentFrameNumber;

			if (!(TimeoutMSRem--))
			  return PIPE_RWSTREAM_Timeout;
		}

		Pipe_Freeze();
		Pipe_SelectPipe(SIInterfaceInfo->Config.DataOUTPipeNumber);
		Pipe_Unfreeze();

		if (Pipe_IsStalled())
		{
			USB_Host_ClearPipeStall(SIInterfaceInfo->Config.DataOUTPipeNumber);
			return PIPE_RWSTREAM_PipeStalled;
		}

		Pipe_Freeze();
		Pipe_SelectPipe(SIInterfaceInfo->Config.DataINPipeNumber);
		Pipe_Unfreeze();

		if (Pipe_IsStalled())
		{
			USB_Host_ClearPipeStall(SIInterfaceInfo->Config.DataINPipeNumber);
			return PIPE_RWSTREAM_PipeStalled;
		}

		if (USB_HostState == HOST_STATE_Unattached)
		  return PIPE_RWSTREAM_DeviceDisconnected;
	}

	Pipe_Read_Stream_LE(PIMAHeader, PIMA_COMMAND_SIZE(0), NULL);

	if (PIMAHeader->Type == PIMA_CONTAINER_ResponseBlock)
	{
		uint8_t ParamBytes = (PIMAHeader->DataLength - PIMA_COMMAND_SIZE(0));

		if (ParamBytes)
		  Pipe_Read_Stream_LE(&PIMAHeader->Params, ParamBytes, NULL);

		Pipe_ClearIN();
	}

	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

uint8_t SI_Host_SendData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                         void* Buffer,
                         const uint16_t Bytes)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	ErrorCode = Pipe_Write_Stream_LE(Buffer, Bytes, NULL);

	Pipe_ClearOUT();
	Pipe_Freeze();

	return ErrorCode;
}

uint8_t SI_Host_ReadData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                         void* Buffer,
                         const uint16_t Bytes)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();

	ErrorCode = Pipe_Read_Stream_LE(Buffer, Bytes, NULL);

	Pipe_Freeze();

	return ErrorCode;
}

bool SI_Host_IsEventReceived(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	bool IsEventReceived = false;

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return false;

	Pipe_SelectPipe(SIInterfaceInfo->Config.EventsPipeNumber);
	Pipe_Unfreeze();

	if (Pipe_BytesInPipe())
	  IsEventReceived = true;

	Pipe_Freeze();

	return IsEventReceived;
}

uint8_t SI_Host_ReceiveEventHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                                   PIMA_Container_t* const PIMAHeader)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(SIInterfaceInfo->Config.EventsPipeNumber);
	Pipe_Unfreeze();

	ErrorCode = Pipe_Read_Stream_LE(PIMAHeader, sizeof(PIMA_Container_t), NULL);

	Pipe_ClearIN();
	Pipe_Freeze();

	return ErrorCode;
}

uint8_t SI_Host_OpenSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	SIInterfaceInfo->State.TransactionID = 0;
	SIInterfaceInfo->State.IsSessionOpen = false;

	PIMA_Container_t PIMABlock = (PIMA_Container_t)
		{
			.DataLength    = PIMA_COMMAND_SIZE(1),
			.Type          = PIMA_CONTAINER_CommandBlock,
			.Code          = 0x1002,
			.Params        = {1},
		};

	if ((ErrorCode = SI_Host_SendBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((ErrorCode = SI_Host_ReceiveBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((PIMABlock.Type != PIMA_CONTAINER_ResponseBlock) || (PIMABlock.Code != 0x2001))
	  return SI_ERROR_LOGICAL_CMD_FAILED;

	SIInterfaceInfo->State.IsSessionOpen = true;

	return PIPE_RWSTREAM_NoError;
}

uint8_t SI_Host_CloseSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	PIMA_Container_t PIMABlock = (PIMA_Container_t)
		{
			.DataLength    = PIMA_COMMAND_SIZE(1),
			.Type          = PIMA_CONTAINER_CommandBlock,
			.Code          = 0x1003,
			.Params        = {1},
		};

	if ((ErrorCode = SI_Host_SendBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((ErrorCode = SI_Host_ReceiveBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	SIInterfaceInfo->State.IsSessionOpen = false;

	if ((PIMABlock.Type != PIMA_CONTAINER_ResponseBlock) || (PIMABlock.Code != 0x2001))
	  return SI_ERROR_LOGICAL_CMD_FAILED;

	return PIPE_RWSTREAM_NoError;
}

uint8_t SI_Host_SendCommand(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
                            const uint16_t Operation,
                            const uint8_t TotalParams,
                            uint32_t* const Params)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	PIMA_Container_t PIMABlock = (PIMA_Container_t)
		{
			.DataLength    = PIMA_COMMAND_SIZE(TotalParams),
			.Type          = PIMA_CONTAINER_CommandBlock,
			.Code          = Operation,
		};

	memcpy(&PIMABlock.Params, Params, sizeof(uint32_t) * TotalParams);

	if ((ErrorCode = SI_Host_SendBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t SI_Host_ReceiveResponse(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	uint8_t ErrorCode;
	PIMA_Container_t PIMABlock;

	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	if ((ErrorCode = SI_Host_ReceiveBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((PIMABlock.Type != PIMA_CONTAINER_ResponseBlock) || (PIMABlock.Code != 0x2001))
	  return SI_ERROR_LOGICAL_CMD_FAILED;

	return PIPE_RWSTREAM_NoError;
}

#endif

