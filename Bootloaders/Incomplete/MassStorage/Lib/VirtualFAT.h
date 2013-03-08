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

	/* Macros: */
		#define VIRTUAL_MEMORY_BLOCK_SIZE 512
		#define ALLOCATION_UNIT_BLOCKS    4
		#define LUN_MEDIA_BLOCKS          ((FLASHEND + 1) / VIRTUAL_MEMORY_BLOCK_SIZE) + 16

	/* Type Definitions: */
		typedef struct
		{
			uint8_t  Bootstrap[3];
			uint8_t  Description[8];
			uint16_t BlockSize;
			uint8_t  BlocksPerAllocationUnit;
			uint16_t ReservedBlocks;
			uint8_t  FATCopies;
			uint16_t RootDirectoryEntries;
			uint16_t TotalBlocks16;
			uint8_t  MediaDescriptor;
			uint16_t BlocksPerFAT;
			uint16_t BlocksPerTrack;
			uint16_t Heads;
			uint32_t HiddenBlocks;
			uint32_t TotalBlocks32;
			uint16_t PhysicalDriveNum;
			uint8_t  ExtendedBootRecordSig;
			uint32_t VolumeSerialNumber;
			uint8_t  VolumeLabel[11];
			uint8_t  FilesystemIdentifier[8];
			uint8_t  BootstrapProgram[448];
			uint16_t MagicSignature;
		} FATBootBlock_t;

		typedef struct
		{
			uint8_t Filename[8];
			uint8_t Extension[3];
			uint8_t Attributes;
			uint8_t Reserved[10];
			uint16_t CreationTime;
			uint16_t CreationDate;
			uint16_t StartingCluster;
			uint32_t FileSize;
		} FATDirectoryEntry_t;

	/* Function Prototypes: */
		void VirtualFAT_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
		                            const uint32_t BlockAddress,
		                            uint16_t TotalBlocks);

		void VirtualFAT_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
		                           const uint32_t BlockAddress,
		                           uint16_t TotalBlocks);
#endif
