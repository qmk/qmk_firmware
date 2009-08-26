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

static uint8_t MassStore_SendCommand(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, MS_CommandBlockWrapper_t* SCSICommandBlock)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;

	if (++MSInterfaceInfo->State.TransactionTag == 0xFFFFFFFF)
	  MSInterfaceInfo->State.TransactionTag = 1;

	Pipe_SelectPipe(MSInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(SCSICommandBlock, sizeof(MS_CommandBlockWrapper_t))) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearOUT();
	while(!(Pipe_IsOUTReady()));

	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

static uint8_t MassStore_WaitForDataReceived(USB_ClassInfo_MS_Host_t* MSInterfaceInfo)
{
	uint16_t TimeoutMSRem = COMMAND_DATA_TIMEOUT_MS;

	Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();

	while (!(Pipe_IsINReceived()))
	{
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_HSOFI);
			TimeoutMSRem--;

			if (!(TimeoutMSRem))
			  return PIPE_RWSTREAM_Timeout;
		}
	
		Pipe_Freeze();
		Pipe_SelectPipe(MSInterfaceInfo->Config.DataOUTPipeNumber);
		Pipe_Unfreeze();

		if (Pipe_IsStalled())
		{
			USB_Host_ClearPipeStall(MSInterfaceInfo->Config.DataOUTPipeNumber);

			return PIPE_RWSTREAM_PipeStalled;
		}
		
		Pipe_Freeze();
		Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
		Pipe_Unfreeze();

		if (Pipe_IsStalled())
		{
			USB_Host_ClearPipeStall(MSInterfaceInfo->Config.DataINPipeNumber);

			return PIPE_RWSTREAM_PipeStalled;
		}
		  
		if (USB_HostState == HOST_STATE_Unattached)
		  return PIPE_RWSTREAM_DeviceDisconnected;
	};
	
	Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Freeze();
		
	Pipe_SelectPipe(MSInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

static uint8_t MassStore_SendReceiveData(USB_ClassInfo_MS_Host_t* MSInterfaceInfo,
                                         MS_CommandBlockWrapper_t* SCSICommandBlock, void* BufferPtr)
{
	uint8_t  ErrorCode = PIPE_RWSTREAM_NoError;
	uint16_t BytesRem  = SCSICommandBlock->DataTransferLength;

	if (SCSICommandBlock->Flags & COMMAND_DIRECTION_DATA_IN)
	{
		Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
		Pipe_Unfreeze();
		
		if ((ErrorCode = Pipe_Read_Stream_LE(BufferPtr, BytesRem)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		Pipe_ClearIN();
	}
	else
	{
		Pipe_SelectPipe(MSInterfaceInfo->Config.DataOUTPipeNumber);
		Pipe_Unfreeze();

		if ((ErrorCode = Pipe_Write_Stream_LE(BufferPtr, BytesRem)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		Pipe_ClearOUT();
		
		while (!(Pipe_IsOUTReady()))
		{
			if (USB_HostState == HOST_STATE_Unattached)
			  return PIPE_RWSTREAM_DeviceDisconnected;
		}
	}

	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

static uint8_t MassStore_GetReturnedStatus(USB_ClassInfo_MS_Host_t* MSInterfaceInfo,
                                           MS_CommandStatusWrapper_t* SCSICommandStatus)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;

	if ((ErrorCode = MassStore_WaitForDataReceived(MSInterfaceInfo)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();
	
	if ((ErrorCode = Pipe_Read_Stream_LE(&SCSICommandStatus, sizeof(MS_CommandStatusWrapper_t))) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	  
	Pipe_ClearIN();
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_ResetMSInterface(USB_ClassInfo_MS_Host_t* MSInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.Active))
	  return HOST_SENDCONTROL_DeviceDisconnect;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_MassStorageReset,
			.wValue        = 0,
			.wIndex        = MSInterfaceInfo->State.InterfaceNumber,
			.wLength       = 0,
		};
	
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t MS_Host_GetMaxLUN(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t* MaxLUNIndex)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.Active))
	  return HOST_SENDCONTROL_DeviceDisconnect;

	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_GetMaxLUN,
			.wValue        = 0,
			.wIndex        = MSInterfaceInfo->State.InterfaceNumber,
			.wLength       = 1,
		};
		
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(MaxLUNIndex)) == HOST_SENDCONTROL_SetupStalled)
	{
		Pipe_ClearStall();

		*MaxLUNIndex = 0;
	}
	
	return ErrorCode;
}

uint8_t MS_Host_GetInquiryData(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, SCSI_Inquiry_Response_t* InquiryData)
{

}

uint8_t MS_Host_TestUnitReady(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex, bool* DeviceReady);
uint8_t MS_Host_ReadDeviceCapacity(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex,
                                   SCSI_Capacity_t* DeviceCapacity);

#endif
