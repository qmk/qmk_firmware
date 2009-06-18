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

/** \file
 *
 *  Mass Storage Device commands, to issue MSD commands to the device for
 *  reading device status, capacity, and other characteristics. This file
 *  also contains block read and write functions, so that device blocks
 *  can be read and written. In general, these functions would be chained
 *  to a FAT library to give file-level access to an attached device's contents.
 *
 *  \note Many Mass Storage devices on the market are non-compliant to the
 *        specifications and thus can prove difficult to interface with. It
 *        may be necessary to retry the functions in the module several times
 *        after they have returned and error to successfully send the command
 *        to the device. Some devices may also need to have the stream function
 *        timeout period extended beyond 100ms (some badly designed devices exceeding
 *        1.5 seconds occasionally) by defining USB_STREAM_TIMEOUT_MS to a
 *        larger value in the project makefile and passing it to the compiler
 *        via the -D switch.
 */
 
#define  INCLUDE_FROM_MASSSTORE_COMMANDS_C
#include "MassStoreCommands.h"

/* Globals: */
/** Current CBW to send to the device. This is automatically filled by the routines
 *  in this file and is not externally accessible.
 */
static CommandBlockWrapper_t  SCSICommandBlock;

/** Current CSW received from the device. This is automatically filled by the routines
 *  in this file and is externally accessible so that the return codes may be checked.
 */
CommandStatusWrapper_t        SCSICommandStatus;

/** Current Tag value used in issued CBWs to the device. This is automatically incremented
 *  by the routines in this file, and is not externally accessible.
 */
static uint32_t               MassStore_Tag = 1;


/** Routine to send the current CBW to the device, and increment the Tag value as needed.
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
static uint8_t MassStore_SendCommand(void)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;

	/* Each transmission should have a unique tag value, excluding values 0 and 0xFFFFFFFF */
	if (++MassStore_Tag == 0xFFFFFFFF)
	  MassStore_Tag = 1;

	/* Select the OUT data pipe for CBW transmission */
	Pipe_SelectPipe(MASS_STORE_DATA_OUT_PIPE);
	Pipe_Unfreeze();

	/* Write the CBW command to the OUT pipe */
	if ((ErrorCode = Pipe_Write_Stream_LE(&SCSICommandBlock, sizeof(CommandBlockWrapper_t))) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	/* Send the data in the OUT pipe to the attached device */
	Pipe_ClearOUT();
	
	while(!(Pipe_IsOUTReady()));

	/* Freeze pipe after use */
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

/** Waits until the attached device is ready to accept data following a CBW, checking
 *  to ensure that the device has not stalled the transaction.
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
static uint8_t MassStore_WaitForDataReceived(void)
{
	uint16_t TimeoutMSRem = COMMAND_DATA_TIMEOUT_MS;

	/* Select the IN data pipe for data reception */
	Pipe_SelectPipe(MASS_STORE_DATA_IN_PIPE);
	Pipe_Unfreeze();

	/* Wait until data received in the IN pipe */
	while (!(Pipe_IsINReceived()))
	{
		/* Check to see if a new frame has been issued (1ms elapsed) */
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			/* Clear the flag and decrement the timeout period counter */
			USB_INT_Clear(USB_INT_HSOFI);
			TimeoutMSRem--;

			/* Check to see if the timeout period for the command has elapsed */
			if (!(TimeoutMSRem))
			  return PIPE_RWSTREAM_Timeout;
		}
	
		Pipe_Freeze();
		Pipe_SelectPipe(MASS_STORE_DATA_OUT_PIPE);
		Pipe_Unfreeze();

		/* Check if pipe stalled (command failed by device) */
		if (Pipe_IsStalled())
		{
			/* Clear the stall condition on the OUT pipe */
			USB_Host_ClearPipeStall(MASS_STORE_DATA_OUT_PIPE);

			return PIPE_RWSTREAM_PipeStalled;
		}
		
		Pipe_Freeze();
		Pipe_SelectPipe(MASS_STORE_DATA_IN_PIPE);
		Pipe_Unfreeze();

		/* Check if pipe stalled (command failed by device) */
		if (Pipe_IsStalled())
		{
			/* Clear the stall condition on the IN pipe */
			USB_Host_ClearPipeStall(MASS_STORE_DATA_IN_PIPE);

			return PIPE_RWSTREAM_PipeStalled;
		}
		  
		/* Check to see if the device was disconnected, if so exit function */
		if (!(USB_IsConnected))
		  return PIPE_RWSTREAM_DeviceDisconnected;
	};
	
	Pipe_SelectPipe(MASS_STORE_DATA_IN_PIPE);
	Pipe_Freeze();
		
	Pipe_SelectPipe(MASS_STORE_DATA_OUT_PIPE);
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

