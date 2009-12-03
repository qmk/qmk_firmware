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
 *  ISP Protocol handler, to process V2 Protocol wrapped ISP commands used in Atmel programmer devices.
 */

#include "ISPProtocol.h"

/** Handler for the CMD_ENTER_PROGMODE_ISP command, which attempts to enter programming mode on
 *  the attached device, returning success or failure back to the host.
 */
void ISPProtocol_EnterISPMode(void)
{
	struct
	{
		uint8_t TimeoutMS;
		uint8_t PinStabDelayMS;
		uint8_t ExecutionDelayMS;
		uint8_t SynchLoops;
		uint8_t ByteDelay;
		uint8_t PollValue;
		uint8_t PollIndex;
		uint8_t EnterProgBytes[4];
	} Enter_ISP_Params;
	
	Endpoint_Read_Stream_LE(&Enter_ISP_Params, sizeof(Enter_ISP_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	uint8_t ResponseStatus = STATUS_CMD_FAILED;
	
	CurrentAddress = 0;

	V2Protocol_DelayMS(Enter_ISP_Params.ExecutionDelayMS); 
	SPI_Init(ISPTarget_GetSPIPrescalerMask() | SPI_SCK_LEAD_RISING | SPI_SAMPLE_LEADING | SPI_MODE_MASTER);
		
	while (Enter_ISP_Params.SynchLoops-- && (ResponseStatus == STATUS_CMD_FAILED))
	{
		uint8_t ResponseBytes[4];

		ISPTarget_ChangeTargetResetLine(true);
		V2Protocol_DelayMS(Enter_ISP_Params.PinStabDelayMS);

		for (uint8_t RByte = 0; RByte < sizeof(ResponseBytes); RByte++)
		{
			V2Protocol_DelayMS(Enter_ISP_Params.ByteDelay);
			ResponseBytes[RByte] = SPI_TransferByte(Enter_ISP_Params.EnterProgBytes[RByte]);
		}
		
		/* Check if polling disabled, or if the polled value matches the expected value */
		if (!(Enter_ISP_Params.PollIndex) || (ResponseBytes[Enter_ISP_Params.PollIndex - 1] == Enter_ISP_Params.PollValue))
		{
			ResponseStatus = STATUS_CMD_OK;
		}
		else
		{
			ISPTarget_ChangeTargetResetLine(false);
			V2Protocol_DelayMS(Enter_ISP_Params.PinStabDelayMS);
		}
	}

	Endpoint_Write_Byte(CMD_ENTER_PROGMODE_ISP);
	Endpoint_Write_Byte(ResponseStatus);
	Endpoint_ClearIN();
}

/** Handler for the CMD_LEAVE_ISP command, which releases the target from programming mode. */
void ISPProtocol_LeaveISPMode(void)
{
	struct
	{
		uint8_t PreDelayMS;
		uint8_t PostDelayMS;
	} Leave_ISP_Params;

	Endpoint_Read_Stream_LE(&Leave_ISP_Params, sizeof(Leave_ISP_Params));
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	V2Protocol_DelayMS(Leave_ISP_Params.PreDelayMS);
	ISPTarget_ChangeTargetResetLine(false);
	SPI_ShutDown();
	V2Protocol_DelayMS(Leave_ISP_Params.PostDelayMS);

	Endpoint_Write_Byte(CMD_LEAVE_PROGMODE_ISP);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

/** Handler for the CMD_PROGRAM_FLASH_ISP and CMD_PROGRAM_EEPROM_ISP commands, writing out bytes,
 *  words or pages of data to the attached device.
 *
 *  \param[in] V2Command  Issued V2 Protocol command byte from the host
 */
void ISPProtocol_ProgramMemory(uint8_t V2Command)
{
	struct
	{
		uint16_t BytesToWrite;
		uint8_t  ProgrammingMode;
		uint8_t  DelayMS;
		uint8_t  ProgrammingCommands[3];
		uint8_t  PollValue1;
		uint8_t  PollValue2;
		uint8_t  ProgData[256]; // Note, the Jungo driver has a very short ACK timeout period, need to buffer the
	} Write_Memory_Params;      // whole page and ACK the packet as fast as possible to prevent it from aborting
	
	Endpoint_Read_Stream_LE(&Write_Memory_Params, (sizeof(Write_Memory_Params) -
	                                               sizeof(Write_Memory_Params.ProgData)));


	Write_Memory_Params.BytesToWrite = SwapEndian_16(Write_Memory_Params.BytesToWrite);
	
	if (Write_Memory_Params.BytesToWrite > sizeof(Write_Memory_Params.ProgData))
	{
		Endpoint_ClearOUT();
		Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

		Endpoint_Write_Byte(V2Command);
		Endpoint_Write_Byte(STATUS_CMD_FAILED);
		Endpoint_ClearIN();
		return;
	}
	
	Endpoint_Read_Stream_LE(&Write_Memory_Params.ProgData, Write_Memory_Params.BytesToWrite);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	uint8_t  ProgrammingStatus = STATUS_CMD_OK;	
	uint16_t PollAddress       = 0;
	uint8_t  PollValue         = (V2Command == CMD_PROGRAM_FLASH_ISP) ? Write_Memory_Params.PollValue1 :
	                                                                    Write_Memory_Params.PollValue2;
	uint8_t* NextWriteByte = Write_Memory_Params.ProgData;

	if (MustSetAddress)
	{
		if (CurrentAddress & (1UL << 31))
		  ISPTarget_LoadExtendedAddress();

		MustSetAddress = false;
	}

	if (Write_Memory_Params.ProgrammingMode & PROG_MODE_PAGED_WRITES_MASK)
	{
		uint16_t StartAddress = (CurrentAddress & 0xFFFF);
	
		/* Paged mode memory programming */
		for (uint16_t CurrentByte = 0; CurrentByte < Write_Memory_Params.BytesToWrite; CurrentByte++)
		{
			bool    IsOddByte   = (CurrentByte & 0x01);
			uint8_t ByteToWrite = *(NextWriteByte++);
		
			if (IsOddByte && (V2Command == CMD_PROGRAM_FLASH_ISP))
			  Write_Memory_Params.ProgrammingCommands[0] |=  READ_WRITE_HIGH_BYTE_MASK;
			else
			  Write_Memory_Params.ProgrammingCommands[0] &= ~READ_WRITE_HIGH_BYTE_MASK;
			  
			SPI_SendByte(Write_Memory_Params.ProgrammingCommands[0]);
			SPI_SendByte(CurrentAddress >> 8);
			SPI_SendByte(CurrentAddress & 0xFF);
			SPI_SendByte(ByteToWrite);
			
			if (!(PollAddress) && (ByteToWrite != PollValue))
			{
				if (IsOddByte && (V2Command == CMD_PROGRAM_FLASH_ISP))
				  Write_Memory_Params.ProgrammingCommands[2] |= READ_WRITE_HIGH_BYTE_MASK;
				  
				PollAddress = (CurrentAddress & 0xFFFF);				
			}		

			if (IsOddByte || (V2Command == CMD_PROGRAM_EEPROM_ISP))
			  CurrentAddress++;
		}
		
		/* If the current page must be committed, send the PROGRAM PAGE command to the target */
		if (Write_Memory_Params.ProgrammingMode & PROG_MODE_COMMIT_PAGE_MASK)
		{
			SPI_SendByte(Write_Memory_Params.ProgrammingCommands[1]);
			SPI_SendByte(StartAddress >> 8);
			SPI_SendByte(StartAddress & 0xFF);
			SPI_SendByte(0x00);
			
			/* Check if polling is possible, if not switch to timed delay mode */
			if (!(PollAddress))
			{
				Write_Memory_Params.ProgrammingMode &= ~PROG_MODE_PAGED_VALUE_MASK;
				Write_Memory_Params.ProgrammingMode |=  PROG_MODE_PAGED_TIMEDELAY_MASK;				
			}

			ProgrammingStatus = ISPTarget_WaitForProgComplete(Write_Memory_Params.ProgrammingMode, PollAddress, PollValue,
			                                                  Write_Memory_Params.DelayMS, Write_Memory_Params.ProgrammingCommands[2]);
		}
	}
	else
	{
		/* Word/byte mode memory programming */
		for (uint16_t CurrentByte = 0; CurrentByte < Write_Memory_Params.BytesToWrite; CurrentByte++)
		{
			bool    IsOddByte   = (CurrentByte & 0x01);
			uint8_t ByteToWrite = *(NextWriteByte++);
		
			if (IsOddByte && (V2Command == CMD_READ_FLASH_ISP))
			  Write_Memory_Params.ProgrammingCommands[0] |=  READ_WRITE_HIGH_BYTE_MASK;
			else
			  Write_Memory_Params.ProgrammingCommands[0] &= ~READ_WRITE_HIGH_BYTE_MASK;			
			  
			SPI_SendByte(Write_Memory_Params.ProgrammingCommands[0]);
			SPI_SendByte(CurrentAddress >> 8);
			SPI_SendByte(CurrentAddress & 0xFF);
			SPI_SendByte(ByteToWrite);
			
			if (ByteToWrite != PollValue)
			{
				if (IsOddByte && (V2Command == CMD_PROGRAM_FLASH_ISP))
				  Write_Memory_Params.ProgrammingCommands[2] |= READ_WRITE_HIGH_BYTE_MASK;
				  
				PollAddress = (CurrentAddress & 0xFFFF);
			}

			if (IsOddByte || (V2Command == CMD_PROGRAM_EEPROM_ISP))
			  CurrentAddress++;
			
			ProgrammingStatus = ISPTarget_WaitForProgComplete(Write_Memory_Params.ProgrammingMode, PollAddress, PollValue,
			                                                  Write_Memory_Params.DelayMS, Write_Memory_Params.ProgrammingCommands[2]);
			  
			if (ProgrammingStatus != STATUS_CMD_OK)
			  break;
		}
	}

	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(ProgrammingStatus);
	Endpoint_ClearIN();
}

/** Handler for the CMD_READ_FLASH_ISP and CMD_READ_EEPROM_ISP commands, reading in bytes,
 *  words or pages of data from the attached device.
 *
 *  \param[in] V2Command  Issued V2 Protocol command byte from the host
 */
void ISPProtocol_ReadMemory(uint8_t V2Command)
{
	struct
	{
		uint16_t BytesToRead;
		uint8_t  ReadMemoryCommand;
	} Read_Memory_Params;
	
	Endpoint_Read_Stream_LE(&Read_Memory_Params, sizeof(Read_Memory_Params));
	Read_Memory_Params.BytesToRead = SwapEndian_16(Read_Memory_Params.BytesToRead);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	
	if (MustSetAddress)
	{
		if (CurrentAddress & (1UL << 31))
		  ISPTarget_LoadExtendedAddress();

		MustSetAddress = false;
	}

	for (uint16_t CurrentByte = 0; CurrentByte < Read_Memory_Params.BytesToRead; CurrentByte++)
	{
		bool IsOddByte = (CurrentByte & 0x01);

		if (IsOddByte && (V2Command == CMD_READ_FLASH_ISP))
		  Read_Memory_Params.ReadMemoryCommand |=  READ_WRITE_HIGH_BYTE_MASK;
		else
		  Read_Memory_Params.ReadMemoryCommand &= ~READ_WRITE_HIGH_BYTE_MASK;

		SPI_SendByte(Read_Memory_Params.ReadMemoryCommand);
		SPI_SendByte(CurrentAddress >> 8);
		SPI_SendByte(CurrentAddress & 0xFF);
		Endpoint_Write_Byte(SPI_ReceiveByte());
		
		/* Check if the endpoint bank is currently full */
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearIN();
			Endpoint_WaitUntilReady();
		}
		
		if ((IsOddByte && (V2Command == CMD_READ_FLASH_ISP)) || (V2Command == CMD_READ_EEPROM_ISP))
		  CurrentAddress++;
	}

	Endpoint_Write_Byte(STATUS_CMD_OK);

	bool IsEndpointFull = !(Endpoint_IsReadWriteAllowed());
	Endpoint_ClearIN();
	
	/* Ensure last packet is a short packet to terminate the transfer */
	if (IsEndpointFull)
	{
		Endpoint_WaitUntilReady();	
		Endpoint_ClearIN();
		Endpoint_WaitUntilReady();	
	}
}

/** Handler for the CMD_CHI_ERASE_ISP command, clearing the target's FLASH memory. */
void ISPProtocol_ChipErase(void)
{
	struct
	{
		uint8_t EraseDelayMS;
		uint8_t PollMethod;
		uint8_t EraseCommandBytes[4];
	} Erase_Chip_Params;
	
	Endpoint_Read_Stream_LE(&Erase_Chip_Params, sizeof(Erase_Chip_Params));
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	uint8_t ResponseStatus = STATUS_CMD_OK;
	
	for (uint8_t SByte = 0; SByte < sizeof(Erase_Chip_Params.EraseCommandBytes); SByte++)
	  SPI_SendByte(Erase_Chip_Params.EraseCommandBytes[SByte]);

	if (!(Erase_Chip_Params.PollMethod))
	  V2Protocol_DelayMS(Erase_Chip_Params.EraseDelayMS);
	else
	  ResponseStatus = ISPTarget_WaitWhileTargetBusy();
	  
	Endpoint_Write_Byte(CMD_CHIP_ERASE_ISP);
	Endpoint_Write_Byte(ResponseStatus);
	Endpoint_ClearIN();
}

/** Handler for the CMD_READ_FUSE_ISP, CMD_READ_LOCK_ISP, CMD_READ_SIGNATURE_ISP and CMD_READ_OSCCAL commands,
 *  reading the requested configuration byte from the device.
 *
 *  \param[in] V2Command  Issued V2 Protocol command byte from the host
 */
void ISPProtocol_ReadFuseLockSigOSCCAL(uint8_t V2Command)
{
	struct
	{
		uint8_t RetByte;
		uint8_t ReadCommandBytes[4];
	} Read_FuseLockSigOSCCAL_Params;
	
	Endpoint_Read_Stream_LE(&Read_FuseLockSigOSCCAL_Params, sizeof(Read_FuseLockSigOSCCAL_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	uint8_t ResponseBytes[4];
		
	for (uint8_t RByte = 0; RByte < sizeof(ResponseBytes); RByte++)
	  ResponseBytes[RByte] = SPI_TransferByte(Read_FuseLockSigOSCCAL_Params.ReadCommandBytes[RByte]);
		
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(ResponseBytes[Read_FuseLockSigOSCCAL_Params.RetByte - 1]);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

/** Handler for the CMD_WRITE_FUSE_ISP and CMD_WRITE_LOCK_ISP commands, writing the requested configuration
 *  byte to the device.
 *
 *  \param[in] V2Command  Issued V2 Protocol command byte from the host
 */
void ISPProtocol_WriteFuseLock(uint8_t V2Command)
{
	struct
	{
		uint8_t WriteCommandBytes[4];
	} Write_FuseLockSig_Params;
	
	Endpoint_Read_Stream_LE(&Write_FuseLockSig_Params, sizeof(Write_FuseLockSig_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	for (uint8_t SByte = 0; SByte < sizeof(Write_FuseLockSig_Params.WriteCommandBytes); SByte++)
	  SPI_SendByte(Write_FuseLockSig_Params.WriteCommandBytes[SByte]);
		
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

/** Handler for the CMD_SPI_MULTI command, writing and reading arbitrary SPI data to and from the attached device. */
void ISPProtocol_SPIMulti(void)
{
	struct
	{
		uint8_t TxBytes;
		uint8_t RxBytes;
		uint8_t RxStartAddr;
		uint8_t TxData[255];
	} SPI_Multi_Params;
	
	Endpoint_Read_Stream_LE(&SPI_Multi_Params, sizeof(SPI_Multi_Params) - sizeof(SPI_Multi_Params.TxData));
	Endpoint_Read_Stream_LE(&SPI_Multi_Params.TxData, SPI_Multi_Params.TxBytes);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	Endpoint_Write_Byte(CMD_SPI_MULTI);
	Endpoint_Write_Byte(STATUS_CMD_OK);

	uint8_t CurrTxPos = 0;
	uint8_t CurrRxPos = 0;

	/* Write out bytes to transmit until the start of the bytes to receive is met */
	while (CurrTxPos < SPI_Multi_Params.RxStartAddr)
	{
		if (CurrTxPos < SPI_Multi_Params.TxBytes)
		  SPI_SendByte(SPI_Multi_Params.TxData[CurrTxPos]);
		else
		  SPI_SendByte(0);
		
		CurrTxPos++;
	}

	/* Transmit remaining bytes with padding as needed, read in response bytes */
	while (CurrRxPos < SPI_Multi_Params.RxBytes)
	{
		if (CurrTxPos < SPI_Multi_Params.TxBytes)
		  Endpoint_Write_Byte(SPI_TransferByte(SPI_Multi_Params.TxData[CurrTxPos++]));
		else
		  Endpoint_Write_Byte(SPI_ReceiveByte());
		
		CurrRxPos++;
	}	
	
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}
