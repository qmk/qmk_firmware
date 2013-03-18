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

#ifndef _VIRTUALFAT_H_
#define _VIRTUALFAT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "../BootloaderAPI.h"

	/* Macros: */
		/** Size of the virtual FIRMWARE.BIN file in bytes. */
		#define FIRMWARE_FILE_SIZE_BYTES  (FLASHEND - (FLASHEND - BOOT_START_ADDR) - AUX_BOOT_SECTION_SIZE)

		/** Number of sectors that comprise a single logical disk cluster. */
		#define SECTOR_PER_CLUSTER        4

		/** Size of a single logical sector on the disk. */
		#define SECTOR_SIZE_BYTES         512

		/** Size of a logical cluster on the disk, in bytes */
		#define CLUSTER_SIZE_BYTES        (SECTOR_PER_CLUSTER * SECTOR_SIZE_BYTES)

		/** Number of sectors required to store a given size in bytes.
		 *
		 *  \param[in] size  Size of the data that needs to be stored
		 *
		 *  \return Number of sectors required to store the given data on the disk.
		 */
		#define FILE_SECTORS(size)        ((size / SECTOR_SIZE_BYTES)  + ((size % SECTOR_SIZE_BYTES)  ? 1 : 0))

		/** Number of clusters required to store a given size in bytes.
		 *
		 *  \param[in] size  Size of the data that needs to be stored
		 *
		 *  \return Number of clusters required to store the given data on the disk.
		 */
		#define FILE_CLUSTERS(size)       ((size / CLUSTER_SIZE_BYTES) + ((size % CLUSTER_SIZE_BYTES) ? 1 : 0))

		/** Total number of logical sectors/blocks on the disk. */
		#define LUN_MEDIA_BLOCKS          (FILE_SECTORS(FIRMWARE_FILE_SIZE_BYTES) + 32)

		/** Converts a given time in HH:MM:SS format to a FAT filesystem time.
		 *
		 *  \note The minimum seconds resolution of FAT is 2, thus odd seconds
		 *        will be truncated to the previous integer multiple of 2 seconds.
		 *
		 *  \param[in] hh  Hours (0-23)
		 *  \param[in] mm  Minutes (0-59)
		 *  \param[in] ss  Seconds (0-59)
		 *
		 *  \return Given time encoded as a FAT filesystem timestamp
		 */
		#define FAT_TIME(hh, mm, ss)      ((hh << 11) | (mm << 5) | (ss >> 1))

		/** Converts a given date in DD/MM/YYYY format to a FAT filesystem date.
		 *
		 *  \param[in] dd    Days in the month (1-31)
		 *  \param[in] mm    Months in the year (1-12)
		 *  \param[in] yyyy  Year (1980 - 2107)
		 *
		 *  \return Given date encoded as a FAT filesystem datestamp
		 */
		#define FAT_DATE(dd, mm, yyyy)    (((yyyy - 1980) << 9) | (mm << 5) | (dd << 0))

	/* Type Definitions: */
		/** FAT boot block structure definition, used to identify the core
		 *  parameters of a FAT filesystem stored on a disk.
		 *
		 *  \note This definition is truncated to save space; the magic signature
		 *        0xAA55 must be appended to the very end of the block for it to
		 *        be detected by the host as a valid boot block.
		 */
		typedef struct
		{
			uint8_t  Bootstrap[3];
			uint8_t  Description[8];
			uint16_t SectorSize;
			uint8_t  SectorsPerCluster;
			uint16_t ReservedSectors;
			uint8_t  FATCopies;
			uint16_t RootDirectoryEntries;
			uint16_t TotalSectors16;
			uint8_t  MediaDescriptor;
			uint16_t SectorsPerFAT;
			uint16_t SectorsPerTrack;
			uint16_t Heads;
			uint32_t HiddenSectors;
			uint32_t TotalSectors32;
			uint16_t PhysicalDriveNum;
			uint8_t  ExtendedBootRecordSig;
			uint32_t VolumeSerialNumber;
			uint8_t  VolumeLabel[11];
			uint8_t  FilesystemIdentifier[8];
			/* uint8_t  BootstrapProgram[448]; */
			/* uint16_t MagicSignature; */
		} FATBootBlock_t;

		/** FAT legacy 8.3 style directory entry structure definition, used to
		 *  identify the files and folders of FAT filesystem stored on a disk.
		 */
		typedef struct
		{
			uint8_t  Filename[8];
			uint8_t  Extension[3];
			uint8_t  Attributes;
			uint8_t  Reserved[10];
			uint16_t CreationTime;
			uint16_t CreationDate;
			uint16_t StartingCluster;
			uint32_t FileSizeBytes;
		} FATDirectoryEntry_t;

	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_VIRTUAL_FAT_C)
			static void UpdateFAT12ClusterEntry(uint8_t* const FATTable,
			                                    const uint16_t Index,
			                                    const uint16_t ChainEntry) AUX_BOOT_SECTION;
			static void WriteVirtualBlock(const uint16_t BlockNumber) AUX_BOOT_SECTION;
			static void ReadVirtualBlock(const uint16_t BlockNumber) AUX_BOOT_SECTION;
		#endif

		void VirtualFAT_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
		                            const uint32_t BlockAddress,
		                            uint16_t TotalBlocks) AUX_BOOT_SECTION;

		void VirtualFAT_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
		                           const uint32_t BlockAddress,
		                           uint16_t TotalBlocks) AUX_BOOT_SECTION;
#endif
