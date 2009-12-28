/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Functions to manage the physical dataflash media, including reading and writing of
 *  blocks of data. These functions are called by the SCSI layer when data must be stored
 *  or retrieved to/from the physical storage media. If a different media is used (such
 *  as a SD card or EEPROM), functions similar to these will need to be generated.
 */

#define  INCLUDE_FROM_DATAFLASHMANAGER_C
#include "DataflashManager.h"

/** Writes blocks (OS blocks, not Dataflash pages) to the storage medium, the board dataflash IC(s), from
 *  the pre-selected data OUT endpoint. This routine reads in OS sized blocks from the endpoint and writes
 *  them to the dataflash in Dataflash page sized blocks.
 *
 *  \param[in] BlockAddress  Data block starting address for the write sequence
 *  \param[in] TotalBlocks   Number of blocks of data to write
 */
void DataflashManager_WriteBlocks(const uint32_t BlockAddress, uint16_t TotalBlocks)
{
	uint16_t CurrDFPage          = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) / DATAFLASH_PAGE_SIZE);
	uint16_t CurrDFPageByte      = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) % DATAFLASH_PAGE_SIZE);
	uint8_t  CurrDFPageByteDiv16 = (CurrDFPageByte >> 4);
	bool     UsingSecondBuffer   = false;

	/* Select the correct starting Dataflash IC for the block requested */
	Dataflash_SelectChipFromPage(CurrDFPage);

#if (DATAFLASH_PAGE_SIZE > VIRTUAL_MEMORY_BLOCK_SIZE)
	/* Copy selected dataflash's current page contents to the dataflash buffer */
	Dataflash_SendByte(DF_CMD_MAINMEMTOBUFF1);
	Dataflash_SendAddressBytes(CurrDFPage, 0);
	Dataflash_WaitWhileBusy();
#endif

	/* Send the dataflash buffer write command */
	Dataflash_SendByte(DF_CMD_BUFF1WRITE);
	Dataflash_SendAddressBytes(0, CurrDFPageByte);

	/* Wait until endpoint is ready before continuing */
	if (Endpoint_WaitUntilReady())
	  return;
	
	while (TotalBlocks)
	{
		uint8_t BytesInBlockDiv16 = 0;
		
		/* Write an endpoint packet sized data block to the dataflash */
		while (BytesInBlockDiv16 < (VIRTUAL_MEMORY_BLOCK_SIZE >> 4))
		{
			/* Check if the endpoint is currently empty */
			if (!(Endpoint_IsReadWriteAllowed()))
			{
				/* Clear the current endpoint bank */
				Endpoint_ClearOUT();
				
				/* Wait until the host has sent another packet */
				if (Endpoint_WaitUntilReady())
				  return;
			}

			/* Check if end of dataflash page reached */
			if (CurrDFPageByteDiv16 == (DATAFLASH_PAGE_SIZE >> 4))
			{
				/* Write the dataflash buffer contents back to the dataflash page */
				Dataflash_WaitWhileBusy();
				Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_BUFF2TOMAINMEMWITHERASE : DF_CMD_BUFF1TOMAINMEMWITHERASE);
				Dataflash_SendAddressBytes(CurrDFPage, 0);

				/* Reset the dataflash buffer counter, increment the page counter */
				CurrDFPageByteDiv16 = 0;
				CurrDFPage++;

				/* Once all the dataflash ICs have had their first buffers filled, switch buffers to maintain throughput */
				if (Dataflash_GetSelectedChip() == DATAFLASH_CHIP_MASK(DATAFLASH_TOTALCHIPS))
				  UsingSecondBuffer = !(UsingSecondBuffer);

				/* Select the next dataflash chip based on the new dataflash page index */
				Dataflash_SelectChipFromPage(CurrDFPage);

#if (DATAFLASH_PAGE_SIZE > VIRTUAL_MEMORY_BLOCK_SIZE)
				/* If less than one dataflash page remaining, copy over the existing page to preserve trailing data */
				if ((TotalBlocks * (VIRTUAL_MEMORY_BLOCK_SIZE >> 4)) < (DATAFLASH_PAGE_SIZE >> 4))
				{
					/* Copy selected dataflash's current page contents to the dataflash buffer */
					Dataflash_WaitWhileBusy();
					Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_MAINMEMTOBUFF2 : DF_CMD_MAINMEMTOBUFF1);
					Dataflash_SendAddressBytes(CurrDFPage, 0);
					Dataflash_WaitWhileBusy();
				}
#endif

				/* Send the dataflash buffer write command */
				Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_BUFF2WRITE : DF_CMD_BUFF1WRITE);
				Dataflash_SendAddressBytes(0, 0);				
			}

			/* Write one 16-byte chunk of data to the dataflash */
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			Dataflash_SendByte(Endpoint_Read_Byte());
			
			/* Increment the dataflash page 16 byte block counter */
			CurrDFPageByteDiv16++;

			/* Increment the block 16 byte block counter */
			BytesInBlockDiv16++;

			/* Check if the current command is being aborted by the host */
			if (IsMassStoreReset)
			  return;			
		}
			
		/* Decrement the blocks remaining counter and reset the sub block counter */
		TotalBlocks--;
	}

	/* Write the dataflash buffer contents back to the dataflash page */
	Dataflash_WaitWhileBusy();
	Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_BUFF2TOMAINMEMWITHERASE : DF_CMD_BUFF1TOMAINMEMWITHERASE);
	Dataflash_SendAddressBytes(CurrDFPage, 0x00);
	Dataflash_WaitWhileBusy();

	/* If the endpoint is empty, clear it ready for the next packet from the host */
	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearOUT();

	/* Deselect all dataflash chips */
	Dataflash_DeselectChip();
}

