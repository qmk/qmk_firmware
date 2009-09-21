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

uint8_t SI_Host_ConfigurePipes(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, uint16_t ConfigDescriptorSize,
                              uint8_t* DeviceConfigDescriptor)
{
	uint8_t  FoundEndpoints = 0;
	
	memset(&SIInterfaceInfo->State, 0x00, sizeof(SIInterfaceInfo->State));
	
	if (DESCRIPTOR_TYPE(DeviceConfigDescriptor) != DTYPE_Configuration)
	  return SI_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &DeviceConfigDescriptor,
	                              DComp_SI_Host_NextSIInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return SI_ENUMERROR_NoSIInterfaceFound;
	}

	while (FoundEndpoints != (SI_FOUND_EVENTS_IN | SI_FOUND_DATAPIPE_IN | SI_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &DeviceConfigDescriptor,
		                              DComp_SI_Host_NextSIInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return SI_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Endpoint_t);

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

	SIInterfaceInfo->State.IsActive = true;
	return SI_ENUMERROR_NoError;
}

uint8_t DComp_SI_Host_NextSIInterface(void* CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);

		if ((CurrentInterface->Class    == STILL_IMAGE_CLASS)    &&
		    (CurrentInterface->SubClass == STILL_IMAGE_SUBCLASS) &&
		    (CurrentInterface->Protocol == STILL_IMAGE_PROTOCOL))
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

void SI_Host_USBTask(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{

}

static uint8_t SImage_Host_SendBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, SI_PIMA_Container_t* const PIMAHeader)
{
	uint8_t ErrorCode;
	
	PIMAHeader->TransactionID = SIInterfaceInfo->State.TransactionID++;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(PIMAHeader, PIMA_COMMAND_SIZE(0), NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	
	uint8_t ParamBytes = (PIMAHeader->DataLength - PIMA_COMMAND_SIZE(0));

	if (ParamBytes)
	{
		if ((ErrorCode = Pipe_Write_Stream_LE(&PIMAHeader->Params, ParamBytes, NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;
	}
	
	Pipe_ClearOUT();	
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

static uint8_t SImage_Host_ReceiveBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, SI_PIMA_Container_t* const PIMAHeader)
{
	uint16_t TimeoutMSRem = COMMAND_DATA_TIMEOUT_MS;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();
	
	while (!(Pipe_IsReadWriteAllowed()))
	{
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_HSOFI);
			TimeoutMSRem--;

			if (!(TimeoutMSRem))
			{
				return PIPE_RWSTREAM_Timeout;
			}
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
	
	Pipe_Read_Stream_LE(PIMAHeader, PIMA_COMMAND_SIZE(0), NO_STREAM_CALLBACK);
	
	if (PIMAHeader->Type == CType_ResponseBlock)
	{
		uint8_t ParamBytes = (PIMAHeader->DataLength - PIMA_COMMAND_SIZE(0));

		if (ParamBytes)
		  Pipe_Read_Stream_LE(&PIMAHeader->Params, ParamBytes, NO_STREAM_CALLBACK);
		
		Pipe_ClearIN();
		
		PIMAHeader->Code &= 0x0000000F;
	}
	
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

uint8_t SImage_Host_SendData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, void* Buffer, const uint16_t Bytes)
{
	uint8_t ErrorCode;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();
	
	ErrorCode = Pipe_Write_Stream_LE(Buffer, Bytes, NO_STREAM_CALLBACK);

	Pipe_ClearOUT();
	Pipe_Freeze();
	
	return ErrorCode;
}

uint8_t SImage_Host_ReadData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, void* Buffer, const uint16_t Bytes)
{
	uint8_t ErrorCode;

	Pipe_SelectPipe(SIInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();

	ErrorCode = Pipe_Read_Stream_LE(Buffer, Bytes, NO_STREAM_CALLBACK);

	Pipe_Freeze();
	
	return ErrorCode;
}

bool SImage_Host_IsEventReceived(USB_ClassInfo_SI_Host_t* SIInterfaceInfo)
{
	bool IsEventReceived = false;

	Pipe_SelectPipe(SIInterfaceInfo->Config.EventsPipeNumber);
	Pipe_Unfreeze();
	
	if (Pipe_BytesInPipe())
	  IsEventReceived = true;
	
	Pipe_Freeze();
	
	return IsEventReceived;
}

uint8_t SImage_Host_ReceiveEventHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, SI_PIMA_Container_t* const PIMAHeader)
{
	uint8_t ErrorCode;

	Pipe_SelectPipe(SIInterfaceInfo->Config.EventsPipeNumber);
	Pipe_Unfreeze();
	
	ErrorCode = Pipe_Read_Stream_LE(PIMAHeader, sizeof(SI_PIMA_Container_t), NO_STREAM_CALLBACK);
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	return ErrorCode;
}

uint8_t SImage_Host_OpenSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnect;

	uint8_t ErrorCode;

	SI_PIMA_Container_t PIMABlock = (SI_PIMA_Container_t)
							{
								.DataLength    = PIMA_COMMAND_SIZE(0),
								.Type          = CType_CommandBlock,
								.Code          = 0x1002,
								.Params        = {},
							};
							
	if ((ErrorCode = SImage_Host_SendBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	  
	if ((ErrorCode = SImage_Host_ReceiveBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	  
	if ((PIMABlock.Type != CType_ResponseBlock) || (PIMABlock.Code != 0x2001))
	  return SI_ERROR_LOGICAL_CMD_FAILED;
	  
	SIInterfaceInfo->State.TransactionID = 0;
	SIInterfaceInfo->State.IsSessionOpen = true;

	return PIPE_RWSTREAM_NoError;
}

uint8_t SImage_Host_CloseSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnect;

	uint8_t ErrorCode;

	SI_PIMA_Container_t PIMABlock = (SI_PIMA_Container_t)
							{
								.DataLength    = PIMA_COMMAND_SIZE(0),
								.Type          = CType_CommandBlock,
								.Code          = 0x1003,
								.Params        = {},
							};
							
	if ((ErrorCode = SImage_Host_SendBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	  
	if ((ErrorCode = SImage_Host_ReceiveBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	SIInterfaceInfo->State.IsSessionOpen = false;

	if ((PIMABlock.Type != CType_ResponseBlock) || (PIMABlock.Code != 0x2001))
	  return SI_ERROR_LOGICAL_CMD_FAILED;

	return PIPE_RWSTREAM_NoError;
}

uint8_t SImage_Host_SendCommand(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, const uint16_t Operation,
                                const uint8_t TotalParams, uint32_t* Params)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(SIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnect;

	uint8_t ErrorCode;

	SI_PIMA_Container_t PIMABlock = (SI_PIMA_Container_t)
							{
								.DataLength    = PIMA_COMMAND_SIZE(TotalParams),
								.Type          = CType_CommandBlock,
								.Code          = Operation,
							};
							
	memcpy(&PIMABlock.Params, Params, sizeof(uint32_t) * TotalParams);
							
	if ((ErrorCode = SImage_Host_SendBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t SImage_Host_ReceiveResponse(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
{
	uint8_t ErrorCode;
	SI_PIMA_Container_t PIMABlock;

	if ((ErrorCode = SImage_Host_ReceiveBlockHeader(SIInterfaceInfo, &PIMABlock)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((PIMABlock.Type != CType_ResponseBlock) || (PIMABlock.Code != 0x2001))
	  return SI_ERROR_LOGICAL_CMD_FAILED;
	  
	return PIPE_RWSTREAM_NoError;
}

#endif
