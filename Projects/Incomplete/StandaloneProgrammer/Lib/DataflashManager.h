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
 *  Header file for DataflashManager.c.
 */
 
#ifndef _DATAFLASH_MANAGER_H
#define _DATAFLASH_MANAGER_H

	/* Includes: */
		#include <avr/io.h>
		
		#include "StandaloneProgrammer.h"
		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/MassStorage.h>
		#include <LUFA/Drivers/Board/Dataflash.h>

	/* Preprocessor Checks: */
		#if (DATAFLASH_PAGE_SIZE % 16)
			#error Dataflash page size must be a multiple of 16 bytes.
		#endif

	/* Defines: */
		/** Total number of bytes of the storage medium, comprised of one or more dataflash ICs. */
		#define VIRTUAL_MEMORY_BYTES                ((uint32_t)DATAFLASH_PAGES * DATAFLASH_PAGE_SIZE * DATAFLASH_TOTALCHIPS)

		/** Block size of the device. This is kept at 512 to remain compatible with the OS despite the underlying
		 *  storage media (Dataflash) using a different native block size. Do not change this value.
		 */
		#define VIRTUAL_MEMORY_BLOCK_SIZE           512
		
		/** Total number of blocks of the virtual memory for reporting to the host as the device's total capacity. Do not
		 *  change this value; change VIRTUAL_MEMORY_BYTES instead to alter the media size.
		 */
		#define VIRTUAL_MEMORY_BLOCKS               (VIRTUAL_MEMORY_BYTES / VIRTUAL_MEMORY_BLOCK_SIZE)
		
	/* Function Prototypes: */
		#if defined(USB_CAN_BE_DEVICE)
			void DataflashManager_WriteBlocks(USB_ClassInfo_MS_Device_t* MSInterfaceInfo, const uint32_t BlockAddress,
											  uint16_t TotalBlocks);
			void DataflashManager_ReadBlocks(USB_ClassInfo_MS_Device_t* MSInterfaceInfo, const uint32_t BlockAddress,
											 uint16_t TotalBlocks);
			void DataflashManager_WriteBlocks_RAM(const uint32_t BlockAddress, uint16_t TotalBlocks,
												  uint8_t* BufferPtr) ATTR_NON_NULL_PTR_ARG(3);
			void DataflashManager_ReadBlocks_RAM(const uint32_t BlockAddress, uint16_t TotalBlocks,
												 uint8_t* BufferPtr) ATTR_NON_NULL_PTR_ARG(3);
			void DataflashManager_ResetDataflashProtections(void);
			bool DataflashManager_CheckDataflashOperation(void);
		#endif

#endif