/** Reads blocks (OS blocks, not Dataflash pages) from the storage medium, the board dataflash IC(s), into
 *  the pre-selected data IN endpoint. This routine reads in Dataflash page sized blocks from the Dataflash
 *  and writes them in OS sized blocks to the endpoint.
 *
 *  \param[in] BlockAddress  Data block starting address for the read sequence
 *  \param[in] TotalBlocks   Number of blocks of data to read
 */
void DataflashManager_ReadBlocks(const uint32_t BlockAddress, uint16_t TotalBlocks)
{
	uint16_t CurrDFPage          = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) / DATAFLASH_PAGE_SIZE);
	uint16_t CurrDFPageByte      = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) % DATAFLASH_PAGE_SIZE);
	uint8_t  CurrDFPageByteDiv16 = (CurrDFPageByte >> 4);

	/* Select the correct starting Dataflash IC for the block requested */
	Dataflash_SelectChipFromPage(CurrDFPage);

	/* Send the dataflash main memory page read command */
	Dataflash_SendByte(DF_CMD_MAINMEMPAGEREAD);
	Dataflash_SendAddressBytes(CurrDFPage, CurrDFPageByte);
	Dataflash_SendByte(0x00);
	Dataflash_SendByte(0x00);
	Dataflash_SendByte(0x00);
	Dataflash_SendByte(0x00);
	
	/* Wait until endpoint is ready before continuing */
	if (Endpoint_WaitUntilReady())
	  return;
	
	while (TotalBlocks)
	{
		uint8_t BytesInBlockDiv16 = 0;
		
		/* Write an endpoint packet sized data block to the dataflash */
		while (BytesInBlockDiv16 < (VIRTUAL_MEMORY_BLOCK_SIZE >> 4))
		{
			/* Check if the endpoint is currently full */
			if (!(Endpoint_IsReadWriteAllowed()))
			{
				/* Clear the endpoint bank to send its contents to the host */
				Endpoint_ClearIN();
				
				/* Wait until the endpoint is ready for more data */
				if (Endpoint_WaitUntilReady())
				  return;
			}
			
			/* Check if end of dataflash page reached */
			if (CurrDFPageByteDiv16 == (DATAFLASH_PAGE_SIZE >> 4))
			{
				/* Reset the dataflash buffer counter, increment the page counter */
				CurrDFPageByteDiv16 = 0;
				CurrDFPage++;

				/* Select the next dataflash chip based on the new dataflash page index */
				Dataflash_SelectChipFromPage(CurrDFPage);
				
				/* Send the dataflash main memory page read command */
				Dataflash_SendByte(DF_CMD_MAINMEMPAGEREAD);
				Dataflash_SendAddressBytes(CurrDFPage, 0);
				Dataflash_SendByte(0x00);
				Dataflash_SendByte(0x00);
				Dataflash_SendByte(0x00);
				Dataflash_SendByte(0x00);
			}	

			/* Read one 16-byte chunk of data from the dataflash */
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			Endpoint_Write_Byte(Dataflash_ReceiveByte());
			
			/* Increment the dataflash page 16 byte block counter */
			CurrDFPageByteDiv16++;
			
			/* Increment the block 16 byte block counter */
			BytesInBlockDiv16++;

			/* Check if the current command is being aborted by the host */
			if (IsMassStoreReset)
			  return;
		}
		
		/* Decrement the blocks remaining counter */
		TotalBlocks--;
	}
	
	/* If the endpoint is full, send its contents to the host */
	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearIN();

	/* Deselect all dataflash chips */
	Dataflash_DeselectChip();
}

