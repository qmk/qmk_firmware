/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for MassStoreCommands.c.
 */

#ifndef _MASS_STORE_COMMANDS_H_
#define _MASS_STORE_COMMANDS_H_

	/* Includes: */
		#include <avr/io.h>

		#include "MassStorageHost.h"

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		/** Timeout period between the issuing of a CBW to a device, and the reception of the first packet. */
		#define COMMAND_DATA_TIMEOUT_MS             10000

		/** Additional error code for Mass Storage functions when a device returns a logical command failure. */
		#define MASS_STORE_SCSI_COMMAND_FAILED      0xC0

	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_MASSSTORE_COMMANDS_C)
			static uint8_t MassStore_SendCommand(MS_CommandBlockWrapper_t* const SCSICommandBlock,
			                                     void* BufferPtr);
			static uint8_t MassStore_WaitForDataReceived(void);
			static uint8_t MassStore_SendReceiveData(MS_CommandBlockWrapper_t* const SCSICommandBlock,
			                                         void* BufferPtr) ATTR_NON_NULL_PTR_ARG(1);
			static uint8_t MassStore_GetReturnedStatus(MS_CommandStatusWrapper_t* const SCSICommandStatus) ATTR_NON_NULL_PTR_ARG(1);
		#endif

		uint8_t MassStore_MassStorageReset(void);
		uint8_t MassStore_GetMaxLUN(uint8_t* const MaxLUNIndex);
		uint8_t MassStore_RequestSense(const uint8_t LUNIndex,
		                               SCSI_Request_Sense_Response_t* const SensePtr) ATTR_NON_NULL_PTR_ARG(2);
		uint8_t MassStore_Inquiry(const uint8_t LUNIndex,
		                          SCSI_Inquiry_Response_t* const InquiryPtr) ATTR_NON_NULL_PTR_ARG(2);
		uint8_t MassStore_ReadDeviceBlock(const uint8_t LUNIndex,
		                                  const uint32_t BlockAddress,
		                                  const uint8_t Blocks,
		                                  const uint16_t BlockSize,
		                                  void* BufferPtr) ATTR_NON_NULL_PTR_ARG(5);
		uint8_t MassStore_WriteDeviceBlock(const uint8_t LUNIndex,
		                                   const uint32_t BlockAddress,
                                           const uint8_t Blocks,
		                                   const uint16_t BlockSize,
		                                   void* BufferPtr) ATTR_NON_NULL_PTR_ARG(5);
		uint8_t MassStore_ReadCapacity(const uint8_t LUNIndex,
		                               SCSI_Capacity_t* const CapacityPtr) ATTR_NON_NULL_PTR_ARG(2);
		uint8_t MassStore_TestUnitReady(const uint8_t LUNIndex);
		uint8_t MassStore_PreventAllowMediumRemoval(const uint8_t LUNIndex,
		                                            const bool PreventRemoval);

#endif

