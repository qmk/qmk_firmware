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
 *  Header file for MassStoreCommands.c.
 */
 
#ifndef _MASS_STORE_COMMANDS_H_
#define _MASS_STORE_COMMANDS_H_

	/* Includes: */
		#include <avr/io.h>

		#include "MassStorageHost.h"
		#include "SCSI_Codes.h"

		#include <LUFA/Drivers/USB/USB.h>                    // USB Functionality

	/* Macros: */
		/** Class specific request to reset the Mass Storage interface of the attached device */
		#define REQ_MassStorageReset             0xFF

		/** Class specific request to retrieve the maximum Logical Unit Number (LUN) index of the attached device */
		#define REQ_GetMaxLUN                    0xFE

		/** Command Block Wrapper signature byte, for verification of valid CBW blocks */
		#define CBW_SIGNATURE                    0x43425355UL

		/** Command Statuc Wrapper signature byte, for verification of valid CSW blocks */
		#define CSW_SIGNATURE                    0x53425355UL
		
		/** Data direction mask for the Flags field of a CBW, indicating Host-to-Device transfer direction */
		#define COMMAND_DIRECTION_DATA_OUT       (0 << 7)

		/** Data direction mask for the Flags field of a CBW, indicating Device-to-Host transfer direction */
		#define COMMAND_DIRECTION_DATA_IN        (1 << 7)
		
		/** Timeout period between the issuing of a CBW to a device, and the reception of the first packet */
		#define COMMAND_DATA_TIMEOUT_MS          500

		/** Pipe number of the Mass Storage data IN pipe */
		#define MASS_STORE_DATA_IN_PIPE          1

		/** Pipe number of the Mass Storage data OUT pipe */
		#define MASS_STORE_DATA_OUT_PIPE         2

	/* Type defines: */
		/** Type define for a Mass Storage class Command Block Wrapper, used to wrap SCSI
		 *  commands for transport over the USB bulk endpoints to the device.
		 */
		typedef struct
		{
			struct
			{
				uint32_t Signature; /**< Command block signature, always equal to CBW_SIGNATURE */
				uint32_t Tag; /**< Current CBW tag, to positively associate a CBW with a CSW */
				uint32_t DataTransferLength; /**< Length of data to transfer, following the CBW */
				uint8_t  Flags; /**< Block flags, equal to one of the COMMAND_DIRECTION_DATA_* macros */
				uint8_t  LUN; /**< Logical Unit Number the CBW is addressed to in the device */
				uint8_t  SCSICommandLength; /**< Length of the SCSI command in the CBW */
			} Header;
			
			uint8_t SCSICommandData[16]; /**< SCSI command to issue to the device */
		} CommandBlockWrapper_t;
		
		/** Type define for a Mass Storage class Command Status Wrapper, used to wrap SCSI
		 *  responses for transport over the USB bulk endpoints from the device.
		 */
		typedef struct
		{
			uint32_t Signature; /**< Command status signature, always equal to CSW_SIGNATURE */
			uint32_t Tag; /**< Current CBW tag, to positively associate a CBW with a CSW */
			uint32_t DataTransferResidue; /**< Length of data not transfered */
			uint8_t  Status; /**< Command status, a value from the MassStorageHost_CommandStatusCodes_t enum */
		} CommandStatusWrapper_t;
		
		/** Type define for a SCSI Sense structure. Structures of this type are filled out by the
		 *  device via the MassStore_RequestSense() function, indicating the current sense data of the
		 *  device (giving explitic error codes for the last issued command). For details of the
		 *  structure contents, refer to the SCSI specifications.
		 */
		typedef struct
		{
			unsigned char ReponseCode         : 7;
			unsigned char Valid               : 1;
			
			uint8_t      SegmentNumber;
			
			unsigned char SenseKey            : 4;
			unsigned char _RESERVED1          : 1;
			unsigned char ILI                 : 1;
			unsigned char EOM                 : 1;
			unsigned char FileMark            : 1;
			
			uint8_t      Information[4];
			uint8_t      AdditionalLength;
			uint8_t      CmdSpecificInformation[4];
			uint8_t      AdditionalSenseCode;
			uint8_t      AdditionalSenseQualifier;
			uint8_t      FieldReplaceableUnitCode;
			uint8_t      SenseKeySpecific[3];
		} SCSI_Request_Sense_Response_t;

		/** SCSI capacity structure, to hold the total capacity of the device in both the number
		 *  of blocks in the current LUN, and the size of each block. This structure is filled by
		 *  the device when the MassStore_ReadCapacity() function is called.
		 */
		typedef struct
		{
			uint32_t Blocks; /**< Number of blocks in the addressed LUN of the device */
			uint32_t BlockSize; /**< Number of bytes in each block in the addressed LUN */
		} SCSI_Capacity_t;

	/* Enums: */
		/** CSW status return codes, indicating the overall status of the issued CBW */
		enum MassStorageHost_CommandStatusCodes_t
		{
			Command_Pass = 0, /**< Command completed successfully */
			Command_Fail = 1, /**< Command failed to complete successfully */
			Phase_Error  = 2 /**< Phase error while processing the issued command */
		};
		
	/* External Variables: */
		extern CommandStatusWrapper_t SCSICommandStatus;
		
	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_MASSSTORE_COMMANDS_C)
			static uint8_t MassStore_SendCommand(void);
			static uint8_t MassStore_WaitForDataReceived(void);
			static uint8_t MassStore_SendReceiveData(void* BufferPtr) ATTR_NON_NULL_PTR_ARG(1);
			static uint8_t MassStore_GetReturnedStatus(void);
		#endif
		
		uint8_t MassStore_ClearPipeStall(const uint8_t EndpointNum);
		uint8_t MassStore_MassStorageReset(void);
		uint8_t MassStore_GetMaxLUN(uint8_t* const MaxLUNIndex);
		uint8_t MassStore_RequestSense(const uint8_t LUNIndex, const SCSI_Request_Sense_Response_t* const SensePtr)
		                               ATTR_NON_NULL_PTR_ARG(2);
		uint8_t MassStore_ReadDeviceBlock(const uint8_t LUNIndex, const uint32_t BlockAddress,
		                                  const uint8_t Blocks, const uint16_t BlockSize, void* BufferPtr) ATTR_NON_NULL_PTR_ARG(5);
		uint8_t MassStore_WriteDeviceBlock(const uint8_t LUNIndex, const uint32_t BlockAddress,
                                           const uint8_t Blocks, const uint16_t BlockSize, void* BufferPtr) ATTR_NON_NULL_PTR_ARG(5);
		uint8_t MassStore_ReadCapacity(const uint8_t LUNIndex, SCSI_Capacity_t* const CapacityPtr)
		                               ATTR_NON_NULL_PTR_ARG(2);
		uint8_t MassStore_TestUnitReady(const uint8_t LUNIndex);
		uint8_t MassStore_PreventAllowMediumRemoval(const uint8_t LUNIndex, const bool PreventRemoval);

#endif