/** Writes blocks (OS blocks, not Dataflash pages) to the storage medium, the board dataflash IC(s), from
 *  the a given RAM buffer. This routine reads in OS sized blocks from the buffer and writes them to the
 *  dataflash in Dataflash page sized blocks. This can be linked to FAT libraries to write files to the
 *  dataflash.
 *
 *  \param[in] BlockAddress  Data block starting address for the write sequence
 *  \param[in] TotalBlocks   Number of blocks of data to write
 *  \param[in] BufferPtr     Pointer to the data source RAM buffer
 */
void DataflashManager_WriteBlocks_RAM(const uint32_t BlockAddress, uint16_t TotalBlocks, uint8_t* BufferPtr)
{
	uint16_t CurrDFPage          = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) / DATAFLASH_PAGE_SIZE);
	uint16_t CurrDFPageByte      = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) % DATAFLASH_PAGE_SIZE);
	uint8_t  CurrDFPageByteDiv16 = (CurrDFPageByte >> 4);
	bool     UsingSecondBuffer   = false;

	/* Select the correct starting Dataflash IC for the block requested */
	Dataflash_SelectChipFromPage(CurrDFPage);

#if (DATAFLASH_PAGE_SIZE > VIRTUAL_MEMORY_BLOCK_SIZE)
	/* Copy selected dataflash's current page contents to the dataflash buffer */
	Dataflash_SendByte(DF_CMD_MAINMEMTOBUFF1);
	Dataflash_SendAddressBytes(CurrDFPage, 0);
	Dataflash_WaitWhileBusy();
