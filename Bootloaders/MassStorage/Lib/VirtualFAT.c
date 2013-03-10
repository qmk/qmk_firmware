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

/** \file
 *
 *  Virtualized FAT12 filesystem implementation, to perform self-programming
 *  in response to read and write requests to the virtual filesystem by the
 *  host PC.
 */

#define  INCLUDE_FROM_VIRTUAL_FAT_C
#include "VirtualFAT.h"

/** FAT filesystem boot sector block, must be the first sector on the physical
 *  disk so that the host can identify the presence of a FAT filesystem. This
 *  block is truncated; normally a large bootstrap section is located near the
 *  end of the block for booting purposes however as this is not meant to be a
 *  bootable disk it is omitted for space reasons.
 *
 *  \note When returning the boot block to the host, the magic signature 0xAA55
 *        must be added to the very end of the block to identify it as a boot
 *        block.
 */
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
		.SectorsPerTrack         = (LUN_MEDIA_BLOCKS % 64),
		.Heads                   = (LUN_MEDIA_BLOCKS / 64),
		.HiddenSectors           = 0,
		.TotalSectors32          = 0,
		.PhysicalDriveNum        = 0,
		.ExtendedBootRecordSig   = 0x29,
		.VolumeSerialNumber      = 0x12345678,
		.VolumeLabel             = "LUFA BOOT  ",
		.FilesystemIdentifier    = "FAT12   ",
	};

/** FAT 8.3 style directory entry, for the virtual FLASH contents file. */
static FATDirectoryEntry_t FirmwareFileEntries[2] =
	{
		/* Root volume label entry; disk label is contained in the Filename and
		 * Extension fields (concantenated) with a special attribute flag - other
		 * fields are ignored. Should be the same as the label in the boot block.
		 */
		{
			.Filename               = "LUFA BOO",
			.Extension              = "T  ",
			.Attributes             = (1 << 3),
			.Reserved               = {0},
			.CreationTime           = 0,
			.CreationDate           = 0,
			.StartingCluster        = 0,
			.FileSizeBytes          = 0,
		},

		/* File entry for the virtual Firmware image. */
		{
			.Filename               = "FIRMWARE",
			.Extension              = "BIN",
			.Attributes             = 0,
			.Reserved               = {0},
			.CreationTime           = FAT_TIME(1, 1, 0),
			.CreationDate           = FAT_DATE(14, 2, 1989),
			.StartingCluster        = 2,
			.FileSizeBytes          = FIRMWARE_FILE_SIZE_BYTES,
		},
	};


/** Updates a FAT12 cluster entry in the FAT file table with the specified next
 *  chain index. If the cluster is the last in the file chain, the magic value
 *  0xFFF is used.
 *
 *  \note FAT data cluster indexes are offset by 2, so that cluster 2 is the
 *        first file data cluster on the disk. See the FAT specification.
 *
 *  \param[out]  FATTable    Pointer to the FAT12 allocation table
 *  \param[in]   Index       Index of the cluster entry to update
 *  \param[in]   ChainEntry  Next cluster index in the file chain
 */
static void UpdateFAT12ClusterEntry(uint8_t* const FATTable,
                                    const uint16_t Index,
                                    const uint16_t ChainEntry)
{
	/* Calculate the starting offset of the cluster entry in the FAT12 table */
	uint8_t FATOffset   = (Index + (Index >> 1));
	bool    UpperNibble = ((Index & 1) != 0);

	/* Check if the start of the entry is at an upper nibble of the byte, fill
	 * out FAT12 entry as required */
	if (UpperNibble)
	{
		FATTable[FATOffset]     = (FATTable[FATOffset] & 0x0F) | ((ChainEntry & 0x0F) << 4);
		FATTable[FATOffset + 1] = (ChainEntry >> 4);
	}
	else
	{
		FATTable[FATOffset]     = ChainEntry;
		FATTable[FATOffset + 1] = (FATTable[FATOffset] & 0xF0) | (ChainEntry >> 8);
	}
}

/** Writes a block of data to the virtual FAT filesystem, from the USB Mass
 *  Storage interface.
 *
 *  \param[in]  BlockNumber  Index of the block to write.
 */
