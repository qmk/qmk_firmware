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
 *  SCSI command processing routines, for SCSI commands issued by the host. Mass Storage
 *  devices use a thin "Bulk-Only Transport" protocol for issuing commands and status information,
 *  which wrap around standard SCSI device commands for controlling the actual storage medium.
 */
 
#define  INCLUDE_FROM_SCSI_C
#include "SCSI.h"

/** Structure to hold the SCSI response data to a SCSI INQUIRY command. This gives information about the device's
 *  features and capabilities.
 */
SCSI_Inquiry_Response_t InquiryData = 
	{
		.DeviceType          = DEVICE_TYPE_BLOCK,
		.PeripheralQualifier = 0,
			
		.Removable           = true,
			
		.Version             = 0,
			
		.ResponseDataFormat  = 2,
		.NormACA             = false,
		.TrmTsk              = false,
		.AERC                = false,

		.AdditionalLength    = 0x1F,
			
		.SoftReset           = false,
		.CmdQue              = false,
		.Linked              = false,
		.Sync                = false,
		.WideBus16Bit        = false,
		.WideBus32Bit        = false,
		.RelAddr             = false,
		
		.VendorID            = "LUFA",
		.ProductID           = "Dataflash Disk",
		.RevisionID          = {'0','.','0','0'},
	};

/** Structure to hold the sense data for the last issued SCSI command, which is returned to the host after a SCSI REQUEST SENSE
 *  command is issued. This gives information on exactly why the last command failed to complete.
 */
SCSI_Request_Sense_Response_t SenseData =
	{
		.ResponseCode        = 0x70,
		.AdditionalLength    = 0x0A,
	};


/** Main routine to process the SCSI command located in the Command Block Wrapper read from the host. This dispatches
 *  to the appropriate SCSI command handling routine if the issued command is supported by the device, else it returns
 *  a command failure due to a ILLEGAL REQUEST.
 */
void SCSI_DecodeSCSICommand(void)
{
	bool CommandSuccess = false;

	/* Run the appropriate SCSI command hander function based on the passed command */
	switch (CommandBlock.SCSICommandData[0])
	{
		case SCSI_CMD_INQUIRY:
			CommandSuccess = SCSI_Command_Inquiry();			
			break;
		case SCSI_CMD_REQUEST_SENSE:
			CommandSuccess = SCSI_Command_Request_Sense();
			break;
		case SCSI_CMD_READ_CAPACITY_10:
			CommandSuccess = SCSI_Command_Read_Capacity_10();			
			break;
		case SCSI_CMD_SEND_DIAGNOSTIC:
			CommandSuccess = SCSI_Command_Send_Diagnostic();
			break;
		case SCSI_CMD_WRITE_10:
			CommandSuccess = SCSI_Command_ReadWrite_10(DATA_WRITE);
			break;
		case SCSI_CMD_READ_10:
			CommandSuccess = SCSI_Command_ReadWrite_10(DATA_READ);
			break;
		case SCSI_CMD_TEST_UNIT_READY:
		case SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL:
		case SCSI_CMD_VERIFY_10:
			/* These commands should just succeed, no handling required */
			CommandSuccess = true;
			CommandBlock.DataTransferLength = 0;
			break;
		default:
			/* Update the SENSE key to reflect the invalid command */
			SCSI_SET_SENSE(SCSI_SENSE_KEY_ILLEGAL_REQUEST,
		                   SCSI_ASENSE_INVALID_COMMAND,
		                   SCSI_ASENSEQ_NO_QUALIFIER);
			break;
	}
	
	/* Check if command was successfully processed */
	if (CommandSuccess)
	{
		/* Command succeeded - set the CSW status and update the SENSE key */
		CommandStatus.Status = Command_Pass;
		
		SCSI_SET_SENSE(SCSI_SENSE_KEY_GOOD,
		               SCSI_ASENSE_NO_ADDITIONAL_INFORMATION,
		               SCSI_ASENSEQ_NO_QUALIFIER);					   
	}
	else
	{
		/* Command failed - set the CSW status - failed command function updates the SENSE key */
		CommandStatus.Status = Command_Fail;
	}
}