#endif

	/* Send the dataflash buffer write command */
	Dataflash_SendByte(DF_CMD_BUFF1WRITE);
	Dataflash_SendAddressBytes(0, CurrDFPageByte);

	while (TotalBlocks)
	{
		uint8_t BytesInBlockDiv16 = 0;
		
		/* Write an endpoint packet sized data block to the dataflash */
		while (BytesInBlockDiv16 < (VIRTUAL_MEMORY_BLOCK_SIZE >> 4))
		{
			/* Check if end of dataflash page reached */
			if (CurrDFPageByteDiv16 == (DATAFLASH_PAGE_SIZE >> 4))
			{
				/* Write the dataflash buffer contents back to the dataflash page */
				Dataflash_WaitWhileBusy();
				Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_BUFF2TOMAINMEMWITHERASE : DF_CMD_BUFF1TOMAINMEMWITHERASE);
				Dataflash_SendAddressBytes(CurrDFPage, 0);

				/* Reset the dataflash buffer counter, increment the page counter */
				CurrDFPageByteDiv16 = 0;
				CurrDFPage++;

				/* Once all the dataflash ICs have had their first buffers filled, switch buffers to maintain throughput */
				if (Dataflash_GetSelectedChip() == DATAFLASH_CHIP_MASK(DATAFLASH_TOTALCHIPS))
				  UsingSecondBuffer = !(UsingSecondBuffer);

				/* Select the next dataflash chip based on the new dataflash page index */
				Dataflash_SelectChipFromPage(CurrDFPage);

#if (DATAFLASH_PAGE_SIZE > VIRTUAL_MEMORY_BLOCK_SIZE)
				/* If less than one dataflash page remaining, copy over the existing page to preserve trailing data */
				if ((TotalBlocks * (VIRTUAL_MEMORY_BLOCK_SIZE >> 4)) < (DATAFLASH_PAGE_SIZE >> 4))
				{
					/* Copy selected dataflash's current page contents to the dataflash buffer */
					Dataflash_WaitWhileBusy();
					Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_MAINMEMTOBUFF2 : DF_CMD_MAINMEMTOBUFF1);
					Dataflash_SendAddressBytes(CurrDFPage, 0);
					Dataflash_WaitWhileBusy();
				}
#endif

				/* Send the dataflash buffer write command */
				Dataflash_ToggleSelectedChipCS();
				Dataflash_SendByte(DF_CMD_BUFF1WRITE);
				Dataflash_SendAddressBytes(0, 0);
			}
			
			/* Write one 16-byte chunk of data to the dataflash */
			for (uint8_t ByteNum = 0; ByteNum < 16; ByteNum++)
			  Dataflash_SendByte(*(BufferPtr++));
			
			/* Increment the dataflash page 16 byte block counter */
			CurrDFPageByteDiv16++;

			/* Increment the block 16 byte block counter */
			BytesInBlockDiv16++;		
		}
			
		/* Decrement the blocks remaining counter and reset the sub block counter */
		TotalBlocks--;
	}

	/* Write the dataflash buffer contents back to the dataflash page */
	Dataflash_WaitWhileBusy();
	Dataflash_SendByte(UsingSecondBuffer ? DF_CMD_BUFF2TOMAINMEMWITHERASE : DF_CMD_BUFF1TOMAINMEMWITHERASE);
	Dataflash_SendAddressBytes(CurrDFPage, 0x00);
	Dataflash_WaitWhileBusy();

	/* Deselect all dataflash chips */
	Dataflash_DeselectChip();
}

/** Reads blocks (OS blocks, not Dataflash pages) from the storage medium, the board dataflash IC(s), into
 *  the a preallocated RAM buffer. This routine reads in Dataflash page sized blocks from the Dataflash
 *  and writes them in OS sized blocks to the given buffer. This can be linked to FAT libraries to read
 *  the files stored on the dataflash.
 *
 *  \param[in] BlockAddress  Data block starting address for the read sequence
 *  \param[in] TotalBlocks   Number of blocks of data to read
 *  \param[out] BufferPtr    Pointer to the data destination RAM buffer
 */