/** Sends or receives the transaction's data stage to or from the attached device, reading or
 *  writing to the nominated buffer.
 *
 *  \param  BufferPtr  Pointer to the data buffer to read from or write to
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
static uint8_t MassStore_SendReceiveData(void* BufferPtr)
{
	uint8_t  ErrorCode = PIPE_RWSTREAM_NoError;
	uint16_t BytesRem  = SCSICommandBlock.Header.DataTransferLength;

	/* Check the direction of the SCSI command data stage */
	if (SCSICommandBlock.Header.Flags & COMMAND_DIRECTION_DATA_IN)
	{
		/* Select the IN data pipe for data reception */
		Pipe_SelectPipe(MASS_STORE_DATA_IN_PIPE);
		Pipe_Unfreeze();
		
		/* Read in the block data from the pipe */
		if ((ErrorCode = Pipe_Read_Stream_LE(BufferPtr, BytesRem)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		/* Acknowledge the packet */
		Pipe_ClearIN();
	}
	else
	{
		/* Select the OUT data pipe for data transmission */
		Pipe_SelectPipe(MASS_STORE_DATA_OUT_PIPE);
		Pipe_Unfreeze();

		/* Write the block data to the pipe */
		if ((ErrorCode = Pipe_Write_Stream_LE(BufferPtr, BytesRem)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		/* Acknowledge the packet */
		Pipe_ClearOUT();
		
		while (!(Pipe_IsOUTReady()));
	}
	
	/* Freeze used pipe after use */
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

/** Routine to receive the current CSW from the device.
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
static uint8_t MassStore_GetReturnedStatus(void)
{
	uint8_t ErrorCode = PIPE_RWSTREAM_NoError;

	/* If an error in the command ocurred, abort */
	if ((ErrorCode = MassStore_WaitForDataReceived()) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	/* Select the IN data pipe for data reception */
	Pipe_SelectPipe(MASS_STORE_DATA_IN_PIPE);
	Pipe_Unfreeze();
	
	/* Load in the CSW from the attached device */
	if ((ErrorCode = Pipe_Read_Stream_LE(&SCSICommandStatus, sizeof(CommandStatusWrapper_t))) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;
	  
	/* Clear the data ready for next reception */
	Pipe_ClearIN();
	
	/* Freeze the IN pipe after use */
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

/** Clears the stall condition in the attached device on the nominated endpoint number.
 *
 *  \param EndpointNum  Endpoint number in the attached device whose stall condition is to be cleared
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t MassStore_ClearPipeStall(const uint8_t EndpointNum)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT),
			.bRequest      = REQ_ClearFeature,
			.wValue        = FEATURE_ENDPOINT_HALT,
			.wIndex        = EndpointNum,
			.wLength       = 0,
		};
	
	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

/** Issues a Mass Storage class specific request to reset the attached device's Mass Storage interface,
 *  readying the device for the next CBW.
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t MassStore_MassStorageReset(void)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_MassStorageReset,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = 0,
		};
	
	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

/** Issues a Mass Storage class specific request to determine the index of the highest numbered Logical
 *  Unit in the attached device.
 *
 *  \param MaxLUNIndex  Pointer to the location that the maximum LUN index value should be stored
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t MassStore_GetMaxLUN(uint8_t* const MaxLUNIndex)
{
	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_GetMaxLUN,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = 1,
		};
		
	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(MaxLUNIndex)) == HOST_SENDCONTROL_SetupStalled)
	{
		/* Clear the pipe stall */
		Pipe_ClearStall();
	
		/* Some faulty Mass Storage devices don't implement the GET_MAX_LUN request, so assume a single LUN */
		*MaxLUNIndex = 0;	
	}
	
	return ErrorCode;
}

/** Issues a SCSI Request Sense command to the attached device, to determine the current SCSI sense information. This
 *  gives error codes for the last issued SCSI command to the device.
 *
 *  \param LUNIndex  Index of the LUN inside the device the command is being addressed to
 *  \param SensePtr  Pointer to the sense data structure where the sense data from the device is to be stored
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t MassStore_RequestSense(const uint8_t LUNIndex, const SCSI_Request_Sense_Response_t* const SensePtr)
{
	uint8_t ReturnCode = PIPE_RWSTREAM_NoError;

	/* Create a CBW with a SCSI command to issue REQUEST SENSE command */
	SCSICommandBlock = (CommandBlockWrapper_t)
		{
			.Header =
				{
					.Signature          = CBW_SIGNATURE,
					.Tag                = MassStore_Tag,
					.DataTransferLength = sizeof(SCSI_Request_Sense_Response_t),
					.Flags              = COMMAND_DIRECTION_DATA_IN,
					.LUN                = LUNIndex,
					.SCSICommandLength  = 6
				},
					
			.SCSICommandData =
				{
					SCSI_CMD_REQUEST_SENSE,
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00,                   // Reserved
					sizeof(SCSI_Request_Sense_Response_t), // Allocation Length
					0x00                    // Unused (control)
				}
		};
	
	/* Send SCSI command to the attached device */
	MassStore_SendCommand();

	/* Wait until data received from the device */
	if ((ReturnCode = MassStore_WaitForDataReceived()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}

	/* Read the returned sense data into the buffer */
	if ((ReturnCode = MassStore_SendReceiveData((uint8_t*)SensePtr)) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}	
	
	/* Read in the returned CSW from the device */
	if ((ReturnCode = MassStore_GetReturnedStatus()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	
	return PIPE_RWSTREAM_NoError;
}

/** Issues a SCSI Device Block Read command to the attached device, to read in one or more data blocks from the
 *  storage medium into a buffer.
 *
 *  \param LUNIndex      Index of the LUN inside the device the command is being addressed to
 *  \param BlockAddress  Start block address to read from
 *  \param Blocks        Number of blocks to read from the device
 *  \param BlockSize     Size in bytes of each block to read
 *  \param BufferPtr     Pointer to the buffer where the read data is to be written to
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t MassStore_ReadDeviceBlock(const uint8_t LUNIndex, const uint32_t BlockAddress,
                                  const uint8_t Blocks, const uint16_t BlockSize, void* BufferPtr)
{
	uint8_t ReturnCode = PIPE_RWSTREAM_NoError;

	/* Create a CBW with a SCSI command to read in the given blocks from the device */
	SCSICommandBlock = (CommandBlockWrapper_t)
		{
			.Header =
				{
					.Signature          = CBW_SIGNATURE,
					.Tag                = MassStore_Tag,
					.DataTransferLength = ((uint32_t)Blocks * BlockSize),
					.Flags              = COMMAND_DIRECTION_DATA_IN,
					.LUN                = LUNIndex,
					.SCSICommandLength  = 10
				},
					
			.SCSICommandData =
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
	
	/* Send SCSI command to the attached device */
	MassStore_SendCommand();

	/* Wait until data received from the device */
	if ((ReturnCode = MassStore_WaitForDataReceived()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}

	/* Read the returned block data into the buffer */
	if ((ReturnCode = MassStore_SendReceiveData(BufferPtr)) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}	
	
	/* Read in the returned CSW from the device */
	if ((ReturnCode = MassStore_GetReturnedStatus()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	
	return PIPE_RWSTREAM_NoError;
}

/** Issues a SCSI Device Block Write command to the attached device, to write one or more data blocks to the
 *  storage medium from a buffer.
 *
 *  \param LUNIndex      Index of the LUN inside the device the command is being addressed to
 *  \param BlockAddress  Start block address to write to
 *  \param Blocks        Number of blocks to write to in the device
 *  \param BlockSize     Size in bytes of each block to write
 *  \param BufferPtr     Pointer to the buffer where the write data is to be sourced from
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t MassStore_WriteDeviceBlock(const uint8_t LUNIndex, const uint32_t BlockAddress,
                                   const uint8_t Blocks, const uint16_t BlockSize, void* BufferPtr)
{
	uint8_t ReturnCode = PIPE_RWSTREAM_NoError;

	/* Create a CBW with a SCSI command to write the given blocks to the device */
	SCSICommandBlock = (CommandBlockWrapper_t)
		{
			.Header =
				{
					.Signature          = CBW_SIGNATURE,
					.Tag                = MassStore_Tag,
					.DataTransferLength = ((uint32_t)Blocks * BlockSize),
					.Flags              = COMMAND_DIRECTION_DATA_OUT,
					.LUN                = LUNIndex,
					.SCSICommandLength  = 10
				},
					
			.SCSICommandData =
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
	
	/* Send SCSI command to the attached device */
	MassStore_SendCommand();

	/* Write the data to the device from the buffer */
	if ((ReturnCode = MassStore_SendReceiveData(BufferPtr)) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}	
	
	/* Read in the returned CSW from the device */
	if ((ReturnCode = MassStore_GetReturnedStatus()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	
	return PIPE_RWSTREAM_NoError;
}

/** Issues a SCSI Device Test Unit Ready command to the attached device, to determine if the device is ready to accept
 *  other commands.
 *
 *  \param LUNIndex      Index of the LUN inside the device the command is being addressed to
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t MassStore_TestUnitReady(const uint8_t LUNIndex)
{
	uint8_t ReturnCode = PIPE_RWSTREAM_NoError;	

	/* Create a CBW with a SCSI command to issue TEST UNIT READY command */
	SCSICommandBlock = (CommandBlockWrapper_t)
		{
			.Header =
				{
					.Signature          = CBW_SIGNATURE,
					.Tag                = MassStore_Tag,
					.DataTransferLength = 0,
					.Flags              = COMMAND_DIRECTION_DATA_IN,
					.LUN                = LUNIndex,
					.SCSICommandLength  = 6
				},
					
			.SCSICommandData =
				{
					SCSI_CMD_TEST_UNIT_READY,
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00,                   // Reserved
					0x00                    // Unused (control)
				}
		};
	
	/* Send SCSI command to the attached device */
	MassStore_SendCommand();

	/* Read in the returned CSW from the device */
	if ((ReturnCode = MassStore_GetReturnedStatus()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	
	return PIPE_RWSTREAM_NoError;
}

/** Issues a SCSI Device Read Capacity command to the attached device, to determine the capacity of the
 *  given Logical Unit within the device.
 *
 *  \param LUNIndex     Index of the LUN inside the device the command is being addressed to
 *  \param CapacityPtr  Device capacity structure where the capacity data is to be stored
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t MassStore_ReadCapacity(const uint8_t LUNIndex, SCSI_Capacity_t* const CapacityPtr)
{
	uint8_t ReturnCode = PIPE_RWSTREAM_NoError;

	/* Create a CBW with a SCSI command to issue READ CAPACITY command */
	SCSICommandBlock = (CommandBlockWrapper_t)
		{
			.Header =
				{
					.Signature          = CBW_SIGNATURE,
					.Tag                = MassStore_Tag,
					.DataTransferLength = sizeof(SCSI_Capacity_t),
					.Flags              = COMMAND_DIRECTION_DATA_IN,
					.LUN                = LUNIndex,
					.SCSICommandLength  = 10
				},
					
			.SCSICommandData =
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
	
	/* Send SCSI command to the attached device */
	MassStore_SendCommand();

	/* Wait until data received from the device */
	if ((ReturnCode = MassStore_WaitForDataReceived()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}

	/* Read the returned capacity data into the buffer */
	if ((ReturnCode = MassStore_SendReceiveData(CapacityPtr)) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	  
	/* Endian-correct the read data */
	CapacityPtr->Blocks    = SwapEndian_32(CapacityPtr->Blocks);
	CapacityPtr->BlockSize = SwapEndian_32(CapacityPtr->BlockSize);
	
	/* Read in the returned CSW from the device */
	if ((ReturnCode = MassStore_GetReturnedStatus()) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	
	return PIPE_RWSTREAM_NoError;
}

/** Issues a SCSI Device Prevent/Allow Medium Removal command to the attached device, to lock the physical media from
 *  being removed. This is a legacy command for SCSI disks with removable storage (such as ZIP disks), but should still
 *  be issued before the first read or write command is sent.
 *
 *  \param LUNIndex        Index of the LUN inside the device the command is being addressed to
 *  \param PreventRemoval  Whether or not the LUN media should be locked to prevent removal or not
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t MassStore_PreventAllowMediumRemoval(const uint8_t LUNIndex, const bool PreventRemoval)
{
	uint8_t ReturnCode = PIPE_RWSTREAM_NoError;

	/* Create a CBW with a SCSI command to issue PREVENT ALLOW MEDIUM REMOVAL command */
	SCSICommandBlock = (CommandBlockWrapper_t)
		{
			.Header =
				{
					.Signature          = CBW_SIGNATURE,
					.Tag                = MassStore_Tag,
					.DataTransferLength = 0,
					.Flags              = COMMAND_DIRECTION_DATA_OUT,
					.LUN                = LUNIndex,
					.SCSICommandLength  = 6
				},
					
			.SCSICommandData =
				{
					SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL,
					0x00,                   // Reserved
					0x00,                   // Reserved
					PreventRemoval,         // Prevent flag
					0x00,                   // Reserved
					0x00                    // Unused (control)
				}
		};
	
	/* Send SCSI command to the attached device */
	MassStore_SendCommand();

	/* Read in the returned CSW from the device */
	if ((ReturnCode = MassStore_GetReturnedStatus()))
	{
		Pipe_Freeze();
		return ReturnCode;
	}
	
	return PIPE_RWSTREAM_NoError;
}