static void WriteVirtualBlock(const uint16_t BlockNumber)
{
	uint8_t BlockBuffer[SECTOR_SIZE_BYTES];

	/* Buffer the entire block to be written from the host */
	Endpoint_Read_Stream_LE(BlockBuffer, sizeof(BlockBuffer), NULL);
	Endpoint_ClearOUT();

	if ((BlockNumber >= 4) && (BlockNumber < (4 + FILE_SECTORS(FIRMWARE_FILE_SIZE_BYTES))))
	{
		uint32_t WriteFlashAddress = (uint32_t)(BlockNumber - 4) * SECTOR_SIZE_BYTES;

		for (uint16_t i = 0; i < SECTOR_SIZE_BYTES; i += 2)
		{
			if ((WriteFlashAddress % SPM_PAGESIZE) == 0)
			{
				/* Erase the given FLASH page, ready to be programmed */
				boot_page_erase(WriteFlashAddress);
				boot_spm_busy_wait();
			}

			/* Write the next data word to the FLASH page */
			boot_page_fill(WriteFlashAddress, (BlockBuffer[i + 1] << 8) | BlockBuffer[i]);
			WriteFlashAddress += 2;

			if ((WriteFlashAddress % SPM_PAGESIZE) == 0)
			{
				/* Write the filled FLASH page to memory */
				boot_page_write(WriteFlashAddress - SPM_PAGESIZE);
				boot_spm_busy_wait();
			}
		}
	}
}

/** Reads a block of data from the virtual FAT filesystem, and sends it to the
 *  host via the USB Mass Storage interface.
 *
 *  \param[in]  BlockNumber  Index of the block to read.
 */
static void ReadVirtualBlock(const uint16_t BlockNumber)
{
	uint8_t BlockBuffer[SECTOR_SIZE_BYTES];
	memset(BlockBuffer, 0x00, sizeof(BlockBuffer));

	switch (BlockNumber)
	{
		case 0: /* Block 0: Boot block sector */
			memcpy(BlockBuffer, &BootBlock, sizeof(FATBootBlock_t));

			/* Add the magic signature to the end of the block */
			BlockBuffer[SECTOR_SIZE_BYTES - 2] = 0x55;
			BlockBuffer[SECTOR_SIZE_BYTES - 1] = 0xAA;
			break;

		case 1: /* Block 1: First FAT12 cluster chain copy */
		case 2: /* Block 2: Second FAT12 cluster chain copy */
			/* Cluster 0: Media type/Reserved */
			UpdateFAT12ClusterEntry(BlockBuffer, 0, 0xF00 | BootBlock.MediaDescriptor);

			/* Cluster 1: Reserved */
			UpdateFAT12ClusterEntry(BlockBuffer, 1, 0xFFF);

			/* Cluster 2 onwards: Cluster chain of FIRMWARE.BIN */
			for (uint16_t i = 0; i < FILE_CLUSTERS(FIRMWARE_FILE_SIZE_BYTES); i++)
			  UpdateFAT12ClusterEntry(BlockBuffer, i+2, i+3);

			/* Mark last cluster as end of file */
			UpdateFAT12ClusterEntry(BlockBuffer, FILE_CLUSTERS(FIRMWARE_FILE_SIZE_BYTES) + 1, 0xFFF);
			break;

		case 3: /* Block 3: Root file entries */
			memcpy(BlockBuffer, FirmwareFileEntries, sizeof(FirmwareFileEntries));
			break;

		default: /* Blocks 4 onwards: Data allocation section */
			if ((BlockNumber >= 4) && (BlockNumber < (4 + FILE_SECTORS(FIRMWARE_FILE_SIZE_BYTES))))
			{
				uint32_t ReadFlashAddress = (uint32_t)(BlockNumber - 4) * SECTOR_SIZE_BYTES;

				for (uint16_t i = 0; i < SECTOR_SIZE_BYTES; i++)
				  BlockBuffer[i] = pgm_read_byte_far(ReadFlashAddress++);
			}

			break;
	}

	/* Write the entire read block Buffer to the host */
	Endpoint_Write_Stream_LE(BlockBuffer, sizeof(BlockBuffer), NULL);
	Endpoint_ClearIN();
}

/** Writes a number of blocks to the virtual FAT file system, from the host
 *  PC via the USB Mass Storage interface.
 *
 *  \param[in] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state
 *  \param[in] BlockAddress  Data block starting address for the write sequence
 *  \param[in] TotalBlocks   Number of blocks of data to write
 */
void VirtualFAT_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                            const uint32_t BlockAddress,
                            uint16_t TotalBlocks)
{
	uint16_t CurrentBlock = (uint16_t)BlockAddress;

	/* Emulated FAT is performed per-block, pass each requested block index
	 * to the emulated FAT block write function */
	while (TotalBlocks--)
	  WriteVirtualBlock(CurrentBlock++);
}

/** Reads a number of blocks from the virtual FAT file system, and sends them
 *  to the host PC via the USB Mass Storage interface.
 *
 *  \param[in] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state
 *  \param[in] BlockAddress  Data block starting address for the read sequence
 *  \param[in] TotalBlocks   Number of blocks of data to read
 */
void VirtualFAT_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                           const uint32_t BlockAddress,
                           uint16_t TotalBlocks)
{
	uint16_t CurrentBlock = (uint16_t)BlockAddress;

	/* Emulated FAT is performed per-block, pass each requested block index
	 * to the emulated FAT block read function */
	while (TotalBlocks--)
	  ReadVirtualBlock(CurrentBlock++);
}