void DataflashManager_ReadBlocks_RAM(const uint32_t BlockAddress, uint16_t TotalBlocks, uint8_t* BufferPtr)
{
	uint16_t CurrDFPage          = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) / DATAFLASH_PAGE_SIZE);
	uint16_t CurrDFPageByte      = ((BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE) % DATAFLASH_PAGE_SIZE);
	uint8_t  CurrDFPageByteDiv16 = (CurrDFPageByte >> 4);

	/* Select the correct starting Dataflash IC for the block requested */
	Dataflash_SelectChipFromPage(CurrDFPage);

	/* Send the dataflash main memory page read command */
	Dataflash_SendByte(DF_CMD_MAINMEMPAGEREAD);
	Dataflash_SendAddressBytes(CurrDFPage, CurrDFPageByte);
	Dataflash_SendByte(0x00);
	Dataflash_SendByte(0x00);
	Dataflash_SendByte(0x00);
	Dataflash_SendByte(0x00);

	while (TotalBlocks)
	{
		uint8_t BytesInBlockDiv16 = 0;
		
		/* Write an endpoint packet sized data block to the dataflash */
		while (BytesInBlockDiv16 < (VIRTUAL_MEMORY_BLOCK_SIZE >> 4))
		{
			/* Check if end of dataflash page reached */
			if (CurrDFPageByteDiv16 == (DATAFLASH_PAGE_SIZE >> 4))
			{
				/* Reset the dataflash buffer counter, increment the page counter */
				CurrDFPageByteDiv16 = 0;
				CurrDFPage++;

				/* Select the next dataflash chip based on the new dataflash page index */
				Dataflash_SelectChipFromPage(CurrDFPage);
				
				/* Send the dataflash main memory page read command */
				Dataflash_SendByte(DF_CMD_MAINMEMPAGEREAD);
				Dataflash_SendAddressBytes(CurrDFPage, 0);
				Dataflash_SendByte(0x00);
				Dataflash_SendByte(0x00);
				Dataflash_SendByte(0x00);
				Dataflash_SendByte(0x00);
			}	

			/* Read one 16-byte chunk of data from the dataflash */
			for (uint8_t ByteNum = 0; ByteNum < 16; ByteNum++)
			  *(BufferPtr++) = Dataflash_ReceiveByte();
			
			/* Increment the dataflash page 16 byte block counter */
			CurrDFPageByteDiv16++;
			
			/* Increment the block 16 byte block counter */
			BytesInBlockDiv16++;
		}
		
		/* Decrement the blocks remaining counter */
		TotalBlocks--;
	}

	/* Deselect all dataflash chips */
	Dataflash_DeselectChip();
}

/** Disables the dataflash memory write protection bits on the board Dataflash ICs, if enabled. */
void DataflashManager_ResetDataflashProtections(void)
{
	/* Select first dataflash chip, send the read status register command */
	Dataflash_SelectChip(DATAFLASH_CHIP1);
	Dataflash_SendByte(DF_CMD_GETSTATUS);
	
	/* Check if sector protection is enabled */
	if (Dataflash_ReceiveByte() & DF_STATUS_SECTORPROTECTION_ON)
	{
		Dataflash_ToggleSelectedChipCS();

		/* Send the commands to disable sector protection */
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[0]);
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[1]);
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[2]);
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[3]);
	}
	
	/* Select second dataflash chip (if present on selected board), send read status register command */
	#if (DATAFLASH_TOTALCHIPS == 2)
	Dataflash_SelectChip(DATAFLASH_CHIP2);
	Dataflash_SendByte(DF_CMD_GETSTATUS);
	
	/* Check if sector protection is enabled */
	if (Dataflash_ReceiveByte() & DF_STATUS_SECTORPROTECTION_ON)
	{
		Dataflash_ToggleSelectedChipCS();

		/* Send the commands to disable sector protection */
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[0]);
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[1]);
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[2]);
		Dataflash_SendByte(DF_CMD_SECTORPROTECTIONOFF[3]);
	}
	#endif
	
	/* Deselect current dataflash chip */
	Dataflash_DeselectChip();
}

/** Performs a simple test on the attached Dataflash IC(s) to ensure that they are working.
 *
 *  \return Boolean true if all media chips are working, false otherwise
 */
bool DataflashManager_CheckDataflashOperation(void)
{
	uint8_t ReturnByte;

	/* Test first Dataflash IC is present and responding to commands */
	Dataflash_SelectChip(DATAFLASH_CHIP1);
	Dataflash_SendByte(DF_CMD_READMANUFACTURERDEVICEINFO);
	ReturnByte = Dataflash_ReceiveByte();
	Dataflash_DeselectChip();

	/* If returned data is invalid, fail the command */
	if (ReturnByte != DF_MANUFACTURER_ATMEL)
	  return false;

	#if (DATAFLASH_TOTALCHIPS == 2)
	/* Test second Dataflash IC is present and responding to commands */
	Dataflash_SelectChip(DATAFLASH_CHIP2);
	Dataflash_SendByte(DF_CMD_READMANUFACTURERDEVICEINFO);
	ReturnByte = Dataflash_ReceiveByte();
	Dataflash_DeselectChip();

	/* If returned data is invalid, fail the command */
	if (ReturnByte != DF_MANUFACTURER_ATMEL)
	  return false;
	#endif
	
	return true;
}
