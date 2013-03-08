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

#include "VirtualFAT.h"

static const FATBootBlock_t BootBlock =
	{
		.Bootstrap               = {0xEB, 0x3C, 0x90},
		.Description             = "mkdosfs",
		.BlockSize               = VIRTUAL_MEMORY_BLOCK_SIZE,
		.BlocksPerAllocationUnit = ALLOCATION_UNIT_BLOCKS,
		.ReservedBlocks          = 1,
		.FATCopies               = 2,
		.RootDirectoryEntries    = 512,
		.TotalBlocks16           = LUN_MEDIA_BLOCKS,
		.MediaDescriptor         = 0xF8,
		.BlocksPerFAT            = 1,
		.BlocksPerTrack          = 32,
		.Heads                   = 64,
		.HiddenBlocks            = 0,
		.TotalBlocks32           = 0,
		.PhysicalDriveNum        = 0,
		.ExtendedBootRecordSig   = 0x29,
		.VolumeSerialNumber      = 0x12345678,
		.VolumeLabel             = "LUFA BOOT  ",
		.FilesystemIdentifier    = "FAT16   ",
		.BootstrapProgram        = {0},
		.MagicSignature          = 0xAA55,
	};

static FATDirectoryEntry_t FirmwareFileEntry =
	{
		.Filename        = "Firmware",
		.Extension       = "bin",
		.Attributes      = 0,
		.Reserved        = {0},
		.CreationTime    = (1 << 11) | (1 << 5),
		.CreationDate    = (9 << 9)  | (2 << 5) | (14 << 0),
		.StartingCluster = 4,
		.FileSize        = (FLASHEND + 1UL),
	};

static void WriteBlock(uint16_t BlockNumber)
{
	uint8_t BlockBuffer[512];

	/* Wait until endpoint is ready before continuing */
	if (Endpoint_WaitUntilReady())
	  return;

	Endpoint_Read_Stream_LE(BlockBuffer, sizeof(BlockBuffer), NULL);
	Endpoint_ClearOUT();

	// TODO: Write to FLASH
}

static void ReadBlock(uint16_t BlockNumber)
{
	uint8_t BlockBuffer[512];
	memset(BlockBuffer, 0x00, sizeof(BlockBuffer));

	switch (BlockNumber)
	{
		case 0:
			memcpy(BlockBuffer, &BootBlock, sizeof(FATBootBlock_t));
			break;

		case 1:
		case 2:
			/* Cluster 0: Media type/Reserved */
			((uint16_t*)&BlockBuffer)[0] = 0xFF00 | BootBlock.MediaDescriptor;

			/* Cluster 1: Reserved */
			((uint16_t*)&BlockBuffer)[1] = 0xFFFF;

			/* Cluster 2: Reserved */
			((uint16_t*)&BlockBuffer)[2] = 0xFFFF;

			/* Cluster 3: FIRMWARE.BIN File Entry */
			((uint16_t*)&BlockBuffer)[3] = 0xFFFF;

			/* Cluster 4 onwards: Cluster chain of FIRMWARE.BIN */
			for (uint16_t i = 0; i < ((FLASHEND + 1) / (VIRTUAL_MEMORY_BLOCK_SIZE * ALLOCATION_UNIT_BLOCKS)); i++)
			{
				((uint16_t*)&BlockBuffer)[i + 4] = i + 5;
			}

			/* Mark last cluster as end of file */
			((uint16_t*)&BlockBuffer)[((FLASHEND + 1) / (VIRTUAL_MEMORY_BLOCK_SIZE * ALLOCATION_UNIT_BLOCKS)) + 4] = 0xFFFF;
			break;

		case 3:
			memcpy(BlockBuffer, &FirmwareFileEntry, sizeof(FATDirectoryEntry_t));
			break;

		default:
			break;
	}

	/* Wait until endpoint is ready before continuing */
	if (Endpoint_WaitUntilReady())
	  return;

	Endpoint_Write_Stream_LE(BlockBuffer, sizeof(BlockBuffer), NULL);
	Endpoint_ClearIN();
}

void VirtualFAT_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                            const uint32_t BlockAddress,
                            uint16_t TotalBlocks)
{
	uint16_t CurrentBlock = (uint16_t)BlockAddress;

	while (TotalBlocks--)
	  WriteBlock(CurrentBlock++);
}

void VirtualFAT_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                           const uint32_t BlockAddress,
                           uint16_t TotalBlocks)
{
	uint16_t CurrentBlock = (uint16_t)BlockAddress;

	while (TotalBlocks--)
	  ReadBlock(CurrentBlock++);
}