/** Command processing for an issued SCSI INQUIRY command. This command returns information about the device's features
 *  and capabilities to the host.
 *
 *  \return Boolean true if the command completed successfully, false otherwise.
 */
static bool SCSI_Command_Inquiry(void)
{
	uint16_t AllocationLength  = (((uint16_t)CommandBlock.SCSICommandData[3] << 8) |
	                                         CommandBlock.SCSICommandData[4]);
	uint16_t BytesTransferred  = (AllocationLength < sizeof(InquiryData))? AllocationLength :
	                                                                       sizeof(InquiryData);

	/* Only the standard INQUIRY data is supported, check if any optional INQUIRY bits set */
	if ((CommandBlock.SCSICommandData[1] & ((1 << 0) | (1 << 1))) ||
	     CommandBlock.SCSICommandData[2])
	{
		/* Optional but unsupported bits set - update the SENSE key and fail the request */
		SCSI_SET_SENSE(SCSI_SENSE_KEY_ILLEGAL_REQUEST,
		               SCSI_ASENSE_INVALID_FIELD_IN_CDB,
		               SCSI_ASENSEQ_NO_QUALIFIER);

		return false;
	}

	/* Write the INQUIRY data to the endpoint */
	Endpoint_Write_Stream_LE(&InquiryData, BytesTransferred, StreamCallback_AbortOnMassStoreReset);

	uint8_t PadBytes[AllocationLength - BytesTransferred];
	
	/* Pad out remaining bytes with 0x00 */
	Endpoint_Write_Stream_LE(&PadBytes, (AllocationLength - BytesTransferred), StreamCallback_AbortOnMassStoreReset);

	/* Finalize the stream transfer to send the last packet */
	Endpoint_ClearIN();

	/* Succeed the command and update the bytes transferred counter */
	CommandBlock.DataTransferLength -= BytesTransferred;
	
	return true;
}

/** Command processing for an issued SCSI REQUEST SENSE command. This command returns information about the last issued command,
 *  including the error code and additional error information so that the host can determine why a command failed to complete.
 *
 *  \return Boolean true if the command completed successfully, false otherwise.
 */
static bool SCSI_Command_Request_Sense(void)
{
	uint8_t  AllocationLength = CommandBlock.SCSICommandData[4];
	uint8_t  BytesTransferred = (AllocationLength < sizeof(SenseData))? AllocationLength : sizeof(SenseData);
	
	/* Send the SENSE data - this indicates to the host the status of the last command */
	Endpoint_Write_Stream_LE(&SenseData, BytesTransferred, StreamCallback_AbortOnMassStoreReset);
	
	uint8_t PadBytes[AllocationLength - BytesTransferred];
	
	/* Pad out remaining bytes with 0x00 */
	Endpoint_Write_Stream_LE(&PadBytes, (AllocationLength - BytesTransferred), StreamCallback_AbortOnMassStoreReset);

	/* Finalize the stream transfer to send the last packet */
	Endpoint_ClearIN();

	/* Succeed the command and update the bytes transferred counter */
	CommandBlock.DataTransferLength -= BytesTransferred;

	return true;
}

/** Command processing for an issued SCSI READ CAPACITY (10) command. This command returns information about the device's capacity
 *  on the selected Logical Unit (drive), as a number of OS-sized blocks.
 *
 *  \return Boolean true if the command completed successfully, false otherwise.
 */
static bool SCSI_Command_Read_Capacity_10(void)
{
	/* Send the total number of logical blocks in the current LUN */
	Endpoint_Write_DWord_BE(LUN_MEDIA_BLOCKS - 1);

	/* Send the logical block size of the device (must be 512 bytes) */
	Endpoint_Write_DWord_BE(VIRTUAL_MEMORY_BLOCK_SIZE);

	/* Check if the current command is being aborted by the host */
	if (IsMassStoreReset)
	  return false;

	/* Send the endpoint data packet to the host */
	Endpoint_ClearIN();

	/* Succeed the command and update the bytes transferred counter */
	CommandBlock.DataTransferLength -= 8;
	
	return true;
}

