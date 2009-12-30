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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define INCLUDE_FROM_MS_CLASS_HOST_C
#include "MassStorage.h"

uint8_t MS_Host_ConfigurePipes(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, uint16_t ConfigDescriptorSize,
							   void* DeviceConfigDescriptor)
{
	uint8_t FoundEndpoints = 0;
	
	memset(&MSInterfaceInfo->State, 0x00, sizeof(MSInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(DeviceConfigDescriptor) != DTYPE_Configuration)
	  return MS_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &DeviceConfigDescriptor,
	                              DComp_NextMSInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return MS_ENUMERROR_NoMSInterfaceFound;
	}

	MSInterfaceInfo->State.InterfaceNumber = DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Interface_t)->InterfaceNumber;
	
	while (FoundEndpoints != (MS_FOUND_DATAPIPE_IN | MS_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &DeviceConfigDescriptor,
		                              DComp_NextMSInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return MS_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(DeviceConfigDescriptor, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			Pipe_ConfigurePipe(MSInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
			                   EndpointData->EndpointAddress, EndpointData->EndpointSize,
			                   MSInterfaceInfo->Config.DataINPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			MSInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= MS_FOUND_DATAPIPE_IN;
		}
		else
		{
			Pipe_ConfigurePipe(MSInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
			                   EndpointData->EndpointAddress, EndpointData->EndpointSize,
			                   MSInterfaceInfo->Config.DataOUTPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			MSInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= MS_FOUND_DATAPIPE_OUT;
		}		
	}

	MSInterfaceInfo->State.IsActive = true;
	return MS_ENUMERROR_NoError;
}

static uint8_t DComp_NextMSInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);

		if ((CurrentInterface->Class    == MASS_STORE_CLASS)    &&
		    (CurrentInterface->SubClass == MASS_STORE_SUBCLASS) &&
		    (CurrentInterface->Protocol == MASS_STORE_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_NextMSInterfaceEndpoint(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);

		uint8_t EndpointType = (CurrentEndpoint->Attributes & EP_TYPE_MASK);

		if ((EndpointType == EP_TYPE_BULK) &&
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

void MS_Host_USBTask(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo)
{
	(void)MSInterfaceInfo;
}

static uint8_t MS_Host_SendCommand(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, MS_CommandBlockWrapper_t* const SCSICommandBlock,
                                   void* BufferPtr)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;

	SCSICommandBlock->Tag = ++MSInterfaceInfo->State.TransactionTag;

	if (MSInterfaceInfo->State.TransactionTag == 0xFFFFFFFF)
	  MSInterfaceInfo->State.TransactionTag = 1;

	Pipe_SelectPipe(MSInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(SCSICommandBlock, sizeof(MS_CommandBlockWrapper_t),
	                                      NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearOUT();
	Pipe_WaitUntilReady();

	Pipe_Freeze();

	if ((BufferPtr != NULL) &&
	    ((ErrorCode = MS_Host_SendReceiveData(MSInterfaceInfo, SCSICommandBlock, BufferPtr)) != PIPE_RWSTREAM_NoError))
	{
		Pipe_Freeze();
		return ErrorCode;
	}
	
	return ErrorCode;
}

static uint8_t MS_Host_WaitForDataReceived(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo)
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

static uint8_t MS_Host_SendReceiveData(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                       MS_CommandBlockWrapper_t* const SCSICommandBlock, void* BufferPtr)
{
	uint8_t  ErrorCode = PIPE_RWSTREAM_NoError;
	uint16_t BytesRem  = SCSICommandBlock->DataTransferLength;

	if (SCSICommandBlock->Flags & COMMAND_DIRECTION_DATA_IN)
	{
		if ((ErrorCode = MS_Host_WaitForDataReceived(MSInterfaceInfo)) != PIPE_RWSTREAM_NoError)
		{
			Pipe_Freeze();
			return ErrorCode;
		}

		Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
		Pipe_Unfreeze();
		
		if ((ErrorCode = Pipe_Read_Stream_LE(BufferPtr, BytesRem, NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		Pipe_ClearIN();
	}
	else
	{
		Pipe_SelectPipe(MSInterfaceInfo->Config.DataOUTPipeNumber);
		Pipe_Unfreeze();

		if ((ErrorCode = Pipe_Write_Stream_LE(BufferPtr, BytesRem, NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		Pipe_ClearOUT();
		
		while (!(Pipe_IsOUTReady()))
		{
			if (USB_HostState == HOST_STATE_Unattached)
			  return PIPE_RWSTREAM_DeviceDisconnected;
		}
	}

	Pipe_Freeze();

	return ErrorCode;
}

static uint8_t MS_Host_GetReturnedStatus(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo,
                                         MS_CommandStatusWrapper_t* const SCSICommandStatus)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;

	if ((ErrorCode = MS_Host_WaitForDataReceived(MSInterfaceInfo)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_SelectPipe(MSInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();
	
	if ((ErrorCode = Pipe_Read_Stream_LE(SCSICommandStatus, sizeof(MS_CommandStatusWrapper_t),
	                                     NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	{
		return ErrorCode;
	}
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	if (SCSICommandStatus->Status != SCSI_Command_Pass)
	  ErrorCode = MS_ERROR_LOGICAL_CMD_FAILED;
	
	return ErrorCode;
}

uint8_t MS_Host_ResetMSInterface(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo)
{
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

uint8_t MS_Host_GetMaxLUN(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, uint8_t* const MaxLUNIndex)
{
	uint8_t ErrorCode = HOST_SENDCONTROL_Successful;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_GetMaxLUN,
			.wValue        = 0,
			.wIndex        = MSInterfaceInfo->State.InterfaceNumber,
			.wLength       = 1,
		};
		
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(MaxLUNIndex)) != HOST_SENDCONTROL_Successful)
	{
		*MaxLUNIndex = 0;
		ErrorCode = HOST_SENDCONTROL_Successful;
	}
	
	return ErrorCode;
}

uint8_t MS_Host_GetInquiryData(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex,
                               SCSI_Inquiry_Response_t* const InquiryData)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;
	  
	uint8_t ErrorCode;

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = sizeof(SCSI_Inquiry_Response_t),
			.Flags              = COMMAND_DIRECTION_DATA_IN,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 6,
			.SCSICommandData    =
				{
					SCSI_CMD_INQUIRY,
					0x00,                            // Reserved
					0x00,                            // Reserved
					0x00,                            // Reserved
					sizeof(SCSI_Inquiry_Response_t), // Allocation Length
					0x00                             // Unused (control)
				}
		};
	
	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, InquiryData)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;	
	
	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_TestUnitReady(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;	

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = 0,
			.Flags              = COMMAND_DIRECTION_DATA_IN,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 6,
			.SCSICommandData    =
				{
					SCSI_CMD_TEST_UNIT_READY,
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00                    // Unused (control)
				}
		};
	
	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, NULL)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;	
	
	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_ReadDeviceCapacity(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex,
                                   SCSI_Capacity_t* const DeviceCapacity)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = sizeof(SCSI_Capacity_t),
			.Flags              = COMMAND_DIRECTION_DATA_IN,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 10,
			.SCSICommandData    =
				{
					SCSI_CMD_READ_CAPACITY_10,
					0x00,                   // Reserved
					0x00,                   // MSB of Logical block address
					0x00,
					0x00,
					0x00,                   // LSB of Logical block address
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00,                   // Partial Medium Indicator
					0x00                    // Unused (control)
				}
		};
	
	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, DeviceCapacity)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	DeviceCapacity->Blocks    = SwapEndian_32(DeviceCapacity->Blocks);
	DeviceCapacity->BlockSize = SwapEndian_32(DeviceCapacity->BlockSize);
	
	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_RequestSense(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex,
                             SCSI_Request_Sense_Response_t* const SenseData)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = sizeof(SCSI_Request_Sense_Response_t),
			.Flags              = COMMAND_DIRECTION_DATA_IN,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 6,
			.SCSICommandData    =
				{
					SCSI_CMD_REQUEST_SENSE,
					0x00,                                  // Reserved
					0x00,                                  // Reserved
					0x00,                                  // Reserved
					sizeof(SCSI_Request_Sense_Response_t), // Allocation Length
					0x00                                   // Unused (control)
				}
		};
	
	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, SenseData)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_PreventAllowMediumRemoval(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex,
                                          const bool PreventRemoval)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = 0,
			.Flags              = COMMAND_DIRECTION_DATA_OUT,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 6,
			.SCSICommandData    =
				{
					SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL,
					0x00,                   // Reserved
					0x00,                   // Reserved
					PreventRemoval,         // Prevent flag
					0x00,                   // Reserved
					0x00                    // Unused (control)
				}
		};
	
	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, NULL)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	
	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_ReadDeviceBlocks(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex, const uint32_t BlockAddress,
                                 const uint8_t Blocks, const uint16_t BlockSize, void* BlockBuffer)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = ((uint32_t)Blocks * BlockSize),
			.Flags              = COMMAND_DIRECTION_DATA_IN,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 10,
			.SCSICommandData    =
				{
					SCSI_CMD_READ_10,
					0x00,                   // Unused (control bits, all off)
					(BlockAddress >> 24),   // MSB of Block Address
					(BlockAddress >> 16),
					(BlockAddress >> 8),
					(BlockAddress & 0xFF),  // LSB of Block Address
					0x00,                   // Unused (reserved)
					0x00,                   // MSB of Total Blocks to Read
					Blocks,                 // LSB of Total Blocks to Read
					0x00                    // Unused (control)
				}
		};

	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, BlockBuffer)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

uint8_t MS_Host_WriteDeviceBlocks(USB_ClassInfo_MS_Host_t* const MSInterfaceInfo, const uint8_t LUNIndex, const uint32_t BlockAddress,
                                  const uint8_t Blocks, const uint16_t BlockSize, void* BlockBuffer)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MSInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	MS_CommandBlockWrapper_t SCSICommandBlock = (MS_CommandBlockWrapper_t)
		{
			.Signature          = CBW_SIGNATURE,
			.DataTransferLength = ((uint32_t)Blocks * BlockSize),
			.Flags              = COMMAND_DIRECTION_DATA_OUT,
			.LUN                = LUNIndex,
			.SCSICommandLength  = 10,
			.SCSICommandData    =
				{
					SCSI_CMD_WRITE_10,
					0x00,                   // Unused (control bits, all off)
					(BlockAddress >> 24),   // MSB of Block Address
					(BlockAddress >> 16),
					(BlockAddress >> 8),
					(BlockAddress & 0xFF),  // LSB of Block Address
					0x00,                   // Unused (reserved)
					0x00,                   // MSB of Total Blocks to Write
					Blocks,                 // LSB of Total Blocks to Write
					0x00                    // Unused (control)
				}
		};

	MS_CommandStatusWrapper_t SCSICommandStatus;

	if ((ErrorCode = MS_Host_SendCommand(MSInterfaceInfo, &SCSICommandBlock, BlockBuffer)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	
	if ((ErrorCode = MS_Host_GetReturnedStatus(MSInterfaceInfo, &SCSICommandStatus)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	return PIPE_RWSTREAM_NoError;
}

#endif
