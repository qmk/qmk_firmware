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

/** \ingroup Group_USBClassMS
 *  @{
 */

#ifndef _MS_CLASS_COMMON_H_
#define _MS_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Macros: */
		/** Mass Storage Class specific request to reset the Mass Storage interface, ready for the next command. */
		#define REQ_MassStorageReset       0xFF

		/** Mass Storage Class specific request to retrieve the total number of Logical Units (drives) in the SCSI device. */
		#define REQ_GetMaxLUN              0xFE
		
		/** Magic signature for a Command Block Wrapper used in the Mass Storage Bulk-Only transport protocol. */
		#define MS_CBW_SIGNATURE           0x43425355UL

		/** Magic signature for a Command Status Wrapper used in the Mass Storage Bulk-Only transport protocol. */
		#define MS_CSW_SIGNATURE           0x53425355UL
		
		/** Mask for a Command Block Wrapper's flags attribute to specify a command with data sent from host-to-device. */
		#define MS_COMMAND_DIR_DATA_OUT    (0 << 7)

		/** Mask for a Command Block Wrapper's flags attribute to specify a command with data sent from device-to-host. */
		#define MS_COMMAND_DIR_DATA_IN     (1 << 7)

	/* Type defines: */
		/** Type define for a Command Block Wrapper, used in the Mass Storage Bulk-Only Transport protocol. */
		typedef struct
		{
			uint32_t Signature; /**< Command block signature, must be CBW_SIGNATURE to indicate a valid Command Block */
			uint32_t Tag; /**< Unique command ID value, to associate a command block wrapper with its command status wrapper */
			uint32_t DataTransferLength; /** Length of the optional data portion of the issued command, in bytes */
			uint8_t  Flags; /**< Command block flags, indicating command data direction */
			uint8_t  LUN; /**< Logical Unit number this command is issued to */
			uint8_t  SCSICommandLength; /**< Length of the issued SCSI command within the SCSI command data array */
			uint8_t  SCSICommandData[16]; /**< Issued SCSI command in the Command Block */
		} CommandBlockWrapper_t;
		
		/** Type define for a Command Status Wrapper, used in the Mass Storage Bulk-Only Transport protocol. */
		typedef struct
		{
			uint32_t Signature; /**< Status block signature, must be CSW_SIGNATURE to indicate a valid Command Status */
			uint32_t Tag; /**< Unique command ID value, to associate a command block wrapper with its command status wrapper */
			uint32_t DataTransferResidue; /**< Number of bytes of data not processed in the SCSI command */
			uint8_t  Status; /**< Status code of the issued command - a value from the MassStorage_CommandStatusCodes_t enum */
		} CommandStatusWrapper_t;
		
	/* Enums: */
		/** Enum for the possible command status wrapper return status codes. */
		enum MassStorage_CommandStatusCodes_t
		{
			SCSI_Command_Pass = 0, /**< Command completed with no error */
			SCSI_Command_Fail = 1, /**< Command failed to complete - host may check the exact error via a SCSI REQUEST SENSE command */
			SCSI_Phase_Error  = 2  /**< Command failed due to being invalid in the current phase */
		};
		
	/* Type Defines: */
		/** Class state structure. An instance of this structure should be made for each Mass Storage interface
		 *  within the user application, and passed to each of the Mass Storage class driver functions as the
		 *  MSInterfaceInfo parameter. The contents of this structure should be set to their correct
		 *  values when used, or ommitted to force the library to use default values.
		 */
		typedef struct
		{
			uint8_t  InterfaceNumber; /**< Interface number of the Mass Storage interface within the device */

			uint8_t  DataINEndpointNumber; /**< Endpoint number of the Mass Storage interface's IN data endpoint */
			uint16_t DataINEndpointSize; /**< Size in bytes of the Mass Storage interface's IN data endpoint */

			uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the Mass Storage interface's OUT data endpoint */
			uint16_t DataOUTEndpointSize;  /**< Size in bytes of the Mass Storage interface's OUT data endpoint */

			uint8_t  TotalLUNs; /**< Total number of logical drives in the Mass Storage interface */

			CommandBlockWrapper_t  CommandBlock; /**< Mass Storage class command block structure, used internally
			                                      *   by the class driver
			                                      */
			CommandStatusWrapper_t CommandStatus; /**< Mass Storage class command status structure, used internally
			                                      *   by the class driver
			                                      */

			bool IsMassStoreReset; /**< Flag indicating that the host has requested that the Mass Storage interface be reset
			                        *   and that all current Mass Storage operations should immediately abort
									*/
		} USB_ClassInfo_MS_t;
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