/** Command processing for an issued SCSI SEND DIAGNOSTIC command. This command performs a quick check of the Dataflash ICs on the
 *  board, and indicates if they are present and functioning correctly. Only the Self-Test portion of the diagnostic command is
 *  supported.
 *
 *  \param[in] MSInterfaceInfo  Pointer to the Mass Storage class interface structure that the command is associated with
 *
 *  \return Boolean true if the command completed successfully, false otherwise.
 */
static bool SCSI_Command_Send_Diagnostic(void)
{
	/* Check to see if the SELF TEST bit is not set */
	if (!(CommandBlock.SCSICommandData[1] & (1 << 2)))
	{
		/* Only self-test supported - update SENSE key and fail the command */
		SCSI_SET_SENSE(SCSI_SENSE_KEY_ILLEGAL_REQUEST,
		               SCSI_ASENSE_INVALID_FIELD_IN_CDB,
		               SCSI_ASENSEQ_NO_QUALIFIER);

		return false;
	}
	
	/* Check to see if all attached Dataflash ICs are functional */
	if (!(DataflashManager_CheckDataflashOperation()))
	{
		/* Update SENSE key with a hardware error condition and return command fail */
		SCSI_SET_SENSE(SCSI_SENSE_KEY_HARDWARE_ERROR,
		               SCSI_ASENSE_NO_ADDITIONAL_INFORMATION,
		               SCSI_ASENSEQ_NO_QUALIFIER);	
	
		return false;
	}
	
	/* Succeed the command and update the bytes transferred counter */
	CommandBlock.DataTransferLength = 0;
	
	return true;
}

/** Command processing for an issued SCSI READ (10) or WRITE (10) command. This command reads in the block start address
 *  and total number of blocks to process, then calls the appropriate low-level dataflash routine to handle the actual
 *  reading and writing of the data.
 *
 *  \param[in] IsDataRead  Indicates if the command is a READ (10) command or WRITE (10) command (DATA_READ or DATA_WRITE)
 *
 *  \return Boolean true if the command completed successfully, false otherwise.
 */
static bool SCSI_Command_ReadWrite_10(const bool IsDataRead)
{
	uint32_t BlockAddress;
	uint16_t TotalBlocks;
	
	/* Load in the 32-bit block address (SCSI uses big-endian, so have to do it byte-by-byte) */
	((uint8_t*)&BlockAddress)[3] = CommandBlock.SCSICommandData[2];
	((uint8_t*)&BlockAddress)[2] = CommandBlock.SCSICommandData[3];
	((uint8_t*)&BlockAddress)[1] = CommandBlock.SCSICommandData[4];
	((uint8_t*)&BlockAddress)[0] = CommandBlock.SCSICommandData[5];

	/* Load in the 16-bit total blocks (SCSI uses big-endian, so have to do it byte-by-byte) */
	((uint8_t*)&TotalBlocks)[1]  = CommandBlock.SCSICommandData[7];
	((uint8_t*)&TotalBlocks)[0]  = CommandBlock.SCSICommandData[8];
	
	/* Check if the block address is outside the maximum allowable value for the LUN */
	if (BlockAddress >= LUN_MEDIA_BLOCKS)
	{
		/* Block address is invalid, update SENSE key and return command fail */
		SCSI_SET_SENSE(SCSI_SENSE_KEY_ILLEGAL_REQUEST,
		               SCSI_ASENSE_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE,
		               SCSI_ASENSEQ_NO_QUALIFIER);

		return false;
	}

	#if (TOTAL_LUNS > 1)
	/* Adjust the given block address to the real media address based on the selected LUN */
	BlockAddress += ((uint32_t)CommandBlock.LUN * LUN_MEDIA_BLOCKS);
	#endif
	
	/* Determine if the packet is a READ (10) or WRITE (10) command, call appropriate function */
	if (IsDataRead == DATA_READ)
	  DataflashManager_ReadBlocks(BlockAddress, TotalBlocks);
	else
	  DataflashManager_WriteBlocks(BlockAddress, TotalBlocks);

	/* Update the bytes transferred counter and succeed the command */
	CommandBlock.DataTransferLength -= ((uint32_t)TotalBlocks * VIRTUAL_MEMORY_BLOCK_SIZE);
	
	return true;
}
