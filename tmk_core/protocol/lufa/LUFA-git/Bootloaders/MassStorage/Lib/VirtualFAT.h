/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
		/** Size of the virtual FLASH.BIN file in bytes. */
		#define FLASH_FILE_SIZE_BYTES     (FLASHEND - (FLASHEND - BOOT_START_ADDR) - AUX_BOOT_SECTION_SIZE)

		/** Size of the virtual EEPROM.BIN file in bytes. */
		#define EEPROM_FILE_SIZE_BYTES    E2END

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
		#define LUN_MEDIA_BLOCKS          (FILE_SECTORS(FLASH_FILE_SIZE_BYTES) + FILE_SECTORS(EEPROM_FILE_SIZE_BYTES) + 32)

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

		/** Bit-rotates a given 8-bit value once to the right.
		 *
		 *  \param x  Value to rotate right once
		 *
		 *  \return Bit-rotated input value, rotated once to the right.
		 */
		#define _ROT8(x)                  ((((x) & 0xFE) >> 1) | (((x) & 1) ? 0x80 : 0x00))

		/** Computes the LFN entry checksum of a MSDOS 8.3 format file entry,
		 *  to associate a LFN entry with its short file entry.
		 *
		 *  \param n0  MSDOS Filename character 1
		 *  \param n1  MSDOS Filename character 2
		 *  \param n2  MSDOS Filename character 3
		 *  \param n3  MSDOS Filename character 4
		 *  \param n4  MSDOS Filename character 5
		 *  \param n5  MSDOS Filename character 6
		 *  \param n6  MSDOS Filename character 7
		 *  \param n7  MSDOS Filename character 8
		 *  \param e0  MSDOS Extension character 1
		 *  \param e1  MSDOS Extension character 2
		 *  \param e2  MSDOS Extension character 3
		 *
		 *  \return LFN checksum of the given MSDOS 8.3 filename.
		 */
		#define FAT_CHECKSUM(n0, n1, n2, n3, n4, n5, n6, n7, e0, e1, e2) \
		   (uint8_t)(_ROT8(_ROT8(_ROT8(_ROT8(_ROT8(_ROT8(_ROT8(_ROT8(_ROT8(_ROT8(n0)+n1)+n2)+n3)+n4)+n5)+n6)+n7)+e0)+e1)+e2)

		/** \name FAT Filesystem Flags */
		//@{
		/** FAT attribute flag to indicate a read-only file. */
		#define FAT_FLAG_READONLY         (1 << 0)

		/** FAT attribute flag to indicate a hidden file. */
		#define FAT_FLAG_HIDDEN           (1 << 1)

		/** FAT attribute flag to indicate a system file. */
		#define FAT_FLAG_SYSTEM           (1 << 2)

		/** FAT attribute flag to indicate a Volume name entry. */
		#define FAT_FLAG_VOLUME_NAME      (1 << 3)

		/** FAT attribute flag to indicate a directory entry. */
		#define FAT_FLAG_DIRECTORY        (1 << 4)

		/** FAT attribute flag to indicate a file ready for archiving. */
		#define FAT_FLAG_ARCHIVE          (1 << 5)

		/** FAT pseudo-attribute flag to indicate a Long File Name entry. */
		#define FAT_FLAG_LONG_FILE_NAME   0x0F

		/** Ordinal flag marker for FAT Long File Name entries to mark the last entry. */
		#define FAT_ORDINAL_LAST_ENTRY    (1 << 6)
		//@}

	/* Enums: */
		/** Enum for the Root FAT file entry indexes on the disk. This can be used
		 *  to retrieve the current contents of a known directory entry.
		 */
		enum
		{
			/** Volume ID directory entry, giving the name of the virtual disk. */
			DISK_FILE_ENTRY_VolumeID      = 0,
			/** Long File Name FAT file entry of the virtual FLASH.BIN image file. */
			DISK_FILE_ENTRY_FLASH_LFN     = 1,
			/** Legacy MSDOS FAT file entry of the virtual FLASH.BIN image file. */
			DISK_FILE_ENTRY_FLASH_MSDOS   = 2,
			/** Long File Name FAT file entry of the virtual EEPROM.BIN image file. */
			DISK_FILE_ENTRY_EEPROM_LFN    = 3,
			/** Legacy MSDOS FAT file entry of the virtual EEPROM.BIN image file. */
			DISK_FILE_ENTRY_EEPROM_MSDOS  = 4,
		};

		/** Enum for the physical disk blocks of the virtual disk. */
		enum
		{
			/** Boot sector disk block. */
			DISK_BLOCK_BootBlock          = 0,
			/** First copy of the FAT table block. */
			DISK_BLOCK_FATBlock1          = 1,
			/** Second copy of the FAT table block. */
			DISK_BLOCK_FATBlock2          = 2,
			/** Root file and directory entries block. */
			DISK_BLOCK_RootFilesBlock     = 3,
			/** Start block of the disk data section. */
			DISK_BLOCK_DataStartBlock     = 4,
		};

	/* Type Definitions: */
		/** FAT boot block structure definition, used to identify the core
		 *  parameters of a FAT file system stored on a disk.
		 *
		 *  \note This definition is truncated to save space; the magic signature
		 *        \c 0xAA55 must be appended to the very end of the block for it
		 *        to be detected by the host as a valid boot block.
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

		/** FAT directory entry structure, for the various kinds of File and
		 *  directory descriptors on a FAT disk.
		 */
		typedef union
		{
			/** VFAT Long File Name file entry. */
			struct
			{
				uint8_t  Ordinal;
				uint16_t Unicode1;
				uint16_t Unicode2;
				uint16_t Unicode3;
				uint16_t Unicode4;
				uint16_t Unicode5;
				uint8_t  Attribute;
				uint8_t  Reserved1;
				uint8_t  Checksum;
				uint16_t Unicode6;
				uint16_t Unicode7;
				uint16_t Unicode8;
				uint16_t Unicode9;
				uint16_t Unicode10;
				uint16_t Unicode11;
				uint16_t Reserved2;
				uint16_t Unicode12;
				uint16_t Unicode13;
			} VFAT_LongFileName;

			/** Legacy FAT MSDOS 8.3 file entry. */
			struct
			{
				uint8_t  Filename[8];
				uint8_t  Extension[3];
				uint8_t  Attributes;
				uint8_t  Reserved[10];
				uint16_t CreationTime;
				uint16_t CreationDate;
				uint16_t StartingCluster;
				uint32_t FileSizeBytes;
			} MSDOS_File;

			/** Legacy FAT MSDOS (sub-)directory entry. */
			struct
			{
				uint8_t  Name[11];
				uint8_t  Attributes;
				uint8_t  Reserved[10];
				uint16_t CreationTime;
				uint16_t CreationDate;
				uint16_t StartingCluster;
				uint32_t Reserved2;
			} MSDOS_Directory;
		} FATDirectoryEntry_t;

	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_VIRTUAL_FAT_C)
			static uint8_t ReadEEPROMByte(const uint8_t* const Address) ATTR_NO_INLINE;

			static void WriteEEPROMByte(uint8_t* const Address,
			                            const uint8_t Data) ATTR_NO_INLINE;

			static void UpdateFAT12ClusterEntry(uint8_t* const FATTable,
			                                    const uint16_t Index,
			                                    const uint16_t ChainEntry) AUX_BOOT_SECTION;

			static void UpdateFAT12ClusterChain(uint8_t* const FATTable,
			                                    const uint16_t StartIndex,
			                                    const uint8_t ChainLength) AUX_BOOT_SECTION;

			static void ReadWriteFLASHFileBlock(const uint16_t BlockNumber,
			                                    uint8_t* BlockBuffer,
			                                    const bool Read) AUX_BOOT_SECTION;

			static void ReadWriteEEPROMFileBlock(const uint16_t BlockNumber,
			                                     uint8_t* BlockBuffer,
			                                     const bool Read) AUX_BOOT_SECTION;
		#endif

		void VirtualFAT_WriteBlock(const uint16_t BlockNumber) AUX_BOOT_SECTION;
		void VirtualFAT_ReadBlock(const uint16_t BlockNumber) AUX_BOOT_SECTION;

#endif
