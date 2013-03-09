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
		.SectorSize              = SECTOR_SIZE_BYTES,
		.SectorsPerCluster       = SECTOR_PER_CLUSTER,
		.ReservedSectors         = 1,
		.FATCopies               = 2,
		.RootDirectoryEntries    = (SECTOR_SIZE_BYTES / sizeof(FATDirectoryEntry_t)),
		.TotalSectors16          = LUN_MEDIA_BLOCKS,
		.MediaDescriptor         = 0xF8,
		.SectorsPerFAT           = 1,
		.SectorsPerTrack         = 32,
		.Heads                   = 64,
		.HiddenSectors           = 0,
		.TotalSectors32          = 0,
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
		.Filename        = "FIRMWARE",
		.Extension       = "BIN",
		.Attributes      = 0,
		.Reserved        = {0},
		.CreationTime    = FAT_TIME(1, 1, 0),
		.CreationDate    = FAT_DATE(14, 2, 1989),
		.StartingCluster = 2,
		.FileSizeBytes   = 2049,
	};


static void WriteBlock(uint16_t BlockNumber)
{
	uint8_t BlockBuffer[512];

	/* Wait until endpoint is ready before continuing */
	if (Endpoint_WaitUntilReady())
	  return;

	Endpoint_Read_Stream_LE(BlockBuffer, sizeof(BlockBuffer), NULL);
	Endpoint_ClearOUT();

	printf("WRITE %d\r\n", BlockNumber);
	// TODO: Write to FLASH
}

static void ReadBlock(uint16_t BlockNumber)
{
	uint8_t BlockBuffer[512];
	memset(BlockBuffer, 0x00, sizeof(BlockBuffer));

	printf("READ %d", BlockNumber);

	switch (BlockNumber)
	{
		case 0:
			memcpy(BlockBuffer, &BootBlock, sizeof(FATBootBlock_t));
			printf(" <B>\r\n");
			break;

		case 1:
		case 2:
			printf(" <F>\r\n");

			/* Cluster 0: Media type/Reserved */
			((uint16_t*)&BlockBuffer)[0] = 0xFF00 | BootBlock.MediaDescriptor;

			/* Cluster 1: Reserved */
			((uint16_t*)&BlockBuffer)[1] = 0xFFFF;

			/* Cluster 2 onwards: Cluster chain of FIRMWARE.BIN */
			for (uint16_t i = 0; i < FILE_CLUSTERS(2049); i++)
			{
				((uint16_t*)&BlockBuffer)[i + 2] = i + 3;
			}

			/* Mark last cluster as end of file */
			((uint16_t*)&BlockBuffer)[FILE_CLUSTERS(2049) + 3] = 0xFFFF;
			break;

		case 3:
			printf("<R>\r\n");
			memcpy(BlockBuffer, &FirmwareFileEntry, sizeof(FATDirectoryEntry_t));
			break;

		default:
			if ((BlockNumber >= 4) && (BlockNumber < (4 + FILE_CLUSTERS(FIRMWARE_FILE_SIZE))))
			{
				printf("<D>\r\n");

				for (uint16_t i = 0; i < 512; i++)
				  BlockBuffer[i] = '0' + BlockNumber; //A' + (i % 26);
			}

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

	/* Emulated FAT is performed per-block, pass each requested block index
	 * to the emulation function */
	while (TotalBlocks--)
	  WriteBlock(CurrentBlock++);
}

void VirtualFAT_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                           const uint32_t BlockAddress,
                           uint16_t TotalBlocks)
{
	uint16_t CurrentBlock = (uint16_t)BlockAddress;

	/* Emulated FAT is performed per-block, pass each requested block index
	 * to the emulation function */
	while (TotalBlocks--)
	  ReadBlock(CurrentBlock++);
}

